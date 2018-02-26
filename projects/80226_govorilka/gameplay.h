#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>

class QPaintEvent;
class QKeyEvent;
class Gameplay : public QWidget
{
    Q_OBJECT
public:
    Gameplay();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent (QKeyEvent * event);
    void keyReleaseEvent (QKeyEvent * event);
};

#endif // GAMEPLAY_H
