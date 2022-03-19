#ifndef CATTHREAD_H
#define CATTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <qglobal.h>

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
    unsigned int strategy { RANDOM };

    void runRandomStrategy();
    void runAStartNonOptimStrategy();

public slots:
    void calculateDirection();

};

#endif // CATTHREAD_H
