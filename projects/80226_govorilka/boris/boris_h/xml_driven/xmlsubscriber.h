#ifndef XMLSUBSCRIBER_H
#define XMLSUBSCRIBER_H

#include <QDomDocument>
#include <QObject>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class XmlPublisher;
class LIBAPP_API XmlSubscriber
{
public:
    XmlSubscriber(XmlPublisher *m_publisher);
    virtual ~XmlSubscriber();
    //Данные изменены извне. Возможно, это как-то надо отобразить(обработать).
    virtual void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain) = 0;
protected:
    //В данном классе данные изменились. Оповестить всех подписчиков об изменении данных.
    void registerXmlDataChanges();

protected:
    QDomDocument m_domdoc;
private:
    XmlPublisher *m_publisher;
friend class XmlPublisher;
};

} // namespace boris

#endif // XMLSUBSCRIBER_H
