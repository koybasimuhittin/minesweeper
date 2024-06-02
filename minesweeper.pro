QT += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    mainMenu.cpp \
    mineButton.cpp \
    game.cpp \
    main.cpp \
    scoreBoard.cpp \
    window.cpp

HEADERS += \
    game.h \
    mainMenu.h \
    mineButton.h \
    scoreBoard.h \
    window.h

RESOURCES += \
    assets.qrc
