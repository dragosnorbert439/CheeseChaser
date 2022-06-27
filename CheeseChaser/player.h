#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>

#include "activeentity.h"
#include "greedycat.h"
#include "cheese.h"

class Player : public ActiveEntity
{
    Q_OBJECT

public:
    Player(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    ~Player();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    bool keyIsPressed {false};
    bool escKeyPressed {false};
    bool isGameOver {false};
    void setUpConnects();

signals:
    void escPressed();
    void playerMoved();
    void playerUndo();
    void playerLose();
    void playerWin();
};

#endif // PLAYER_H
