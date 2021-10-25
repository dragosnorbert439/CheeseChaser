#include "game.h"

void Game::initVariables()
{
    // [HU] mutatok
    this->mainLayout = new QVBoxLayout();
    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->canMove = new bool[4];
}

void Game::initGame()
{
    /*
     *  [HU] Ez a fuggveny teszi meg a kovetkezoket:
     *       - valamely bemenetrol megszerzi a mereteket (rows, cols)
     *       - memoriat foglal a palyanak (tiles[rows][cols])
     *       - a jatekos poziciojat (is) beolvasvan elhelyezi a palyara
     *       - a palyat (is) beolvassa (hol van fal, hol nincs, stb)
     *       - figyelem: a sorrent szamit ahogy inicializalom
     */

    // [EN] for now it's hard coded for testing purposes
    this->gameRows = 8;
    this->gameCols = 8;

    // [EN] the map
    this->tiles = new Tile**[this->gameRows];

    for (int i = 0; i < this->gameRows; ++i) tiles[i] = new Tile*[this->gameCols];

    for (int i = 0; i < this->gameRows; ++i)
    {
        for (int j = 0; j < this->gameCols; ++j)
        {
            if (i == 0 || j == 0 ) tiles[i][j] = new Tile(i, j, Tile::UNPASSABLE);
            else tiles[i][j] = new Tile(i, j, Tile::PASSABLE);
            scene->addItem(tiles[i][j]);
        }
    }

    // [EN] the player
    this->player = new Player(tiles, gameRows, gameCols, 2.f, 2.f);

    scene->addItem(player);

    // [EN] we have the player, but we still need to make it focusable for events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    view->show();
}


Game::Game() : QWidget()
{
    qDebug() << "Game constructor called\n";
    initVariables();
    initGame();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // can't be focused so this will never run
    qDebug() << "GAME::KeyPressed::Code:" << event->key();
}
