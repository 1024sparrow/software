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
    void initialize();

protected:
    void paintEvent(QPaintEvent *pe);
    void timerEvent(QTimerEvent *te);
private:
    void updatePixmaps(); // обновляем данные об используемых рабочих столах
    int desktopNum(char id, char mode);
    static const int MODE_COUNT;
    static const int POINT_SIZE;
    static const int POINT_PADDING;
    static const int animDuration;
    static QSet<int> pointsFixed;

private:
    bool fehPowered;
    char m_mode; // текущая группа рабочих столов
    char m_cur; // текущий рабочий стол
    QPixmap m_pix[4];
    ComandListener *m_comandListener;
    //QThread m_comandListenerThread;
    //
    int m_currentPix;
    int animationTimerId;
};

#endif // FOOTER_H
