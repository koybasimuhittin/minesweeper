// ScoreCounter.cpp

#include "scoreBoard.h".h "

ScoreBoard::ScoreBoard(QWidget *parent)
    : QLabel(parent)
{
    clearScore();
}

void ScoreBoard::clearScore()
{
    score = 0;
    setText(QString("Score: 0"));
}

void ScoreBoard::increaseScore()
{
    score = score + 1;
    setText(QString("Score: ") + QString::number(score));
}

int ScoreBoard::getScore()
{
    return score;
}
