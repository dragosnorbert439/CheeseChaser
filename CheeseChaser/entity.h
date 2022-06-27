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

    short getEntityLevel() const;

protected:
    void loadImage(const QString& img);
    short entityLevel {0};

private:
    QPixmap* image;

};

#endif // ENTITY_H
