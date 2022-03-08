#ifndef CAT_H
#define CAT_H

#include "activeentity.h"

class Cat : public ActiveEntity
{
    Q_OBJECT

public:
    Cat(GameMap* gameMap = nullptr, float x = 0.f, float y = 0.f);
    ~Cat();
};

#endif // CAT_H
