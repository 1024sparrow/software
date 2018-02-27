#ifndef XMLDELEGATEPLUGIN_H
#define XMLDELEGATEPLUGIN_H

#include <QObject>
#include <QWidget>
#include <QDomDocument>
#include <QStyleOptionViewItem>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class LIBAPP_API XmlDelegatePlugin
{
public:
    XmlDelegatePlugin();
    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QDomDocument &domdoc) const;
    virtual void setEditorData(QWidget * editor, const QDomDocument &domdoc) const;
    virtual QDomDocument dataForModel(QWidget * editor) const;
};

} // namespace boris

#endif // XMLDELEGATEPLUGIN_H
