#ifndef MYSCORE_H
#define MYSCORE_H

#include <QLabel>
#include <QMessageBox>

class MyScore : public QObject
{
    Q_OBJECT

public:
    MyScore();
    QTimer *score;
    QLabel *label;
    int counter;

public slots:
    void MyScoreSlot();
};

#endif // MYSCORE_H
