#include "minebutton.h"
#include <QQueue>

const int BUTTON_W = 30;
const int BUTTON_H = 30;

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
    connect(this, &QPushButton::clicked, this, &MineButton::startReveal);
}

void MineButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        if (!clickable)
            return;
        update_flag();
    } else {
        // Otherwise, pass the event back to the base class
        QPushButton::mousePressEvent(event);
    }
}

void MineButton::reveal()
{
    if (isClicked)
        return;
    if (number != 9) {
        emit scoreIncreased();
    }
    isClicked = true;
    QString real_icon_path = iconPaths.at(number);
    set_icon(real_icon_path);
}

void MineButton::update_flag()
{
    if (!isClicked && clickable) {
        QString iconPath;
        if (!isFlagged) {
            iconPath = flagPath;

        } else {
            iconPath = emptyPath;
        }
        set_icon(iconPath);
        isFlagged = !isFlagged;
    }
}

void MineButton::set_icon(QString icon_path)
{
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

void MineButton::startReveal()
{
    if (isClicked && !clickable)
        return;
    emit(revealStarted(row, col));
    if (number == 9) {
        emit(mineClicked(row, col));
    }
}

void MineButton::setWrongFlagged()
{
    set_icon(wrongFlagPath);
}

void MineButton::setClickable(bool state)
{
    clickable = state;
}
