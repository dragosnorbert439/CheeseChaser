#ifndef ACTIVEENTITY_H
#define ACTIVEENTITY_H

#include <QPair>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>

#include "entity.h"
#include "gamemap.h"

class ActiveEntity : public Entity
{
    Q_OBJECT

public:
    ActiveEntity(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    virtual ~ActiveEntity();
    void moveAnimated(int direction = 0);


    QPair<int, int> getMapCoord() const;
    float distanceToEntity(const Entity& e) const;

    // for movement
    void moveByAmount(int direction = 0, float amount = TILE_SIZE / GameMap::maxTransitionFrames); // Doesn't check enviorment collision
    void move(int direction = 0);
    bool isMoving() const;
    bool setDirection(const int direction);
    bool setMoving(const bool moving);
    virtual bool canMove(int direction = 0);

    enum MOVE { LEFT, RIGHT, UP, DOWN };

protected:
    GameMap* map;
    int direction {0};

    void checkForEntityCollision();

    bool moving = false;
};

#endif // ACTIVEENTITY_H
