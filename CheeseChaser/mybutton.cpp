#include "mybutton.h"

void MyButton::initSprite(int type)
{
    this->image = new QPixmap();
    this->buttonType = type;

    switch (type)
    {
    case START:
        if (!image->load("C:/Egyetem/Allamvizsga/images/startButton1.png")) qDebug() << "MYBUTTON::ERROR::Could not load image for QPixmap\n";
        break;
    case QUIT:
        if (!image->load("C:/Egyetem/Allamvizsga/images/quitButton2.png")) qDebug() << "MYBUTTON::ERROR::Could not load image for QPixmap\n";
        break;
    default:
        qDebug() << "MYBUTTON::INITSPRITE::Incorrect parameter!";

    }

    this->setPixmap(*image);
}

MyButton::MyButton(int buttonType, float x, float y)
{
    this->setAttribute(Qt::WA_Hover, true);
    this->initSprite(buttonType);
    this->setPos(x * TILE_SIZE, y * TILE_SIZE);

}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();

    switch (this->buttonType)
    {
    case QUIT:
        exit(EXIT_SUCCESS);
        break;
    }
}

