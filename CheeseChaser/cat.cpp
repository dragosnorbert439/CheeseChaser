#include "cat.h"

Cat::Cat(GameMap *gameMap, float x, float y) : ActiveEntity {gameMap, x, y}
{
    loadImage(":/enemy/cat");
    catThread = new CatThread(this);
    setUpConnects();
}

Cat::~Cat()
{
    delete catThread;
}

void Cat::setUpConnects()
{
    connect(map, &GameMap::playerMoved, catThread, &CatThread::calculateDirection);

}
