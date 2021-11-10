#include "gamemenu.h"

void GameMenu::initVariables()
{
    this->mainLayout = new QVBoxLayout();
    this->gameStartButton = new QPushButton();
    this->gameExitButton = new QPushButton();

    this->gameStartButton->setText("GAME START");
    this->gameExitButton->setText("QUIT GAME");

    this->mainLayout->addWidget(this->gameStartButton, Qt::AlignCenter);
    this->mainLayout->addWidget(this->gameExitButton, Qt::AlignHCenter);

    this->setLayout(this->mainLayout);
}

GameMenu::GameMenu()
{
    this->initVariables();

    this->setGeometry(QRect(240, 400, 480, 320));

    connect(gameStartButton, &QPushButton::pressed, [&]()
    {
        Game* game = new Game;
        this->hide();
    });
    connect(gameExitButton, &QPushButton::pressed, [&]()
    {
        disconnect(gameStartButton);
        exit(0);
    });

    this->show();
}
