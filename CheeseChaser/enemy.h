#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "tile.h"
#include "entity.h"

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

// [EN] Private members
    QPixmap* image;

// [EN] Private functions
    void initSprite();

    public:
// [EN] Constructor
    Enemy(float x = 0.f, float y = 0.f);

};

#endif // ENEMY_H
