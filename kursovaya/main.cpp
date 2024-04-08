#include "mainmenu.h"
//#include "mainwindow.h"
#include <QFile>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Mainmenu window;
    QFile file("D:/c++/kursovaya/Combinear.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    }
    window.show();

    return a.exec();
}
