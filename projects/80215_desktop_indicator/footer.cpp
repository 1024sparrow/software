#include "footer.h"
#include <QPainter>
#include <QFont>

const int Footer::MODE_COUNT = 3;
const int Footer::POINT_SIZE = 2;
const int Footer::H = 12;
const int Footer::animDuration = 400;

Footer::Footer(QWidget *parent)
    :QWidget(parent), m_cur('~'), m_mode(1), animationTimerId(0)
{
    onSwitched('Q');
    animationTimerId = startTimer(animDuration);
}

void Footer::onSwitched(char id)
{
    m_cur = id;
    updatePixmaps();
    if (isVisible())
        repaint();
}

void Footer::onModeSwicthed()
{
    m_mode = ++m_mode % MODE_COUNT;
    updatePixmaps();
    if (isVisible())
        repaint();
}

void Footer::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(64,0,0));
    painter.drawPixmap(0, 0, m_pix[m_currentPix]);

    /*QPainter p(this);
    QFont font;
    font.setPixelSize(H - 2);
    p.setFont(font);
    p.fillRect(this->rect(), Qt::yellow);
    p.drawText(rect(), QString(m_cur));*/
}

void Footer::timerEvent(QTimerEvent *te)
{
    m_currentPix = ++m_currentPix % 4;
    if (isVisible())
        repaint();
    if (m_currentPix == 3)
        updatePixmaps();
}
