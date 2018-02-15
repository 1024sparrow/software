#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>

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

private:
    char m_cur;
};

#endif // FOOTER_H
