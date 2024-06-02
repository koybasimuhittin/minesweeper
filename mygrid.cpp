#include "mygrid.h"
#include "minebutton.h"

MyGrid::MyGrid()
    : QGridLayout()
{}

// void MyGrid::check_colors()
// {
//     bool all_same = true;
//     QString prev = "";
//     for (int i = 0; i < this->count(); ++i)
//     {
//         MineButton *widget = qobject_cast<MineButton*>(this->itemAt(i)->widget());
//         if (prev == "")
//         {
//             prev = widget->color;
//         }
//         else if (prev != widget->color)
//         {
//             all_same = false;
//         }
//     }

//     if (all_same)
//     {
//         this->timer->stop();
//         QMessageBox msgBox;
//         msgBox.setText("You won!");
//         msgBox.exec();
//         msgBox.setStandardButtons(QMessageBox::Cancel);
//     }
// }
