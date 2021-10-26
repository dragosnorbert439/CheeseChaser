#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
private:
    int flag;

public:
    Entity();

    enum { PLAYER, ENEMY, CHEESE, ENVIORMENT };
    int getEntityFlag() const;
    void setEntityFlag(int value);
};

#endif // ENTITY_H
