#include <QApplication>

#include "gameplay.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Gameplay *gp = new Gameplay();
    gp->setLetter(QList<int>()<<12<<3<<6<<7);
    gp->show();

    return app.exec();
}
