#include "entity.h"

int Entity::getEntityFlag() const
{
    return flag;
}

void Entity::setEntityFlag(int value)
{
    flag = value;
}

Entity::Entity()
{
    this->setEntityFlag(PLAYER);
}
