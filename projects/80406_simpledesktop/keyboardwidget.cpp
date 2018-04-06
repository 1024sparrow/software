#include "keyboardwidget.h"
#include "globaldefs.h"
#include <QPainter>

KeyboardWidget::KeyboardWidget(QWidget *parent)
    :QWidget(parent)
{
}

void KeyboardWidget::resizeEvent(QResizeEvent *)
{
    /*int w = width();
    int h = height();
    int buttonSize = qMin(w/maxCountInRow, h/rowCount);
    px = QPixmap(maxCountInRow * buttonSize, rowCount * buttonSize);
    QPainter painter(&px);
    //painter.fillRect(rect(), Qt::black);
    for (int i_key = 0 ; i_key < pointsCount ; ++i_key)
    {
        painter.setPen(QColor(colors[pointsMutableBase[i_key].colorIndex]));
        int x = (pointsMutableBase[i_key].x * 3 + pointsMutableBase[i_key].y) * buttonSize / 3;
        int y = pointsMutableBase[i_key].y * buttonSize;
        //painter.drawRect(x, y, buttonSize - 4, buttonSize - 4);
        painter.drawRoundRect(x, y, buttonSize - 4, buttonSize - 4, 5, 5);
    }*/
}

void KeyboardWidget::paintEvent(QPaintEvent *)
{
    int w = width();
    int h = height();
    int buttonSize = qMin(w/maxCountInRow, h/rowCount);
    px = QPixmap(maxCountInRow * buttonSize, rowCount * buttonSize);
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), Qt::black);
    //painter.drawPixmap(0,0,px);
    for (int i_key = 0 ; i_key < pointsCount ; ++i_key)
    {
        painter.setPen(QColor(colors[pointsMutableBase[i_key].colorIndex]));
        int x = (pointsMutableBase[i_key].x * 3 + pointsMutableBase[i_key].y) * buttonSize / 3;
        int y = pointsMutableBase[i_key].y * buttonSize;
        //painter.drawRect(x, y, buttonSize - 4, buttonSize - 4);
        painter.drawRoundRect(x, y, buttonSize - 4, buttonSize - 4, 5, 5);
    }
    painter.end();
}
