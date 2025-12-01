QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    TaskManager.cpp \
    allCommands.cpp \
    commandparser.cpp \
    main.cpp \
    MainWindow.cpp \
    task.cpp

HEADERS += \
    MainWindow.h \
    TaskManager.h \
    allCommands.h \
    command.h \
    commandparser.h \
    task.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
