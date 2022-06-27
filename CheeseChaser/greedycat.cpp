#include "greedycat.h"

GreedyCat::GreedyCat(GameMap *gameMap, float x, float y) : Cat{gameMap, x, y}
{
}

GreedyCat::~GreedyCat()
{
}

bool GreedyCat::runAStarAlgorithm()
{
    // randomness - small chance for the outcome just be random - may change it later
    srand(time(0LL));
    const float distanceToTarget = (distanceToEntity(*map->getPlayer()) / TILE_SIZE_SQR);
    const float randomNumberGenerated = qrand() % (map->getRows() * map->getCols() / 2);
    if (distanceToTarget >= randomNumberGenerated)
    {
        setDirection(getRandomDirection());
        done = true;
        return true;
    }

    // Variables
    // map dimensions
    const int rows = map->getRows();
    const int cols = map->getCols();
    // map
    int** mmap = new int* [rows];
    for (int i = 0; i < rows; ++i) { mmap[i] = new int[cols]; }
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (typeid (*map->getMap()[i][j]).name() == typeid (PassableTile).name()) {  mmap[i][j] = INT_MAX; }
            else { mmap[i][j] = -1; }
        }
    }
    // starting and target positions
    QPair<int, int> startingPosition = getMapCoord();
    QPair<int, int> targetPosition = static_cast<ActiveEntity*>(map->getPlayer())->getMapCoord();
    switch (static_cast<ActiveEntity*>(map->getPlayer())->getDirection())
    {
    case LEFT: targetPosition.second -= 1;
    case RIGHT: targetPosition.second += 1;
    case UP: targetPosition.first -= 1;
    case DOWN: targetPosition.first += 1;
    }

    // fill the mmap
    fillDistanceMap(mmap, rows, cols, targetPosition.first, targetPosition.second, -1);

    // copy of map for calculations
    int** copyMap = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        copyMap[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            if (mmap[i][j] == -1) { copyMap[i][j] = mmap[i][j]; }
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
    copyMap[startingPosition.first][startingPosition.second] = mmap[startingPosition.first][startingPosition.second];
    while (currentPosition != targetPosition && !pq.empty())
    {
        currentPosition.first = pq.top()[0];
        currentPosition.second = pq.top()[1];
        distanceTravelled = pq.top()[3];
        pq.pop();

        for (int i = 0; i < 4; ++i)
        {
            int tempNextI = currentPosition.first + pIndices[i];
            int tempNextJ = currentPosition.second + qIndices[i];

            if (tempNextI < 0 || tempNextI >= rows
                || tempNextJ < 0 || tempNextJ >= cols
                || copyMap[tempNextI][tempNextJ] == -1
                || !(copyMap[tempNextI][tempNextJ] == INT_MAX)) continue;

            copyMap[tempNextI][tempNextJ] = mmap[tempNextI][tempNextJ] + distanceTravelled;
            pq.push(QVector<int>() << tempNextI << tempNextJ << mmap[tempNextI][tempNextJ] + distanceTravelled << distanceTravelled + 1);
        }
    }

    // now decide direction
    // if couldn't find the target for some reason, then choose randomly a direction
    if (targetPosition != currentPosition)
    {
        // free dynamically allocated memory
        for (int i = 0; i < rows; ++i)
        {
            delete[] mmap[i];
            delete[] copyMap[i];
        }
        delete[] mmap;
        delete[] copyMap;
        setDirection(getRandomDirection());
        done = true;
        return true;
    }

    // if we did find the target position, it means we have at least one good direction to go towards
    QVector<int> optimalDirection;
    if (canMove(ActiveEntity::LEFT) && copyMap[startingPosition.first][startingPosition.second - 1] == copyMap[startingPosition.first][startingPosition.second])
    {
        optimalDirection.push_back(ActiveEntity::LEFT);
    }
    if (canMove(ActiveEntity::RIGHT) && copyMap[startingPosition.first][startingPosition.second + 1] == copyMap[startingPosition.first][startingPosition.second])
    {
        optimalDirection.push_back(ActiveEntity::RIGHT);
    }
    if (canMove(ActiveEntity::UP) && copyMap[startingPosition.first - 1][startingPosition.second] == copyMap[startingPosition.first][startingPosition.second])
    {
        optimalDirection.push_back(ActiveEntity::UP);
    }
    if (canMove(ActiveEntity::DOWN) && copyMap[startingPosition.first + 1][startingPosition.second] == copyMap[startingPosition.first][startingPosition.second])
    {
        optimalDirection.push_back(ActiveEntity::DOWN);
    }

    // free dynamically allocated memory
    for (int i = 0; i < rows; ++i)
    {
        delete[] mmap[i];
        delete[] copyMap[i];
    }
    delete[] mmap;
    delete[] copyMap;

    // if there isn't an optimal direction to go to, it means we hit the target, so we'll just move randomly (special case)
    if (optimalDirection.empty())
    {
        setDirection(getRandomDirection());
        done = true;
        return true;
    }

    srand(time(0LL));
    setDirection(optimalDirection[rand() % optimalDirection.size()]);
    done = true;
    return true;
}

void GreedyCat::fillDistanceMap(int **distMap, int rows, int cols, int indexI, int indexJ, int distance)
{
    if (distMap[indexI][indexJ] > distance) distMap[indexI][indexJ] = distance + 1;
    else return;
    for (int i = 0; i < 4; ++i )
    {
        int tempNextI = indexI +  pIndices[i];
        int tempNextJ = indexJ + qIndices[i];
        if (tempNextI < 0 || tempNextI >= rows
                || tempNextJ < 0 || tempNextJ >= cols
                || distMap[tempNextI][tempNextJ] == -1) continue;
        fillDistanceMap(distMap, rows, cols, tempNextI, tempNextJ, distance + 1);
    }
}

void GreedyCat::calculateDirection()
{
    runAStarAlgorithm();
    futureComputation.waitForFinished();
}






