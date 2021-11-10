#include "player.h"

void Player::initSprite()
{
    image = new QPixmap();
    if (!image->load("C:/Egyetem/Allamvizsga/images/mouse.png")) qDebug() << "PLAYER::ERROR::Could not load image for QPixmap\n";
    this->setPixmap(*image);
}

void Player::movePlayer(int direction)
{
    switch (direction)
    {
    case LEFT:
        if (canMove[LEFT])
        {
            this->moves->push_back(LEFT);
            currentFrame = 0; mapCoordJ -= 1; this->direction = LEFT;
            updateTileState(); map[mapCoordI][mapCoordJ + 1]->setEntityFlag(Entity::ENVIORMENT);
        }
        break;

    case RIGHT:
        if (canMove[RIGHT])
        {
            qDebug() << "moved to right";
            this->moves->push_back(RIGHT);
            currentFrame = 0; mapCoordJ += 1; this->direction = RIGHT;
            updateTileState(); map[mapCoordI][mapCoordJ - 1]->setEntityFlag(Entity::ENVIORMENT);
        }
        break;

    case UP:
        if (canMove[UP])
        {
            this->moves->push_back(UP);
            currentFrame = 0; mapCoordI -= 1; this->direction = UP;
            updateTileState(); map[mapCoordI + 1][mapCoordJ]->setEntityFlag(Entity::ENVIORMENT);
        }
        break;

    case DOWN:
        if (canMove[DOWN])
        {
            this->moves->push_back(DOWN);
            currentFrame = 0; mapCoordI += 1; this->direction = DOWN;
            updateTileState(); map[mapCoordI - 1][mapCoordJ]->setEntityFlag(Entity::ENVIORMENT);
        }
        break;
    }

    updateCanMove();
}

Player::Player(Tile*** map, int mapRows, int mapCols, float posX, float posY)
{
    // [EN] init sprite call
    this->initSprite();

    // [EN] members
    this->map = map;
    this->mapRows = mapRows;
    this->mapCols = mapCols;

    this->moves = new QQueue<int>;
    this->setPos(posX * TILE_SIZE, posY * TILE_SIZE);
    this->startingPoint = this->pos();
    this->mapCoordI = posY;
    this->mapCoordJ = posX;

    this->canMove = new bool[4];
    this->updateCanMove();

    this->transitionFrames = 60;
    this->currentFrame = 0;
    this->timer = new QTimer();

    this->direction = STOP;

    // [EN] the timer (for delayed movement)
    connect(timer, &QTimer::timeout, [&]()
    {
        // [EN] from input
        if (this->direction < STOP && currentFrame != transitionFrames)
        {
            switch (this->direction)
            {
                case LEFT: this->setX(this->pos().x() - TILE_SIZE / transitionFrames); break;
                case RIGHT: this->setX(this->pos().x() + TILE_SIZE / transitionFrames); break;
                case UP: this->setY(this->pos().y() - TILE_SIZE / transitionFrames); break;
                case DOWN: this->setY(this->pos().y() + TILE_SIZE / transitionFrames); break;
            }

            ++currentFrame;
        }
        else if (this->direction < STOP)
        {
            this->direction = STOP;
        }

        // [EN] from START button
        if (this->direction == RUNNING && currentFrame != transitionFrames && !this->moves->isEmpty())
        {
            switch (this->moves->first())
            {
                case LEFT: this->setX(this->pos().x() - TILE_SIZE / transitionFrames); break;
                case RIGHT: this->setX(this->pos().x() + TILE_SIZE / transitionFrames); break;
                case UP: this->setY(this->pos().y() - TILE_SIZE / transitionFrames); break;
                case DOWN: this->setY(this->pos().y() + TILE_SIZE / transitionFrames); break;
            }

            ++currentFrame;
        }
        else if (direction == RUNNING && currentFrame == transitionFrames && !this->moves->isEmpty())
        {
            this->moves->pop_front();
            currentFrame = 0;
        }
    });

    this->timer->start(TIMER_MS);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    // qDebug() << "PLAYER::KeyPressed::Code:" << event->key();
    if (direction < STOP) return;
    if (direction == RUNNING) return;

    switch (event->key())
    {
    case Qt::Key_A:
        movePlayer(LEFT);
        break;

    case Qt::Key_D:
        movePlayer(RIGHT);
        break;

    case Qt::Key_W:
        movePlayer(UP);
        break;

    case Qt::Key_S:
        movePlayer(DOWN);
        break;
    }
}

