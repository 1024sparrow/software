#ifndef TABLEMODELCOLUMNSEXTENSION_H
#define TABLEMODELCOLUMNSEXTENSION_H

class QModelIndex;

#include "xmlsubscriber.h"

#include <QObject>
#include <QVariant>
#include <QDomDocument>
#include <QDomElement>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{
class TableModelColumnsExtensible;

class LIBAPP_API TableModelColumnsExtension : public QObject, public XmlSubscriber
{
    Q_OBJECT
public:
    TableModelColumnsExtension(TableModelColumnsExtensible *master);
    virtual QString name() const;
    bool enabled() const;

    virtual int columnCount() const;
    virtual QVariant headerData(int index, int role = Qt::DisplayRole) const;
    virtual QVariant data(const QDomElement &e, int column, int role = Qt::DisplayRole) const;
    virtual bool setData(const QDomElement &_e, int column, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QDomElement &e, int column) const;
public slots:
    void setEnabled(bool ifEnabled);
protected:
    void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain);
signals:
    void xmlChanged();

private:
    bool m_enabled;
    TableModelColumnsExtensible *m_master;
};

} // namespace boris

#endif // TABLEMODELCOLUMNSEXTENSION_H
