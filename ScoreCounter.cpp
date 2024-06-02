// ScoreCounter.cpp

#include "scorecounter.h"
int ScoreCounter::m_score = 0;


ScoreCounter::ScoreCounter(QObject *parent)
    : QObject(parent)
{

}

int ScoreCounter::getScore() const {

    return m_score;
}


void ScoreCounter::increaseScore() {
    m_score++;
}
