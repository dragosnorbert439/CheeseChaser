#ifndef ACTIVEENTITY_H
#define ACTIVEENTITY_H

#include "entity.h"
#include "gamemap.h"
#include <QPair>

class ActiveEntity : public Entity
{
    Q_OBJECT

public:
    ActiveEntity(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    virtual ~ActiveEntity();
    void move(int direction = 0);

    enum MOVE { LEFT, RIGHT, UP, DOWN };

protected:
    GameMap* map;
    QPair<int, int> getMapCoord() const;

    virtual bool canMove(int direction = 0);
    float distanceToEntity(const Entity& e) const;
    void checkForEntityCollision();

};

#endif // ACTIVEENTITY_H
