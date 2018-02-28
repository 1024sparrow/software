#ifndef SQLITEDEBUGWIDGET_H
#define SQLITEDEBUGWIDGET_H

class QStackedWidget;
class QTabBar;

#include <QWidget>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

namespace boris
{

class LIBAPP_API SqliteDebugWidget : public QWidget
{
    Q_OBJECT
public:
    SqliteDebugWidget(QWidget *parent = 0);
    void setDbPath(const QString &path);
    void setDbPath(const QList<QPair<QString, QString> > &path);//first - title to show, second - filepath

private:
    QStackedWidget *m_stackedWidget;
    QTabBar *m_tabbar;
};

} // namespace boris

#endif // SQLITEDEBUGWIDGET_H
