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

    QFile file("C:/Egyetem/Allamvizsga/CheeseChaser/CheeseChaser/textInput.txt");
    QString line;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "GAME::initGame::ERROR::Could not open text file!";
        return;
    }

    QTextStream in(&file);
    QStringList fields;
    QPair <int, int> playerPos;
    QPair <int, int> cheesePos;
    line = in.readLine();
    fields = line.split(" ");
    this->gameRows = fields[0].toInt();
    this->gameCols = fields[1].toInt();

    // [EN] the map
    this->tiles = new Tile**[this->gameRows];
    for (int i = 0; i < this->gameRows; ++i) tiles[i] = new Tile*[this->gameCols];

    for (int i = 0; i < this->gameRows; ++i)
    {
        line = in.readLine();
        fields = line.split(" ");

        for (int j = 0; j < this->gameCols; ++j)
        {
            if (fields[j].toInt() == 0)
            {
                tiles[i][j] = new Tile(j, i, Tile::PASSABLE);
                tiles[i][j]->setEntityFlag(Entity::ENVIORMENT);
            }
            else if (fields[j].toInt() == 2)
            {
                tiles[i][j] = new Tile(j, i, Tile::PASSABLE);
                tiles[i][j]->setEntityFlag(Entity::PLAYER);
                playerPos = {j, i};
            }
            else if (fields[j].toInt() == 3)
            {
                tiles[i][j] = new Tile(j, i, Tile::PASSABLE);
                tiles[i][j]->setEntityFlag(Entity::CHEESE);
                cheesePos = {j, i};
            }
            else if (fields[j].toInt() == 1)
            {
                tiles[i][j] = new Tile(j, i, Tile::UNPASSABLE);
                tiles[i][j]->setEntityFlag(Entity::ENVIORMENT);
            }
            else
            {
                qDebug() << "GAME::initGame::ERROR::Something went wrong!";
            }
            scene->addItem(tiles[i][j]);
        }
    }

    file.close();

    // [EN] the cheese
    this->cheese = new Cheese(cheesePos.first, cheesePos.second);
    scene->addItem(cheese);

    // [EN] the player
    this->player = new Player(tiles, gameRows, gameCols, playerPos.first, playerPos.second);
    scene->addItem(player);

    // [EN] we have the player, but we still need to make it focusable for events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    view->show();
}


Game::Game() : QWidget()
{
    initVariables();
    initGame();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // can't be focused so this will never run
    qDebug() << "GAME::KeyPressed::Code:" << event->key();
}
