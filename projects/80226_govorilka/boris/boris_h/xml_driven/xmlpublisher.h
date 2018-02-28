#ifndef XMLPUBLISHER_H
#define XMLPUBLISHER_H

class QDomDocument;

#include <QObject>
#include <QSet>
#include <QDomDocument>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class XmlSubscriber;
class LIBAPP_API XmlPublisher : public QObject
{
    Q_OBJECT
public:
    XmlPublisher(QObject *parent = 0);
    ~XmlPublisher();
    QDomDocument xmlDocument() const;
    void setXml(const QDomDocument &doc);
    void registerSubscriber(XmlSubscriber *subscriber);
    void unregisterSubscriber(XmlSubscriber *subscriber);
    void processXmlDataChanges(const XmlSubscriber *sender);
signals:
    void xmlChanged();

private:
    QDomDocument m_domdoc;
    QSet<XmlSubscriber *> subscribers;
};

} // namespace boris

#endif // XMLPUBLISHER_H
