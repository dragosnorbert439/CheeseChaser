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

protected:
    Cat* cat;
    void run() override;

public slots:
    void calculateDirection();

};

#endif // CATTHREAD_H
