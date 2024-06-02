// ScoreCounter.cpp

#include "scoreBoard.h".h "

ScoreBoard::ScoreBoard(QWidget *parent)
    : QLabel(parent)
{
    clearScore(); // clear the score and sets for the new game
}

void ScoreBoard::clearScore()
{
    // show 0 initially
    score = 0;
    setText(QString("Score: 0"));
}

// increase score slot triggered buy Game class
void ScoreBoard::increaseScore()
{
    score = score + 1;
    setText(QString("Score: ") + QString::number(score));
}

// returns the integer value of the score
int ScoreBoard::getScore()
{
    return score;
}
