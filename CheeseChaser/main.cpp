#include <QApplication>
#include "game.h"
#include "gamemenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;
    // GameMenu gameMenu = GameMenu();

    return a.exec();
}
