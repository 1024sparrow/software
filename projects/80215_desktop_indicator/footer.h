#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>
#include <QThread>

class QPaintEvent;
class QTimerEvent;
class ComandListener;
class Footer : public QWidget
{
    Q_OBJECT
public:
    Footer();
    static const int H;
public slots:
    void onSwitched(char id);
    void onModeSwicthedUp();
    void onModeSwicthedDown();

protected:
    void paintEvent(QPaintEvent *pe);
    void timerEvent(QTimerEvent *te);
private:
    void updatePixmaps(); // ��������� ������ �� ������������ ������� ������
    static const int MODE_COUNT;
    static const int POINT_SIZE;
    static const int POINT_PADDING;
    static const int animDuration;

private:
    bool fehPowered;
    char m_mode; // ������� ������ ������� ������
    char m_cur; // ������� ������� ����
    QPixmap m_pix[4];
    ComandListener *m_comandListener;
    //QThread m_comandListenerThread;
    //
    int m_currentPix;
    int animationTimerId;
};

#endif // FOOTER_H
