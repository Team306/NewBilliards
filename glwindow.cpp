// Copyright (C) 2014 Team306

#include <QMouseEvent>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include "glwindow.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

// fps
const int msPerFrame = 16;
// update times in each frame
const int updateCount = 20;

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
}

void GLWindow::mousePressEvent(QMouseEvent *event)
{
    mousePressTime.start();
}

void GLWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int elapsedTime = mousePressTime.elapsed();
    // call game method
    game.mousePress(elapsedTime);
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    game.setMousePosition(Vector2(event->x(), event->y()));
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
