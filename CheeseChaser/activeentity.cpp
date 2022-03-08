#include "activeentity.h"

ActiveEntity::ActiveEntity(GameMap *gameMap, float x, float y) : Entity {x, y}
{
    map = gameMap;
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
    default: qDebug() << "ActiveEntity::move::ERROR::Something went wrong!";
    }
    checkForEntityCollision();
}

QPair<int, int> ActiveEntity::getMapCoord() const // returns i,j indeces
{
    return QPair<int, int>((int)(pos().y() / TILE_SIZE), (int)(pos().x() / TILE_SIZE));
}

bool ActiveEntity::canMove(int direction)
{
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

float ActiveEntity::distanceToEntity(const Entity &e) const
{
    return (pos().x() - e.pos().x())*(pos().x() - e.pos().x()) + (pos().y() - e.pos().y())*(pos().y() - e.pos().y());
}

void ActiveEntity::checkForEntityCollision()
{
    const float TILE_SIZE_SQR = TILE_SIZE * TILE_SIZE;
    for (auto& entity : *map->getEntities())
    {
        if (entity == this) continue;
        if (distanceToEntity(*entity) < TILE_SIZE_SQR)
        {
            qDebug() << "Entities collided";

        }
    }
}
