#ifndef CATTHREAD_H
#define CATTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <qglobal.h>
#include <utility>
#include <queue>
#include <QMap>
#include <limits.h>

#include "cat.h"

class Cat;
class CatThread : public QThread
{
    Q_OBJECT

public:
    CatThread(Cat* cat = nullptr);

    enum Strategy
    {
        RANDOM, A_STAR_NONOPTIM
    };

protected:
    Cat* cat;
    void run() override;
    unsigned int strategy { A_STAR_NONOPTIM };

    void runRandomStrategy();
    void runAStartNonOptimStrategy();

private:
    // A* functions
    void goNextFillDistance(int** map, int rows, int cols, int i, int j, int dist);

public slots:
    void calculateDirection();

};

#endif // CATTHREAD_H
