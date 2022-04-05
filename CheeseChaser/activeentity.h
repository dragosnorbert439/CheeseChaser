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
    // constructor/destructor
    ActiveEntity(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    virtual ~ActiveEntity();

    // map related
    QPair<int, int> getMapCoord() const;
    float distanceToEntity(const Entity& e) const;

    // for movement
    void moveByAmount(int direction = 0, float amount = TILE_SIZE / maxTransitionFrames); // Doesn't check enviorment collision
    void move(int direction = 0);
    bool isMoving() const;
    bool setDirection(const int direction);
    int getDirection() const;
    bool setMoving(const bool moving);
    virtual bool canMove(int direction = 0);

    enum MOVE { LEFT, RIGHT, UP, DOWN };

protected:
    GameMap* map;
    int direction {0};
    bool moving {false};

    void checkForEntityCollision() const;

};

#endif // ACTIVEENTITY_H
