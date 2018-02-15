#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QPixmap>

class Gameplay : public QWidget
{
    Q_OBJECT
public:
    Gameplay();
public slots:
    void setLetter(const QList<int> &letter);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

private:
    QPixmap m_pix[3];
    int m_currentPix;
};

#endif // GAMEPLAY_H
