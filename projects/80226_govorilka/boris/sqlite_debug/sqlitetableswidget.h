#ifndef SQLITETABLESWIDGET_H
#define SQLITETABLESWIDGET_H

class QComboBox;
class QStandardItemModel;
class QLabel;

#include <QWidget>
#include <QSqlDatabase>
#include <QMap>
#include <QList>
#include <QVariantList>

namespace boris
{

class SqliteTablesWidget : public QWidget
{
    Q_OBJECT
public:
    SqliteTablesWidget(QWidget *parent = 0);
    void setDbPath(const QString &path);
private slots:
    void onUpdateButtonClicked();
    void onChangeCurTable(int index);

private:
    QComboBox *cbTables;
    QString m_dbPath;
    QStandardItemModel *model;
    QLabel *labelError;
    QSqlDatabase db;
    QMap<QString, QList<QVariantList> > m_cache;
    static int dbSessionId;
};

} // namespace boris

#endif // SQLITETABLESWIDGET_H
