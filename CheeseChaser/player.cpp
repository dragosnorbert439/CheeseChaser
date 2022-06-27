#include "player.h"

Player::Player(GameMap* gameMap, float x, float y) : ActiveEntity {gameMap, x, y}
{    
    loadImage(":/player/mouse");
    entityLevel = 1;
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFocus();
    setZValue(2);
    setUpConnects();
}

Player::~Player()
{
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (isGameOver) return;
    if (event->key() == Qt::Key_Escape)
    {
        escKeyPressed = !escKeyPressed;
        emit escPressed(); return;
    }
    if (keyIsPressed || moving || escKeyPressed) return;
    switch (event->key())
    {
    case Qt::Key_A: direction = LEFT; break;
    case Qt::Key_D: direction = RIGHT; break;
    case Qt::Key_W: direction = UP; break;
    case Qt::Key_S: direction = DOWN; break;
    case Qt::Key_Z: emit playerUndo(); direction = -1; break;
    default: return;
    }
    if (canMove(direction))
    {
        keyIsPressed= true;
        moving = true;
        emit playerMoved();
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;
    keyIsPressed = false;
}

void Player::setUpConnects()
{
    connect(this, &Player::escPressed, map, &GameMap::escPressed);
    connect(this, &Player::playerMoved, map, &GameMap::playerMovedNotify);
    connect(map, &GameMap::setPlayerMovingFalse, [&](){ moving = false; });
    connect(this, &Player::playerUndo, map, &GameMap::undoAllEntities);
    connect(map, &GameMap::playerLose, [&]() { isGameOver = true; });
    connect(map, &GameMap::playerWin, [&]() { isGameOver = true; });
}


