#include "gameplay.h"

#include <QPainter>
#include <QDesktopWidget>
#include <QApplication>
#include <QImage>
//#include <../../../../boris/boris_h/debug.h>

Gameplay::Gameplay()
    :QWidget(0, Qt::SplashScreen)
    ,m_currentPix(0)
{
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    setFixedSize(10,10);
    //bDebug(QApplication::desktop()->height() - 64);
    move(QPoint(80, QApplication::desktop()->screenGeometry().height() - 10));
    startTimer(400);
}

void Gameplay::setLetter(const QList<int> &letter)
{
    QRgb color = 0xffffff;
    QRgb colorA = 0xffffff;
    QRgb colorB = 0x0080ff;
    QRgb colorC = 0xff0000;
    QRgb colorD = 0x0080ff;
    QImage image0(QSize(5,5), QImage::Format_RGB32);
    {
        image0.fill(Qt::black);
        image0.setPixel(2, 2, color);

    }
    QImage image1(QSize(5,5), QImage::Format_RGB32);
    {
        image1.fill(Qt::black);
        if (letter.value(0) & 4)
            image1.setPixel(2, 1, colorA);
        if (letter.value(1) & 4)
            image1.setPixel(3, 2, colorB);
        if (letter.value(2) & 4)
            image1.setPixel(2, 3, colorC);
        if (letter.value(3) & 4)
            image1.setPixel(1, 2, colorD);
    }
    QImage image2(QSize(5,5), QImage::Format_RGB32);
    {
        image2.fill(Qt::black);
        image0.setPixel(2, 2, color);
        if (letter.value(0) & 2)
            image2.setPixel(3, 0, colorA);
        if (letter.value(1) & 2)
            image2.setPixel(4, 3, colorB);
        if (letter.value(2) & 2)
            image2.setPixel(1, 4, colorC);
        if (letter.value(3) & 2)
            image2.setPixel(0, 1, colorD);

        if (letter.value(0) & 1)
            image2.setPixel(1, 0, colorA);
        if (letter.value(1) & 1)
            image2.setPixel(4, 1, colorB);
        if (letter.value(2) & 1)
            image2.setPixel(3, 4, colorC);
        if (letter.value(3) & 1)
            image2.setPixel(0, 3, colorD);
    }

    m_pix[0] = QPixmap::fromImage(image0);
    m_pix[1] = QPixmap::fromImage(image1);
    m_pix[2] = QPixmap::fromImage(image2);

    m_currentPix = 0;
    if (isVisible())
        repaint();
}

void Gameplay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, 10, 10, m_pix[m_currentPix], 0, 0, 5, 5);
//    painter.fillRect(rect(), Qt::red);
}

void Gameplay::timerEvent(QTimerEvent *)
{
    m_currentPix = ++m_currentPix % 3;
    if (isVisible())
        repaint();
}
