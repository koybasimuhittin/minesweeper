#include "game.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMovie>
#include <QQueue>
#include <QTime>
#include <QTimer>
#include "mineButton.h"
#include <scoreBoard.h>

const double DENSITY = 0.1; // constant coefficient to calculate mine number

int mineCount;

Game::Game(QWidget *parent)
    : QWidget(parent)
{
    std::srand(static_cast<unsigned int>(
        std::time(nullptr))); // Use current time as seed for random generator
    msgBox->setStandardButtons(QMessageBox::Ok); // initialize the messagebox with default ok button

    // Set up the vertical layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create a QLabel for displaying the time
    timeLabel = new QLabel(this);
    timeLabel->setStyleSheet("QLabel { color: red; font-size: 20px; }"); // Set text color to red
    updateTime(); // Update the time label initially

    // Create a timer to update the time label every second
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateTime);
    timer->start(1000); // Update every 1000 ms (1 second)

    // Add the time label to the layout and align it to the top right corner of the center
    layout->addWidget(timeLabel, 0, Qt::AlignTop | Qt::AlignRight);
    layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Create a game info widget which holds score, hint button and restart button
    gameInfoWidget = new QWidget();
    layout->addWidget(gameInfoWidget);

    QHBoxLayout *gameInfoLayout = new QHBoxLayout(gameInfoWidget);
    gameInfoLayout->setAlignment(Qt::AlignCenter | Qt::AlignRight);

    gameInfoWidget->setLayout(gameInfoLayout);

    scoreBoard = new ScoreBoard(gameInfoWidget);
    QObject::connect(this, &Game::increaseTheScore, scoreBoard, &ScoreBoard::increaseScore);

    QPushButton *restartButton = new QPushButton("Restart");
    gameInfoLayout->addWidget(restartButton);
    restartButton->setFixedWidth(60);

    QPushButton *hintButton = new QPushButton("Hint");
    gameInfoLayout->addWidget(hintButton);
    hintButton->setFixedWidth(60);

    // connect the restart button's clicked signal to the restart slot of the Game class
    QObject::connect(restartButton, &QPushButton::clicked, this, &Game::restart);
    // connect the hint button's clicked signal to the findOrApply slot of the Game class
    QObject::connect(hintButton, &QPushButton::clicked, this, &Game::findOrApplyHint);

    QWidget *mineWidget = new QWidget(); // widget holding the game area
    layout->addWidget(mineWidget); // add to the layout

    mineLayout = new QGridLayout(mineWidget);

    mineLayout->setAlignment(
        Qt::AlignHCenter); // Center the grid layout within the horizontal layout
    mineLayout->setHorizontalSpacing(0);

    mineWidget->setLayout(mineLayout);

    button = new QPushButton("Go Main Menu", this);
    layout->addWidget(button);

    // confettiLabel = new QLabel(this);
    // movie = new QMovie(":/confetti.gif");  // Set the path to your GIF file
    // confettiLabel->setMovie(movie);
    // movie->start();
    // confettiLabel->setFixedSize(1920, 1080);
    // confettiLabel->setGeometry(-200, 0, 1920, 1080);

    // confettiLabel->setScaledContents(true);
    // confettiLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    setLayout(layout);
}

void Game::updateTime()
{
    // Update the time counter and convert it to a formatted string
    timeCounter++;
    QString timeText = QString("%1:%2:%3")
                           .arg(timeCounter / 3600, 2, 10, QChar('0'))
                           .arg((timeCounter / 60) % 60, 2, 10, QChar('0'))
                           .arg(timeCounter % 60, 2, 10, QChar('0'));

    // Update the time label
    if (displayTime) {
        timeLabel->setText(timeText);
    }
}
// Clears the time counter for the next game
void Game::clearTimeCounter()
{
    timeCounter = 0;
    displayTime = true;
}

// Clears the game related informations for the next game
void Game::clearGame()
{
    scoreBoard->clearScore();
    displayTime = false;
    timeLabel->setText("00:00:00");

    while (mineLayout->count()) {
        QWidget *widget = mineLayout->itemAt(0)->widget();
        if (widget) {
            mineLayout->removeWidget(widget);
            delete widget;
        }
    }
}

