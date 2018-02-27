#include "xmllistwidgetprivatemodel.h"

#include <QColor>
#include <QBrush>

using namespace boris;

XmlListWidgetPrivateModel::XmlListWidgetPrivateModel(const QStringList &headerLabels, QObject *parent)
    :QAbstractTableModel(parent), m_headerLabels(headerLabels)
{
}

void XmlListWidgetPrivateModel::setSelected(const QString &ids)
{
    if (m_flags.contains(QChar('s')))
    {
        m_selectedIds.clear();
        foreach (QString i, ids.split(QChar(';'), QString::SkipEmptyParts))
        {
            int candidate = i.trimmed().toInt();
            m_selectedIds.insert(candidate);
        }
        emit dataChanged(this->index(0, 0), this->index(m_ids.count() - 1, 0));
    }
}

void XmlListWidgetPrivateModel::clear()
{
    beginResetModel();
    m_ids.clear();
    m_data.clear();
    m_selectedIds.clear();
    endResetModel();
}

void XmlListWidgetPrivateModel::addRow(int id, const QStringList &rowData)
{
    beginResetModel();
    m_ids.append(id);
    m_data.append(rowData);
    endResetModel();
}

int XmlListWidgetPrivateModel::columnCount(const QModelIndex &parent) const
{
    int retVal= m_headerLabels.count();
    return retVal;
}

int XmlListWidgetPrivateModel::rowCount(const QModelIndex &parent) const
{
    return m_ids.count();
}

QVariant XmlListWidgetPrivateModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        int i = section;
        return m_headerLabels.value(i);
    }
    return QVariant();
}

QVariant XmlListWidgetPrivateModel::data(const QModelIndex &index, int role) const
{
    int id = m_ids.value(index.row(), -1);
    int column = index.column();
    if (m_flags.contains(QChar('s')))
    {
        if (column == 0)
        {
            if (role == Qt::CheckStateRole)
            {
                Qt::CheckState retVal = Qt::Unchecked;
                if (m_selectedIds.contains(id))
                    retVal = Qt::Checked;
                return retVal;
            }
        }
    }
    if (role == Qt::BackgroundRole)
    {
        if (m_selectedIds.contains(id))
            return QBrush(QColor(160,160,160), Qt::BDiagPattern);
    }
    if (role == Qt::DisplayRole)
    {
        return m_data.value(index.row()).value(column);
    }

    return QVariant();
}

bool XmlListWidgetPrivateModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        if (index.column() == 0)
        {
            int id = m_ids.value(index.row(), -1);
            if (value.toInt() == Qt::Unchecked)
                m_selectedIds.remove(id);
            else if (value.toInt() == Qt::Checked)
            {
                if (!m_flags.contains(QChar('m')))
                    m_selectedIds.clear();
                m_selectedIds.insert(id);
            }
            emit dataChanged(this->index(0, 0), this->index(m_ids.count() - 1, 0));
            QString str;
            foreach (int i, m_selectedIds)
            {
                if (!str.isEmpty())
                    str.append(QChar(';'));
                str.append(QString::number(i));
            }
            emit selectionChanged(str);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags XmlListWidgetPrivateModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags retVal;
    retVal |= Qt::ItemIsEnabled;
//    if (m_flags.contains(QChar('h')))
//        retVal |= Qt::ItemIsSelectable;
    if (m_flags.contains(QChar('s')))
    {
        if (index.column() == 0)
            retVal |= Qt::ItemIsUserCheckable;
    }
    return retVal;
}

void XmlListWidgetPrivateModel::setFlags(const QString &flags)
{
    beginResetModel();
    m_flags = flags;
    endResetModel();
}
