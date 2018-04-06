#include <QApplication>
#include "keyboardwidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    KeyboardWidget *w = new KeyboardWidget();
    w->showMaximized();

    return app.exec();
}
