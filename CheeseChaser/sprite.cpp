#include "sprite.h"

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->initSprite();
    painter->drawPixmap(-10,-10, *spriteImage, currentFrame, 0, 20,20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::initSprite()
{
    this->setRect(0, 0, 100, 100);
}

QRectF Sprite::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

Sprite::Sprite(QObject *parent) : QObject(parent), QGraphicsRectItem()
{
    initSprite();
    currentFrame = 0;
    spriteImage = new QPixmap("sprite_sheet.png"); // [EN] load the image

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Sprite::nextFrame);
    timer->start(25);
}

void Sprite::nextFrame()
{
    currentFrame += 20;
    if (currentFrame >= 300 ) currentFrame = 0;
    this->update(-10,-10,20,20);
}
