#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPaintEvent;
class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
protected:
    void paintEvent(QPaintEvent *pe);
};

#endif // WINDOW_H
