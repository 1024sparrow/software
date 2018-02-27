#include "sqlitetableswidget.h"
#include "boris_h/debug.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

using namespace boris;

int SqliteTablesWidget::dbSessionId = 0;

SqliteTablesWidget::SqliteTablesWidget(QWidget *parent)
    :QWidget(parent)
{
//    setMinimumSize(32,32);
//    {
//        QPalette pal = palette();
//        pal.setColor(QPalette::Window, Qt::red);
//        setPalette(pal);
//        setAutoFillBackground(true);
//    }

    ++dbSessionId;
    db = QSqlDatabase::addDatabase("QSQLITE", QString("sqlite_debug_tables_%1").arg(dbSessionId));
    model = new QStandardItemModel(this);

    cbTables = new QComboBox(this);
    {
//        cbTables->setFrame(false);
        connect(cbTables, SIGNAL(currentIndexChanged(int)), SLOT(onChangeCurTable(int)));
    }
    QTableView *tv = new QTableView(this);
    {
        tv->setFrameShape(QFrame::Box);
        tv->setModel(model);
    }
    QPushButton *bnUpdate = new QPushButton("update", this);
    {
        connect(bnUpdate, SIGNAL(clicked()), SLOT(onUpdateButtonClicked()));
    }
    labelError = new QLabel(this);

    QBoxLayout *lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->addWidget(cbTables);
    lay->addWidget(tv);
    lay->addWidget(bnUpdate);
    lay->addWidget(labelError);
}

void SqliteTablesWidget::setDbPath(const QString &path)
{
    cbTables->clear();

    m_dbPath = path;
}

void SqliteTablesWidget::onUpdateButtonClicked()
{
    cbTables->blockSignals(true);
    QString prevTableName = cbTables->itemData(cbTables->currentIndex()).toString();
    cbTables->clear();
    model->clear();
    m_cache.clear();
//    bDebug(m_dbPath);

    db.setDatabaseName(m_dbPath);
    db.open();
    if (!db.isOpen())
    {
        labelError->setText("database is not open.");
        return;
    }
    QSqlQuery qry(db);
    QStringList tableNames;
    if (!qry.exec("SELECT name FROM sqlite_master WHERE type='table';"))
    {
        labelError->setText(qry.lastError().text());
    }
    else
    {
        while (qry.next())
        {
            tableNames.append(qry.value(0).toString());
        }
    }

    foreach (QString tablename, tableNames)
    {
        if (!qry.exec("select * from " + tablename))
        {
            bDebug("epic fail:"<<qry.lastError().text());
            continue;
        }
        QList<QVariantList> dataCandidate;
        {
            QVariantList headerDataStrip;
            int columnCount = qry.record().count();
            for (int iH = 0 ; iH < columnCount ; ++iH)
            {
                headerDataStrip.append(qry.record().fieldName(iH));
            }
            dataCandidate.append(headerDataStrip);
            while (qry.next())
            {
                QVariantList candidate;
                for (int iD = 0 ; iD < columnCount ; ++iD)
                {
                    candidate.append(qry.value(iD));
                }
                dataCandidate.append(candidate);
            }
        }
        m_cache.insert(tablename, dataCandidate);
        cbTables->addItem(tablename, tablename);
    }
    db.close();
    //QString prevTableName = cbTables->itemData(cbTables->currentIndex()).toString();
    int indexToSetCurrent = 0;
    {
        int counter = 0;
        foreach (QString tablename, tableNames)
        {
            if (QString::compare(tablename, prevTableName, Qt::CaseSensitive) == 0)
            {
                indexToSetCurrent = counter;
                break;
            }
            ++counter;
        }
    }

    if (cbTables->count())
    {
        cbTables->setCurrentIndex(indexToSetCurrent);
        onChangeCurTable(indexToSetCurrent);
    }
    cbTables->blockSignals(false);
}

void SqliteTablesWidget::onChangeCurTable(int index)
{
    QString tablename = cbTables->itemData(index).toString();
    model->clear();
    QList<QVariantList> data = m_cache.value(tablename);
    if (data.isEmpty())
    {
        bDebug("oops");
        return;
    }
    int columnCount = data.first().count();
    model->setColumnCount(columnCount);
    {
        QStringList headerTitles;
        foreach (QVariant i, data.first())
        {
            headerTitles.append(i.toString());
        }
        model->setHorizontalHeaderLabels(headerTitles);
    }
    int rowCount = data.count() - 1;
    model->setRowCount(rowCount);
    for (int row = 0 ; row < rowCount ; ++row)
    {
        for (int col = 0 ; col < columnCount ; ++col)
        {
            QModelIndex index = model->index(row, col);
            model->setData(index, data.value(row + 1).value(col));
        }
    }
}
