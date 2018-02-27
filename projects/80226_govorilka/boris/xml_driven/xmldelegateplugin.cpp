#include "boris_h/xml_driven/xmldelegateplugin.h"

#include <QLabel>//
#include <QTextEdit>

using namespace boris;

XmlDelegatePlugin::XmlDelegatePlugin()
{
}

QWidget * XmlDelegatePlugin::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QDomDocument &domdoc) const
{
//    return 0;
//    return new QLabel("fghjkljhgfghj", parent);
    QTextEdit *retVal = new QTextEdit(parent);
    retVal->setAcceptRichText(false);

    retVal->setMinimumSize(256,256);
    return retVal;
}

void XmlDelegatePlugin::setEditorData(QWidget *editor, const QDomDocument &domdoc) const
{
    QTextEdit *te = qobject_cast<QTextEdit *>(editor);
    if (te)
    {
        QString text = domdoc.toString();
        te->setPlainText(text);
    }
}

QDomDocument XmlDelegatePlugin::dataForModel(QWidget *editor) const
{
    QDomDocument retVal;
    QTextEdit *te = qobject_cast<QTextEdit *>(editor);
    if (te)
    {
        QString text = te->toPlainText();
        retVal.setContent(text);
    }
    return retVal;
}
