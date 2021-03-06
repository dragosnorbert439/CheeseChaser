#include "activeentity.h"

ActiveEntity::ActiveEntity(GameMap *gameMap, float x, float y) : Entity {x, y}
{
    map = gameMap;
    movesStack = new QStack<short>;
    connect(map, &GameMap::tick, [&]()
    {
        moveByAmount(direction);
    });
    connect(map, &GameMap::undoAllEntities, [&]()
    {
        undoEntityMove();
    });
    connect(map, &GameMap::setPlayerMovingFalse, [&]()
    {
        movesStack->push(direction);
    });
}

ActiveEntity::~ActiveEntity()
{
    delete movesStack;
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
        return false;
    }

    return true;
}

void ActiveEntity::undoEntityMove()
{
    if (!movesStack->empty())
    {
        short reverseMove = -1;
        switch (movesStack->top())
        {
        case RIGHT: reverseMove = LEFT; break;
        case LEFT: reverseMove = RIGHT; break;
        case UP: reverseMove = DOWN; break;
        case DOWN: reverseMove = UP; break;
        default: movesStack->pop(); return;
        }
        move(reverseMove);
        movesStack->pop();
    }
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

void ActiveEntity::checkForEntityCollision()
{
    for (auto& entity : *map->getEntities())
    {
        if (entity == this) continue;
        if (entity->getEntityLevel() == this->getEntityLevel()) continue;
        else if (distanceToEntity(*entity) == 0)
        {
            // if we hit the cat or vice versa
            if ((this->entityLevel == 1 && entity->getEntityLevel() == 2)
                    ||(this->entityLevel == 2 && entity->getEntityLevel() == 1))
            {
                emit map->playerLose();
            }
            // if we find the finish
            else if (this->entityLevel == 1 && entity->getEntityLevel() == 0)
            {
                emit map->playerWin();
            }
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

