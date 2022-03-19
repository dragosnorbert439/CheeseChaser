#include "player.h"

Player::Player(GameMap* gameMap, float x, float y) : ActiveEntity {gameMap, x, y}
{    
    loadImage(":/player/mouse");
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
    if (keyIsPressed || moving) return;
    switch (event->key())
    {
    case Qt::Key_A: direction = LEFT; break;
    case Qt::Key_D: direction = RIGHT; break;
    case Qt::Key_W: direction = UP; break;
    case Qt::Key_S: direction = DOWN; break;
    case Qt::Key_Escape: emit escPressed(); return;
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
    connect(this, &Player::playerMoved, map, &GameMap::playerMovedToDirection);
    connect(map, &GameMap::setPlayerMovingFalse, [&](){ moving = false; });
}


