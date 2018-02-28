#ifndef XMLDEBUGWIDGET_H
#define XMLDEBUGWIDGET_H

#include "xmlsubscriber.h"

class QTextEdit;

#include <QWidget>
#include <QDomDocument>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class LIBAPP_API XmlDebugWidget : public QWidget, public XmlSubscriber
{
    Q_OBJECT
public:
    XmlDebugWidget(XmlPublisher *xmlPublisher, QWidget *parent = 0);
protected:
    void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain);
private slots:
    void onBnApplyXmlClicked();

private:
    QTextEdit *te;
};

} // namespace boris

#endif // XMLDEBUGWIDGET_H
