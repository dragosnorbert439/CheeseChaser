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
    case A_STAR_NONOPTIM: runAStartNonOptimStrategy(); break;
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
    // Variables
    // map dimensions
    const int rows = cat->map->getRows();
    const int cols = cat->map->getCols();
    // map
    int** map = new int* [rows];
    for (int i = 0; i < rows; ++i) { map[i] = new int[cols]; }
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (typeid (*cat->map->getMap()[i][j]).name() == typeid (PassableTile).name()) {  map[i][j] = INT_MAX; }
            else { map[i][j] = -1; }
        }
    }
    // starting and target positions
    QPair<int, int> startingPosition = cat->getMapCoord();
    QPair<int, int> targetPosition = static_cast<ActiveEntity*>(cat->map->getPlayer())->getMapCoord();
    // fill the map
    goNextFillDistance(map, rows, cols, targetPosition.first, targetPosition.second, -1);
    // copy of map for calculations
    int** copyMap = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        copyMap[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            if (map[i][j] == -1) { copyMap[i][j] = map[i][j]; }
            else copyMap[i][j] = INT_MAX;
        }
    }
    // comparator for the priority queue
    struct comparator { bool operator()(QVector<int> a, QVector<int> b) { return a[3] < b[3]; }; };
    // priority queue
    std::priority_queue<QVector<int>, QVector<QVector<int>>, comparator> pq;

    // A* algorithm
    int distanceTravelled = 0;
    QPair<int, int> currentPosition = startingPosition;
    pq.push(QVector<int>() << currentPosition.first << currentPosition.second << copyMap[currentPosition.first][currentPosition.second] << 1);
    copyMap[startingPosition.first][startingPosition.second] = map[startingPosition.first][startingPosition.second];
    while (currentPosition != targetPosition)
    {
        currentPosition.first = pq.top()[0];
        currentPosition.second = pq.top()[1];
        distanceTravelled = pq.top()[3];
        pq.pop();

        for (int p = -1; p < 2; ++p)
        {
            for (int q = -1; q < 2; ++q)
            {
                int tempNextI = currentPosition.first + p;
                int tempNextJ = currentPosition.second + q;

                if (tempNextI < 0 || tempNextI >= rows
                    || tempNextJ < 0 || tempNextJ >= cols
                    || copyMap[tempNextI][tempNextJ] == -1
                    || !(copyMap[tempNextI][tempNextJ] == INT_MAX)
                    || (p == 0 && q == 0)
                    || (abs(p) == abs(q))) continue;

                copyMap[tempNextI][tempNextJ] = map[tempNextI][tempNextJ] + distanceTravelled;
                pq.push(QVector<int>() << tempNextI << tempNextJ << map[tempNextI][tempNextJ] + distanceTravelled << distanceTravelled + 1);
            }
        }
    }

    // now decide direction
    if (cat->canMove(ActiveEntity::LEFT) && copyMap[startingPosition.first][startingPosition.second - 1] == copyMap[startingPosition.first][startingPosition.second])
    {
        cat->setDirection(ActiveEntity::LEFT);
    }
    else if (cat->canMove(ActiveEntity::RIGHT) && copyMap[startingPosition.first][startingPosition.second + 1] == copyMap[startingPosition.first][startingPosition.second])
    {
        cat->setDirection(ActiveEntity::RIGHT);
    }
    else if (cat->canMove(ActiveEntity::UP) && copyMap[startingPosition.first - 1][startingPosition.second] == copyMap[startingPosition.first][startingPosition.second])
    {
        cat->setDirection(ActiveEntity::UP);
    }
    else if (cat->canMove(ActiveEntity::DOWN) && copyMap[startingPosition.first + 1][startingPosition.second] == copyMap[startingPosition.first][startingPosition.second])
    {
        cat->setDirection(ActiveEntity::DOWN);
    }
    else
    {
        switch (cat->direction)
        {
        case ActiveEntity::LEFT: cat->setDirection(ActiveEntity::RIGHT); break;
        case ActiveEntity::RIGHT: cat->setDirection(ActiveEntity::LEFT); break;
        case ActiveEntity::UP: cat->setDirection(ActiveEntity::DOWN); break;
        case ActiveEntity::DOWN: cat->setDirection(ActiveEntity::UP); break;
        default:
            // shouldn't reach here
            qDebug() << "CatThread::run() - Something's wrong!";
        }
    }
    cat->done = true;
}

void CatThread::goNextFillDistance(int **map, int rows, int cols, int indexI, int indexJ, int currentDistance)
{
    if (map[indexI][indexJ] > currentDistance + 1) map[indexI][indexJ] = currentDistance + 1;
    else return;
    for (int p = -1; p < 2; ++p)
    {
        for (int q = -1; q < 2; ++q)
        {
            int tempNextI = indexI + p;
            int tempNextJ = indexJ + q;

            if (tempNextI < 0 || tempNextI >= rows
                || tempNextJ < 0 || tempNextJ >= cols
                || map[tempNextI][tempNextJ] == -1
                || (p == 0 && q == 0)
                || (abs(p) == abs(q))) continue;

            goNextFillDistance(map, rows, cols, tempNextI, tempNextJ, currentDistance + 1);
        }
    }
}

void CatThread::calculateDirection()
{
    start();
}
