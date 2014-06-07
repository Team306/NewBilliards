// Copyright (C) 2014 Team306

#include "Cue.h"
#include "Game.h"

Cue::Cue()
{
}

Cue::~Cue()
{
}

void Cue::init(Referee& referee)
{
	ballRadius = referee.getBallRadius();
	cueLength = 50;
}

void Cue::Update(int gameState, Vector2 mousePosition)
{
	// Update here
	switch ((GAME_STATE)gameState)
	{
		case WAIT_FOR_STROKE:
		case FREE_BALL:
			this->mousePosition = mousePosition;
			break;
	}
}

void Cue::Draw(QPainter& painter, Ball& cueBall)
{
	// Draw front sight 
	QColor frontSightColor(200, 200, 200, 100);

    QPen pen;
    pen.setColor(QColor(50, 50, 50, 200));
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);

	painter.setBrush(frontSightColor);
    painter.drawEllipse(QPoint(mousePosition.getX(), mousePosition.getY()), ballRadius, ballRadius);

    Vector2 cuePosition = cueBall.getPosition();

    Vector2 direction = mousePosition - cuePosition;
    direction = direction.getNormalize();
    Vector2 offset = direction * cueBall.getRadius();
    Vector2 beginPosition = cuePosition + offset;
    Vector2 endPosition = mousePosition - offset;

	painter.drawLine(beginPosition.getX(), beginPosition.getY(), endPosition.getX(), endPosition.getY());

	// draw the cue
	offset = offset * (-3);
	endPosition = cuePosition + offset;
	offset = offset * 8;
	beginPosition = cuePosition + offset;
	QColor cueColor(143, 100, 69);
	painter.setPen(QPen(cueColor, 12, Qt::SolidLine, Qt::RoundCap));
	painter.drawLine(beginPosition.getX(), beginPosition.getY(), endPosition.getX(), endPosition.getY());

}

void Cue::Stroke(int elapsed, Ball& cueBall)
{
	// use elapsed to calc the speed
	Vector2 cuePosition = cueBall.getPosition();
	Vector2 speed = mousePosition - cuePosition;
    float scale = (float)elapsed / 1000;
    // set max speed
    if (scale > 1)
	{
        scale = 1;
	}
	// set min speed ? is needed?
	if (scale < 0.2)
	{
		scale = 0.2;
	}
	speed = speed.getNormalize() * scale;
	cueBall.setSpeed(speed);
}
