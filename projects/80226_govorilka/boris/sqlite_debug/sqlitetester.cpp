#include "sqlitetester.h"
#include "boris_h/btr.h"
#include "boris_h/debug.h"

#include <QBoxLayout>
#include <QLineEdit>
#include <QTableView>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QFileDialog>
#include <QTextStream>

using namespace boris;

int SqliteTester::dbSessionId = 0;

SqliteTester::SqliteTester(QWidget *parent)
    :QWidget(parent)
{
//    setMinimumSize(32,32);
//    {
//        QPalette pal = palette();
//        pal.setColor(QPalette::Window, Qt::green);
//        setPalette(pal);
//        setAutoFillBackground(true);
//    }

    model = new QStandardItemModel(this);

    actionExec = new QAction("execute", this);
    actionExec->setToolTip(btr("Выполнить введённый ниже в строке ввода SQL-запрос"));
    connect(actionExec, SIGNAL(triggered()), SLOT(onExecToggled()));
    QAction *actionExecBatch = new QAction("execute batch", this);
    actionExecBatch->setToolTip(btr("Выполнить пакетный файл (кодировка UTF-8)"));
    connect(actionExecBatch, SIGNAL(triggered()), SLOT(onExecBatchToggled()));
    actionOpenDb = new QAction("open DB", this);
    actionOpenDb->setToolTip(btr("Открыть базу данных\nпо умолчанию БД не открыта"));
    connect(actionOpenDb, SIGNAL(triggered()), SLOT(onOpenDbTriggered()));
    actionCloseDb = new QAction("close DB", this);
    actionCloseDb->setToolTip(btr("Закрыть базу данных"));
    connect(actionCloseDb, SIGNAL(triggered()), SLOT(onCloseDbTriggered()));

    leRequest = new QLineEdit(this);
    leRequest->setPlaceholderText(btr("Введите SQL-запрос здесь"));
    QTableView *tv = new QTableView(this);
    {
        tv->setFrameShape(QFrame::Box);
        tv->setModel(model);
    }
    QToolBar *toolbar = new QToolBar(this);
    {
        toolbar->addAction(actionOpenDb);
        toolbar->addAction(actionExec);
        toolbar->addAction(actionExecBatch);
        toolbar->addAction(actionCloseDb);
    }
    labelError = new QLabel(this);
    {
        labelError->setWordWrap(true);
    }

    QBoxLayout *lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->addWidget(toolbar);
    lay->addWidget(leRequest);
    lay->addWidget(tv);
    lay->addWidget(labelError);
}

void SqliteTester::setDbPath(const QString &path, bool forceOpen)
{
    model->clear();
    labelError->clear();

    if (db.isOpen())
        db.close();
    if (path.isEmpty())
        return;
    ++dbSessionId;
    db = QSqlDatabase::addDatabase("QSQLITE", QString("sqlite_debug_manual_queries_%1").arg(dbSessionId));
    db.setDatabaseName(path);
    if (forceOpen)
        onOpenDbTriggered();
}

void SqliteTester::onExecToggled()
{
    model->clear();
    labelError->clear();

    if (db.isOpen())
    {
        QString queryString = leRequest->text().simplified();
        if (queryString.isEmpty())
        {
            labelError->setText("Empty request!");
            return;
        }
        QSqlQuery qry(db);
        if (qry.exec(queryString))
        {
            int columnCount = qry.record().count();
            model->setColumnCount(columnCount);
            for (int col = 0 ; col < columnCount ; ++col)
            {
                QString headerTitle = qry.record().fieldName(col);
                model->setHeaderData(col, Qt::Horizontal, headerTitle);
            }
            int rowCounter = 0;
            while (qry.next())
            {
                QList<QStandardItem *> dataCandidate;
                for (int col = 0 ; col < columnCount ; ++col)
                {
                    QStandardItem *itemCandidate = new QStandardItem(qry.value(col).toString());
                    dataCandidate.append(itemCandidate);
                }
                model->appendRow(dataCandidate);
                ++rowCounter;
            }
        }
        else
        {
            labelError->setText(qry.lastError().text());
        }
    }
    else
    {
        labelError->setText("Database is not open!");
    }
}

void SqliteTester::onExecBatchToggled()
{
    model->clear();
    labelError->clear();

    if (db.isOpen())
    {
        QString filename = QFileDialog::getOpenFileName(this, "Select batch file");
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly))
        {
            QString requestsLine;
            QMap<int, int> rowsForRequests;
            {
                QTextStream str(&file);
                str.setCodec("utf8");
                int requestCounter = 0;
                int rowCounter = 1;
                while (!str.atEnd())
                {
                    QString line = str.readLine();
                    int commentPos = line.indexOf("--");
                    if (commentPos >= 0)
                        line.chop(line.count() - commentPos);
                    line = line.trimmed();
                    requestsLine.append(QString(" ") + line);
                    for (int i = 0, c = line.count(QChar(';')) ; i < c ; ++i)
                    {
                        rowsForRequests[requestCounter] = rowCounter;
                        ++requestCounter;
                    }
                    ++rowCounter;
                }
            }
            file.close();

            QSqlQuery qry(db);
            qry.exec("begin;");
            bool ok = true;
            QStringList requests;
            int rowCounter = 1;
            foreach (QString i, requestsLine.split(";"))
            {
                i = i.trimmed();
                if (!i.isEmpty())
                {
                    requests.append(i);
                }
                ++rowCounter;
            }
            const QString percTempl = "/" + QString::number(requests.count());
            labelError->setText("0" + percTempl);
            int counter = 0;
            foreach (QString sql, requests)
            {
                if (!qry.exec(sql))
                {
                    ok = false;
                    QString details = QString("db error (line %1): %2\nerror sql: %3")
                            .arg(rowsForRequests.value(counter, -1))
                            .arg(qry.lastError().text())
                            .arg(sql);
                    labelError->setText(details);
                    break;
                }
                labelError->setText(QString::number(counter) + percTempl);
                ++counter;
            }

            if (ok)
            {
                qry.exec("commit;");
                labelError->setText("ready");
            }
            else
            {
                qry.exec("rollback;");
            }
        }
        else
        {
            labelError->setText("Error: can not open the batch file.");
        }
    }
    else
    {
        labelError->setText("Database is not open!");
    }
}

void SqliteTester::onOpenDbTriggered()
{
    db.open();
    actionOpenDb->setEnabled(db.isOpen());
}

void SqliteTester::onCloseDbTriggered()
{
    db.close();
    actionCloseDb->setDisabled(db.isOpen());
}