// set the current level of the game and calculates the mine count according to level
void Game::setLevel(Level l)
{
    level = l;
    if (level == Easy) {
        rowSize = colSize = 10;
    } else if (level == Medium) {
        rowSize = colSize = 15;
    } else if (level == Hard) {
        rowSize = colSize = 20;
    }

    mineCount = rowSize * colSize * DENSITY;
}

// checks if the coordinates are outside of the game area or not
bool Game::isValid(int x, int y)
{
    return (x >= 0 && x < rowSize && y >= 0 && y < colSize);
}

void Game::handleMineClicked(int x, int y)
{
    // if game is finished there aren no click to the buttons
    if (gameStatus != Ongoing)
        return;

    // if mine really clicked
    if (mineButtonVector[x][y]->number == 9) {

        // set the game status lose and stop the timer
        setGameStatus(Lose);
        displayTime = false; // still continues displaying just stops counting

        // reveal the other mines
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                mineButtonVector[i][j]->setClickable(false);
                if (mineButtonVector[i][j]->number == 9) {
                    mineButtonVector[i][j]->reveal();
                } else if (mineButtonVector[i][j]->isFlagged) {
                    mineButtonVector[i][j]->setWrongFlagged();
                }
            }
        }

        // alert the message box with lose information
        msgBox->setText("You lose!");
        msgBox->exec();
    }
}

// initialize the game board
void Game::initializeGame()
{
    // set the game status ongoing
    setGameStatus(Ongoing);

    // clear hintFound
    hintFound = false;

    // initialize mapLocations with using random function
    mineMap = new bool *[rowSize];
    for (int i = 0; i < colSize; ++i) {
        mineMap[i] = new bool[rowSize];
        for (int j = 0; j < colSize; j++) {
            mineMap[i][j] = false;
        }
    }

    for (int i = 0; i < mineCount; i++) {
        int randomRow = std::rand() % rowSize;    // Random row index
        int randomColumn = std::rand() % colSize; // Random column index

        while (mineMap[randomRow][randomColumn]) {
            randomRow = std::rand() % rowSize; // Random row index
            randomColumn = std::rand() % colSize;
        }

        mineMap[randomRow][randomColumn] = true;
    }


    mineButtonVector.resize(rowSize); // Resize the outer vector to rowSize

    for (int i = 0; i < rowSize; ++i) {
        mineButtonVector[i].resize(colSize); // Resize each inner vector to colSize
    }

    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {

            // create mine button object
            MineButton *randButton = new MineButton();
            randButton->row = row;
            randButton->col = col;

            if (mineMap[row][col]) {
                randButton->number = 9;
            } else {
                int sum = 0;

                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (i == 0 && j == 0) {
                            continue;
                        }
                        int newRow = row + i;
                        int newCol = col + j;

                        // Check if the new indices are within the bounds of the array
                        if (isValid(newRow, newCol)) {
                            // find the neighbour mine count
                            sum += mineMap[newRow][newCol];
                        }
                    }
                }

                randButton->number = sum;
            }

            // connect the neccesary signals
            QObject::connect(randButton,
                             &MineButton::scoreIncreased,
                             this,
                             &Game::handleScoreIncreased);
            QObject::connect(randButton, &MineButton::revealStarted, this, &Game::revealButtons);
            QObject::connect(randButton, &MineButton::mineClicked, this, &Game::handleMineClicked);
            mineButtonVector[row][col] = randButton;
            mineLayout->addWidget(randButton, row, col);
        }
    }
    //gameInfoWidget->setFixedWidth(mineLayout->sizeHint().width());
}

void Game::revealButtons(int x, int y)
{
    // hint should be cleared if any buttons are revealing
    hintFound = false;

    // if the game ended do not continue to revealing
    if (gameStatus != Ongoing)
        return;


    // bfs to reach all empty cells one their neighbours which are only one cell away
    QQueue<MineButton *> queue;
    MineButton *current;
    queue.enqueue(mineButtonVector[x][y]);

    bool **visited = new bool *[rowSize];
    for (int i = 0; i < colSize; ++i) {
        visited[i] = new bool[rowSize];
        for (int j = 0; j < colSize; j++) {
            visited[i][j] = false;
        }
    }

    while (!queue.isEmpty()) {
        current = queue.dequeue();
        current->reveal();
        visited[current->row][current->col] = true;
        if (current->number > 0) {
            continue;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                int newRow = current->row + i;
                int newCol = current->col + j;

                if (isValid(newRow, newCol) && !visited[newRow][newCol]) {
                    if (mineButtonVector[newRow][newCol]->number < 9) {
                        queue.enqueue(mineButtonVector[newRow][newCol]);
                    }
                }
            }
        }
    }

    // check if the game ends
    int score = scoreBoard->getScore();
    if (score == rowSize * colSize - mineCount && gameStatus == Ongoing) {

        // set the status and stop the timer
        setGameStatus(Win);
        displayTime = false;

        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                mineButtonVector[i][j]->setClickable(false);

                // display flag for each mine (see: https://minesweeper.online/game/3417713902 the last 2 second should be enough)
                if (mineButtonVector[i][j]->number == 9) {
                    mineButtonVector[i][j]->set_icon(mineButtonVector[i][j]->flagPath);
                }
            }
        }

        // alert the win text
        msgBox->setText("You won!");
        msgBox->exec();
    }
}

