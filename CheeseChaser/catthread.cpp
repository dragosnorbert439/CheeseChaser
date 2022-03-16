#include "catthread.h"

CatThread::CatThread(Cat* cat)
{
    this->cat = cat;
}

void CatThread::run()
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

void CatThread::calculateDirection()
{
    start();
}
