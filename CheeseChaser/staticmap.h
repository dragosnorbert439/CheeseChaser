#ifndef STATICMAP_H
#define STATICMAP_H
#include <QFile>
#include <QGraphicsScene>

#include "gamemap.h"
#include "player.h"
#include "cat.h"
#include "cheese.h"
#include "greedycat.h"
#include "settings.h"

class StaticMap : public GameMap
{
public:
    StaticMap(QGraphicsScene* scene = nullptr);
    ~StaticMap() override;

    virtual void setMap() override;
};

#endif // STATICMAP_H
