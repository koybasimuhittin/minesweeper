#include <QApplication>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>

#include "minebutton.h"
#include "mygrid.h"
#include "scorecounter.h"

const int ROW_COUNT = 20;
const int COLUMN_COUNT = 20;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *cw = new QWidget; // this is our main widget
    QVBoxLayout *vb = new QVBoxLayout(cw);
    vb->setAlignment(Qt::AlignCenter); // Center the vertical layout

    ScoreCounter* counter = new ScoreCounter();
    QLabel *scoreLabel = new QLabel("Score : 0");
    QPushButton *increaseButton = new QPushButton("Increase Score");
    QPushButton *decreaseButton = new QPushButton("Decrease Score");

    vb->addWidget(scoreLabel);
    vb->addWidget(increaseButton);
    vb->addWidget(decreaseButton);

    MyGrid *gl = new MyGrid();
    gl->setAlignment(Qt::AlignCenter); // Center the grid layout within the horizontal layout
    gl->setHorizontalSpacing(0);

    QObject::connect(increaseButton, &QPushButton::clicked, counter, &ScoreCounter::increaseScore);
    QObject::connect(counter, &ScoreCounter::scoreChanged, [=](int newScore){
        scoreLabel->setText(QString("Score: %1").arg(newScore));
    });
    for (int row = 0; row < ROW_COUNT; row++) {
        for (int col = 0; col < COLUMN_COUNT; col++) {

            MineButton *randButton = new MineButton(":/assets/empty.png");
            if (row == 0 && col == 0){
                randButton->number = 3;
            }
            gl->addWidget(randButton, row, col);
        }
    }
    vb->addLayout(gl); // Add the horizontal layout (containing the grid) to the vertical layout

    cw->setWindowTitle("MineSweeper");
    cw->show();

    return app.exec();
}
