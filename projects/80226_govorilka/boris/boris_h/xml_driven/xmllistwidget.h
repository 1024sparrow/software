#ifndef XMLLISTWIDGET_H
#define XMLLISTWIDGET_H

class QModelIndex;
class QPushButton;
#include <QWidget>
#include <QAbstractTableModel>
#include <QList>
#include <QVariantList>
#include <QStringList>
#include <QSet>

#include <boris_h/xml_driven/xmlsubscriber.h>

namespace boris
{
class XmlListWidgetPrivate;
class LIBAPP_API XmlListWidget : public QWidget, public boris::XmlSubscriber
{
    Q_OBJECT
public:
    /*
     * mode - flags
     * s - selectable (add checkbox to each line in table);
     * a - addable (button "add" appeared)
     * h - enable highlighting - read only selecting (into "marks" write 'h' instead of 's')
     *  - not implemented
     */
    XmlListWidget(boris::XmlPublisher *xmlPublisher, const QString &title,
                const QStringList &headerLabels, QWidget *parent = 0);
    void processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain);
    virtual bool processAddItem(int itemId, QDomElement &item, QString &itemName);
    virtual QDomElement baseElement(const QDomDocument &domdoc) const;
    void clean();
signals:
    void switchedToViewMode();//flag 'h'. Selected not highlighted.
    void switchedToEditMode();//flag 'h'. Selected the same as highlighted.
protected:
    void addRow(int id, const QStringList &rowData);

private:
    XmlListWidgetPrivate *d;
friend class XmlListWidgetPrivate;
};

} // namespace boris

#endif // XMLLISTWIDGET_H
