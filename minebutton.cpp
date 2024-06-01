#include "minebutton.h"

const int BUTTON_W = 30;
const int BUTTON_H = 30;

MineButton::MineButton(const QString &icon_path, QWidget *parent)
    : QPushButton(parent)
    , icon_path(icon_path) // Initialize icon_path properly
{
    setFixedSize(QSize(BUTTON_W, BUTTON_H));

    set_icon(icon_path);

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
    connect(this, &QPushButton::clicked, this, &MineButton::reveal_button);

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


void MineButton::reveal_button(){
    isClicked = true;
    QString real_icon_path = iconPaths.at(number);
    set_icon(real_icon_path);
    qDebug() << "Button clicked!";
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
