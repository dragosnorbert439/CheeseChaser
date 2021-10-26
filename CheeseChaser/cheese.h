#ifndef CHEESE_H
#define CHEESE_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "tile.h"
#include "entity.h"

class Cheese : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

// [EN] Private members
    QPixmap* image;

// [EN] Private functions
    void initSprite();

public:
// [EN] Constructor
    Cheese(float x = 0.f, float y = 0.f);
};

#endif // CHEESE_H
