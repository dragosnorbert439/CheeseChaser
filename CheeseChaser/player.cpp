#include "player.h"

Player::Player(GameMap* gameMap, float x, float y) : ActiveEntity {gameMap, x, y}
{    
    loadImage(":/player/mouse");
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFocus();
    setUpConnects();
    setZValue(2);
}

Player::~Player()
{
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A: move(LEFT); break;
    case Qt::Key_D: move(RIGHT); break;
    case Qt::Key_W: move(UP); break;
    case Qt::Key_S: move(DOWN); break;
    case Qt::Key_Escape: emit escPressed(); break;
    }
}

void Player::setUpConnects()
{
    connect(this, &Player::escPressed, map, &GameMap::escPressed);
}


