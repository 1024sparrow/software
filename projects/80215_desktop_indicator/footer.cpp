#include "footer.h"
#include "comandlistener.h"
#include <QPainter>
#include <QFont>
#include <QProcess>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

const int Footer::MODE_COUNT = 3;
//const int Footer::MODE_COUNT = 1;//
const int Footer::POINT_SIZE = 4;
const int Footer::POINT_PADDING = 1;
const int Footer::H = Footer::POINT_SIZE * 3;
const int Footer::animDuration = 400;

Footer::Footer()
    :QWidget(0, Qt::SplashScreen), fehPowered(false), m_cur('~'), m_mode(1), animationTimerId(0)
    ,m_currentPix(0)
{
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

    m_comandListener = new ComandListener(this);
    //m_comandListener->moveToThread(&m_comandListenerThread);

    QSize SZ = QApplication::desktop()->availableGeometry().size();
    setFixedSize(SZ.width(), Footer::H);
    //move(0, QApplication::desktop()->screenGeometry().height());// - Footer::H);
    move(QPoint(0, QApplication::desktop()->screenGeometry().height() - Footer::H));

    onSwitched('Q');
    animationTimerId = startTimer(animDuration);

    connect(m_comandListener, SIGNAL(sgnSwitch(char)), this, SLOT(onSwitched(char)));
    connect(m_comandListener, SIGNAL(sgnSwitchModeUp()), this, SLOT(onModeSwicthedUp()));
    connect(m_comandListener, SIGNAL(sgnSwitchModeDown()), this, SLOT(onModeSwicthedDown()));
    m_comandListener->start();
}

void Footer::onSwitched(char id)
{
    //qDebug()<<"desktop: "<<id;
    m_cur = id;
    updatePixmaps();
    if (isVisible())
        repaint();
}

void Footer::onModeSwicthedUp()
{
    m_mode = (m_mode + 1) % MODE_COUNT;
    m_currentPix = 2;
    updatePixmaps();
    if (isVisible())
        repaint();
}

void Footer::onModeSwicthedDown()
{
    m_mode = (m_mode + MODE_COUNT - 1) % MODE_COUNT;
    m_currentPix = 2;
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
