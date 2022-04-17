#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "game.h"
#include "settings.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    QSize SIZE_SMALL = QSize(800, 600);

    MainMenu();
    ~MainMenu();

private:
    Game* game;
    Settings* settings;

    QVBoxLayout* mainLayout;
    QPushButton* startButton;
    QPushButton* exitButton;
    QPushButton* optionsButton;

    void initVariables();
    void initGame();
    void setUpConnects();
    void setStyle();

private slots:
    void returnToMenu();

};

#endif // MAINMENU_H
