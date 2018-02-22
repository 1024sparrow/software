#include <QApplication>
//#include "window.h"
#include "footer.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    //(new Window())->show();//FullScreen();
    QWidget *w = new Footer();//Window();
    w->show();
    return app.exec();
}
