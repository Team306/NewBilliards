// Copyright (C) 2014 Team306

#ifndef GLWINDOW_H
#define GLWINDOW_H 

#include <QGLWidget>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <GL/glu.h>
#include <QObject>
#include <QTimer>
#include <QTIme>
#include <QPushButton>
#include <QSound>
#include "Game.h"

class GLWindow : public QGLWidget
{
	Q_OBJECT

public:
	GLWindow(QWidget *parent = 0);
	~GLWindow();

public slots:

protected:
	void initializeGL();
    void resizeGL( int width, int height );
    void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void MainLoop();
    void newConnect();
    void serverRead();
    void clientRead();
    void clientConnected();
    void tryConnect();

    void test();

private:
	Game game;

	QTimer timer;
    QTimer testTime;
    QTimer connectTimer;
    int countTest;
    QByteArray ReadData;
    QByteArray SendData;
    QList<QByteArray> toReadList;
    void ClientProcessList();
    void ServerProcessList();
    QSound *sound;
};


#endif
