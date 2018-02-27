#include "xmldelegateprivate.h"
#include "boris_h/xml_driven/xmlstring.h"
#include "boris_h/debug.h"

#include <QSet>
#include <QVariant>
#include <QModelIndex>
#include <QDomDocument>
#include <QDomElement>

using namespace boris;

const int XmlDelegatePrivate::typeId=qRegisterMetaType<XmlString>();

XmlDelegatePrivate::XmlDelegatePrivate(QObject *parent)
    :QObject(parent)
{
}

XmlDelegatePrivate::~XmlDelegatePrivate()
{
    QSet<XmlDelegatePlugin *> pluginsToDelete;
    for (QMap<QString, XmlDelegatePlugin *>::Iterator it = m_plugins.begin(); it != m_plugins.end() ; ++it)
    {
        pluginsToDelete.insert(it.value());
    }
    foreach (XmlDelegatePlugin *i, pluginsToDelete)
    {
        delete i;
    }
}

bool XmlDelegatePrivate::checkIfIsXmlByIndex(
        const QModelIndex &index, XmlDelegatePlugin **pluginPointer, QDomDocument *domdoc) const
{
    QVariant editData = index.data(Qt::EditRole);
    if (editData.type() != QVariant::UserType)
        return false;
    if (editData.userType() != typeId)
        return false;
    if (pluginPointer)
    {
        QDomDocument dd;
        dd.setContent(editData.value<XmlString>().text);
        QString tagName = dd.documentElement().tagName();
        if (tagName.isEmpty())
            *pluginPointer = 0;
        else
            *pluginPointer = m_plugins.value(tagName, 0);
        if (*pluginPointer)
        {
            if (domdoc)
            {
                *domdoc = dd;
            }
        }
        else
        {
            bDebug("unregistered tagName:"<<tagName);
        }
    }
    return true;
}

void XmlDelegatePrivate::registerPlugin(const QString &tagName, XmlDelegatePlugin *plugin)
{
    if (m_plugins.contains(tagName))
    {
        delete m_plugins[tagName];
        if (plugin == 0)
            m_plugins.remove(tagName);
    }
    if (plugin)
    {
        m_plugins.insert(tagName, plugin);
    }
}
