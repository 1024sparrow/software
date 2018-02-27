#ifndef BORIS_ARCHIEVER_ARCHIEVER_H
#define BORIS_ARCHIEVER_ARCHIEVER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

class QTemporaryFile;

namespace boris
{

class LIBAPP_API Archiever : public QObject
{
    Q_OBJECT
public:
    Archiever(QObject *parent = 0);
    virtual ~Archiever();
    QString lastError() const;

    bool openFile(const QString &filePath);
    bool clear();
    bool saveFile(const QString &filePath);

    bool addSubFile(const QString &id, const QString &tmpFileTemplate = QString());
    bool removeSubFile(const QString &id);
    QStringList ids() const;
    QString filepathForSection(const QString &id) const;
signals:
    void subfilesTableChanged();

private:
    QString lastErrorPrivate;
    QMap<QString, QTemporaryFile *> tmpFilePaths;
};

} // namespace boris

#endif // BORIS_ARCHIEVER_ARCHIEVER_H
