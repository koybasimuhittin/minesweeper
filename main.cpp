#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include "minebutton.h"
#include "mytimer.h"
#include "mygrid.h"

const int ROW_COUNT = 20;
const int COLUMN_COUNT = 20;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *cw = new QWidget; // this is our main widget
    QVBoxLayout *vb = new QVBoxLayout(cw);
    vb->setAlignment(Qt::AlignCenter); // Center the vertical layout

    MyTimer mt;

    MyGrid *gl = new MyGrid(mt.timer);
    gl->setAlignment(Qt::AlignCenter); // Center the grid layout within the horizontal layout
    gl->setHorizontalSpacing(0);

    for (int row = 0; row < ROW_COUNT; row++)
    {
        for (int col = 0; col < COLUMN_COUNT; col++)
        {
            MineButton *randButton = new MineButton(":/assets/empty.png");
            gl->addWidget(randButton, row, col);
        }
    }

    vb->addWidget(mt.label);
    vb->addLayout(gl); // Add the horizontal layout (containing the grid) to the vertical layout

    cw->setWindowTitle("MineSweeper");
    cw->show();

    return app.exec();
}
