#include "cat.h"

Cat::Cat(GameMap *gameMap, float x, float y) : ActiveEntity {gameMap, x, y}
{
    loadImage(":/enemy/cat");
    connect(map, &GameMap::playerMoved, this, &Cat::calculateDirection);
}

Cat::~Cat()
{
}

int Cat::getRandomDirection()
{
    QVector<int> directions;
    if (canMove(LEFT)) directions.push_back(LEFT);
    if (canMove(RIGHT)) directions.push_back(RIGHT);
    if (canMove(UP)) directions.push_back(UP);
    if (canMove(DOWN)) directions.push_back(DOWN);
    if (directions.isEmpty()) return -1;
    srand(time(0LL));
    return directions[rand() % directions.size()];
}

void Cat::calculateDirection()
{
    // to override in child classes
    done = true;
}
