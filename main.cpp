#include <QApplication>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QLabel>
#include <cstdlib>  // For std::rand() and std::srand()
#include <ctime>    // For std::time()


#include "minebutton.h"
#include "mygrid.h"
#include "scorecounter.h"

const int LEVEL = 1;
// 0 easy, 10 x 10
// 1 medium 20 x 20
// 2 hard 30 x 30

const double DENSITY = 0.1;

int ROW_COUNT = 10; // by default
int COLUMN_COUNT = 10; // by default
int MINE_COUNT = ROW_COUNT * COLUMN_COUNT * DENSITY;


// void empty_bfs(QVector<MineButton*> mineButtonMap[], MineButton* curButton){

//     QQueue<MineButton*> queue;
//     MineButton* current;


//     queue.enqueue(curButton);

//     bool** visited = new bool*[ROW_COUNT];
//     for (int i = 0; i < ROW_COUNT; ++i) {
//         visited[i] = new bool[COLUMN_COUNT];
//         for (int j = 0; j < COLUMN_COUNT; j++){
//             visited[i][j] = false;
//         }
//     }

//     while (!queue.isEmpty()){
//         current = queue.dequeue();
//         visited[current->row][current->col] = true;
//         if (current->number > 0){
//             current->reveal_button();
//             break;
//         }


//         for (int i = -1 ; i <=1 ; i++){
//             for (int j = -1 ; j <=1 ; j++){
//                 if (i == 0 && j == 0){
//                     continue;
//                 }
//                 int newRow = current->row + i;
//                 int newCol = current->col + j;

//                 // Check if the new indices are within the bounds of the array
//                 if (newRow >= 0 && newRow < ROW_COUNT && newCol >= 0 && newCol < COLUMN_COUNT && !visited[newRow][newCol]) {
//                     if (mineButtonMap[newRow][newCol]->number < 9){
//                         queue.enqueue(mineButtonMap[newRow][newCol]);
//                     }
//                 }
//             }
//         }
//     }
// }



void restart(){
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Use current time as seed for random generator

    QWidget *cw = new QWidget; // this is our main widget
    QWidget *mw = new QWidget; // this is our main widget
    QVBoxLayout *vb = new QVBoxLayout(cw);
    QHBoxLayout *hb = new QHBoxLayout(mw);
    vb->addWidget(mw);
    vb->setAlignment(Qt::AlignCenter); // Center the vertical layout

    ScoreCounter* counter = new ScoreCounter();
    QLabel *scoreLabel = new QLabel("Score : 0");
    QPushButton *restartButton = new QPushButton("Restart");

    hb->addWidget(scoreLabel);
    hb->addWidget(restartButton);

    MyGrid *gl = new MyGrid();
    gl->setAlignment(Qt::AlignCenter); // Center the grid layout within the horizontal layout
    gl->setHorizontalSpacing(0);

    QObject::connect(restartButton, &QPushButton::clicked, restart);



    switch(LEVEL){
    case 1:
        ROW_COUNT = COLUMN_COUNT = 10;
        break;
    case 2:
        ROW_COUNT = COLUMN_COUNT = 15;
        break;
    case 3:
        ROW_COUNT = COLUMN_COUNT = 20;
        break;
    default:
        ROW_COUNT = COLUMN_COUNT = 10;
    }

    bool** mineMap = new bool*[ROW_COUNT];
    for (int i = 0; i < ROW_COUNT; ++i) {
        mineMap[i] = new bool[COLUMN_COUNT];
        for (int j = 0; j < COLUMN_COUNT; j++){
            mineMap[i][j] = false;
        }
    }

    // QVector<MineButton*> mineButtonMap[ROW_COUNT];
    MINE_COUNT = ROW_COUNT * COLUMN_COUNT * DENSITY;


    for (int i = 0; i < MINE_COUNT; i++){
        int randomRow = std::rand() % ROW_COUNT;     // Random row index
        int randomColumn = std::rand() % COLUMN_COUNT; // Random column index

        while(mineMap[randomRow][randomColumn]){
            randomRow = std::rand() % ROW_COUNT;     // Random row index
            randomColumn = std::rand() % COLUMN_COUNT;
        }

        mineMap[randomRow][randomColumn] = true;
    }


    for (int row = 0; row < ROW_COUNT; row++) {
        for (int col = 0; col < COLUMN_COUNT; col++) {


            MineButton *randButton = new MineButton();
            QObject::connect(randButton, &MineButton::scoreChanged, [=](int newScore){
                scoreLabel->setText(QString("Score: %1").arg(newScore));
            });
            randButton->ROW_COUNT = ROW_COUNT;
            randButton->COL_COUNT = COLUMN_COUNT;
            randButton->row = row;
            randButton->col = col;
            randButton->mineButtonMap[row].push_back(randButton);
            if (mineMap[row][col]){
                randButton->number = 9;
            }
            else {
                int sum = 0;

                for (int i = -1 ; i <=1 ; i++){
                    for (int j = -1 ; j <=1 ; j++){
                        if (i == 0 && j == 0){
                            continue;
                        }
                        int newRow = row + i;
                        int newCol = col + j;

                        // Check if the new indices are within the bounds of the array
                        if (newRow >= 0 && newRow < ROW_COUNT && newCol >= 0 && newCol < COLUMN_COUNT) {
                            sum += mineMap[newRow][newCol];
                        }
                    }
                }

                randButton->number = sum;
            }
            gl->addWidget(randButton, row, col);
        }
    }
    vb->addLayout(gl); // Add the horizontal layout (containing the grid) to the vertical layout

    cw->setWindowTitle("MineSweeper");
    cw->show();

}

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Use current time as seed for random generator

    QApplication app(argc, argv);
    restart();
    return app.exec();
}
