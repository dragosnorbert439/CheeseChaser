#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "entity.h"

const float TILE_SIZE = 50.f;

class Tile : public QObject, public QGraphicsPixmapItem, public Entity
{
    Q_OBJECT

private:
    // [EN] private members
    float x;
    float y;
    QPixmap* image;
    int state; // 0 = passable, 1 = unpassable

    // [EN] private methods
    void initSprite();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

public:
    // [EN] Constructor
    Tile(float x = 0.f, float y = 0.f, unsigned int state = 0); // [EN] state: 0 passable, 1 unpassable

    int getState() const { return state; }
    enum { PASSABLE, UNPASSABLE };

signals:

};

#endif // TILE_H
