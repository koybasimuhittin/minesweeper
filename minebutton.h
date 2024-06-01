#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QPalette>

class MineButton : public QPushButton
{
    Q_OBJECT

public:
    MineButton(const QString& icon_path, QWidget* parent = 0);
    QString icon_path;

public slots:
              // void change_color();
};

#endif // MINEBUTTON_H
