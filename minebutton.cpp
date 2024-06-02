#include "minebutton.h"
#include "scorecounter.h"
#include <QQueue>

const int BUTTON_W = 30;
const int BUTTON_H = 30;
QVector<MineButton*> MineButton::mineButtonMap[30];
int MineButton::ROW_COUNT;
int MineButton::COL_COUNT;
ScoreCounter counter;


MineButton::MineButton(QWidget *parent)
    : QPushButton(parent)
{
    setFixedSize(QSize(BUTTON_W, BUTTON_H));

    set_icon(emptyPath);
    // QPixmap pixmap(":/assets/empty.png");
    // Scale the pixmap to the button size
    // QPixmap scaledPixmap = pixmap.scaled(BUTTON_W,
    //                                      BUTTON_H,
    //                                      Qt::KeepAspectRatio,
    //                                      Qt::SmoothTransformation);
    // QIcon ButtonIcon(scaledPixmap);

    // setIcon(ButtonIcon);
    // setIconSize(QSize(BUTTON_W, BUTTON_H)); // Ensure the icon size matches the button size
    // setAutoFillBackground(true);
    connect(this, &QPushButton::clicked, this, &MineButton::empty_bfs);


    }


void MineButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        // If the right button is pressed, call update_flag()
        update_flag();
    } else {
        // Otherwise, pass the event back to the base class
        QPushButton::mousePressEvent(event);
    }
}
void MineButton::empty_bfs(){

    QQueue<MineButton*> queue;
    MineButton* current;


    queue.enqueue(this);
    bool** visited = new bool*[30];
    for (int i = 0; i < 30; ++i) {
        visited[i] = new bool[30];
        for (int j = 0; j < 30; j++){
            visited[i][j] = false;
        }
    }

    while (!queue.isEmpty()){
        current = queue.dequeue();
        counter.increaseScore();
        visited[current->row][current->col] = true;
        current->reveal_button();
        if (current->number > 0){
            continue;
        }


        for (int i = -1 ; i <=1 ; i++){
            for (int j = -1 ; j <=1 ; j++){
                if (i == 0 && j == 0){
                    continue;
                }
                int newRow = current->row + i;
                int newCol = current->col + j;

                // Check if the new indices are within the bounds of the array
                if (newRow >= 0 && newRow < this->ROW_COUNT && newCol >= 0 && newCol < this->COL_COUNT && !visited[newRow][newCol]) {
                    if (this->mineButtonMap[newRow][newCol]->number < 9){
                        visited[newRow][newCol] = true;
                        queue.enqueue(this->mineButtonMap[newRow][newCol]);
                    }
                }
            }
        }
    }
}

void MineButton::reveal_button(){
    isClicked = true;
    QString real_icon_path = iconPaths.at(number);
    set_icon(real_icon_path);
    emit(scoreChanged(counter.getScore()));
}

void MineButton::update_flag(){
    if (!isClicked){
        QString iconPath;
        if (!isFlagged){
            iconPath = flagPath;

        }
        else{
            iconPath = emptyPath;
        }
        set_icon(iconPath);
        isFlagged = !isFlagged;
    }
}



void MineButton::set_icon(QString icon_path){
    QPixmap pixmap(icon_path);

    // Scale the pixmap to the button size
    QPixmap scaledPixmap = pixmap.scaled(BUTTON_W,
                                         BUTTON_H,
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);
    QIcon ButtonIcon(scaledPixmap);

    setIcon(ButtonIcon);
    setIconSize(QSize(BUTTON_W, BUTTON_H)); // Ensure the icon size matches the button size
    setAutoFillBackground(true);
    update();
}

// void ColorButton::change_color()
// {
//     QPalette pal = palette();
//     int color = rand() % 3;
//     if (color == 0) {
//         this->color = "blue";
//         pal.setColor(QPalette::Button, QColor(Qt::blue));
//     } else if (color == 1) {
//         this->color = "red";
//         pal.setColor(QPalette::Button, QColor(Qt::red));
//     } else {
//         this->color = "green";
//         pal.setColor(QPalette::Button, QColor(Qt::green));
//     }
//     setFlat(true);
//     setAutoFillBackground(true);
//     setPalette(pal);
//     update();
// }
