#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <mineButton.h>
#include <QMessageBox>
#include <scoreBoard.h>

enum Level {Easy, Medium, Hard};
enum GameStatus {Lose, Ongoing, Win};

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    QPushButton* getButton() const;
    void clearTimeCounter();
    void clearGame();
    void setLevel(Level l);
    int rowSize;
    int colSize;
    bool** mineMap;
    void initializeGame();
    void setGameStatus(GameStatus);
    // QLabel *confettiLabel;

private:
    QPushButton *button;
    QLabel *timeLabel;
    void updateTime();
    int timeCounter = 0;
    bool displayTime = false;
    bool isValid(int x, int y);
    QGridLayout *mineLayout;
    QVector<QVector<MineButton*>> mineButtonVector;
    QMessageBox *msgBox = new QMessageBox();
    ScoreBoard *scoreBoard;
    QWidget *gameInfoWidget;
    void restart();
    bool hintFound = false;
    int hintX;
    int hintY;
    // QMovie *movie;

protected:
    GameStatus gameStatus = Ongoing;
    Level level = Easy;

public slots:
    void revealButtons(int x, int y);
    void handleMineClicked(int x, int y);
    void handleScoreIncreased();
    void findOrApplyHint();

signals:
    void increaseTheScore();

};



#endif // GAME_H
