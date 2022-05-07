#include "mainmenu.h"

MainMenu::MainMenu()
{
    initVariables();
    setUpConnects();

    // for testing settings
    if(!settings->getInstance()->readOptionsFromJson()) qDebug() << "Could not read JSON file!";
    setUpComboBox();

    setStyle();
}

MainMenu::~MainMenu()
{
    delete startButton;
    delete exitButton;
    delete mainLayout;
}
void MainMenu::initVariables()
{
    // [EN] pointers
    mainLayout = new QHBoxLayout();
    buttonsLayout = new QVBoxLayout();
    optionsLayout = new QVBoxLayout();
    startButton = new QPushButton(tr("START"));
    exitButton = new QPushButton(tr("EXIT"));
    optionsButton = new QPushButton(tr("OPTIONS"));
    mapNamesComboBox = new QComboBox();

    // [EN] layouts
    buttonsLayout->addWidget(startButton, Qt::AlignCenter);
    buttonsLayout->addWidget(optionsButton, Qt::AlignCenter);
    buttonsLayout->addWidget(exitButton, Qt::AlignCenter);
    optionsLayout->addWidget(mapNamesComboBox, Qt::AlignHCenter);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(optionsLayout);
    setLayout(mainLayout);

    // [EN] window properties
    resize(SIZE_SMALL);
    mainLayout->setMargin(8);
    buttonsLayout->setMargin(64);
    optionsLayout->setMargin(8);
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
    connect(mapNamesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&]()
    {
        Settings::getInstance()->setSelectedMapNameIndex(mapNamesComboBox->currentIndex());
    });
}

void MainMenu::setStyle()
{
    setStyleSheet(mainBackgroungStyleSheet);
    startButton->setStyleSheet(buttonsStyleSheet);
    optionsButton->setStyleSheet(buttonsStyleSheet);
    exitButton->setStyleSheet(buttonsStyleSheet);
    mapNamesComboBox->setStyleSheet(comboBoxStyleSheet);
}

void MainMenu::setUpComboBox()
{
    for (auto& mapName : Settings::getInstance()->getAllMapNames())
    {
        mapNamesComboBox->addItem(mapName);
    }
}

void MainMenu::returnToMenu()
{
    show();
}


