#ifndef BORIS_DIALOG_H
#define BORIS_DIALOG_H

#include <QDialog>
#include <QString>

#undef LIBAPP_EXPORTS
#ifdef BORIS_MAKE_DLL
#   define LIBAPP_EXPORTS
#endif
#include <boris_h/dllexport.h>

class QFrame;

namespace boris
{

class LIBAPP_API Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(const QString &okButtonText, const QString &cancelByttonText = QString(), QWidget *parent = 0);
    void setContentWidget(QWidget *contentWidget);

private:
    QFrame *contentContainer;
};

}// namespace monitordocs

#endif // BORIS_DIALOG_H
