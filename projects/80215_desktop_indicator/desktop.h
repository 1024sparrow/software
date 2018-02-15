#ifndef DESKTOP_H
#define DESKTOP_H

#include <QWidget>

class QPaintEvent;
class Desktop : public QWidget
{
    Q_OBJECT
public:
    Desktop(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *pe);
};

#endif // DESKTOP_H
