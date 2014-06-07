#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T14:03:25
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Billiards
TEMPLATE = app


SOURCES += main.cpp\
    Game.cpp \
    Ball.cpp \
    Vector2.cpp \
    BallsManager.cpp \
    Table.cpp \
    glwindow.cpp \
    Referee.cpp \
    Cue.cpp \
    Player.cpp

HEADERS  += \
    Ball.h \
    BallsManager.h \
    Cue.h \
    Game.h \
    Vector2.h \
    Table.h \
    glwindow.h \
    Referee.h \
    Player.h
