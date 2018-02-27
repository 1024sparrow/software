#include "display.h"
#include <QPainter>

Display::Display(boris::XmlPublisher *publisher, QWidget *parent)
    :QWidget(parent), boris::XmlSubscriber(publisher)
{

}

void Display::processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain)
{
    //
}

void Display::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::red);
}

