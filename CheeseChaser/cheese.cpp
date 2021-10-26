#include "cheese.h"

void Cheese::initSprite()
{
    image = new QPixmap();
    if (!image->load("C:/Egyetem/Allamvizsga/images/cheese.png")) qDebug() << "CHEESE::ERROR::Could not load image for QPixmap\n";
    this->setPixmap(*image);
}

Cheese::Cheese(float x, float y)
{
    this->initSprite();
    this->setPos(x * TILE_SIZE, y * TILE_SIZE);
}
