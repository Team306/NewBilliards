// Copyright (C) 2014 Team306

#include "Cue.h"
#include "Game.h"
#include <iostream>

Cue::Cue()
{
    sound = new QSound("./sound/Hit.wav");
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
    powerGainIncrement = true;

    // // // load image
    // cueImage.load("Textures/cue.png");

    // // debug info
    // if (cueImage.isNull())
    // {
    //     std::cout << "Load Textures fails in cue" << std::endl;
    // }
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
                if (powerGainIncrement)
                {
                    powerGainCount++;
                }
                else
                {
                    powerGainCount--;
                }

                if (powerGainCount >= 540 - 1)
                {
                    powerGainIncrement = false;
                }
                if (powerGainCount <= 0)
                {
                    powerGainIncrement = true;
                }
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

    QLinearGradient linearGradient(beginPosition.getX(), beginPosition.getY(), endPosition.getX(), endPosition.getY());
    linearGradient.setColorAt(1, QColor(183, 136, 87));
    linearGradient.setColorAt(0.66, QColor(217, 167, 116));
    linearGradient.setColorAt(0.32, QColor(206, 147, 97));
    linearGradient.setColorAt(0.30, QColor(62, 27, 26));
    linearGradient.setColorAt(0, QColor(62, 27, 26));
	// QColor cueColor(143, 100, 69);
    // QColor cueColor(183, 136, 87);
	// painter.setPen(QPen(cueColor, 8, Qt::SolidLine, Qt::RoundCap));
    QPen cuePen(QBrush(linearGradient), 8);
    cuePen.setCapStyle(Qt::RoundCap);
    painter.setPen(cuePen);
	painter.drawLine(beginPosition.getX(), beginPosition.getY(), endPosition.getX(), endPosition.getY());

    // // draw cue image
    // const float PI = 3.141593;
    // if (direction.getX() >= 0)
    // {
    //     if (direction.getY() >= 0)
    //     {
    //         // right down
    //         int angle = atan(direction.getY() / direction.getX()) / PI * 180;
    //         Vector2 drawPoint = cuePosition;
    //         QMatrix matrix;
    //         matrix.rotate(angle);
    //         QImage rotateImage = cueImage.transformed(matrix);
    //         QPixmap pixmap = QPixmap::fromImage(rotateImage);
    //         painter.drawPixmap(drawPoint.getX(), drawPoint.getY(), pixmap);
    //     }
    //     else
    //     {
    //         // right up
    //     }
    // }
    // else
    // {
    //     if (direction.getY() >= 0)
    //     {
    //         // left down
    //     }
    //     else
    //     {
    //         // left up
    //     }
    // }

    // QMatrix matrix;
    // matrix.rotate(0);
    // QImage rotateImage = cueImage.transformed(matrix);
    // QPixmap pixmap = QPixmap::fromImage(rotateImage);
    // painter.drawPixmap(100, 100, pixmap);

    // draw power gauge
    if (powerGainEnableFlag)
    {
        // draw arc
        int offset = 35;
        int angle = (powerGainCount / 2) % 270;
        QConicalGradient conicalGradient(cuePosition.getX(), cuePosition.getY(), 0);
        conicalGradient.setColorAt(0, QColor(255, 255, 255));
        conicalGradient.setColorAt(0.3, QColor(0xE4, 0x00, 0x7F));
        conicalGradient.setColorAt(0.8, QColor(255, 0, 0));        
        conicalGradient.setColorAt(1, QColor(255, 255, 255));
        painter.setPen(QPen(QBrush(conicalGradient), 5));
        painter.drawArc(QRectF(cuePosition.getX() - offset, cuePosition.getY() - offset, offset * 2, offset * 2), 0, angle * 16);
    }
}

void Cue::Stroke(Ball& cueBall, Vector2 mousePosition, Vector2 hitPosition, int hitAngle,int HitRadius)
{
    sound->play();
	// use elapsed to calc the speed
    Vector3 hitPoint(0,0,0);
    Vector3 hitDirection=GetNormalize(Vector3(mousePosition)-cueBall.getPosition());
    Vector3 v_temp1(specialAntiRotate90(Vector2(-hitDirection.getX(),-hitDirection.getY())));
    Vector3 v_temp2=Vector3(0,0,-1)*cos(hitAngle*M_PI/180.0)+hitDirection*sin(hitAngle*M_PI/180.0);
    Vector3 v_temp=v_temp1*(hitPosition.getX()/HitRadius*cueBall.getRadius())\
                    + v_temp2*(-hitPosition.getY()/HitRadius*cueBall.getRadius());

    hitDirection=hitDirection*cos(hitAngle*M_PI/180.0)+Vector3(0,0,sin(hitAngle*M_PI/180.0));
    hitPoint=cueBall.getPosition() + v_temp + (-hitDirection)*sqrt(cueBall.getRadius()*cueBall.getRadius()-v_temp.Length2());
    cout<<hitPoint[0]<<";"<<hitPoint[1]<<";"<<hitPoint[2]<<endl;
    //cout<<cueBall.getRadius()<<endl;
    //cout<<v_temp1.Length2()<<endl;
    //cout<<v_temp2.Length2()<<endl<<endl;

    // float scale = (float)elapsed / 100;
    float scale = (float)powerGainCount / 50;

    cueBall.ApplyImpulse(scale*hitDirection,hitPoint);
    //debug info
    //std::cout<<"speed::"<<speed.getX()<<","<<speed.getY()<<std::endl;
    //std::cout<<"mousepos::"<<mousePosition.getX()<<","<<mousePosition.getY()<<std::endl;
    //std::cout<<"scale::"<<powerGainCount<<std::endl;
}

void Cue::enablePowerGain()
{
	powerGainCount = 0;
	powerGainEnableFlag = true;
    powerGainIncrement = true;
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
