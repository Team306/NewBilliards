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
    pocketRadius = 35;
    lineX = (float)65 / (float)254 * size.getX();

    p0.setXY(position.getX() + 8, position.getY() + 8);
    p1.setXY(position.getX() + size.getX() - 8, position.getY() + 8);
    p2.setXY(position.getX() + 8, position.getY() + size.getY() - 8);
    p3.setXY(position.getX() + size.getX() - 8, position.getY() + size.getY() - 8);
    p4.setXY(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + pocketRadius);
    p5.setXY(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + picSize.getY() - pocketRadius);

    checkp.push_back(Vector2(position.getX() + pocketRadius + 28, position.getY() + 15));//topleft_left
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius - 8, position.getY() + 15));//topleft_right
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius + 8, position.getY() + 15));//topright_left
    checkp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 28,position.getY() + 15));//topright_right
    checkp.push_back(Vector2(position.getX() + pocketRadius + 28, position.getY() + size.getY() - 15));//bottomleft_left
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius - 8, position.getY() + size.getY() - 15));//bottomleft_right
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius + 8, position.getY() + size.getY() - 15));//bottomright_left
    checkp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 28, position.getY() + size.getY() - 15));//bottomright_right
    checkp.push_back(Vector2(position.getX() + 15, position.getY() + pocketRadius + 28));//left_top
    checkp.push_back(Vector2(position.getX() + 15, position.getY() + size.getY() - pocketRadius - 28));//left_bottom
    checkp.push_back(Vector2(position.getX() + size.getX() - 15, position.getY() + pocketRadius + 28));//right_top
    checkp.push_back(Vector2(position.getX() + size.getX() - 15, position.getY() + size.getY() - pocketRadius - 28));//right_bottom

    pocketp.push_back(Vector2(position.getX() + pocketRadius + 8, position.getY()));//same position with checkp
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius, position.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius, position.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 8,position.getY()));
    pocketp.push_back(Vector2(position.getX() + pocketRadius + 8, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 8, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX(), position.getY() + pocketRadius + 8));
    pocketp.push_back(Vector2(position.getX(), position.getY() + size.getY() - pocketRadius - 8));
    pocketp.push_back(Vector2(position.getX() + size.getX(), position.getY() + pocketRadius + 8));
    pocketp.push_back(Vector2(position.getX() + size.getX(), position.getY() + size.getY() - pocketRadius - 8));

    T1<<QPoint(pocketp[0].getX(),pocketp[0].getY())<<QPoint(pocketp[1].getX(),pocketp[1].getY())
            <<QPoint(checkp[1].getX(),checkp[1].getY())<<QPoint(checkp[0].getX(),checkp[0].getY());

    T2<<QPoint(pocketp[2].getX(),pocketp[2].getY())<<QPoint(pocketp[3].getX(),pocketp[3].getY())
            <<QPoint(checkp[3].getX(),checkp[3].getY())<<QPoint(checkp[2].getX(),checkp[2].getY());

    T3<<QPoint(pocketp[4].getX(),pocketp[4].getY())<<QPoint(pocketp[5].getX(),pocketp[5].getY())
            <<QPoint(checkp[5].getX(),checkp[5].getY())<<QPoint(checkp[4].getX(),checkp[4].getY());

    T4<<QPoint(pocketp[6].getX(),pocketp[6].getY())<<QPoint(pocketp[7].getX(),pocketp[7].getY())
            <<QPoint(checkp[7].getX(),checkp[7].getY())<<QPoint(checkp[6].getX(),checkp[6].getY());

    T5<<QPoint(pocketp[8].getX(),pocketp[8].getY())<<QPoint(pocketp[9].getX(),pocketp[9].getY())
            <<QPoint(checkp[9].getX(),checkp[9].getY())<<QPoint(checkp[8].getX(),checkp[8].getY());

    T6<<QPoint(pocketp[10].getX(),pocketp[10].getY())<<QPoint(pocketp[11].getX(),pocketp[11].getY())
            <<QPoint(checkp[11].getX(),checkp[11].getY())<<QPoint(checkp[10].getX(),checkp[10].getY());
}

Vector2 Table::getSize() const
{
    return size;
}

vector<Vector2> Table::getCheckp() const
{
    return this->checkp;
}

vector<Vector2> Table::getPocketp() const
{
    return this->pocketp;
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

    painter.drawRect(QRectF(0, 600, 1280, 120));

    painter.drawRect(QRectF(picPosition.getX(), picPosition.getY(), picSize.getX(), picSize.getY()));

    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.setBrush(QBrush(QColor(68, 149, 60)));
    painter.drawRect(QRectF(position.getX(), position.getY(), size.getX(), size.getY()));

    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.setBrush(QBrush(QColor(0,0,0)));
    painter.drawEllipse(QPoint(position.getX() + 8, position.getY() + 8),pocketRadius, pocketRadius);
    painter.drawEllipse(QPoint(position.getX() + size.getX() - 8, position.getY() + 8), pocketRadius , pocketRadius);
    painter.drawEllipse(QPoint(position.getX() + 8, position.getY()+size.getY() - 8), pocketRadius,pocketRadius);
    painter.drawEllipse(QPoint(position.getX() + size.getX() - 8, position.getY() + size.getY() - 8),
                        pocketRadius,pocketRadius);
    painter.drawEllipse(QPoint(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + pocketRadius),
                        pocketRadius, 0.75 * pocketRadius);
    painter.drawEllipse(QPoint(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + picSize.getY() - pocketRadius),
                        pocketRadius, 0.75 * pocketRadius);

    painter.setPen(QPen(QColor(255,255,255)));
    painter.drawLine(position.getX() + lineX, position.getY(), position.getX() + lineX, position.getY() + size.getY());

    painter.setPen(QPen(QColor(100,100,100)));
    painter.setBrush(QBrush(QColor(80,149,80)));
    painter.drawPolygon(T1);
    painter.drawPolygon(T2);
    painter.drawPolygon(T3);
    painter.drawPolygon(T4);
    painter.drawPolygon(T5);
    painter.drawPolygon(T6);
}

bool Table::positionIsLegal(Vector2 p,Referee &referee)
{
    Vector3 V(p.getX(),p.getY(),0);
    if( (p.getX() > checkp[9].getX() + referee.getBallRadius()) && (p.getX() < position.getX() + lineX) &&
            (p.getY() > checkp[0].getY() + referee.getBallRadius()) &&
            (p.getY() < checkp[5].getY() - referee.getBallRadius()))
        {
            int i;
            for(i = 0; i < referee.getBallsList().size(); i++)
            {
                if(referee.getBallsList()[i].getPosition().DistanceTo(V) < 2 * referee.getBallRadius())
                    break;
            }
            if(i != referee.getBallsList().size())
                return false;
            else
                return true;
    }
    return false;
}

bool Table::checkPockets(Ball& ball)
{
    // if the ball is in the pocket return true;
    if((ball.getPosition().DistanceTo(p0) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p1) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p2) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p3) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p4) <= 0.75 * pocketRadius )||
            (ball.getPosition().DistanceTo(p5) <= 0.75 * pocketRadius ))
        return true;
    return false;
}

void Table::clear()
{
    checkp.clear();
    pocketp.clear();

    T1.clear();
    T2.clear();
    T3.clear();
    T4.clear();
    T5.clear();
    T6.clear();
}
