// Copyright (C) 2014 Team306

#include "Table.h"

Table::Table()
{
}

Table::~Table()
{
}

void Table::init(Referee& referee)
{
	// init method
    picPosition.setXY(0, 0);
    position.setXY(40, 40);
    picSize.setXY(1280, 680);
    size.setXY(1200, 600);
    pocketRadius = 40;

    p1.setXY(position.getX() + size.getX(), position.getY());
    p2.setXY(position.getX(), position.getY() + size.getY());
    p3.setXY(position.getX() + size.getX(), position.getY() + size.getY());

    //R1 to R6 is used to detect crash
    R1.setCoords(position.getX() + pocketRadius, position.getY(), position.getX() + size.getX() / 2 - pocketRadius,
                 position.getY() + referee.getBallRadius());//topleft

    R2.setCoords(position.getX() + size.getX() / 2 + pocketRadius, position.getY(),
                 position.getX() + size.getX() - pocketRadius,position.getY() + referee.getBallRadius());//topright

    R3.setCoords(position.getX() + pocketRadius, position.getY() + size.getY() - referee.getBallRadius(),
                 position.getX() + size.getX() / 2 - pocketRadius, position.getY() + size.getY());//bottomleft

    R4.setCoords(position.getX() + size.getX() / 2  + pocketRadius, position.getY() + size.getY() - referee.getBallRadius(),
                 position.getX() + size.getX() - pocketRadius,position.getY() + size.getY());//bottomright

    R5.setCoords(position.getX(), position.getY() + pocketRadius, position.getX() + referee.getBallRadius(),
                 position.getY() + size.getY() - pocketRadius);//left

    R6.setCoords(position.getX() + size.getX() - referee.getBallRadius(), position.getY() + pocketRadius,
                 position.getX() + size.getX(),position.getY() + size.getY() - pocketRadius);//right
    //R7 to R8 middle pocket
    R7.setCoords(position.getX() + size.getX() / 2 - 30,position.getY() - referee.getBallRadius(),
                 position.getX() + size.getX() / 2 + 30,position.getY());

    R8.setCoords(position.getX() + size.getX() / 2 - 30,position.getY() + size.getY(),
                 position.getX() + size.getX() / 2 + 30,position.getY() + size.getY() + referee.getBallRadius());
}

Vector2 Table::getSize() const
{
	return size;
}

QRect Table::GetWall(int i) const
{
    assert(i>=1 && i<=6);
    if(i==1) return R1;
    if(i==2) return R2;
    if(i==3) return R3;
    if(i==4) return R4;
    if(i==5) return R5;
    return R6;
}

// update and draw
void Table::Update()
{
	// update here
}

void Table::Draw(QPainter& painter)
{
	// draw here
    QColor brown(91, 29, 28);
    painter.setBrush(QBrush(brown));
    painter.setPen(QPen(brown));
	painter.drawRect(QRectF(picPosition.getX(), picPosition.getY(), picSize.getX(), picSize.getY()));

    painter.drawRect(QRectF(0, 600, 1280, 120));    

    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.setBrush(QBrush(QColor(0,0,0)));
    painter.drawEllipse(QPoint(position.getX(), position.getY()),40,40);
    painter.drawEllipse(QPoint(position.getX()+size.getX(), position.getY()),40,40);
    painter.drawEllipse(QPoint(position.getX(), position.getY()+size.getY()),40,40);
    painter.drawEllipse(QPoint(position.getX()+size.getX(), position.getY()+size.getY()),40,40);
    painter.drawEllipse(QPoint(picPosition.getX()+picSize.getX()/2, picPosition.getY()+40),40,40);
    painter.drawEllipse(QPoint(picPosition.getX()+picSize.getX()/2, picPosition.getY()+size.getY()+40),40,40);

    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.setBrush(QBrush(QColor(68, 149, 60)));
    painter.drawRoundRect(QRectF(position.getX(), position.getY(), size.getX(), size.getY()),7,14);

    painter.setPen(QPen(QColor(255,255,255)));
    float lineX = (float)65 / (float)254 * size.getX();
    painter.drawLine(position.getX() + lineX, position.getY(), position.getX() + lineX, position.getY() + size.getY());
    //test
    painter.setBrush(QBrush(QColor(100,100,100)));
    /*painter.drawRect(R1);
    painter.drawRect(R2);
    painter.drawRect(R3);
    painter.drawRect(R4);
    painter.drawRect(R5);
    painter.drawRect(R6);
    painter.drawRect(R7);
    painter.drawRect(R8);*/
}

