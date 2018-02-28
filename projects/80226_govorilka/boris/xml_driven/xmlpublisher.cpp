#include "boris_h/xml_driven/xmlpublisher.h"
#include "boris_h/xml_driven/xmlsubscriber.h"

#include <QDomDocument>

using namespace boris;

XmlPublisher::XmlPublisher(QObject *parent)
    :QObject(parent)
{
}

XmlPublisher::~XmlPublisher()
{
    foreach (XmlSubscriber *i, subscribers)
    {
        i->m_publisher = 0;
    }
}

QDomDocument XmlPublisher::xmlDocument() const
{
    return m_domdoc;
}

void XmlPublisher::setXml(const QDomDocument &doc)
{
    m_domdoc = doc;
    emit xmlChanged();
    foreach (XmlSubscriber *i, subscribers)
    {
        i->m_domdoc = doc;
        i->processXmlDataChanges(doc, true);
    }
}

void XmlPublisher::registerSubscriber(XmlSubscriber *subscriber)
{
    subscriber->m_domdoc = m_domdoc;
    subscriber->processXmlDataChanges(m_domdoc, true);
    subscribers.insert(subscriber);
}

void XmlPublisher::unregisterSubscriber(XmlSubscriber *subscriber)
{
    subscribers.remove(subscriber);
}

void XmlPublisher::processXmlDataChanges(const XmlSubscriber *sender)
{
    m_domdoc = sender->m_domdoc;
    emit xmlChanged();

    foreach (XmlSubscriber *i, subscribers)
    {
        if (i == sender)
            continue;
        i->m_domdoc = m_domdoc;
        i->processXmlDataChanges(m_domdoc, false);
    }
}
