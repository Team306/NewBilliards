// Copyright (C) 2014 Team306

#ifndef GLWINDOW_H
#define GLWINDOW_H 


#include <QGLWidget>
#include <QTimer>
#include <QTIme>
#include <QPushButton>
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
    void paintGL();
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void MainLoop();

private:
	Game game;

	QTimer timer;
	QTime mousePressTime;
};


#endif
