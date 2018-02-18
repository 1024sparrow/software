#include "window.h"
#include "desktop.h"
#include "footer.h"
#include "tester.h"

#include <QPainter>
#include <QDesktopWidget>
#include <QBoxLayout>

Window::Window()
    :QWidget(0)
{
    QSize SZ = QDesktopWidget().availableGeometry().size();
    QWidget *wDesktop = new Desktop(this);
    wDesktop->setFixedSize(SZ.width(), SZ.height() - Footer::H);
    Footer *wFooter = new Footer(this);
    wFooter->setFixedSize(SZ.width(), Footer::H);
    wFooter->move(0, SZ.height() - Footer::H);

    //QWidget *tester = new Tester(wFooter, 0);
}

void Window::paintEvent(QPaintEvent *pe)
{
    //QPainter p(this);
    //p.fillRect(this->rect(), Qt::yellow);
    //
}
