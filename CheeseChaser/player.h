#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QTimer>
#include <QQueue>
#include <QPointF>
#include <QThread>

#include "entity.h"
#include "tile.h"
#include "cheese.h"

const int TIMER_MS = 5;

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
// [EN] private members
    // [EN] members for player
    bool* canMove;
    QPixmap* image;

    // [EN] members for the map
    Tile*** map;
    int mapCoordI;
    int mapCoordJ;
    int mapRows;
    int mapCols;

    // [EN] saved player movement
    QPointF startingPoint;
    QQueue<int>* moves;

    // [EN] other
    QTimer* timer;
    unsigned int transitionFrames;
    unsigned int currentFrame;
    int direction; // [EN] direction flag

// [EN] Private functions
    void initSprite();

private slots:
    void movePlayer(int direction);

public:
// [EN] Constructor
    Player(Tile*** map, int mapRows, int mapCols, float x = 0.f, float y = 0.f);

// [EN] Public functions
    void keyPressEvent(QKeyEvent* event);
    void updateCanMove();
    void updateTileState();

    enum MOVE { LEFT, RIGHT, UP, DOWN, STOP, RUNNING, STOPRUNNING };

public slots:
    void runPlayer();

};

#endif // PLAYER_H
