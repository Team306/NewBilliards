// Copyright (C) 2014 Team306

#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
    // start frame
    titleRect = QRectF(100, 80, 1000, 250);
    titleBackRect = QRectF(108, 88, 1000, 250);

    practiceModeRectChosen = QRect(400, 300, 350, 50); 
    practiceModeRectSmall = QRectF(400, 300, 350, 50);
    practiceModeRectBig = QRectF(340, 280, 500, 100);
    versusModeRectChosen = QRect(400, 390, 350, 50); 
    versusModeRectSmall = QRectF(400, 390, 350, 50);
    versusModeRectBig = QRectF(340, 370, 500, 100);
    networkModeRectChosen = QRect(400, 480, 350, 50);
    networkModeRectSmall = QRectF(400, 480, 350, 50);
    networkModeRectBig = QRectF(340, 460, 500, 100);

    eightBallRuleRect = QRectF(840, 570, 300, 30);
    nineBallRuleRect = QRectF(840, 610, 300, 30);
    snookerRuleRect = QRectF(840, 650, 300, 30);

    eightBallChosen = QRect(840, 570, 300, 30);
    nineBallChosen = QRect(840, 610, 300, 30);
    snookerChosen = QRect(840, 650, 300, 30);

    eightBallTick = QRectF(800, 570, 300, 30);
    nineBallTick = QRectF(800, 610, 300, 30);
    snookerTick = QRectF(800, 650, 300, 30);

    copyrightRect = QRectF(50, 640, 250, 25);

    // end frame
    endTitleRect = QRectF(410, 260, 1000, 250);
    endContinueRect = QRectF(340, 480, 1000, 250);

    // player
    player1RectSmall = QRectF(250, 620, 1000, 250);
    player1RectBig = QRectF(200, 600, 1000, 250);
    player2RectSmall = QRectF(680, 620, 1000, 250);
    player2RectBig = QRectF(630, 600, 1000, 250);

    // waiting frame
    waitingRect = QRectF(320, 260, 1000, 250);

    // connect frame
    startRectChosen = QRect(300, 500, 200, 50);
    startRectSmall = QRectF(300, 500, 200, 50);
    startRectBig = QRectF(265, 480, 300, 80);
    connectRectChosen = QRect(680, 500, 200, 50);
    connectRectSmall = QRectF(680, 500, 200, 50);
    connectRectBig = QRectF(630, 480, 300, 80);

    // hit point
    hitPointRadius = 60;
    hitPointCenterPosition = Vector2(940, 635);
    redPointRadius = 7;
    
    // hit angle
    circularWidth = 25;
    offset = 5;
}

Menu::~Menu()
{
}

void Menu::displayStartFrame(QPainter& painter, Vector2 mousePosition, int gameRule)
{
    // set font
    QFont font("Consolas", 100, 100, false);
    painter.setFont(font);

    // paint the lower part
    QColor gray(100, 100, 100, 200);
    painter.setPen(gray);
    painter.drawText(titleBackRect, "Billiards");

    // paint the upper part
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);
    painter.drawText(titleRect, "Billiards");

    // print the 3 mode choose
    if (practiceModeRectChosen.contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        font.setWeight(50);
        painter.setFont(font);
        painter.drawText(practiceModeRectBig, "Practice Mode");
    }
    else
    {
        font.setPointSize(30);
        font.setWeight(30);            
        painter.setFont(font);
        painter.drawText(practiceModeRectSmall, "Practice Mode");
    }
            
    if (versusModeRectChosen.contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        font.setWeight(50);
        painter.setFont(font);
        painter.drawText(versusModeRectBig, "Versus Mode");
    }
    else
    {
        font.setPointSize(30);
        font.setWeight(30);            
        painter.setFont(font);
        painter.drawText(versusModeRectSmall, "Versus Mode");
    }
            
    if (networkModeRectChosen.contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        font.setWeight(50);
        painter.setFont(font);
        painter.drawText(networkModeRectBig, "Network Mode");
    }
    else
    {
        font.setPointSize(30);
        font.setWeight(30);            
        painter.setFont(font);
        painter.drawText(networkModeRectSmall, "Network Mode");
    }

    // print 3 rule
    font.setPointSize(20);
    font.setWeight(20);
    painter.setFont(font);
    painter.drawText(eightBallRuleRect, "Eight Ball");
    painter.drawText(nineBallRuleRect, "Nine Ball");
    painter.drawText(snookerRuleRect, "Snooker");

    // paint chosen rule
    switch (gameRule)
    {
        case EIGHT_BALL:
            painter.drawText(eightBallTick, "√");
            break;
        case NINE_BALL:
            painter.drawText(nineBallTick, "√");
            break;
        case SNOOKER:
            painter.drawText(snookerTick, "√");
            break;
    }

    // print the copyright text
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(copyrightRect, "Copyright (C) 2014 Team306");
}

