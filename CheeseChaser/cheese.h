#ifndef CHEESE_H
#define CHEESE_H

#include "entity.h"

class Cheese : public Entity
{
    Q_OBJECT

public:
    Cheese(float x = 0.f, float y = 0.f);
    ~Cheese();
};

#endif // CHEESE_H
