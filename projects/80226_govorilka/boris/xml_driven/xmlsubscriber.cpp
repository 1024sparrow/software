#include "boris_h/xml_driven/xmlsubscriber.h"
#include "boris_h/xml_driven/xmlpublisher.h"

using namespace boris;

XmlSubscriber::XmlSubscriber(XmlPublisher *publisher)
    :m_publisher(publisher)
{
//    m_publisher->registerSubscriber(this);//boris commented
}

XmlSubscriber::~XmlSubscriber()
{
    if (m_publisher)
        m_publisher->unregisterSubscriber(this);
}

void XmlSubscriber::registerXmlDataChanges()
{
    if (m_publisher)
        m_publisher->processXmlDataChanges(this);
}
