#include "passabletile.h"

PassableTile::PassableTile(float x, float y) : Tile{ x, y }
{
    loadImage(":/tile/passable_tile");
}

PassableTile::~PassableTile()
{
}
