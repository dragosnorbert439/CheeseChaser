#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QComboBox>

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

    QHBoxLayout* mainLayout;
    QVBoxLayout* buttonsLayout;
    QVBoxLayout* optionsLayout;
    QHBoxLayout* optionsButtonLayout;

    QPushButton* startButton;
    QPushButton* exitButton;
    QPushButton* optionsButton;

    QComboBox* mapNamesComboBox;
    QPushButton* saveSettingsButton;
    QPushButton* backSettingsButton;

    bool optionsAreVisible {false};

    void initVariables();
    void initGame();
    void setUpConnects();
    void setStyle();
    void setUpComboBox();

private slots:
    void returnToMenu();

};

#endif // MAINMENU_H