void Menu::displayEndFrame(QPainter& painter, const Player& player1)
{
    // display end frame here
    QColor gray(20, 20, 20, 150);
    painter.setPen(gray);
    painter.setBrush(QBrush(gray));
    painter.drawRect(QRectF(0, 0, 1280, 720));

    QFont font("Consolas", 30, 30, false);
    painter.setFont(font);
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);

    if (player1.getGameresult() == SUCCESS)
    {
        painter.drawText(endTitleRect, "Player 1 Wins!");
    }
    else
    {
        painter.drawText(endTitleRect, "Player 2 Wins!");
    }

    font.setPointSize(20);
    painter.setFont(font);
    painter.drawText(endContinueRect, "Press Mouse Button to continue...");
}

void Menu::displayPlayer(QPainter& painter, bool isPlayer1)
{
    // display player here
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);

    QFont fontBig("Consolas", 40, 40, false);
    QFont fontSmall("Consolas", 20, 20, false);
    painter.setFont(fontSmall);

    if (isPlayer1)
    {
        painter.setFont(fontBig);
        painter.drawText(player1RectBig, "Player 1");
        painter.setFont(fontSmall);
        painter.drawText(player2RectSmall, "Player 2");    
    }
    else
    {
        painter.setFont(fontSmall);
        painter.drawText(player1RectSmall, "Player 1");
        painter.setFont(fontBig);
        painter.drawText(player2RectBig, "Player 2");            
    }
}

void Menu::displayWaitingFrame(QPainter& painter)
{
    QColor gray(20, 20, 20, 150);
    painter.setPen(gray);
    painter.setBrush(QBrush(gray));
    painter.drawRect(QRectF(0, 0, 1280, 720));

    QFont font("Consolas", 30, 30, false);
    painter.setFont(font);
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);
    painter.drawText(waitingRect, "Waiting for connecting...");    
}

void Menu::displayConnectFrame(QPainter& painter, Vector2 mousePosition)
{
    QColor gray(20, 20, 20, 150);
    painter.setPen(gray);
    painter.setBrush(QBrush(gray));
    painter.drawRect(QRectF(0, 0, 1280, 720));

    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);

    QFont font("Consolas", 30, 30, false);
    if (startRectChosen.contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        painter.setFont(font);
        painter.drawText(startRectBig, "Start");
    }
    else
    {
        font.setPointSize(30);
        painter.setFont(font);
        painter.drawText(startRectSmall, "Start");
    }

    if (connectRectChosen.contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        painter.setFont(font);
        painter.drawText(connectRectBig, "Connect");
    }
    else
    {
        font.setPointSize(30);
        painter.setFont(font);
        painter.drawText(connectRectSmall, "Connect");
    }
}

