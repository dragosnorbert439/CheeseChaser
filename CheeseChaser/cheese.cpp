#include "cheese.h"

Cheese::Cheese(float x, float y) : Entity {x, y}
{
    loadImage(":/cheese/cheese");
}

Cheese::~Cheese()
{
}
