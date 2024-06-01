// ScoreCounter.h

#ifndef SCORECOUNTER_H
#define SCORECOUNTER_H

#include <QObject>

class ScoreCounter : public QObject
{
    Q_OBJECT

public:
    explicit ScoreCounter(QObject *parent = nullptr);

    int getScore() const;

public slots:
    void increaseScore();

signals:
    void scoreChanged(int newScore);

private:
    int m_score;
};

#endif // SCORECOUNTER_H
