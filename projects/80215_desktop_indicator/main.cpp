#include <QApplication>
#include "window.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    (new Window())->showFullScreen();
    return app.exec();
}