void Player::updateCanMove()
{
    if (map == nullptr)
    {
        qDebug() << "PLAYER::updateCanMove::ERROR::No map found exception.";
        return;
    }

    // [EN] movement restriction for I axis
    canMove[UP] = true; canMove[DOWN] = true;
    if (mapCoordI == 0)
    {
        canMove[UP] = false;
        if (map[mapCoordI + 1][mapCoordJ]->getState() == Tile::UNPASSABLE) canMove[DOWN] = false;
    }
    if (mapCoordI + 1 == mapRows)
    {
        canMove[DOWN] = false;
        if (map[mapCoordI - 1][mapCoordJ]->getState() == Tile::UNPASSABLE) canMove[UP] = false;
    }
    if (mapCoordI > 0 && mapCoordI + 1 < mapRows)
    {
        if (map[mapCoordI - 1][mapCoordJ]->getState() == Tile::UNPASSABLE) canMove[UP] = false;
        if (map[mapCoordI + 1][mapCoordJ]->getState() == Tile::UNPASSABLE) canMove[DOWN] = false;
    }

    // [EN] movement restriction for J axis
    canMove[LEFT] = true; canMove[RIGHT] = true;
    if (mapCoordJ == 0)
    {
        canMove[LEFT] = false;
        if (map[mapCoordI][mapCoordJ + 1]->getState() == Tile::UNPASSABLE) canMove[RIGHT] = false;
    }
    if (mapCoordJ == mapCols - 1)
    {
        canMove[RIGHT] = false;
        if (map[mapCoordI][mapCoordJ - 1]->getState() == Tile::UNPASSABLE) canMove[LEFT] = false;
    }
    if (mapCoordJ > 0 && mapCoordJ + 1 < mapCols)
    {
        if (map[mapCoordI][mapCoordJ - 1]->getState() == Tile::UNPASSABLE) canMove[LEFT] = false;
        if (map[mapCoordI][mapCoordJ + 1]->getState() == Tile::UNPASSABLE) canMove[RIGHT] = false;
    }
}

void Player::updateTileState()
{
    switch (this->map[mapCoordI][mapCoordJ]->getEntityFlag())
    {
    case Entity::ENEMY:
        // [EN] game over
        qDebug() << "PLAYER::MESSAGEGAME OVER";
        break;
    case Entity::CHEESE:
        // [EN] game won
        qDebug() << "PLAYER::MESSAGE::GAME WON";
        break;
    case Entity::ENVIORMENT:
        // [EN] player movement
        this->map[mapCoordI][mapCoordJ]->setEntityFlag(Entity::PLAYER);
        break;
    case Entity::PLAYER:
        // [EN] in theory this case can become true but has very low chances
        qDebug() << "PLAYER::ERROR::TILE_ENTITY_FLAG_ALREADY_PLAYER";
        break;
    }
}

void Player::runPlayer()
{

    qDebug() << "PLAYER::runPlayer() called";

    for (const auto& e : *moves)
    {
        qDebug() << e;
    }

    if (this->direction < STOP) return;

    qDebug() << "Repositioning player..." << this->startingPoint;

    this->setX(this->startingPoint.x());
    this->setY(this->startingPoint.y());
    this->mapCoordI = this->startingPoint.y() / TILE_SIZE;
    this->mapCoordJ = this->startingPoint.x() / TILE_SIZE;
    this->updateCanMove();

    qDebug() << mapCoordI << mapCoordJ;

    currentFrame = 0;
    this->direction = RUNNING;
}


