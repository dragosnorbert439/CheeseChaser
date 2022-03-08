#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QVector>
#include <QWidget>

#include "passabletile.h"
#include "unpassabletile.h"
#include "entity.h"

class GameMap : public QObject
{
    Q_OBJECT

public:
    GameMap();
    virtual ~GameMap();

    int getRows() const;
    int getCols() const;
    bool setRows(int newRowCount);
    bool setCols(int newColCount);

    virtual void setMap();

    Tile*** getMap();
    QVector<Entity*>* getEntities() const;


protected:
    int rows;
    int cols;
    Tile*** map;
    QVector<Entity*>* entities;


public slots:
    void escPressed();

signals:
    void bringUpMenu();

};

#endif // GAMEMAP_H
