#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QMouseEvent>
#include <QPalette>
#include <QPushButton>

class MineButton : public QPushButton
{
    Q_OBJECT

public:
    MineButton(QWidget *parent = 0);
    int number;
    QStringList iconPaths = {":/assets/0.png",
                             ":/assets/1.png",
                             ":/assets/2.png",
                             ":/assets/3.png",
                             ":/assets/4.png",
                             ":/assets/5.png",
                             ":/assets/6.png",
                             ":/assets/7.png",
                             ":/assets/8.png",
                             ":/assets/mine.png"};
    QString flagPath = ":/assets/flag.png";
    //QString minePath = ":/assets/mine.png";
    QString hintPath = ":/assets/hint.png";
    QString wrongFlagPath = ":/assets/wrong-flag.png";
    QString emptyPath = ":/assets/empty.png";
    bool isClicked = false;
    bool isFlagged = false;
    int row;
    int col;
    void setWrongFlagged();
    void setClickable(bool);

private:
    void startReveal();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    bool clickable = true;

signals:
    void revealStarted(int x, int y);
    void mineClicked(int x, int y);
    void scoreIncreased();

public slots:
    void update_flag();
    void reveal();
    void set_icon(QString);
};

#endif // MINEBUTTON_H
