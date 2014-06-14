// Copyright (C) 2014 Team306

#include "Ball.h"

Ball::Ball()
{
    ballState = STILL;
}
Ball::Ball(const Vector3& position, float radius)
    : position(position), radius(radius)
{
    this->speed=Vector3(0,0,0);
    this->anglespeed=Vector3(0,0,0);
    this->Im=0.4f*M*(this->radius)*(this->radius);
    Ball();
}

Ball::Ball(const Vector2& position, float radius)
    : position(position), radius(radius)
{
    this->speed=Vector3(0,0,0);
    this->anglespeed=Vector3(0,0,0);
    this->Im=0.4f*M*(this->radius)*(this->radius);
    Ball();
}

Ball::~Ball()
{
}

Vector3 Ball::getPosition() const
{
    return this->position;
}

void Ball::setPosition(const Vector2& v)
{
    position = Vector3(v);
}

void Ball::setPosition(const Vector3& v)
{
    position = v;
}

Vector3 Ball::getSpeed() const
{
    return this->speed;
}

void Ball::setSpeed(const Vector3& v)
{
    if(v.Length()>=0)
        this->ballState=RUNNING;
    this->speed = v;
}

Vector3 Ball::getAngleSpeed() const
{
    return this->anglespeed;
}

void Ball::setAngleSpeed(const Vector3& v)
{
    if(v.Length()>=0)
        this->ballState=RUNNING;
    this->anglespeed = v;
}


float Ball::getRadius() const
{
    return this->radius;
}

float Ball::getIm() const
{
    return this->Im;
}

int Ball::getBallState() const
{
    return ballState;
}

void Ball::setBallState(int newState)
{
    ballState = (BALL_STATE)newState;
}

std::string Ball::getName() const
{
    return name;
}

void Ball::setName(std::string n)
{
    name = n;
}

void Ball::setColor(QColor c)
{
    color = c;
}

void Ball::ApplyImpulse(const Vector3& impulse,const Vector3& collideposition)
{
    this->speed += (impulse/M);
    //??
    /*if(impulse[2]!=0.0 && fabs(impulse[2])>1)
    {
        this->speed.setX(this->speed[0]/impulse[2]);
        this->speed.setY(this->speed[1]/impulse[2]);
    }*/
    this->speed.setZ(0.0f);
    this->anglespeed+= CrossProduct(collideposition-this->position,impulse)/this->Im;
    if(this->speed.Length()>0 || this->anglespeed.Length()>0)
        this->ballState=RUNNING;
}

void Ball::Move()
{
    if(this->ballState==STILL)
        return;
    Vector3 rollspeed;
    Vector3 wholespeed;
    rollspeed=CrossProduct(this->anglespeed,Vector3(0,0,this->radius)); //(ωy*r,-ωx*r,0)
    wholespeed=rollspeed+this->speed;

    if(rollspeed.Length()<Froll_Threshold && this->speed.Length()<Froll_Threshold)
    {
        if(this->anglespeed[2]<Frotate_Threshold)
        {
            this->ballState=STILL;
            this->speed=Vector3(0,0,0);
            this->anglespeed=Vector3(0,0,0);
        }
        else
        {
            if (this->anglespeed[2]>0)
                this->anglespeed.setZ(this->anglespeed[2]-Frotate_GroundToBall) ;
            else
                this->anglespeed.setZ(this->anglespeed[2]+Frotate_GroundToBall);
        }
    }
    else
    {
        if(wholespeed.Length()<Fslip_Threshold)
        {
            this->ApplyImpulse(GetNormalize(this->speed)*(-M * Froll_GroundToBall), this->position);
            this->anglespeed.setX( this->speed[1] / this->radius );
            this->anglespeed.setY(- this->speed[0] / this->radius );
        }
        else
        {
            this->ApplyImpulse(GetNormalize(wholespeed)*(-M * Fslip_GroundToBall ), (this->position+Vector3(0, 0, this->radius)));//去除对ωz影响
        }
        if (this->anglespeed[2]>0)
            this->anglespeed.setZ(this->anglespeed[2]-Frotate_GroundToBall);
        else
            this->anglespeed.setZ(this->anglespeed[2]+Frotate_GroundToBall);
    }
    this->position += (this->speed * 1.0f);
}

void Ball::Draw(QPainter& painter)
{
    if (ballState == ON_THE_POCKET)
    {
        return;
    }

    // draw itself
    QRadialGradient gradient(QPointF(radius, radius), radius, QPointF(radius * 0.5, radius * 0.5));
    gradient.setColorAt(0, QColor(255, 255, 255, 255));
    gradient.setColorAt(0.05, QColor(255, 255, 255));
    gradient.setColorAt(1, color);

    painter.save();
    painter.translate(position.getX() - radius, position.getY() - radius);
    painter.setBrush(QBrush(gradient));
    painter.setPen(color);
    painter.drawEllipse(0, 0, radius * 2, radius * 2);
    painter.restore();

    // painter.setBrush(color);
    // painter.drawEllipse(QPoint(position.getX(), position.getY()), radius, radius);

    // debug info
    // QFont font;
    // painter.setFont(font);
    // painter.drawText(QRectF(position.getX() - radius, position.getY() - 5, 50, 50), name.c_str());
}
