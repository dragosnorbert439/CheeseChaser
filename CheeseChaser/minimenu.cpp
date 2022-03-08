#include "minimenu.h"

MiniMenu::MiniMenu(QWidget *parent) : QWidget{parent}
{
    initVariables();
}

MiniMenu::~MiniMenu()
{
    delete returnToMainMenuButton;
    delete exitButton;
    delete mainLayout;
}

void MiniMenu::initVariables()
{
    mainLayout = new QVBoxLayout();
    exitButton = new QPushButton(tr("EXIT GAME"));
    returnToMainMenuButton = new QPushButton(tr("RETURN TO MAIN MENU"));

    mainLayout->addWidget(returnToMainMenuButton, Qt::AlignHCenter);
    mainLayout->addWidget(exitButton, Qt::AlignHCenter);

    setLayout(mainLayout);
}

