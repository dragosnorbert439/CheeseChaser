#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "constants.h"

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Tile(float x = 0.f, float y = 0.f);
    virtual ~Tile();

protected:
    void loadImage(const QString& img);

private:
    QPixmap* image;

};

#endif // TILE_H
