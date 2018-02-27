#ifndef XMLUNDOREDO_H
#define XMLUNDOREDO_H

#include <boris_h/xml_driven/xmlsubscriber.h>

#include <QObject>
#include <QStringList>

class QAction;

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class LIBAPP_API XmlUndoRedo : public QObject, public boris::XmlSubscriber
{
    Q_OBJECT
public:
    XmlUndoRedo(boris::XmlPublisher *publisher, QObject *parent);
    void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain);
    QAction * undoAction() const;
    QAction * redoAction() const;
private slots:
    void onUndoActionTriggered();
    void onRedoActionTriggered();
private:
    void updateButtons();

private:
    QStringList m_history;
    int m_curPos;//in history
    QAction *actionUndo;
    QAction *actionRedo;
};

} // namespace boris

#endif // XMLUNDOREDO_H
