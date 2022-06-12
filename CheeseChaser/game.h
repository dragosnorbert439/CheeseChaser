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
#include "constants.h"

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
    bool isMiniMenuVisible {false};
    QPushButton* exitButton;
    QPushButton* returnToMainMenuButton;
    QGraphicsProxyWidget* exitButtonProxy;
    QGraphicsProxyWidget* returnToMainMenuProxy;

    void initVariables();
    void setUpConnects();
    void hideMiniMenu();
    void showMiniMenu();
    void updateMiniMenu();
    void setStyle();

signals:
    void returnToMainMenu();
    void startPermaDelay();

public slots:
    void bringUpMenu();

};

#endif // GAME_H
