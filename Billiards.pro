#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T14:03:25
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Billiards
TEMPLATE = app


SOURCES += main.cpp\
    Game.cpp \
    Ball.cpp \
    BallsManager.cpp \
    Table.cpp \
    glwindow.cpp \
    Referee.cpp \
    Cue.cpp \
    Player.cpp \
    CollideEngine.cpp \
    MyMath.cpp \
    GameSever.cpp \
    GameClient.cpp \
    Menu.cpp

HEADERS  += \
    Ball.h \
    BallsManager.h \
    Cue.h \
    Game.h \
    Table.h \
    glwindow.h \
    Referee.h \
    Player.h \
    CollideEngine.h \
    MyMath.h \
    GameSever.h \
    GameClient.h

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}
