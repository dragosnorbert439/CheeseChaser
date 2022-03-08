#ifndef PASSABLETILE_H
#define PASSABLETILE_H

#include "tile.h"

class PassableTile : public Tile
{
public:
    PassableTile(float x = 0.f, float y = 0.f);
    virtual ~PassableTile();
};

#endif // PASSABLETILE_H
