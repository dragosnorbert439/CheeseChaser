#ifndef MINIMENU_H
#define MINIMENU_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class MiniMenu : public QWidget
{
    Q_OBJECT

public:
    MiniMenu(QWidget *parent = nullptr);
    ~MiniMenu();

private:
    void initVariables();

protected:
    QVBoxLayout* mainLayout;
    QPushButton* exitButton;
    QPushButton* returnToMainMenuButton;

signals:
    void exitGame();
    void returnToMainMenu();

};

#endif // MINIMENU_H
