#pragma once
#ifndef CAT_H
#define CAT_H

#include "activeentity.h"

class Cat : public ActiveEntity
{
    Q_OBJECT

public:
    Cat(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    ~Cat();
    bool done {false};

protected:
    int getRandomDirection();

public slots:
    virtual void calculateDirection();

};

#endif // CAT_H
