#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QPixmap>

class QResizeEvent;
class KeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    KeyboardWidget(QWidget *parent = 0);
protected:
    void resizeEvent(QResizeEvent *re);
    void paintEvent(QPaintEvent *);
private:
    QPixmap px;
};

#endif // KEYBOARDWIDGET_H
