#include <QApplication>
#include "gameplay.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Gameplay *gp = new Gameplay();
    gp->showMaximized();

    return app.exec();
}
