#ifndef TESTER_H
#define TESTER_H

#include <QWidget>

class Footer;
class Tester : public QWidget
{
    Q_OBJECT
public:
    Tester(Footer *footer, QWidget *parent = 0);
private slots:
    void onQ();
    void onW();
    void onE();
    void onMode();

private:
    Footer *m_footer;
};

#endif // TESTER_H
