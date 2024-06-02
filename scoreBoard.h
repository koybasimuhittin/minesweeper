// ScoreCounter.h

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QLabel>>

class ScoreBoard : public QLabel
{
    Q_OBJECT

public:
    ScoreBoard(QWidget *parent = nullptr);
    void clearScore();
    int getScore();

private:
    int score = 0;

public slots:
    void increaseScore();

private:
};

#endif // SCOREBOARD_H
