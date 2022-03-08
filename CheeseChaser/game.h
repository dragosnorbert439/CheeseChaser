#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>

#include "staticmap.h"
#include "gamemap.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game();
    ~Game();
    void showGame() const;
    void hideGame();

protected:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsRectItem* miniMenuBackground;
    GameMap* gameMap;
    bool showingMiniMenu;
    QPushButton* exitButton;
    QPushButton* returnToMainMenuButton;
    QGraphicsProxyWidget* exitButtonProxy;
    QGraphicsProxyWidget* returnToMainMenuProxy;

    void initVariables();
    void setUpConnects();

signals:
    void returnToMainMenu();

public slots:
    void bringUpMenu();

};

#endif // GAME_H
