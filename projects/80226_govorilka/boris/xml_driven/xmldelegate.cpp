#include "boris_h/xml_driven/xmldelegate.h"
#include "private/xmldelegateprivate.h"
#include "boris_h/xml_driven/xmlstring.h"
#include "boris_h/xml_driven/xmldelegateplugin.h"

#include <QVariant>

using namespace boris;

XmlDelegate::XmlDelegate(QObject *parent)
    :QItemDelegate(parent)
{
    d = new XmlDelegatePrivate(this);
}

void XmlDelegate::registerPlugin(const QString &tagName, XmlDelegatePlugin *plugin)
{
    d->registerPlugin(tagName, plugin);
}

QWidget * XmlDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    XmlDelegatePlugin *plugin = 0;
    QDomDocument domdoc;
    if (d->checkIfIsXmlByIndex(index, &plugin, &domdoc))
    {
        QWidget *retVal = 0;
        if (plugin)
            retVal = plugin->createEditor(parent, option, domdoc);
        return retVal;
    }
    return QItemDelegate::createEditor(parent, option, index);
}

void XmlDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
    XmlDelegatePlugin *plugin = 0;
    QDomDocument domdoc;
    if (d->checkIfIsXmlByIndex(index, &plugin, &domdoc))
    {
        if (plugin)
            plugin->setEditorData(editor, domdoc);
    }
    return QItemDelegate::setEditorData(editor, index);
}

void XmlDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
    XmlDelegatePlugin *plugin = 0;
    if (d->checkIfIsXmlByIndex(index, &plugin))
    {
        if (plugin)
        {
            QDomDocument domdoc = plugin->dataForModel(editor);
            XmlString xmlString(domdoc.toString());
            model->setData(index, QVariant::fromValue(xmlString), Qt::EditRole);
        }
    }
    return QItemDelegate::setEditorData(editor, index);
}

void XmlDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setAutoFillBackground(true);
    QItemDelegate::updateEditorGeometry(editor, option, index);
    return;
}