// collision detection
bool Table::collidesWith(Ball& b)
{
	// detect collision here
    // speed is for test
    if(R1.contains(b.getPosition().getX(),b.getPosition().getY(),false))//topleft
    {
        if(b.getSpeed().getY() < 0)
            b.setSpeed(Vector2(b.getSpeed().getX(),0 - b.getSpeed().getY()));
        return true;
    }
    if(R2.contains(b.getPosition().getX(),b.getPosition().getY(),false))//topright
    {
        if(b.getSpeed().getY() < 0)
            b.setSpeed(Vector2(b.getSpeed().getX(),0 - b.getSpeed().getY()));
        return true;
    }
    if(R3.contains(b.getPosition().getX(),b.getPosition().getY(),false))//bottomleft
    {
        if(b.getSpeed().getY() > 0)
            b.setSpeed(Vector2(b.getSpeed().getX(),0 - b.getSpeed().getY()));
        return true;
    }
    if(R4.contains(b.getPosition().getX(),b.getPosition().getY(),false))//topright
    {
        if(b.getSpeed().getY() > 0)
            b.setSpeed(Vector2(b.getSpeed().getX(),0 - b.getSpeed().getY()));
        return true;
    }
    if(R5.contains(b.getPosition().getX(),b.getPosition().getY(),false))//left
    {
        if(b.getSpeed().getX() < 0)
            b.setSpeed(Vector2(0 - b.getSpeed().getX(), b.getSpeed().getY()));
        return true;
    }
    if(R6.contains(b.getPosition().getX(),b.getPosition().getY(),false))//right
    {
        if(b.getSpeed().getX() > 0)
            b.setSpeed(Vector2(0 - b.getSpeed().getX(), b.getSpeed().getY()));
        return true;
    }

    //topleft_pocket,2 points
    Vector2 detectP1(position.getX() + pocketRadius, position.getY());//top
    Vector2 detectP2(position.getX(), position.getY() + pocketRadius);//left
    if(b.getPosition().DistanceTo(detectP1) <= b.getRadius())
    {
        b.setSpeed(Vector2(b.getSpeed().getY(), 0 - b.getSpeed().getX()));
        return true;
    }
    if(b.getPosition().DistanceTo(detectP2) <= b.getRadius())
    {
        b.setSpeed(Vector2( 0 - b.getSpeed().getY(), b.getSpeed().getX()));
        return true;
    }

    //topcenter_pocket, 2 points
    Vector2 detectP3(position.getX() + size.getX() / 2 - pocketRadius, position.getY());//left
    Vector2 detectP4(position.getX() + size.getX() / 2 + pocketRadius, position.getY());//right
    if(b.getPosition().DistanceTo(detectP3) <= b.getRadius())
    {
        b.setSpeed(Vector2(b.getSpeed().getY(), 0 - b.getSpeed().getX()));
        return true;
    }
    if(b.getPosition().DistanceTo(detectP4) <= b.getRadius())
    {
        b.setSpeed(Vector2(0 - b.getSpeed().getY(),b.getSpeed().getX()));
        return true;
    }

    //topright_pocket, 2 points
    Vector2 detectP5(position.getX() +size.getX() - pocketRadius, position.getY());//top
    Vector2 detectP6(position.getX() +size.getX(), position.getY() + pocketRadius);//left
    if(b.getPosition().DistanceTo(detectP5) <= b.getRadius())
    {
        b.setSpeed(Vector2(b.getSpeed().getY(), 0 - b.getSpeed().getX()));
        return true;
    }
    if(b.getPosition().DistanceTo(detectP6) <= b.getRadius())
    {
        b.setSpeed(Vector2( 0 - b.getSpeed().getY(), b.getSpeed().getX()));
        return true;
    }

    //bottomleft_pocket, 2 points
    Vector2 detectP7(position.getX() + pocketRadius, position.getY() + size.getY());//bottom
    Vector2 detectP8(position.getX(), position.getY() + size.getY() - pocketRadius);//left
    if(b.getPosition().DistanceTo(detectP7) <= b.getRadius())
    {
        b.setSpeed(Vector2(b.getSpeed().getY(), 0 - b.getSpeed().getX()));
        return true;
    }
    if(b.getPosition().DistanceTo(detectP8) <= b.getRadius())
    {
        b.setSpeed(Vector2( 0 - b.getSpeed().getY(), b.getSpeed().getX()));
        return true;
    }

    //bottomcenter_pocket, 2 points
    Vector2 detectP9(position.getX() + size.getX() / 2 + pocketRadius, position.getY() + size.getY());//right
    Vector2 detectP10(position.getX() + size.getX() / 2 - pocketRadius, position.getY() + size.getY());//left
    if(b.getPosition().DistanceTo(detectP9) <= b.getRadius())
    {
        b.setSpeed(Vector2(0 - b.getSpeed().getY(),b.getSpeed().getX()));
        return true;
    }
    if(b.getPosition().DistanceTo(detectP10) <= b.getRadius())
    {
        b.setSpeed(Vector2(b.getSpeed().getY(), 0 - b.getSpeed().getX()));
        return true;
    }

    //bottomright_pocket, 2 points
    Vector2 detectP11(position.getX() +size.getX(), position.getY() + size.getY() - pocketRadius);//right
    Vector2 detectP12(position.getX() +size.getX() - pocketRadius, position.getY() + size.getY());//bottom
    if(b.getPosition().DistanceTo(detectP11) <= b.getRadius())
    {
        b.setSpeed(Vector2(b.getSpeed().getY(), 0 - b.getSpeed().getX()));
        return true;
    }
    if(b.getPosition().DistanceTo(detectP12) <= b.getRadius())
    {
        b.setSpeed(Vector2( 0 - b.getSpeed().getY(), b.getSpeed().getX()));
        return true;
    }

    return false;
}

bool Table::positionIsLegal(Vector2 p,Referee &referee)
{
    QRect R(position.getX() + referee.getBallRadius(), position.getY() + referee.getBallRadius(),
            300 - 2 * referee.getBallRadius(),size.getY() - 2 * referee.getBallRadius());
    if(R.contains(p.getX(), p.getY(),true))
        return true;
    return false;
}

bool Table::checkPockets(Ball& ball)
{
    // if the ball is in the pocket return true;
    if(R7.contains(ball.getPosition().getX(), ball.getPosition().getY(), false)||
            R8.contains(ball.getPosition().getX(), ball.getPosition().getY(), false))
        return true;

    if((ball.getPosition().DistanceTo(position) <= 0.5 * pocketRadius )||
            (ball.getPosition().DistanceTo(p1) <= 0.5 * pocketRadius )||
            (ball.getPosition().DistanceTo(p2) <= 0.5 * pocketRadius )||
            (ball.getPosition().DistanceTo(p3) <= 0.5 * pocketRadius ))
        return true;
    return false;
}
