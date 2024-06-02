#ifndef MYGRID_H
#define MYGRID_H

#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>

class MyGrid : public QGridLayout
{
    Q_OBJECT

public:
    MyGrid();

public slots:
    // void check_colors();
};

#endif // MYGRID_H
