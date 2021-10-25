#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

/*
 * Help from:   https://evileg.com/en/post/92/
 *              https://www.youtube.com/watch?v=8ntEQpg7gck
 */

class Sprite : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void initSprite();
    QRectF boundingRect() const;
    QTimer* timer;
    QPixmap* spriteImage;
    unsigned int currentFrame;

public:
    explicit Sprite(QObject *parent = nullptr);

signals:

private slots:
    void nextFrame(); // [EN] Slot for turning images into QPixmap

};

#endif // SPRITE_H
