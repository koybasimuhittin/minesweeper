#include "mainMenu.h"
#include <QApplication>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{

    // Set up the GIF background
    backgroundLabel = new QLabel(this);
    movie = new QMovie(":/background.gif");  // Set the path to your GIF file
    backgroundLabel->setMovie(movie);
    movie->start();

    // Ensure the background label covers the entire widget
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    backgroundLabel->setFixedSize(1920, 1080);
    backgroundLabel->setGeometry(0, 0, 1920, 1080);

    // Set up the transparent layer
    transparentLayer = new QLabel(this);
    transparentLayer->setFixedSize(1920, 1080);
    transparentLayer->setStyleSheet("background-color: rgba(0, 0, 0, 220);"); // Set black background with 50% opacity

    // Set up button
    easyButton = new QPushButton("Easy (10x10)", this);
    easyButton->setFixedSize(200, 50); // Set button size
    easyButton->setStyleSheet("background-color: gray;");

    mediumButton = new QPushButton("Medium (15x15)", this);
    mediumButton->setFixedSize(200, 50); // Set button size
    mediumButton->setStyleSheet("background-color: gray;");

    hardButton = new QPushButton("Hard (20x20)", this);
    hardButton->setFixedSize(200, 50); // Set button size
    hardButton->setStyleSheet("background-color: gray;");

    quitButton = new QPushButton("Quit", this);
    quitButton->setFixedSize(200, 50); // Set button size
    quitButton->setStyleSheet("background-color: #3d3838;");



    // Position the button at the center of the widget

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setLoops(-1);

    // Create a layout for the buttons
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(easyButton);
    buttonLayout->addWidget(mediumButton);
    buttonLayout->addWidget(hardButton);
    buttonLayout->addWidget(quitButton);

    // Set the layout alignment to center

    // Set up the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    buttonLayout->setAlignment(Qt::AlignCenter);

    // Set the main layout for the widget
    setLayout(mainLayout);
    // Set the source and volume for the player
    player->setSource(QUrl::fromLocalFile("/Users/muhittinkoybasi/Desktop/minesweeper/sound.mp3"));
    audioOutput->setVolume(10);
    player->play();

    // Create mute/unmute button
    muteButton = new QPushButton(this);
    muteButton->setFixedSize(30, 30);
    muteButton->setStyleSheet("QPushButton { border-image: url(:/sound/mute.png); background-color:white; border-radius: 5px; margin: 5px;}"); // Set the unmute icon

    connect(muteButton, &QPushButton::clicked, this, &MainMenu::toggleSoundSlot);
    connect(quitButton, &QPushButton::clicked, this, &MainMenu::quitGameSlot);
}

void MainMenu::toggleSoundSlot()
{
    if (audioOutput->isMuted()) {
        audioOutput->setMuted(false); // Unmute the sound
        muteButton->setStyleSheet("QPushButton { border-image: url(:/sound/mute.png); background-color:white; border-radius: 5px; margin: 5px;}"); // Set the mute icon
    } else {
        audioOutput->setMuted(true); // Mute the sound
        muteButton->setStyleSheet("QPushButton { border-image: url(:/sound/unmute.png); background-color:white; border-radius: 5px; margin: 5px;}"); // Set the unmute icon
    }
}

void MainMenu::quitGameSlot()
{
    QApplication::quit(); // Close the application
}

QPushButton* MainMenu::getEasyButton() const
{
    return easyButton;
}

QPushButton* MainMenu::getMediumButton() const
{
    return mediumButton;
}

QPushButton* MainMenu::getHardButton() const
{
    return hardButton;
}



