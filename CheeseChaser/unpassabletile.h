#ifndef UNPASSABLETILE_H
#define UNPASSABLETILE_H

#include "tile.h"

class UnpassableTile : public Tile
{
public:
    UnpassableTile(float x = 0.f, float y = 0.f);
    ~UnpassableTile();
};

#endif // UNPASSABLETILE_H
