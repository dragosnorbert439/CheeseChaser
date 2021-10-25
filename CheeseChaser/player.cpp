#include "player.h"

void Player::initSprite()
{
    image = new QPixmap();
    if (!image->load("C:/Egyetem/Allamvizsga/images/mouse.png")) qDebug() << "PLAYER::ERROR::Could not load image for QPixmap\n";
    this->setPixmap(*image);
}

Player::Player(Tile*** map, int mapRows, int mapCols, float posX, float posY)
{
    // [EN] init sprite call
    initSprite();

    this->map = map;
    this->mapRows = mapRows;
    this->mapCols = mapCols;

    this->setPos(posX * TILE_SIZE, posY * TILE_SIZE);
    this->mapCoordI = posY;
    this->mapCoordJ = posX;

    this->canMove = new bool[4];
    this->updateCanMove();

    this->transitionFrames = 5;
    this->currentFrame = 0;
    this->timer = new QTimer();

    this->direction = STOP;

    connect(timer, &QTimer::timeout, this, [&]()
    {
        switch (this->direction)
        {
        case LEFT:
            if (currentFrame != transitionFrames)
            {
                ++currentFrame;
                this->setX(this->pos().x() - TILE_SIZE / transitionFrames);
            }
            else this->direction = STOP;
            break;
        case RIGHT:
            if (currentFrame != transitionFrames)
            {
                ++currentFrame;
                this->setX(this->pos().x() + TILE_SIZE / transitionFrames);
            }
            else this->direction = STOP;
            break;
        case UP:
            if (currentFrame != transitionFrames)
            {
                ++currentFrame;
                this->setY(this->pos().y() - TILE_SIZE / transitionFrames);
            }
            else this->direction = STOP;
            break;
        case DOWN:
            if (currentFrame != transitionFrames)
            {
                ++currentFrame;
                this->setY(this->pos().y() + TILE_SIZE / transitionFrames);
            }
            else this->direction = STOP;
            break;
        }
    });

    this->timer->start(30);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "PLAYER::KeyPressed::Code:" << event->key();

    if (direction < STOP) return;

    switch (event->key())
    {
    case Qt::Key_A:
        if (canMove[LEFT])
        {
            currentFrame = 0;
            this->direction = LEFT;
            this->mapCoordJ -= 1;
        }
        break;

    case Qt::Key_D:
        if (canMove[RIGHT])
        {
            currentFrame = 0;
            this->direction = RIGHT;
            this->mapCoordJ += 1;
        }
        break;

    case Qt::Key_W:
        if (canMove[UP])
        {
            currentFrame = 0;
            this->direction = UP;
            this->mapCoordI -= 1;
        }
        break;

    case Qt::Key_S:
        if (canMove[DOWN])
        {
            currentFrame = 0;
            this->direction = DOWN;
            this->mapCoordI += 1;
        }
        break;
    }

    qDebug() << this->x() << this->y();
    qDebug() << mapCoordI << mapCoordJ;
    updateCanMove();

    qDebug() << "left:" << canMove[0] << "right:" << canMove[1] << "up:" << canMove[2] << "down:" << canMove[3];
}

void Player::updateCanMove()
{
    if (map == nullptr)
    {
        qDebug() << "PLAYER::updateCanMove::ERROR::No map found exception.";
        return;
    }

    // [EN] movement restriction for I axis
    if (mapCoordI > 0 && mapCoordI < (int)mapRows - 1)
    {
        if (map[mapCoordI - 1][mapCoordJ]->getState() == Tile::UNPASSABLE) canMove[2] = false;
        else canMove[2] = true;
        if (map[mapCoordI + 1][mapCoordJ]->getState() == Tile::UNPASSABLE) canMove[3] = false;
        else canMove[3] = true;
    }
    else if (mapCoordI == 0) canMove[2] = false;
    else if (mapCoordI == (int)mapRows - 1) canMove[3] = false;

    // [EN] movement restriction for J aXis
    if (mapCoordJ > 0 && mapCoordJ < (int)mapCols - 1)
    {
        if (map[mapCoordI][mapCoordJ - 1]->getState() == Tile::UNPASSABLE) canMove[0] = false;
        else canMove[0] = true;
        if (map[mapCoordI][mapCoordJ + 1]->getState() == Tile::UNPASSABLE) canMove[1] = false;
        else canMove[1] = true;
    }
    else if (mapCoordJ == 0) canMove[0] = false;
    else if (mapCoordJ == (int)mapCols - 1) canMove[1] = false;
}











