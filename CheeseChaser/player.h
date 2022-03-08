#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>

#include "activeentity.h"
#include "game.h"

class Player : public ActiveEntity
{
    Q_OBJECT

public:
    Player(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    ~Player();
    void keyPressEvent(QKeyEvent* event);

private:
    void setUpConnects();

signals:
    void escPressed();
};

#endif // PLAYER_H
