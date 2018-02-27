#include "boris_h/btr.h"
#include "boris_h/debug.h"
#include "boris_h/archiever/archiever.h"

#include <QTemporaryFile>

#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

using namespace boris;

QByteArray filetype_mark = "borisdb_0\n";

Archiever::Archiever(QObject *parent)
    :QObject(parent)
{
}

Archiever::~Archiever()
{
    clear();
}

QString Archiever::lastError() const
{
    return lastErrorPrivate;
}

bool Archiever::openFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        lastErrorPrivate = btr("Невозможно открыть файл:\n%1").arg(file.errorString());
        return false;
    }
    QByteArray data = file.readAll();
    file.close();
    if (!data.startsWith(filetype_mark))
    {
        lastErrorPrivate = btr("Неверный формат файла");
        return false;
    }
    clear();
    data.remove(0, filetype_mark.length());
    int mapSize = -1;
    {
        QBuffer buffer(&data);
        buffer.open(QIODevice::ReadOnly);
        QDataStream stream(&buffer);
        stream >> mapSize;
    }
    if (mapSize < 0)
    {
        lastErrorPrivate = "epic fail";
        return false;
    }
    data.remove(0, 4);
    QString mapString = data.left(mapSize);
    data.remove(0, mapSize);

    //quint32 totalDataLength = data.left(4).toUInt();//can be used
    data.remove(0, 4);

    QStringList mapStringList = mapString.split(";");
    int counter = 0;
    foreach (QString i, mapStringList)
    {
        QStringList pair = i.split(":");
        QString id = pair.first();
        int size = pair.last().toInt() - counter;
        bDebug(QString("File '%1' requires %2 bytes").arg(id).arg(size));
        addSubFile(id);
        QTemporaryFile *tempFile = tmpFilePaths.value(id, 0);
        if (size > 0)
        {
            const QByteArray &ba = data.left(size);
            QFile f(tempFile->fileName());
            f.open(QIODevice::WriteOnly);
            f.write(ba);
            data.remove(0, size);
            counter += size;
        }
    }
    emit subfilesTableChanged();
    return true;
}

bool Archiever::clear()
{
    QString errorCollector;
    bool ok = true;
    for (QMap<QString, QTemporaryFile *>::const_iterator it = tmpFilePaths.constBegin() ; it != tmpFilePaths.constEnd() ; ++it)
    {
//        bDebug(it.key()<<"**"<<it.value());
        QTemporaryFile *tempFile = it.value();
        if (tempFile->isOpen())
            tempFile->close();
        if (!tempFile->remove())
        {
            ok = false;
            if (!errorCollector.isEmpty())
                errorCollector.append("\";\"");
            errorCollector.append(QString("\"%1\"(\"%2\")").arg(it.key()).arg(tempFile->fileName()));
        }
        delete tempFile;
    }
    tmpFilePaths.clear();
    if (!ok)
        lastErrorPrivate = QString("unremovable temporary files leaved: %1").arg(errorCollector);
    emit subfilesTableChanged();
    return ok;
}

bool Archiever::saveFile(const QString &filePath)
{
    QByteArray data;
    data.append(filetype_mark);
    QString sectionMap;
    QByteArray body;
    int byteCounter = 0;
    for (QMap<QString, QTemporaryFile *>::const_iterator it = tmpFilePaths.constBegin() ; it != tmpFilePaths.constEnd() ; ++it)
    {
        QTemporaryFile *tempFile = it.value();
        bool isOpenInitially = tempFile->isOpen();
        if (!isOpenInitially)
        {
            if (!tempFile->open())
            {
                lastErrorPrivate = btr("Ошибка открытия файла, соответвующего разделу '%1':\n%2")
                        .arg(it.key())
                        .arg(tempFile->errorString());
                return false;
            }
        }
        if (!sectionMap.isEmpty())
            sectionMap.append(";");

        QFile f(tempFile->fileName());
        f.open(QIODevice::ReadOnly);

        QByteArray tempFileData = f.readAll();
        f.close();
        byteCounter += tempFileData.size();
        sectionMap.append(QString("%1:%2").arg(it.key()).arg(byteCounter));
        body.append(tempFileData);
        if (!isOpenInitially)
            tempFile->close();
    }
    QByteArray tmpBytearray;
    {
        QBuffer buffer(&tmpBytearray);
        buffer.open(QIODevice::WriteOnly);
        QDataStream stream(&buffer);
        stream << static_cast<quint32>(sectionMap.length());
    }
    data.append(tmpBytearray);
    data.append(sectionMap);

    tmpBytearray.clear();
    {
        QBuffer buffer(&tmpBytearray);
        buffer.open(QIODevice::WriteOnly);
        QDataStream stream(&buffer);
        stream << static_cast<quint32>(body.length());
    }
    data.append(tmpBytearray);
    data.append(body);

    QFile file(filePath);
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        lastErrorPrivate = btr("Ошибка открытия файла:")+file.errorString();
        return false;
    }
    file.write(data);
    file.close();
    return true;
}

bool Archiever::addSubFile(const QString &id, const QString &tmpFileTemplate)
{
    QString idSimplified = id.simplified();
    if (tmpFilePaths.contains(idSimplified))
    {
        lastErrorPrivate = btr("Раздел с указанным идентификатором уже существует. Задайте другой идентификатор.");
        return false;
    }
    //создаём временный файл и сохраняем его параметры
    QTemporaryFile *tempFile = 0;
    if (tmpFileTemplate.isEmpty())
        tempFile = new QTemporaryFile();
    else
        tempFile = new QTemporaryFile(tmpFileTemplate);
    if (tempFile->open())
    {
        tmpFilePaths.insert(idSimplified, tempFile);
        emit subfilesTableChanged();
        return true;
    }
    lastErrorPrivate = btr("Не удалось создать временный файл:\n") + tempFile->errorString();
    return false;
}

bool Archiever::removeSubFile(const QString &id)
{
    QString idSimplified = id.simplified();
    if (!tmpFilePaths.contains(idSimplified))
    {
        lastErrorPrivate = btr("Раздел с указанным идентификатором не существует.");
        return false;
    }
    QTemporaryFile *tempFile = tmpFilePaths.value(idSimplified);
    if (tempFile->isOpen())
        tempFile->close();
    if (!tempFile->remove())
    {
        lastErrorPrivate = tempFile->errorString();
        return false;
    }
    tmpFilePaths.remove(id);
    emit subfilesTableChanged();
    return true;
}

QStringList Archiever::ids() const
{
    return tmpFilePaths.keys();
}

QString Archiever::filepathForSection(const QString &id) const
{
    QString retVal;
    QTemporaryFile *file = tmpFilePaths.value(id, 0);
    if (file)
        retVal = file->fileName();
    return retVal;
}
