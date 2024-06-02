#include <QApplication>
#include "window.h"

// Commented out code pieces will be using during the live demo,
// they are using some large media files which are not fit 2mb zipped folder limit.

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();
}
