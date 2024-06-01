#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPalette>
#include <QPushButton>
#include <QMouseEvent>


class MineButton : public QPushButton
{
    Q_OBJECT

public:
    MineButton(const QString &icon_path, QWidget *parent = 0);
    QString icon_path;
    int number;
    QStringList iconPaths = {
        ":/assets/0.png",
        ":/assets/1.png",
        ":/assets/2.png",
        ":/assets/3.png",
        ":/assets/4.png",
        ":/assets/5.png",
        ":/assets/6.png",
        ":/assets/7.png",
        ":/assets/8.png"
    };
    QString flagPath = ":/assets/flag.png";
    QString minePath = ":/assets/mine.png";
    QString hintPath = ":/assets/hint.png";
    QString wrongFlagPath = ":/assets/wrong-flag.png";
    QString emptyPath = ":/assets/empty.png";
    bool isClicked = false;
    bool isFlagged = false;
protected:
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void update_flag();
    void reveal_button();
    void set_icon(QString);
};


#endif // MINEBUTTON_H
