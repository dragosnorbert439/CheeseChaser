#include "catthread.h"

CatThread::CatThread(Cat* cat)
{
    this->cat = cat;
}

void CatThread::run()
{
    switch (strategy)
    {
    case RANDOM: runRandomStrategy(); break;
    default: // shouldn't reach here
        qDebug() << "CatThread::run() no strategy detected!";
    }
}

void CatThread::runRandomStrategy()
{
    srand(time(NULL));
    int tDirection = 0;
    do
    {
        tDirection = rand() % 4;
    }
    while (!cat->canMove(tDirection));

    if(!cat->setDirection(tDirection))
    {
        qDebug() << "CatThread::run()::setDirection() couldn't change direction:" << tDirection;
    }
    cat->done = true;
}

void CatThread::runAStartNonOptimStrategy()
{
    // variables
    int rows = cat->map->getRows();
    int cols = cat->map->getCols();
    GameMap* map = cat->map;

}

void CatThread::calculateDirection()
{
    start();
}
