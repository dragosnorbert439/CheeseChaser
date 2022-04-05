#include "gamemap.h"

GameMap::GameMap(QGraphicsScene* scene)
{
    gameScene = scene;
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

void GameMap::setMap()
{
    // to override in child classes
}

Tile*** GameMap::getMap()
{
    return map;
}

QVector<Entity*>* GameMap::getEntities() const
{
    return entities;
}

Entity *GameMap::getPlayer() const
{
    return player;
}

void GameMap::escPressed()
{
    emit bringUpMenu();
}

void GameMap::playerMovedToDirection()
{
    bool doneAll = false;
    for(auto& v : threadAnswers) *v = false;
    emit playerMoved();
    while(!doneAll)
    {
        delay(20);
        doneAll = true;
        for(auto& v : threadAnswers) doneAll &= *v;
    }

    delay(drawDelay);
    for (int transitionFrame = 0; transitionFrame < maxTransitionFrames; ++transitionFrame)
    {
        emit tick();
        if (transitionFrame < maxTransitionFrames + 1) delay(drawDelay);
    }
    emit setPlayerMovingFalse();
}

void GameMap::delay(float amount)
{
    QTime delayTime = QTime::currentTime().addMSecs(amount);
    while (QTime::currentTime() < delayTime) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameMap::setScene(QGraphicsScene *scene)
{
    gameScene = scene;
}
