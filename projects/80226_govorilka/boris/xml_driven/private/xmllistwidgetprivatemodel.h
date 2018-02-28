#ifndef XMLLISTWIDGETPRIVATEMODEL_H
#define XMLLISTWIDGETPRIVATEMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QSet>
#include <QStringList>

namespace boris
{

class XmlListWidgetPrivateModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    XmlListWidgetPrivateModel(const QStringList &headerLabels, QObject *parent = 0);
    void setSelected(const QString &ids);
    void clear();
    void addRow(int id, const QStringList &rowData);

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setFlags(const QString &flags);
signals:
    void selectionChanged(QString ids);

private:
    QString m_flags;
    QStringList m_headerLabels;
    QList<int> m_ids;
    QList<QStringList> m_data;

    QSet<int> m_selectedIds;
};

} // namespace boris

#endif // XMLLISTWIDGETPRIVATEMODEL_H
