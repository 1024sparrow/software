#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>

class QPaintEvent;
class QResizeEvent;
class QKeyEvent;
class Display;
class Gameplay : public QWidget
{
    Q_OBJECT
public:
    Gameplay();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent (QKeyEvent * event);
    void keyReleaseEvent (QKeyEvent * event);

private:
    Display *m_display;
};

#endif // GAMEPLAY_H
