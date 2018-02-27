#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <boris_h/xml_driven/xmlsubscriber.h>

class QPaintEvent;
class Display : public QWidget, public boris::XmlSubscriber
{
public:
    Display(boris::XmlPublisher *publisher, QWidget *parent);
    void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain);
    void paintEvent(QPaintEvent *);
};

#endif // DISPLAY_H
