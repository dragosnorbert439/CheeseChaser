#include "game.h"

void Game::initVariables()
{
    // [HU] mutatok
    this->mainLayout = new QVBoxLayout();
    this->menuLayout = new QVBoxLayout();
    this->scene = new QGraphicsScene();
    this->menuScene = new QGraphicsScene();
    this->view = new QGraphicsView(this->scene);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::SolidPattern));
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
    QVector <QPair <int, int>> enemyPositions;
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
            else if (fields[j].toInt() == 4)
            {
                tiles[i][j] = new Tile(j, i, Tile::PASSABLE);
                tiles[i][j]->setEntityFlag(Entity::ENEMY);
                enemyPositions.push_back({j, i});
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
    this->scene->addItem(cheese);

    // [EN] the enemies (cats)
    for (auto& element : enemyPositions)
    {
        Enemy* cat = new Enemy(element.first, element.second);
        this->scene->addItem(cat);
    }

    // [EN] the player
    this->player = new Player(this->tiles, this->gameRows, this->gameCols, playerPos.first, playerPos.second);
    this->scene->addItem(this->player);

    // [EN] we have the player, but we still need to make it focusable for events
    this->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->player->setFocus();

    this->goButton = new MyButton(MyButton::START, this->gameCols, 0.f);
    this->quitButton = new MyButton(MyButton::QUIT, this->gameCols, this->gameRows - 2);

    connect(goButton, &MyButton::clicked, player, &Player::runPlayer);

    this->scene->addItem(this->goButton);
    this->scene->addItem(this->quitButton);
}

void Game::initMenu()
{
    /*
     *  [EN]
     *  default scene will remain the game during the developing
     *  of the game and its features
     */

    /*
    this->view->setFixedSize(QSize(this->gameCols * TILE_SIZE, this->gameRows * TILE_SIZE));

    this->menuLayout->addWidget(new QPushButton("START"));
    this->menuLayout->addWidget(new QPushButton("OPTIONS"));
    this->menuLayout->addWidget(new QPushButton("QUIT"));

    this->view->setLayout(this->menuLayout);
    */
}


Game::Game() : QWidget()
{
    this->initVariables();
    this->initGame();
    this->initMenu();



    this->view->show();
}



