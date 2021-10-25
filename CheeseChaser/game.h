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

#include "sprite.h"
#include "player.h"
#include "tile.h"

class Game : public QWidget
{
    Q_OBJECT
private:
    // [EN] Private variables
    int gameRows;
    int gameCols;

    QVBoxLayout* mainLayout;
    QGraphicsScene* scene;
    QGraphicsView* view;

    Tile*** tiles;

    // [EN] variables for the player
    Player* player;
    bool* canMove; // 0 LEFT, 1 RIGHT, 2 UP, 3 DOWN

    // [EN] Private functions
    void initVariables();
    void initGame();

public:
    explicit Game();
    void keyPressEvent(QKeyEvent* event);

signals:

};

#endif // GAME_H
