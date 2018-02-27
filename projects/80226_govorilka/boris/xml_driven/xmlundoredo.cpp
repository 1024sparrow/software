#include "boris_h/xml_driven/xmlundoredo.h"
#include "boris_h/btr.h"
#include "boris_h/debug.h"

#include <QAction>
#include <QIcon>

using namespace boris;

XmlUndoRedo::XmlUndoRedo(boris::XmlPublisher *publisher, QObject *parent)
    :QObject(parent), boris::XmlSubscriber(publisher)
    ,m_curPos(-1)
{
    actionUndo = new QAction(QIcon(":xml_driven/undo.png"), btr("Отменить последнее действие"), this);
    {
        actionUndo->setEnabled(false);
        connect(actionUndo, SIGNAL(triggered()), SLOT(onUndoActionTriggered()));
    }
    actionRedo = new QAction(QIcon(":xml_driven/redo.png"), btr("Повторить отменённое действие"), this);
    {
        actionRedo->setEnabled(false);
        connect(actionRedo, SIGNAL(triggered()), SLOT(onRedoActionTriggered()));
    }
}

void XmlUndoRedo::processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain)
{
    Q_UNUSED(domdoc);
    if (ifResetXmlChain)
    {
        m_curPos = -1;
        m_history.clear();
    }
    if (m_curPos < 0)
        m_history.clear();
    else
    {
        for (int i = 1, c = m_history.count() - m_curPos ; i < c ; ++i)
        {
            m_history.removeLast();
        }
    }
    m_history.append(m_domdoc.toString());
    ++m_curPos;

    actionRedo->setEnabled(m_curPos < (m_history.count() - 1));
    actionUndo->setEnabled(m_curPos > 0);
}

QAction * XmlUndoRedo::undoAction() const
{
    return actionUndo;
}

QAction * XmlUndoRedo::redoAction() const
{
    return actionRedo;
}

void XmlUndoRedo::onUndoActionTriggered()
{
    if (m_curPos > 0)
        --m_curPos;
    m_domdoc.setContent(m_history.at(m_curPos));
    registerXmlDataChanges();
    updateButtons();
}

void XmlUndoRedo::onRedoActionTriggered()
{
    if (m_curPos < (m_history.count() - 1))
        ++m_curPos;
    m_domdoc.setContent(m_history.at(m_curPos));
    registerXmlDataChanges();
    updateButtons();
}

void XmlUndoRedo::updateButtons()
{
    actionRedo->setEnabled(m_curPos < (m_history.count() - 1));
    actionUndo->setEnabled(m_curPos > 0);
}
