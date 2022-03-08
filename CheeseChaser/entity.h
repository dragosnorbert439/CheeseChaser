#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPair>

#include "tile.h"

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Entity(float x = 0.f, float y = 0.f);
    virtual ~Entity();

protected:
    void loadImage(const QString& img);

private:
    QPixmap* image;

};

#endif // ENTITY_H
