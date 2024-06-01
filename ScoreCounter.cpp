// ScoreCounter.cpp

#include "scorecounter.h"

ScoreCounter::ScoreCounter(QObject *parent)
    : QObject(parent), m_score(0)
{
}

int ScoreCounter::getScore() const {
    return m_score;
}


void ScoreCounter::increaseScore() {
    m_score ++;
    emit scoreChanged(m_score);

}
