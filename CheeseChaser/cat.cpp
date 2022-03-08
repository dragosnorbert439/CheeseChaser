#include "cat.h"

Cat::Cat(GameMap *gameMap, float x, float y) : ActiveEntity {gameMap, x, y}
{
    loadImage(":/enemy/cat");
}

Cat::~Cat()
{
}
