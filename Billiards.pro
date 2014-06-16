#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T14:03:25
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Billiards
TEMPLATE = app


SOURCES += \
    src/Ball.cpp \
    src/BallsManager.cpp \
    src/CollideEngine.cpp \
    src/Cue.cpp \
    src/Game.cpp \
    src/GameClient.cpp \
    src/GameSever.cpp \
    src/glwindow.cpp \
    src/main.cpp \
    src/Menu.cpp \
    src/MyMath.cpp \
    src/Player.cpp \
    src/Referee.cpp \
    src/Table.cpp

HEADERS  += \
    src/Ball.h \
    src/BallsManager.h \
    src/CollideEngine.h \
    src/Cue.h \
    src/Game.h \
    src/GameClient.h \
    src/GameSever.h \
    src/glwindow.h \
    src/Menu.h \
    src/MyMath.h \
    src/Player.h \
    src/Referee.h \
    src/Table.h

INCLUDEPATH += $$PWD/Lua5.2/include
LIBS += -L$$PWD/Lua5.2 -llua52

OTHER_FILES += \
    myicon.rc

RC_FILE += myicon.rc
