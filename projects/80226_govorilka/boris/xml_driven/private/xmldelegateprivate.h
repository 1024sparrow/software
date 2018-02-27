#ifndef XMLDELEGATEPRIVATE_H
#define XMLDELEGATEPRIVATE_H

namespace boris
{
    class XmlDelegatePlugin;
}
class QModelIndex;
class QDomDocument;

#include <QObject>
#include <QString>
#include <QMap>

namespace boris
{

class XmlDelegatePrivate : public QObject
{
    Q_OBJECT
public:
    XmlDelegatePrivate(QObject *parent = 0);
    ~XmlDelegatePrivate();
    bool checkIfIsXmlByIndex(const QModelIndex &index, XmlDelegatePlugin **pluginPointer = 0, QDomDocument *domdoc = 0) const;
    void registerPlugin(const QString &tagName, XmlDelegatePlugin *plugin);

private:
    QMap<QString, XmlDelegatePlugin *> m_plugins;
    static const int typeId;
};

} // namespace monitoringbase

#endif // XMLDELEGATEPRIVATE_H
