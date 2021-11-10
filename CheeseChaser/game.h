#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>
#include <QFile>
#include <QPushButton>

#include "sprite.h"
#include "player.h"
#include "tile.h"
#include "cheese.h"
#include "enemy.h"
#include "mybutton.h"

class Game : public QWidget
{
    Q_OBJECT
private:
    // [EN] Private variables
    int gameRows;
    int gameCols;

    QVBoxLayout* mainLayout;
    QGraphicsScene* scene;
    QGraphicsScene* menuScene;
    QVBoxLayout* menuLayout;
    QGraphicsView* view;

    Tile*** tiles;

    MyButton* goButton;
    MyButton* quitButton;

    // [EN] variables for the player
    Player* player;

    // [EN] variable for the cheese
    Cheese* cheese;

    // [EN] Private functions
    void initVariables();
    void initGame();
    void initMenu();

public:
    // [EN] constructor
    explicit Game();

signals:

};

#endif // GAME_H