void Menu::displayHitPoint(QPainter& painter, Vector2 hitPosition, int hitAngle)
{
    // int hitAngle = 10;
    const float PI = 3.141593;

    // first draw the hit angle
    QColor brown(91, 29, 28);
    QColor frontColor(56, 149, 8);
    QColor frontLine(40, 128, 8);

    // set gradient
    QLinearGradient LinearGradient(hitPointCenterPosition.getX() + hitPointRadius + offset + circularWidth, hitPointCenterPosition.getY(), 
        hitPointCenterPosition.getX(), hitPointCenterPosition.getY());
    LinearGradient.setColorAt(0.0, frontLine);
    LinearGradient.setColorAt(0.2, frontColor);
    LinearGradient.setColorAt(1, QColor(255, 255, 255));

    painter.setPen(QPen(frontLine, 3, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(LinearGradient));

    // draw
    painter.drawPie(QRectF(hitPointCenterPosition.getX() - hitPointRadius - circularWidth - offset, 
        hitPointCenterPosition.getY() - hitPointRadius - circularWidth - offset, 
        (hitPointRadius + circularWidth + offset) * 2, (hitPointRadius + circularWidth + offset) * 2), 0, 85 * 16);
    painter.setPen(QPen(brown, 3, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(brown);
    painter.drawPie(QRectF(hitPointCenterPosition.getX() - hitPointRadius - offset, hitPointCenterPosition.getY() - hitPointRadius - offset, 
        (hitPointRadius + offset) * 2, (hitPointRadius + offset) * 2), 0, 85 * 16);
    painter.setPen(QPen(frontLine, 3, Qt::SolidLine, Qt::FlatCap));
    painter.drawArc(QRectF(hitPointCenterPosition.getX() - hitPointRadius - offset, hitPointCenterPosition.getY() - hitPointRadius - offset, 
        (hitPointRadius + offset) * 2, (hitPointRadius + offset) * 2), -1 * 16, 86 * 16);

    // draw point line
    QColor pointLineColor(145, 13, 12);
    painter.setPen(QPen(pointLineColor, 2, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(hitPointCenterPosition.getX() + (hitPointRadius + offset + 1) * cos(float(hitAngle) / 180 * PI), 
        hitPointCenterPosition.getY() - (hitPointRadius + offset + 1) * sin(float(hitAngle) / 180 * PI), 
        hitPointCenterPosition.getX() + (hitPointRadius + offset + circularWidth + 1) * cos(float(hitAngle) / 180 * PI), 
        hitPointCenterPosition.getY() - (hitPointRadius + offset + circularWidth + 1) * sin(float(hitAngle) / 180 * PI));

    // Hit Point
    // draw white ball
    QRadialGradient gradient(QPointF(hitPointRadius, hitPointRadius), hitPointRadius, QPointF(hitPointRadius * 0.5, hitPointRadius * 0.5));
    gradient.setColorAt(0, QColor(255, 255, 255, 255));
    gradient.setColorAt(0.05, QColor(255, 255, 255));
    gradient.setColorAt(1, QColor(195, 195, 195));

    painter.save();
    painter.translate(hitPointCenterPosition.getX() - hitPointRadius, hitPointCenterPosition.getY() - hitPointRadius);
    painter.setBrush(QBrush(gradient));
    painter.setPen(QColor(195, 195, 195));
    painter.drawEllipse(0, 0, hitPointRadius * 2, hitPointRadius * 2);
    painter.restore();

    // display red point
    Vector2 redPosition = hitPointCenterPosition + hitPosition;
    painter.save();
    painter.translate(redPosition.getX() - redPointRadius, redPosition.getY() - redPointRadius);
    painter.setBrush(QBrush(QColor(255, 0, 0)));
    painter.setPen(QColor(255, 0, 0));
    painter.drawEllipse(0, 0, redPointRadius * 2, redPointRadius * 2);
    painter.restore();

    // display angle rectangle

    // sector color R 56 G 149 B 8 
    // point line color R 145 G 13 B 12
    // background color R 72 G 8 B 8 
}

void Menu::displayPauseButton(QPainter& painter)
{
    QFont font("Consolas", 16, 16, false);
    painter.setFont(font);
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);
    painter.drawText(QRectF(1050, 680, 200, 30), "Pause");
}

QRect Menu::getPracticeChosen() const
{
    return practiceModeRectChosen;
}

QRect Menu::getVersusChosen() const
{
    return versusModeRectChosen;
}

QRect Menu::getNetworkChosen() const
{
    return networkModeRectChosen;
}

QRect Menu::getEightBallChosen() const
{
    return eightBallChosen;
}

QRect Menu::getNineBallChosen() const
{
    return nineBallChosen;
}

QRect Menu::getSnookerChosen() const
{
    return snookerChosen;
}

QRect Menu::getStartChosen() const
{
    return startRectChosen;
}

QRect Menu::getConnectChosen() const
{
    return connectRectChosen;
}

Vector2 Menu::getHitCenterPosition() const
{
    return hitPointCenterPosition;
}

int Menu::getHitRadius() const
{
    return hitPointRadius;
}

int Menu::getAngleRadius() const
{
    return hitPointRadius + offset + circularWidth + offset;
}
