#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QVector>
#include <QWidget>
#include <QTime>
#include <QCoreApplication>

#include "passabletile.h"
#include "unpassabletile.h"
#include "entity.h"

class GameMap : public QObject
{
    Q_OBJECT

public:
    // constructor/destructor
    GameMap();
    virtual ~GameMap();

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
    static const int maxTransitionFrames = 20;
    static constexpr float drawDelay = 10.42f;
    void delay(float amount);

protected:
    // map related variables
    int rows;
    int cols;
    Tile*** map;

    // entities on the map
    QVector<Entity*>* entities;
    Entity* player;

    // for drawing
    QVector<bool*> catThreadAnswers;

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
