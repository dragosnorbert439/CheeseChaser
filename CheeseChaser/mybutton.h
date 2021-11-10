#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "tile.h"

class MyButton : public QWidget, public QGraphicsPixmapItem
{
    Q_OBJECT

// [EN] Private members
    QPixmap* image;
    int buttonType;

// [EN] Private functions
    void initSprite(int);

    public:
// [EN] Constructor
    MyButton(int type, float x = 0.f, float y = 0.f);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

// [EN] button type
    enum { START, QUIT };

// [EN]
signals:
    void clicked();

};


#endif // MYBUTTON_H