// setter function for game status
void Game::setGameStatus(GameStatus g)
{
    gameStatus = g;
}

// bearer signal which carries the actual signal coming from mineButton through the scoreboard
void Game::handleScoreIncreased()
{
    emit increaseTheScore();
}

// restart function to clear the board and set ready for the next game
void Game::restart()
{
    clearGame();
    clearTimeCounter();
    initializeGame();
}

// function to find hint or if there is a hint found last click reveals the hint
void Game::findOrApplyHint()
{
    // if the game is not ongoing do not continue
    if (gameStatus != Ongoing)
        return;

    // if there is already a hint reveal the coordinats
    if (hintFound) {
        revealButtons(hintX, hintY);
        hintFound = false;
        return;
    }

    hintFound = false;
    // idea:
    // go through each revealed cell and check its neighbours
    // if unrevealed neighbours equals to the cell's number marks each unrevealed cells as bomb
    // repeats this proces untill there is no new bomb mark

    //check every cell if unrevealed neighbours count > cell's number and cell's number is equal
    //to neighbour bomb marks count at least one of the non marked cell is free to click

    bool **bombMap = new bool *[rowSize];
    for (int i = 0; i < colSize; ++i) {
        bombMap[i] = new bool[rowSize];
        for (int j = 0; j < colSize; j++) {
            bombMap[i][j] = false;
        }
    }

    bool anyBombFound = true;
    while (anyBombFound) {
        anyBombFound = false;
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                int emptyCellSum = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dy == dx && dx == 0)
                            continue;

                        int row = i + dx;
                        int col = j + dy;

                        if (!isValid(row, col))
                            continue;

                        if (!mineButtonVector[row][col]->isClicked
                            || (!mineButtonVector[row][col]->isClicked
                                && mineButtonVector[row][col]->number == 9)
                            || (bombMap[row][col])) {
                            emptyCellSum += 1;
                        }
                    }
                }
                if (mineButtonVector[i][j]->number > 0 && mineButtonVector[i][j]->number < 9
                    && emptyCellSum == mineButtonVector[i][j]->number) {
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dy == dx && dx == 0)
                                continue;

                            int row = i + dx;
                            int col = j + dy;

                            if (!isValid(row, col))
                                continue;

                            if ((!mineButtonVector[row][col]->isClicked) && !bombMap[row][col]) {
                                bombMap[row][col] = true;
                                anyBombFound = true;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (!mineButtonVector[i][j]->isClicked)
                continue;
            int emptyCellSum = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dy == dx && dx == 0)
                        continue;

                    int row = i + dx;
                    int col = j + dy;

                    if (!isValid(row, col))
                        continue;

                    if (bombMap[row][col]) {
                        emptyCellSum += 1;
                    }
                }
            }
            if (mineButtonVector[i][j]->number > 0 && mineButtonVector[i][j]->number < 9
                && emptyCellSum == mineButtonVector[i][j]->number) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dy == dx && dx == 0)
                            continue;

                        int row = i + dx;
                        int col = j + dy;

                        if (!isValid(row, col) || mineButtonVector[row][col]->isClicked)
                            continue;

                        if (!bombMap[row][col]) {
                            hintFound = true;
                            hintX = row;
                            hintY = col;
                            mineButtonVector[row][col]->set_icon(
                                mineButtonVector[row][col]->hintPath);
                            return;
                        }
                    }
                }
            }
        }
    }
}

QPushButton *Game::getButton() const
{
    return button;
}
