#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QVector>
#include <QWidget>
#include <QTime>
#include <QCoreApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "passabletile.h"
#include "unpassabletile.h"
#include "entity.h"
#include "constants.h"

class GameMap : public QObject
{
    Q_OBJECT

public:
    // constructor/destructor
    GameMap(QGraphicsScene* scene = nullptr);
    ~GameMap();

    // the map and related methods
    Tile*** getMap();
    virtual void setMap();
    int getRows() const;
    int getCols() const;
    bool setRows(const int newRowCount);
    bool setCols(const int newColCount);

    // entities on the map
    QVector<Entity*>* getEntities() const;
    Entity* getPlayer() const;

    // for drawing and entity movement smoothing
    void delay(float amount);

    // to set or change the scene
    void setScene(QGraphicsScene *scene);

protected:
    // the scene where the items are drawn on
    QGraphicsScene* gameScene;

    // map related variables
    int rows;
    int cols;
    Tile*** map;

    // entities on the map
    QVector<Entity*>* entities;
    Entity* player;

    // for drawing
    QVector<bool*> threadAnswers;

public slots:
    void escPressed();
    void playerMovedToDirection();

signals:
    void bringUpMenu();
    void tick();
    void setPlayerMovingFalse();
    void playerMoved();

};

#endif // GAMEMAP_H
