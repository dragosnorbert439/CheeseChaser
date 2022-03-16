#pragma once
#ifndef CAT_H
#define CAT_H

#include "catthread.h"
#include "activeentity.h"

class CatThread;
class Cat : public ActiveEntity
{
    Q_OBJECT

public:
    Cat(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    ~Cat();
    bool done {false};

private:
    CatThread* catThread;
    void setUpConnects();

};

#endif // CAT_H
