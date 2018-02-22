#include "footer.h"
#include <QPainter>
#include <QFont>
#include <QProcess>
#include <QApplication>
#include <QDesktopWidget>

const int Footer::MODE_COUNT = 3;
//const int Footer::MODE_COUNT = 1;//
const int Footer::POINT_SIZE = 4;
const int Footer::POINT_PADDING = 1;
const int Footer::H = Footer::POINT_SIZE * 3;
const int Footer::animDuration = 400;

Footer::Footer(QWidget *parent)
    :QWidget(0, Qt::SplashScreen), fehPowered(false), m_cur('~'), m_mode(1), animationTimerId(0)
{
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    QSize SZ = QApplication::desktop()->availableGeometry().size();
    setFixedSize(SZ.width(), Footer::H);
    //move(0, QApplication::desktop()->screenGeometry().height());// - Footer::H);
    move(QPoint(0, QApplication::desktop()->screenGeometry().height() - Footer::H));

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
    painter.fillRect(rect(), QColor(0,0,0));
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
    if (fehPowered)
    {
        QProcess *process = new QProcess(this);
        process->start(QString("feh --bg-fill /home/boris/.desktopIndicator_%1.png").arg(m_currentPix));
        process->waitForFinished(500);
    }
}
