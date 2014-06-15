// Copyright (C) 2014 Team306

#include "Cue.h"
#include "Game.h"
#include<iostream>

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
	powerGainEnableFlag = false;
	powerGainCount = 0;

    // load image
    QImage rawImage;
    rawImage.load("Textures/HitAngle—left.png");

    // debug info
    if (rawImage.isNull())
    {
        std::cout << "Load Textures fails in cue" << std::endl;
    }

    // format: QImage::Format_ARGB32
    for (int i = 0; i < 22; ++i)
    {
        image[i] = new QImage(43, 47, QImage::Format_ARGB32);
        *image[i] = rawImage.copy(i * 43 + 1, 0, 43, 47);
    }
    rawImage.load("Textures/HitAngle—right.png");
    for (int i = 22; i < 29; ++i)
    {
        image[i] = new QImage(43, 47, QImage::Format_ARGB32);
        *image[i] = rawImage.copy((i - 22) * 43 + 1, 0, 43, 47);
    }

    // has some problem below
    for (int i = 29; i < 33; ++i)
    {
        image[i] = new QImage(43, 47, QImage::Format_ARGB32);
        *image[i] = rawImage.copy((i - 22) * 43 + 1, 0, 43, 47);
    }

    // adapt the bad picture
    for (int i = 33; i < 44; ++i)
    {
        image[i] = new QImage(43, 47, QImage::Format_ARGB32);
        *image[i] = rawImage.copy((i - 22) * 43, 0, 43, 47);
    }

    // debug info
    if (rawImage.isNull())
    {
        std::cout << "Load Textures fails in cue" << std::endl;
    }
}

void Cue::Update(int gameState, Vector2 mousePosition)
{
	// Update here
	switch ((GAME_STATE)gameState)
	{
		case WAIT_FOR_STROKE:
		case FREE_BALL:
			this->mousePosition = mousePosition;
			if (powerGainEnableFlag)
			{
				powerGainCount++;
			}

			break;
        default:
            break;
	}
}

void Cue::Draw(QPainter& painter, Ball& cueBall, Vector2 mousePosition)
{
	// Draw front sight 
	QColor frontSightColor(200, 200, 200, 100);

    QPen pen;
    pen.setColor(QColor(50, 50, 50, 200));
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);

	painter.setBrush(frontSightColor);
    painter.drawEllipse(QPoint(mousePosition.getX(), mousePosition.getY()), ballRadius, ballRadius);

    Vector2 cuePosition = Vector2(cueBall.getPosition().getX(), cueBall.getPosition().getY());

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

    // draw power gauge
    // for (int i = 0; i < 22; ++i)
    // {
    //     QPixmap pixmap = QPixmap::fromImage(*image[i]);
    //     painter.drawPixmap(100, 100 + i * 20, pixmap);
    // }
    // for (int i = 22; i < 44; ++i)
    // {
    //     QPixmap pixmap = QPixmap::fromImage(*image[i]);
    //     painter.drawPixmap(200, 100 + (i - 22) * 20, pixmap);
    // }
    if (powerGainEnableFlag)
    {
    	// draw
        int beginIndex = 0;
        int index = (powerGainCount / 10) % (44 - beginIndex) + beginIndex;
        QPixmap pixmap = QPixmap::fromImage(*image[index]);
    	int offset = 50;
    	painter.drawPixmap(cuePosition.getX(), cuePosition.getY() - offset, pixmap);
    }
}

void Cue::Stroke(int elapsed, Ball& cueBall, Vector2 mousePosition, Vector2 hitPosition, int hitAngle)
{
	// use elapsed to calc the speed
    Vector2 cuePosition = Vector2(cueBall.getPosition().getX(),cueBall.getPosition().getY());
    ///std::cout<<"cueball::"<<cuePosition.getX()<<","<<cuePosition.getY()<<std::endl;
	Vector2 speed = mousePosition - cuePosition;
    // float scale = (float)elapsed / 100;
    float scale = (float)powerGainCount / 100;
    // set max speed
    if (scale > 3)
	{
        scale = 3;
	}
	// set min speed ? is needed?
	if (scale < 0.2)
	{
		scale = 0.2;
	}
	speed = speed.getNormalize() * scale;
    speed.setXY(speed.getX(),speed.getY());
	cueBall.setSpeed(speed);
    //debug info
    //std::cout<<"speed::"<<speed.getX()<<","<<speed.getY()<<std::endl;
    //std::cout<<"mousepos::"<<mousePosition.getX()<<","<<mousePosition.getY()<<std::endl;
    //std::cout<<"scale::"<<scale<<std::endl;
}

void Cue::enablePowerGain()
{
	powerGainCount = 0;
	powerGainEnableFlag = true;
}

void Cue::disablePowerGain()
{
	powerGainEnableFlag = false;
}

int Cue::getPowerCount() const
{
    return powerGainCount;
}

void Cue::setPowerCount(int powerCount){
    powerGainCount = powerCount;
}
