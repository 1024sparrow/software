#include <QApplication>
#include "gameplay.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Gameplay *gp = new Gameplay();
    gp->show();//Maximized();

    return app.exec();
}
