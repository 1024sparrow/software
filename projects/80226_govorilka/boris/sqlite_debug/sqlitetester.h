#ifndef SQLITETESTER_H
#define SQLITETESTER_H

class QAction;
class QLineEdit;
class QLabel;
class QStandardItemModel;

#include <QWidget>
#include <QSqlDatabase>

namespace boris
{

class SqliteTester : public QWidget
{
    Q_OBJECT
public:
    SqliteTester(QWidget *parent = 0);
    void setDbPath(const QString &path, bool forceOpen = false);
private slots:
    void onExecToggled();
    void onExecBatchToggled();
    void onOpenDbTriggered();
    void onCloseDbTriggered();

private:
    QSqlDatabase db;
    QAction *actionExec;
    QAction *actionOpenDb;
    QAction *actionCloseDb;

    QLineEdit *leRequest;
    QLabel *labelError;
    QStandardItemModel *model;
    static int dbSessionId;
};

} // namespace boris

#endif // SQLITETESTER_H
