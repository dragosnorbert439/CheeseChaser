#include "tile.h"

Tile::Tile(float x, float y)
{
    setPos(x * TILE_SIZE, y * TILE_SIZE);
    image = new QPixmap();

    setFlag(ItemIsFocusable, false);
    setFlag(QGraphicsItem::ItemStopsFocusHandling, true);
}

Tile::~Tile()
{
    delete image;
}

void Tile::loadImage(const QString &img)
{
    if (!image->load(img))
    {
        //qDebug() << "TILE::ERROR::Could not load image for QPixmap\n";
    }
    setPixmap(image->scaled(TILE_SIZE, TILE_SIZE));
}
