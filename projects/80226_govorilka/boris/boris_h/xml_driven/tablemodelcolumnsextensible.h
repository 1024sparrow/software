#ifndef TABLEMODELCOLUMNSEXTENSIBLE_H
#define TABLEMODELCOLUMNSEXTENSIBLE_H

#include <QAbstractTableModel>
#include <QDomDocument>
#include <QList>
#include <QPair>

#include "xmlpublisher.h"
#include "xmlsubscriber.h"

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{
class TableModelColumnsExtension;

class LIBAPP_API TableModelColumnsExtensible : public QAbstractTableModel, public XmlSubscriber
{
    Q_OBJECT
    friend class TableModelColumnsExtension;
public:
    TableModelColumnsExtensible(XmlPublisher *xmlPublisher, QObject *parent = 0);
    QDomDocument xmlDocument() const;
//    void setXmlDocument(const QDomDocument &domdoc);
    void addColumnExtension(TableModelColumnsExtension *ext);
    QList<QPair<QString, TableModelColumnsExtension *> > columnExtensions() const;

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
protected:
    virtual QMap<int, QDomElement> initializeElementsByRow(const QDomDocument &doc) const = 0;
    virtual QVariant vertHeaderData(int section, int role) const;
    void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain);
private slots:
    void onXmlChanged();
private:
    //for uage by TableModelColumnsExtension
    void setColumnExtensionEnabled(const TableModelColumnsExtension *ext, bool ifEnabled);

private:
    QList<TableModelColumnsExtension *> m_columnExtensions;
    QMap<int, QDomElement> m_elementsByRow;
    XmlPublisher *m_xmlPublisher;
};

} // namespace boris

#endif // TABLEMODELCOLUMNSEXTENSIBLE_H
