#include "mainmenu.h"

MainMenu::MainMenu()
{
    initVariables();
    setUpConnects();

    // for testing settings
    if(!settings->getInstance()->readOptionsFromJson()); //qDebug() << "Could not read Settings.json file.";
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
    optionsButtonLayout = new QHBoxLayout();
    startButton = new QPushButton(tr("START"));
    exitButton = new QPushButton(tr("EXIT"));
    optionsButton = new QPushButton(tr("OPTIONS"));
    mapNamesComboBox = new QComboBox();
    saveSettingsButton = new QPushButton(tr("SAVE"));
    backSettingsButton = new QPushButton(tr("BACK"));

    // [EN] layouts
    buttonsLayout->addWidget(startButton, Qt::AlignCenter);
    buttonsLayout->addWidget(optionsButton, Qt::AlignCenter);
    buttonsLayout->addWidget(exitButton, Qt::AlignCenter);
    optionsLayout->addWidget(mapNamesComboBox, Qt::AlignHCenter);
    optionsButtonLayout->addWidget(backSettingsButton, Qt::AlignVCenter);
    optionsButtonLayout->addWidget(saveSettingsButton, Qt::AlignVCenter);
    optionsLayout->addLayout(optionsButtonLayout);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(optionsLayout);
    setLayout(mainLayout);

    // [EN] window properties
    resize(SIZE_SMALL);
    mainLayout->setMargin(8);
    buttonsLayout->setMargin(16);
    optionsLayout->setMargin(16);

    // other
    mapNamesComboBox->hide();
    saveSettingsButton->hide();
    backSettingsButton->hide();
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
        if (!optionsAreVisible)
        {
            // show options
            mapNamesComboBox->show();
            saveSettingsButton->show();
            backSettingsButton->show();

            // hide main menu
            startButton->hide();
            optionsButton->hide();
            exitButton->hide();

            optionsAreVisible = true;
        }
    });
    connect(backSettingsButton, &QPushButton::clicked, [&]()
    {
        if (optionsAreVisible)
        {
            // hide options
            mapNamesComboBox->hide();
            saveSettingsButton->hide();
            backSettingsButton->hide();

            // show main menu
            startButton->show();
            optionsButton->show();
            exitButton->show();

            optionsAreVisible = false;
        }
    });
    connect(mapNamesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&]()
    {
    });
    connect(saveSettingsButton, &QPushButton::clicked, [&]()
    {
        Settings::getInstance()->setSelectedMapNameIndex(mapNamesComboBox->currentIndex());
        settings->saveSettings(mapNamesComboBox->itemText(mapNamesComboBox->currentIndex()));
    });
}

void MainMenu::setStyle()
{
    setStyleSheet(mainBackgroungStyleSheet);
    startButton->setStyleSheet(buttonsStyleSheet);
    optionsButton->setStyleSheet(buttonsStyleSheet);
    exitButton->setStyleSheet(buttonsStyleSheet);
    mapNamesComboBox->setStyleSheet(comboBoxStyleSheet);
    backSettingsButton->setStyleSheet(buttonsStyleSheet);
    saveSettingsButton->setStyleSheet(buttonsStyleSheet);
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


