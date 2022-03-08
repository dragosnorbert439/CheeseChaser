#include "gamemap.h"

GameMap::GameMap()
{
    entities = new QVector<Entity*>;
    setMap();
}

GameMap::~GameMap()
{
    delete entities;
}

int GameMap::getRows() const
{
    if (rows != NULL && rows > 0) return rows;
    return -1;
}

int GameMap::getCols() const
{
    if (cols != NULL && cols > 0) return cols;
    return -1;
}

bool GameMap::setRows(int newRowCount)
{
    if (newRowCount > 0 && newRowCount != NULL)
    {
        rows = newRowCount;
        return true;
    }
    return false;
}

bool GameMap::setCols(int newColCount)
{
    if (newColCount > 0 && newColCount != NULL)
    {
        cols = newColCount;
        return true;
    }
    return false;
}

void GameMap::setMap(){} /// TODO

Tile*** GameMap::getMap()
{
    return map;
}

QVector<Entity*>* GameMap::getEntities() const
{
    return entities;
}

void GameMap::escPressed()
{
    emit bringUpMenu();
}