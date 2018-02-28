#include "boris_h/xml_driven/tablemodelcolumnsextension.h"
#include "boris_h/xml_driven/tablemodelcolumnsextensible.h"

#include <QModelIndex>

using namespace boris;

TableModelColumnsExtension::TableModelColumnsExtension(TableModelColumnsExtensible *master)
    :QObject(master), XmlSubscriber(master->m_xmlPublisher), m_enabled(true), m_master(master)
{
}

QString TableModelColumnsExtension::name() const
{
    return "base col ext";
}

bool TableModelColumnsExtension::enabled() const
{
    return m_enabled;
}

int TableModelColumnsExtension::columnCount() const
{
    return 3;
}

QVariant TableModelColumnsExtension::headerData(int index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index == 0)
            return "first";
        else if (index == 1)
            return "second";
        else if (index == 2)
            return "third";
    }
    return QVariant();
}

QVariant TableModelColumnsExtension::data(const QDomElement &e, int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        QString retVal = "tag(%1), id(%2), col(%3)";
        return retVal.arg(e.tagName()).arg(e.attribute("id")).arg(column);
    }
    if (role == Qt::CheckStateRole)
    {
        if (column == 1)
        {
            return e.hasAttribute("checked") ? Qt::Checked : Qt::Unchecked;
        }
    }
    return QVariant();
}

bool TableModelColumnsExtension::setData(const QDomElement &_e, int column, const QVariant &value, int role)
{
    if (column == 1)
    {
        QDomElement e = _e;
        if (value == Qt::Checked)
            e.setAttribute("checked", "1");
        else
            e.removeAttribute("checked");

        registerXmlDataChanges();
    }
    return false;
}

Qt::ItemFlags TableModelColumnsExtension::flags(const QDomElement &e, int column) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

void TableModelColumnsExtension::setEnabled(bool ifEnabled)
{
    m_enabled = ifEnabled;
    m_master->setColumnExtensionEnabled(this, ifEnabled);
}

void TableModelColumnsExtension::processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain)
{
    Q_UNUSED(domdoc);
    Q_UNUSED(ifResetXmlChain);
}
