#include "mytimer.h"

MyTimer::MyTimer()
{
    timer = new QTimer(this);
    label = new QLabel("Time (secs): 0");
    counter = 0;

    // setup signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    timer->start(1000);
}

void MyTimer::MyTimerSlot()
{
    counter += 1;
    label->setText("Time (secs): " + QString::number(this->counter));

    if (counter >= 100) {
        this->timer->stop();
        QMessageBox msgBox;
        msgBox.setText("You failed!");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
    }
}
