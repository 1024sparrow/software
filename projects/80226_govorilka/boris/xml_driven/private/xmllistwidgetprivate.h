#ifndef XMLLISTWIDGETPRIVATE_H
#define XMLLISTWIDGETPRIVATE_H

#include <QObject>
#include <QDomElement>

class QPushButton;
namespace boris
{

class XmlListWidget;
class XmlListWidgetPrivateModel;
class XmlListWidgetPrivate : public QObject
{
    Q_OBJECT
public:
    XmlListWidgetPrivate(XmlListWidget *master, const QString &title, const QStringList &headerLabels);
    void processXmlDataChanges(const QDomDocument &domdoc);
    void addRow(int id, const QStringList &rowData);
private slots:
    void onSelectionChanged(QString selectedIds);
    void onSelectNeeded(int selectedId);
    void onBnAddClicked();

public:
    QString m_mode;
    QString m_itemTag;
    XmlListWidgetPrivateModel *m_model;
    int m_maxId;
    QPushButton *bnAdd;
    QDomElement m_eBase;
private:
    XmlListWidget *master;
};

} // namespace boris

#endif // XMLLISTWIDGETPRIVATE_H
