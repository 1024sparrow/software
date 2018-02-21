#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>

class QPaintEvent;
class QTimerEvent;
class Footer : public QWidget
{
    Q_OBJECT
public:
    Footer(QWidget *parent = 0);
    static const int H;
public slots:
    void onSwitched(char id);
    void onModeSwicthed();

protected:
    void paintEvent(QPaintEvent *pe);
    void timerEvent(QTimerEvent *te);
private:
    void updatePixmaps(); // обновляем данные об используемых рабочих столах
    static const int MODE_COUNT;
    static const int POINT_SIZE;
    static const int POINT_PADDING;
    static const int animDuration;

private:
    bool fehPowered;
    char m_mode; // текущая группа рабочих столов
    char m_cur; // текущий рабочий стол
    QPixmap m_pix[4];
    //
    int m_currentPix;
    int animationTimerId;
};

#endif // FOOTER_H
