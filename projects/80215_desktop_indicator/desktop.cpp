#include "desktop.h"
#include <QPainter>

Desktop::Desktop(QWidget *parent)
    :QWidget(parent)
{
}

void Desktop::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);
    p.fillRect(this->rect(), Qt::black);
    //
}
