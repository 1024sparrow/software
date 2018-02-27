#include "boris_h/xml_driven/tablemodelcolumnsextensible.h"
#include "boris_h/xml_driven/tablemodelcolumnsextension.h"

using namespace boris;

TableModelColumnsExtensible::TableModelColumnsExtensible(XmlPublisher *xmlPublisher, QObject *parent)
    :QAbstractTableModel(parent), XmlSubscriber(xmlPublisher)
{
    m_xmlPublisher = new XmlPublisher(this);
    connect(m_xmlPublisher, SIGNAL(xmlChanged()), SLOT(onXmlChanged()));
}

QDomDocument TableModelColumnsExtensible::xmlDocument() const
{
    return m_xmlPublisher->xmlDocument();
}

//void TableModelColumnsExtensible::setXmlDocument(const QDomDocument &domdoc)
//{
//    m_xmlPublisher->setXml();
//}

void TableModelColumnsExtensible::addColumnExtension(TableModelColumnsExtension *ext)
{
    ext->setParent(this);

    beginResetModel();
    m_columnExtensions.append(ext);
    m_xmlPublisher->registerSubscriber(ext);
    endResetModel();
}

QList<QPair<QString, TableModelColumnsExtension *> > TableModelColumnsExtensible::columnExtensions() const
{
    QList<QPair<QString, TableModelColumnsExtension *> > retVal;
    foreach (TableModelColumnsExtension *i, m_columnExtensions)
    {
        QString extDescr = i->name();
        retVal.append(QPair<QString, TableModelColumnsExtension *>(extDescr, i));
    }

    return retVal;
}

int TableModelColumnsExtensible::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    int retVal = 0;

    foreach (TableModelColumnsExtension *i, m_columnExtensions)
    {
        if (i->enabled())
            retVal += i->columnCount();
    }

    return retVal;
}

int TableModelColumnsExtensible::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    int retVal = m_elementsByRow.count();
    return retVal;
}

QVariant TableModelColumnsExtensible::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        QVariant retVal;
        int columnCounter = 0;
        foreach (TableModelColumnsExtension *ext, m_columnExtensions)
        {
            if (!ext->enabled())
                continue;
            if (section < (columnCounter + ext->columnCount()))
            {
                retVal = ext->headerData(section - columnCounter, role);
                break;
            }
            columnCounter += ext->columnCount();
        }
        return retVal;
    }
    return vertHeaderData(section, role);
}

QVariant TableModelColumnsExtensible::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QDomElement elem = m_elementsByRow.value(index.row());

    int col = index.column();
    QVariant retVal;
    int columnCounter = 0;
    foreach (TableModelColumnsExtension *ext, m_columnExtensions)
    {
        if (!ext->enabled())
            continue;
        if (col < (columnCounter + ext->columnCount()))
        {
            retVal = ext->data(elem, col - columnCounter, role);
            break;
        }
        columnCounter += ext->columnCount();
    }
    return retVal;
}

bool TableModelColumnsExtensible::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    QDomElement elem = m_elementsByRow.value(index.row());

    int col = index.column();
    bool retVal = false;
    int columnCounter = 0;
    foreach (TableModelColumnsExtension *ext, m_columnExtensions)
    {
        if (!ext->enabled())
            continue;
        if (col < (columnCounter + ext->columnCount()))
        {
            retVal = ext->setData(elem, col - columnCounter, value, role);
            break;
        }
        columnCounter += ext->columnCount();
    }
    return retVal;
}

Qt::ItemFlags TableModelColumnsExtensible::flags(const QModelIndex &index) const
{
    Qt::ItemFlags retVal = Qt::NoItemFlags;
    if (!index.isValid())
        return retVal;
    QDomElement elem = m_elementsByRow.value(index.row());

    int col = index.column();
    int columnCounter = 0;
    foreach (TableModelColumnsExtension *ext, m_columnExtensions)
    {
        if (!ext->enabled())
            continue;
        if (col < (columnCounter + ext->columnCount()))
        {
            retVal = ext->flags(elem, col - columnCounter);
            break;
        }
        columnCounter += ext->columnCount();
    }

    return retVal;
}

//QMap<int, QDomElement> TableModelColumnsExtensible::initializeElementsByRow(const QDomDocument &doc) const
//{
//    QMap<int, QDomElement> retVal;

//    int rowCounter = 0;
//    QDomNodeList list = doc.elementsByTagName("TactTasks").at(0).childNodes();
//    for (int i = 0, c = list.count() ; i < c ; ++i)
//    {
//        QDomElement e = list.at(i).toElement();
//        retVal.insert(rowCounter, e);
//        ++rowCounter;
//    }

//    return retVal;
//}

QVariant TableModelColumnsExtensible::vertHeaderData(int section, int role) const
{
    return QVariant();
}

void TableModelColumnsExtensible::processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain)
{
    Q_UNUSED(ifResetXmlChain);
    beginResetModel();
    m_elementsByRow = initializeElementsByRow(domdoc);
    m_xmlPublisher->setXml(domdoc);
    endResetModel();
}

void TableModelColumnsExtensible::onXmlChanged()
{
    m_domdoc = m_xmlPublisher->xmlDocument();
    registerXmlDataChanges();
    emit dataChanged(QModelIndex(), QModelIndex());
}

void TableModelColumnsExtensible::setColumnExtensionEnabled(const TableModelColumnsExtension *ext, bool ifEnabled)
{
    Q_UNUSED(ifEnabled);//TODO: reregister/unregister "ext" as subscriber
    foreach (TableModelColumnsExtension *i, m_columnExtensions)
    {
        if (i == ext)
        {
            beginResetModel();
            endResetModel();
        }
    }
}
