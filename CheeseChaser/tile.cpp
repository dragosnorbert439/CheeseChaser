#include "tile.h"

void Tile::initSprite()
{
    image = new QPixmap();

    if (this->state == PASSABLE)
    {
        if (!image->load("C:/Egyetem/Allamvizsga/images/ground.png")) qDebug() << "TILE::ERROR::Could not load image for QPixmap\n";
    }
    else if (this->state == UNPASSABLE)
    {
        if (!image->load("C:/Egyetem/Allamvizsga/images/wall.png")) qDebug() << "TILE::ERROR::Could not load image for QPixmap\n";
    }

    this->setPixmap(*image);
}

Tile::Tile(float x, float y, unsigned int state)
{
    this->state = state;
    initSprite();
    this->x = x;
    this->y = y;
    this->setPos(x * TILE_SIZE, y * TILE_SIZE);
}

