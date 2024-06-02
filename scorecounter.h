// ScoreCounter.h

#ifndef SCORECOUNTER_H
#define SCORECOUNTER_H

#include <QObject>

class ScoreCounter : public QObject
{
    Q_OBJECT

public:
    explicit ScoreCounter(QObject *parent = nullptr);
    static int m_score;

    int getScore() const;

public slots:
    static void increaseScore();

private:
};


#endif // SCORECOUNTER_H
