#include "enemy.h"

void Enemy::initSprite()
{
    image = new QPixmap();
    if (!image->load("C:/Egyetem/Allamvizsga/images/cat.png")) qDebug() << "ENEMY::ERROR::Could not load image for QPixmap\n";
    this->setPixmap(*image);
}

Enemy::Enemy(float x, float y)
{
    this->initSprite();
    this->setPos(x * TILE_SIZE, y * TILE_SIZE);
}

