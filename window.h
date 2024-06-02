#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "game.h"
#include "mainMenu.h"

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private slots:
    void showMainMenu();
    void startEasyGame();
    void startMediumGame();
    void startHardGame();

private:
    QStackedWidget *stackedWidget;
    Game *game;
    MainMenu *mainMenu;
};



#endif // WINDOW_H
