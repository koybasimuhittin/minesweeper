#include "minebutton.h"

const int BUTTON_W = 30;
const int BUTTON_H = 30;

MineButton::MineButton(const QString& icon_path, QWidget* parent)
    : QPushButton(parent), icon_path(icon_path) // Initialize icon_path properly
{
    setFixedSize(QSize(BUTTON_W, BUTTON_H));

    QPixmap pixmap(":/assets/empty.png");

    // Scale the pixmap to the button size
    QPixmap scaledPixmap = pixmap.scaled(BUTTON_W, BUTTON_H, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon ButtonIcon(scaledPixmap);

    setIcon(ButtonIcon);
    setIconSize(QSize(BUTTON_W, BUTTON_H)); // Ensure the icon size matches the button size

    setAutoFillBackground(true);
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
