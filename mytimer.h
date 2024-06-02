#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include <QLabel>
#include <QMessageBox>

    class MyTimer : public QObject
{
    Q_OBJECT

public:
    MyTimer();
    QTimer *timer;
    QLabel *label;
    int counter;

public slots:
    void MyTimerSlot();
};

#endif // MYTIMER_H
