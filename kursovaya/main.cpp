#include "mainmenu.h"
//#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mainmenu window;
    window.show();

    return a.exec();
}
