#include "window.h"
#include <QResizeEvent>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    if (isFullScreen()) {
        this->setWindowState(Qt::WindowMaximized);
    } else {
        this->setWindowState(Qt::WindowFullScreen);
    }

    setMinimumSize(QSize(720, 720));

    stackedWidget = new QStackedWidget(this);
    game = new Game(this);
    mainMenu = new MainMenu(this);

    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(game);

    setCentralWidget(stackedWidget);

    // Connect buttons
    connect(game->getButton(), &QPushButton::clicked, this, &Window::showMainMenu);
    connect(mainMenu->getEasyButton(), &QPushButton::clicked, this, &Window::startEasyGame);
    connect(mainMenu->getMediumButton(), &QPushButton::clicked, this, &Window::startMediumGame);
    connect(mainMenu->getHardButton(), &QPushButton::clicked, this, &Window::startHardGame);
}

Window::~Window() {}

void Window::showMainMenu()
{
    game->clearGame();
    stackedWidget->setCurrentWidget(mainMenu);
    //mainMenu->audioOutput->setVolume(20);
}

void Window::startEasyGame()
{
    game->clearTimeCounter();
    game->setLevel(Easy);
    game->initializeGame();
    stackedWidget->setCurrentWidget(game);
    //mainMenu->audioOutput->setVolume(0);
}

void Window::startMediumGame()
{
    game->clearTimeCounter();
    game->setLevel(Medium);
    game->initializeGame();
    stackedWidget->setCurrentWidget(game);
    //mainMenu->audioOutput->setVolume(0);
}

void Window::startHardGame()
{
    game->clearTimeCounter();
    game->setLevel(Hard);
    game->initializeGame();
    stackedWidget->setCurrentWidget(game);
    //mainMenu->audioOutput->setVolume(0);
}
