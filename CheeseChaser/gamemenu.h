#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "game.h"

class GameMenu : public QWidget
{
    Q_OBJECT

// [EN] private members
    QVBoxLayout* mainLayout;
    QPushButton* gameStartButton;
    QPushButton* gameExitButton;

// [EN] private function
    void initVariables();

public:
// [EN] constructor
    GameMenu();

};

#endif // GAMEMENU_H
