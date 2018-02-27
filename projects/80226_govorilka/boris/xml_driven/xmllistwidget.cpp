#include "boris_h/xml_driven/xmllistwidget.h"
#include "boris_h/debug.h"
#include "boris_h/btr.h"

#include "private/xmllistwidgetprivate.h"
#include "private/xmllistwidgetprivatemodel.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>

namespace boris
{

XmlListWidget::XmlListWidget(
        boris::XmlPublisher *xmlPublisher, const QString &title, const QStringList &headerLabels, QWidget *parent)
    :QWidget(parent)
    ,boris::XmlSubscriber(xmlPublisher)
    ,d(new XmlListWidgetPrivate(this, title, headerLabels))
{
}

void XmlListWidget::processXmlDataChanges(const QDomDocument &domdoc, bool ifResetXmlChain)
{
    Q_UNUSED(ifResetXmlChain);
    d->processXmlDataChanges(domdoc);
}

bool XmlListWidget::processAddItem(int itemId, QDomElement &item, QString &itemName)
{
    Q_UNUSED(itemId);
    Q_UNUSED(item);
    Q_UNUSED(itemName);
    return false;
}

QDomElement XmlListWidget::baseElement(const QDomDocument &domdoc) const
{
    return domdoc.documentElement();
}

void XmlListWidget::clean()
{
    d->m_model->clear();
    d->m_maxId = 0;
}

void XmlListWidget::addRow(int id, const QStringList &rowData)
{
    d->addRow(id, rowData);
}

} // namespace boris
