#include "footer.h"
#include <QPainter>
#include <QFont>

#define POINT_SIZE 2
const int Footer::H = 12;

Footer::Footer(QWidget *parent)
    :QWidget(parent), m_cur('~')
{
}

void Footer::onSwitched(char id)
{
    m_cur = id;
    if (isVisible())
        repaint();
}

void Footer::onModeSwicthed()
{
    //
}

void Footer::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);
    QFont font;
    font.setPixelSize(H - 2);
    p.setFont(font);
    p.fillRect(this->rect(), Qt::yellow);
    p.drawText(rect(), QString(m_cur));
}
