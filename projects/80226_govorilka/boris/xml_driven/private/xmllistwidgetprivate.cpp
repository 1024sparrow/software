#include "xmllistwidgetprivate.h"
#include "boris_h/xml_driven/xmllistwidget.h"
#include "xmllistwidgetprivatemodel.h"
#include "boris_h/debug.h"
#include "boris_h/btr.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QTableView>
#include <QHeaderView>

using namespace boris;

XmlListWidgetPrivate::XmlListWidgetPrivate(XmlListWidget *master, const QString &title, const QStringList &headerLabels)
    :QObject(master), master(master)
    ,m_maxId(0), m_itemTag("<no_tag>")
{
    m_model = new XmlListWidgetPrivateModel(headerLabels, master);
    connect(m_model, SIGNAL(selectionChanged(QString)), SLOT(onSelectionChanged(QString)));

    QLabel *labelTitle = new QLabel(title, master);
    labelTitle->setWordWrap(true);

    bnAdd = new QPushButton(master);
    bnAdd->setIcon(QPixmap("://xml_driven/add.png"));
    bnAdd->setVisible(false);
    connect(bnAdd, SIGNAL(clicked()), SLOT(onBnAddClicked()));

    QWidget *header = new QWidget(master);
    {
        QBoxLayout *lay = new QHBoxLayout(header);
        lay->setMargin(0);
        lay->addWidget(labelTitle, 1);
        lay->addWidget(bnAdd, 0, Qt::AlignTop);
    }

    QTableView *tableView = new QTableView(master);
    {
        tableView->setModel(m_model);
        tableView->horizontalHeader()->setVisible(false);
        {
            foreach (QString i, headerLabels)
            {
                if (!i.isEmpty())
                {
                    tableView->horizontalHeader()->setVisible(true);
                    break;
                }
            }
        }
        tableView->verticalHeader()->setVisible(false);
        tableView->horizontalHeader()->setStretchLastSection(true);

        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    }

    QBoxLayout *lay = new QVBoxLayout(master);
    lay->setMargin(0);
    lay->addWidget(header);
    lay->addWidget(tableView);

    master->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void XmlListWidgetPrivate::processXmlDataChanges(const QDomDocument &domdoc)
{
    master->clean();
    m_eBase = master->baseElement(domdoc);
    if (m_eBase.isNull())
        return;
    m_mode.clear();
    {
        QStringList listOptions = m_eBase.attribute("list_options").split(QChar(':'), QString::KeepEmptyParts);
        if (!listOptions.isEmpty())
            m_mode = listOptions.takeFirst();
        if (listOptions.isEmpty())
            m_itemTag = "<no_tag>";
        else
            m_itemTag = listOptions.takeFirst();
    }
    bDebug(m_mode<<m_itemTag);

    bnAdd->setVisible(m_mode.contains(QChar('a')));
    m_model->setFlags(m_mode);
    QDomNodeList list = m_eBase.childNodes();
    QString selectedIds;
    for (int i = 0, c = list.count() ; i < c ; ++i)
    {
        QDomElement e = list.at(i).toElement();
        if (e.tagName() != m_itemTag)
            continue;
        int id = e.attribute("id").trimmed().toInt();
        if (e.attribute("marks").contains(QChar('s')))
        {
            if (!selectedIds.isEmpty())
                selectedIds.append(QChar(';'));
            selectedIds.append(QString::number(id));
        }
        QString name = e.attribute("name", btr("<ошибка>"));
        addRow(id, QStringList()<<name);
    }
    m_model->setSelected(selectedIds);
}

void XmlListWidgetPrivate::addRow(int id, const QStringList &rowData)
{
    m_model->addRow(id, rowData);
    if (id >= 0)
    {
        if (id > m_maxId)
            m_maxId = id;
    }
}

void XmlListWidgetPrivate::onSelectionChanged(QString selectedIds)
{
    QSet<int> ids;
    foreach (QString i, selectedIds.split(QChar(';'), QString::SkipEmptyParts))
    {
        int candidate = i.trimmed().toInt();
        ids.insert(candidate);
    }

    QDomNodeList list = m_eBase.childNodes();
    bool hasChanges = false;
    for (int i = 0, c = list.count() ; i < c ; ++i)
    {
        QDomElement e = list.at(i).toElement();
        QString marks = e.attribute("marks");
        int id = e.attribute("id", "-1").trimmed().toInt();
        if (ids.contains(id))
        {
            if (!marks.contains(QChar('s')))
            {
                marks.append(QChar('s'));
                e.setAttribute("marks", marks);
                hasChanges = true;
            }
        }
        else
        {
            if (marks.contains(QChar('s')))
            {
                marks.remove(QChar('s'));
                e.setAttribute("marks", marks);
                hasChanges = true;
            }
        }
    }
    if (hasChanges)
        master->registerXmlDataChanges();
}

void XmlListWidgetPrivate::onSelectNeeded(int selectedId)
{
    m_model->setSelected(QString::number(selectedId));
}

void XmlListWidgetPrivate::onBnAddClicked()
{
    if (m_itemTag.contains(QChar('<')))
    {
        bDebug("epic fail");
        return;
    }
    int candidateId = m_maxId + 1;
    QDomElement eRoot = master->baseElement(master->m_domdoc);
    QDomElement eItem = master->m_domdoc.createElement(m_itemTag);
    eItem.setAttribute("id", candidateId);
    QString itemName;
    if (master->processAddItem(candidateId, eItem, itemName))
    {
        eItem.setAttribute("name", itemName);
        m_maxId = candidateId;
        eRoot.appendChild(eItem);
    }
    master->registerXmlDataChanges();
}
