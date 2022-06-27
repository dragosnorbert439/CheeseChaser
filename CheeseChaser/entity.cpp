#include "entity.h"

Entity::Entity(float x, float y)
{
    image = new QPixmap();
    setPos(x * TILE_SIZE, y * TILE_SIZE);
}

Entity::~Entity()
{
    delete image;
}

short Entity::getEntityLevel() const
{
    return entityLevel;
}

void Entity::loadImage(const QString &img)
{
    if (!image->load(img))
    {
        //qDebug() << "Entity::ERROR::Could not load image for QPixmap\n";
        return;
    }
    setPixmap(image->scaled(TILE_SIZE, TILE_SIZE));
}

