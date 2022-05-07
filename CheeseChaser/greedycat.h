#ifndef GREEDYCAT_H
#define GREEDYCAT_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QPair>
#include <queue>
#include <QVector>
#include <limits.h>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <qfuture.h>
#include <QDebug>
#include <limits.h>
#include <QtGlobal>
#include <QGlobalStatic>

#include "cat.h"
#include "constants.h"

class GreedyCat : public Cat
{
    Q_OBJECT

public:
    // Constructor/destructor
    GreedyCat(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    ~GreedyCat();

private:
    QFuture<bool> futureComputation;
    QPair<int, int> startingPosition;
    QPair<int, int> targetPosition;

    const int rows = map->getRows();
    const int cols = map->getCols();

    bool runAStarAlgorithm();
    void fillDistanceMap(int** distMap, int rows, int cols, int i, int j, int distance);

public slots:
    virtual void calculateDirection() override;
};

#endif // GREEDYCAT_H



