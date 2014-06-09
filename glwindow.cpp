// Copyright (C) 2014 Team306

#include <QMouseEvent>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include "glwindow.h"
#include <iostream>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

// fps
const int msPerFrame = 16;
// update times in each frame
const int updateCount = 10;

GLWindow::GLWindow(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(MainLoop()));
    timer.start(msPerFrame);

    setFixedSize(1280, 720);
    setWindowTitle(tr("Billiards by Team306"));

    // put the window in center
    QDesktopWidget *desktop = QApplication::desktop();
    if (desktop->width() != 1366 && desktop->height() != 768)
    {
        move((1920 - 1280) / 2, (1080 - 720) / 2);
    }
    else
    {
        move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    }

    // about mouse event
    setMouseTracking(true);
    // setCursor(Qt::CrossCursor);
}

GLWindow::~GLWindow()
{
}

void GLWindow::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    // glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // temp put init here
    game.init();
    connect(game.getGameSever(),SIGNAL(newConnection()),this,SLOT(newConnect()));
    connect(game.getGameClient(),SIGNAL(readyRead()),this,SLOT(clientRead()));
}

void GLWindow::mousePressEvent(QMouseEvent *event)
{
    if(game.getPlayerFlag() == LOCAL || game.getGameMode() != NETWORK_MODE || game.getGameState() == END_FRAME){
        mousePressTime.start();
    }
}

void GLWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(game.getPlayerFlag() == LOCAL || game.getGameMode() != NETWORK_MODE || game.getGameState() == END_FRAME){
        int elapsedTime = mousePressTime.elapsed();
    // call game method
        game.setMousePosition(Vector2(event->x(), event->y()));
        game.mousePress(elapsedTime);
        if(game.getGameMode() == NETWORK_MODE && (game.getGameState() == WAIT_FOR_STROKE || game.getGameState() == FREE_BALL
                                                  ||game.getGameState() == BALL_IS_RUNNING )){
            SendData.clear();
            SendData.append(QString("EL#"));
            SendData.append(QString::number(elapsedTime));
            SendData.append(QString(","));
            SendData.append(QString::number(event->x()));
            SendData.append(QString(","));
            SendData.append(QString::number(event->y()));
            SendData.append(QString("#"));
            QString sendStr = QVariant(SendData).toString();
            //std::cout<<sendStr.toStdString()<<std::endl;

            if(game.getNetworkRule() == SERVER){
                game.getGameSever()->sendMessage(SendData);
                std::cout<<sendStr.toStdString()<<std::endl;
            }
            if(game.getNetworkRule() == CLIENT){
                game.getGameClient()->sendMessage(SendData);
                std::cout<<sendStr.toStdString()<<std::endl;
            }
        }
    }
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(game.getPlayerFlag() == LOCAL || game.getGameMode() != NETWORK_MODE || game.getGameState() == END_FRAME){
        game.setMousePosition(Vector2(event->x(), event->y()));
        if(game.getGameMode() == NETWORK_MODE && (game.getGameState() == WAIT_FOR_STROKE || game.getGameState() == FREE_BALL)){
            SendData.clear();
            SendData.append(QString("P#"));
            SendData.append(QString::number(event->x()));
            SendData.append(QString(","));
            SendData.append(QString::number(event->y()));
            SendData.append(QString("#"));
            QString sendStr = QVariant(SendData).toString();
            if(game.getNetworkRule() == SERVER){
                game.getGameSever()->sendMessage(SendData);
                std::cout<<sendStr.toStdString()<<std::endl;
            }
            if(game.getNetworkRule() == CLIENT){
                game.getGameClient()->sendMessage(SendData);
                std::cout<<sendStr.toStdString()<<std::endl;
            }
        }
    }

}

void GLWindow::paintEvent(QPaintEvent *event)
{
    // makeCurrent();
    // glClear(GL_COLOR_BUFFER_BIT);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    game.Draw(painter);
    painter.end();
}

void GLWindow::MainLoop()
{
    for (int i = 0; i < updateCount; ++i)
    {
        game.Update();
    }
    // change cursor
    switch (game.getGameState())
    {
        case WAIT_FOR_STROKE:
            setCursor(Qt::CrossCursor);
            break;
        case FREE_BALL:
            setCursor(Qt::PointingHandCursor);
            break;
        case BALL_IS_RUNNING:
            setCursor(Qt::BlankCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
    }
    // call repaint
    update();
    // updateGL();
}

void GLWindow::paintGL()
{
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT);

    //
}


void GLWindow::newConnect(){
    game.getGameSever()->setClient();
    QByteArray start;
    start.clear();
    start.append(QString("S#"));
    start.append(QString::number(game.getGameRule()));
    start.append(QString("#"));
    game.getGameSever()->sendMessage(start);
    game.GameBegin();
    connect(game.getGameSever()->getClient(),SIGNAL(readyRead()),this,SLOT(serverRead()));
}

void GLWindow::serverRead(){
    ReadData.clear();
    ReadData = game.getGameSever()->getMessage();
    QString readStr = QVariant(ReadData).toString();
    //std::cout<<"Read::::"<<readStr.toStdString()<<std::endl;
    QStringList readlist = readStr.split("#");
    for(int i = 0; i< readlist.size();){
        if(readlist[i] == "EL"){
            QStringList infolist = readlist[i+1].split(",");
            int elapsedTime = infolist[0].toInt();
            game.setMousePosition(Vector2(infolist[1].toFloat(),infolist[2].toFloat()));
            game.mousePress(elapsedTime);
            i = i+2;
        }
        else{
            if(readlist[i] == "P"){
                QStringList position = readlist[i+1].split(",");
                game.setMousePosition(Vector2(position[0].toFloat(),position[1].toFloat()));
                i = i+2;
            }
            else i = i+2;
        }
    }
}

void GLWindow::clientRead(){
    ReadData.clear();
    ReadData = game.getGameClient()->getMessage();
    QString readStr = QVariant(ReadData).toString();
    //std::cout<<readStr.toStdString()<<std::endl;
    QStringList readlist = readStr.split("#");
   for(int i = 0; i<readlist.size();){
        if(readlist[i] == "EL"){
            QStringList infolist = readlist[i+1].split(",");
            int elapsedTime = infolist[0].toInt();
            game.setMousePosition(Vector2(infolist[1].toFloat(),infolist[2].toFloat()));
            game.mousePress(elapsedTime);
            i = i+2;
        }
        else{
            if(readlist[i] == "P"){
                QStringList position = readlist[i+1].split(",");
                game.setMousePosition(Vector2(position[0].toFloat(),position[1].toFloat()));
                i = i+2;
            }
            else{
                    if(readlist[i] == "S"){
                    game.ClientInit(readlist[i+1].toInt());
                    i = i+2;
                    }
                    else i = i+2;
            }
        }
   }
}
