#include "boris_h/sqlitedebugwidget.h"
#include "sqlitetableswidget.h"
#include "sqlitetester.h"

#include <QBoxLayout>
#include <QToolBox>
#include <QStackedWidget>
#include <QTabBar>

using namespace boris;

SqliteDebugWidget::SqliteDebugWidget(QWidget *parent)
    :QWidget(parent)
{
//    QToolBox *toolbox = new QToolBox(this);
//    {
//        tablesWidget = new SqliteTablesWidget(toolbox);
//        tester = new SqliteTester(this);

//        toolbox->addItem(tester, "manual sql requests");
//        toolbox->addItem(tablesWidget, "data");
//        toolbox->setCurrentIndex(1);
//    }
//    toolbox->setStyleSheet(s);

    m_tabbar = new QTabBar(this);
    m_tabbar->setVisible(false);
    m_stackedWidget = new QStackedWidget(this);

    connect(m_tabbar, SIGNAL(currentChanged(int)), m_stackedWidget, SLOT(setCurrentIndex(int)));

    QBoxLayout *lay = new QVBoxLayout(this);
    lay->setMargin(0);
    //lay->addWidget(toolbox);
    lay->addWidget(m_tabbar);
    lay->addWidget(m_stackedWidget);

    setStyleSheet(
                " QToolBox::tab { "
                      "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                            "      stop: 0 green, stop: 0.4 green,"
                                                "  stop: 0.5 green, stop: 1.0 green);"
                     " border-radius: 5px;"
                    "  color: #aca;"
         "         }"
                " QToolBox::tab:selected { "
                "color: #ffc;"
                "}"

                "QToolButton { /* all types of tool button */"
                    " border: 2px solid #8f8f91;"
                    " border-radius: 6px;"
                    " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                     "  stop: 0 #f6f7fa, stop: 1 #dadbde);"
                "color: black;"
        "         }"
                );
}

void SqliteDebugWidget::setDbPath(const QString &path)
{
    //tester->setDbPath(path);
    //tablesWidget->setDbPath(path);
    setDbPath(QList<QPair<QString, QString> >()<<qMakePair(QString(), path));
}

void SqliteDebugWidget::setDbPath(const QList<QPair<QString, QString> > &path)
{
    for (int i = 0, c = m_stackedWidget->count() ; i < c ; ++i)
    {
        QWidget *w = m_stackedWidget->widget(i);
        m_stackedWidget->removeWidget(w);
        w->setParent(0);
        delete w;
    }
    m_tabbar->setVisible(path.count() > 1);
    QPair<QString, QString> i;
    foreach (i, path)
    {
        QToolBox *toolbox = new QToolBox(m_stackedWidget);
        {
            SqliteTablesWidget *tablesWidget = new SqliteTablesWidget(toolbox);
            SqliteTester *tester = new SqliteTester(this);

            toolbox->addItem(tester, "manual sql requests");
            toolbox->addItem(tablesWidget, "data");
            toolbox->setCurrentIndex(1);

            tester->setDbPath(i.second);
            tablesWidget->setDbPath(i.second);
        }
        m_tabbar->addTab(i.first);
        m_stackedWidget->addWidget(toolbox);
    }
}
