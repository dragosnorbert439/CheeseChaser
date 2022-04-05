#include "game.h"

Game::Game()
{
    initVariables();
    setUpConnects();
}

Game::~Game()
{
    delete view;
    delete scene;
    delete gameMap;
    delete exitButton;
    delete returnToMainMenuButton;
    delete exitButtonProxy;
    delete returnToMainMenuProxy;
    delete miniMenuBackground;
}

void Game::showGame() const
{
    view->show();
}

void Game::hideGame()
{
    view->hide();
    delete gameMap;
}

void Game::initVariables()
{
    // pointers
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setScene(scene);
    gameMap = new StaticMap(scene);
    exitButton = new QPushButton(tr("EXIT"));
    exitButtonProxy = new QGraphicsProxyWidget();
    returnToMainMenuButton = new QPushButton(tr("MAIN MENU"));
    miniMenuBackground = new QGraphicsRectItem();

    // mini menu components
    showingMiniMenu = false;
    miniMenuBackground->setBrush(Qt::black);
    miniMenuBackground->setOpacity(0.618f);
    miniMenuBackground->hide();
    exitButton->hide();
    returnToMainMenuButton->hide();
    scene->addItem(miniMenuBackground);
    returnToMainMenuProxy = scene->addWidget(returnToMainMenuButton);
    exitButtonProxy = scene->addWidget(exitButton);
    miniMenuBackground->setZValue(3);
    exitButtonProxy->setZValue(4);
    returnToMainMenuProxy->setZValue(4);
}

void Game::setUpConnects()
{
    connect(gameMap, &GameMap::bringUpMenu, this, &Game::bringUpMenu);
    connect(exitButton, &QPushButton::clicked, [&](){ exit(EXIT_SUCCESS); });
    connect(returnToMainMenuButton, &QPushButton::clicked, this, &Game::returnToMainMenu);
}

void Game::bringUpMenu()
{
    if (showingMiniMenu)
    {
        // hide all the mini menu components
        exitButton->hide();
        returnToMainMenuButton->hide();
        miniMenuBackground->hide();

        showingMiniMenu = false;
    }
    else
    {
        // update mini menu components
        miniMenuBackground->setRect(view->viewport()->rect().adjusted(1.f, 1.f, -1.f, -1.f));
        returnToMainMenuProxy->setPos(view->viewport()->width() / 2 - returnToMainMenuButton->width() / 2,
                                      view->viewport()->height() / 2 - returnToMainMenuButton->height() - 100.f);
        exitButtonProxy->setPos(view->viewport()->width() / 2 - exitButton->width() / 2,
                                view->viewport()->height() / 2);

        // show all the mini menu components
        exitButton->show();
        returnToMainMenuButton->show();
        miniMenuBackground->show();

        showingMiniMenu = true;
    }
}

