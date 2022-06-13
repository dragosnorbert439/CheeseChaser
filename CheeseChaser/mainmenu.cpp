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
    saveSettingsButton = new QPushButton(tr("SAVE"));

    // [EN] layouts
    buttonsLayout->addWidget(startButton, Qt::AlignCenter);
    buttonsLayout->addWidget(optionsButton, Qt::AlignCenter);
    buttonsLayout->addWidget(exitButton, Qt::AlignCenter);
    optionsLayout->addWidget(mapNamesComboBox, Qt::AlignHCenter);
    optionsLayout->addWidget(saveSettingsButton, Qt::AlignHCenter);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(optionsLayout);
    setLayout(mainLayout);

    // [EN] window properties
    resize(SIZE_SMALL);
    mainLayout->setMargin(8);
    buttonsLayout->setMargin(64);
    optionsLayout->setMargin(8);

    // other
    mapNamesComboBox->hide();
    saveSettingsButton->hide();
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
        if (optionsAreVisible)
        {
            mapNamesComboBox->hide();
            saveSettingsButton->hide();
            optionsAreVisible = false;
        }
        else
        {
            mapNamesComboBox->show();
            saveSettingsButton->show();
            optionsAreVisible = true;
        }
    });
    connect(mapNamesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&]()
    {
    });
    connect(saveSettingsButton, &QPushButton::clicked, [&]()
    {
        qDebug() << "Save options button works!";
        Settings::getInstance()->setSelectedMapNameIndex(mapNamesComboBox->currentIndex());
        qDebug() << "Current text: " << mapNamesComboBox->itemText(mapNamesComboBox->currentIndex());
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


