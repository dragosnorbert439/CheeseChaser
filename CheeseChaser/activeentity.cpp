#include "activeentity.h"

ActiveEntity::ActiveEntity(GameMap *gameMap, float x, float y) : Entity {x, y}
{
    map = gameMap;
    connect(map, &GameMap::tick, [&]()
    {
        moveByAmount(direction);
    });
}

ActiveEntity::~ActiveEntity()
{
}

void ActiveEntity::move(int direction)
{
    if (!canMove(direction)) return;
    switch (direction)
    {
    case LEFT: setX(pos().x() - TILE_SIZE); break;
    case RIGHT: setX(pos().x() + TILE_SIZE); break;
    case UP: setY(pos().y() - TILE_SIZE); break;
    case DOWN: setY(pos().y() + TILE_SIZE); break;
    }
    // if there's a -1 directoin it means the entity is stuck and has no viable moves to make
    checkForEntityCollision();
}

void ActiveEntity::moveByAmount(int direction, float amount)
{
    switch (direction)
    {
    case LEFT: setX(pos().x() - amount); break;
    case RIGHT: setX(pos().x() + amount); break;
    case UP: setY(pos().y() - amount); break;
    case DOWN: setY(pos().y() + amount); break;
    }
    // if there's a -1 directoin it means the entity is stuck and has no viable moves to make
    checkForEntityCollision();
}

QPair<int, int> ActiveEntity::getMapCoord() const // returns i,j indeces
{
    return QPair<int, int>((int)(pos().y() / TILE_SIZE), (int)(pos().x() / TILE_SIZE));
}

bool ActiveEntity::canMove(int direction)
{
    if (moving) return false;
    int i = getMapCoord().first;
    int j = getMapCoord().second;
    switch (direction)
    {
    case LEFT:
        if (j == 0) return false;
        if (typeid (*map->getMap()[i][j - 1]).name() == typeid (UnpassableTile).name()) return false;
        break;
    case RIGHT:
        if (j + 1 == map->getCols()) return false;
        if (typeid (*map->getMap()[i][j + 1]).name() == typeid (UnpassableTile).name()) return false;
        break;
    case UP:
        if (i == 0) return false;
        if (typeid (*map->getMap()[i - 1][j]).name() == typeid (UnpassableTile).name()) return false;
        break;
    case DOWN:
        if (i + 1 == map->getRows()) return false;
        if (typeid (*map->getMap()[i + 1][j]).name() == typeid (UnpassableTile).name()) return false;
        break;
    default:
        // shouldn't reach here
        qDebug() << "ActiveEntity::canMove::ERROR::Something went wrong!";
    }

    return true;
}

bool ActiveEntity::setDirection(const int direction)
{
    if (direction >= 0 && direction <= 4)
    {
        this->direction = direction;
        return true;
    }
    if (direction == -1) this->direction = direction;
    return false;
}

int ActiveEntity::getDirection() const
{
    return direction;
}

float ActiveEntity::distanceToEntity(const Entity &e) const
{
    return (pos().x() - e.pos().x())*(pos().x() - e.pos().x()) + (pos().y() - e.pos().y())*(pos().y() - e.pos().y());
}

void ActiveEntity::checkForEntityCollision() const
{
    for (auto& entity : *map->getEntities())
    {
        if (entity == this) continue;
        if (distanceToEntity(*entity) == 0)
        {
            qDebug() << "Entities collided - Találkozott két entitás";
        }
    }
}

bool ActiveEntity::isMoving() const
{
    return moving;
}

bool ActiveEntity::setMoving(const bool moving)
{
    if (moving != NULL)
    {
        this->moving = moving;
        return true;
    }
    return false;
}

