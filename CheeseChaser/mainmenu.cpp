#include "mainmenu.h"

MainMenu::MainMenu()
{
    initVariables();
    setUpConnects();
    setStyle();

    // for testing settings
    if(!settings->getInstance()->readOptionsFromJson()) qDebug() << "Could not read JSON file!";
}

MainMenu::~MainMenu()
{
    settings->deleteInstance();
    delete startButton;
    delete exitButton;
    delete mainLayout;
}
void MainMenu::initVariables()
{
    // [EN] pointers
    mainLayout = new QVBoxLayout();
    startButton = new QPushButton(tr("START"));
    exitButton = new QPushButton(tr("EXIT"));
    optionsButton = new QPushButton(tr("OPTIONS"));

    // [EN] layout
    mainLayout->addWidget(startButton, Qt::AlignCenter);
    mainLayout->addWidget(optionsButton, Qt::AlignCenter);
    mainLayout->addWidget(exitButton, Qt::AlignCenter);
    setLayout(mainLayout);

    // [EN] window properties
    resize(SIZE_SMALL);
    mainLayout->setMargin(64);
}

void MainMenu::initGame()
{
    game = new Game();

    // game ptr must be initialized before connecting
    connect(game, &Game::returnToMainMenu, [&]()
    {
        game->hideGame();
        show();
        disconnect(game);
    });
}

void MainMenu::setUpConnects()
{
    connect(exitButton, &QPushButton::clicked, [&](){ exit(EXIT_SUCCESS); });
    connect(startButton, &QPushButton::clicked, [&]()
    {
        hide();
        initGame();
        game->showGame();
    });
    connect(optionsButton, &QPushButton::clicked,[&]()
    {
        qDebug() << "Options button clicked";
    });
}

void MainMenu::setStyle()
{
    setStyleSheet(mainBackgroungStyleSheet);
    startButton->setStyleSheet(buttonsStyleSheet);
    optionsButton->setStyleSheet(buttonsStyleSheet);
    exitButton->setStyleSheet(buttonsStyleSheet);
}

void MainMenu::returnToMenu()
{
    show();
}


