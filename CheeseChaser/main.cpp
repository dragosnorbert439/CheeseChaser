#include <QApplication>

#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/player/mouse"));

    MainMenu menu;
    menu.show();

    return a.exec();
}
