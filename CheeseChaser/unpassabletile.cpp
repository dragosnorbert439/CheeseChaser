#include "unpassabletile.h"

UnpassableTile::UnpassableTile(float x, float y) : Tile {x, y}
{
    loadImage(":/tile/unpassable_tile");
}

UnpassableTile::~UnpassableTile()
{
}
