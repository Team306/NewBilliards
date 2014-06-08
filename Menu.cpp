// Copyright (C) 2014 Team306

#include "Game.h"

void Game::displayStartFrame(QPainter& painter)
{
    QColor gray(100, 100, 100, 200);
    painter.setPen(gray);

    QFont font("Consolas", 100, 100, false);
    painter.setFont(font);
            
    painter.drawText(QRectF(108, 88, 1000, 250), "Billiards");

    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);

    painter.drawText(QRectF(100, 80, 1000, 250), "Billiards");

    // print the 3 mode choose
    if (QRect(420, 300, 350, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        font.setWeight(50);
        painter.setFont(font);
        painter.drawText(QRectF(360, 280, 500, 100), "Practice Mode");
    }
    else
    {
        font.setPointSize(30);
        font.setWeight(30);            
        painter.setFont(font);
        painter.drawText(QRectF(420, 300, 350, 50), "Practice Mode");
    }
            
    if (QRect(420, 400, 350, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        font.setWeight(50);
        painter.setFont(font);
        painter.drawText(QRectF(360, 380, 500, 100), "Versus Mode");
    }
    else
    {
        font.setPointSize(30);
        font.setWeight(30);            
        painter.setFont(font);
        painter.drawText(QRectF(420, 400, 350, 50), "Versus Mode");
    }
            
    if (QRect(420, 500, 350, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        font.setWeight(50);
        painter.setFont(font);
        painter.drawText(QRectF(360, 480, 500, 100), "Network Mode");
    }
    else
    {
        font.setPointSize(30);
        font.setWeight(30);            
        painter.setFont(font);
        painter.drawText(QRectF(420, 500, 350, 50), "Network Mode");
    }

    // print 3 rule
    font.setPointSize(20);
    font.setWeight(20);
    painter.setFont(font);
    painter.drawText(QRectF(900, 490, 300, 30), "Eight Ball");
    painter.drawText(QRectF(900, 540, 300, 30), "Nine Ball");
    painter.drawText(QRectF(900, 590, 300, 30), "Snooker");

    switch (gameRule)
    {
        case EIGHT_BALL:
            painter.drawText(QRectF(860, 490, 300, 30), "√");
            break;
        case NINE_BALL:
            painter.drawText(QRectF(860, 540, 300, 30), "√");
            break;
        case SNOOKER:
            painter.drawText(QRectF(860, 590, 300, 30), "√");
            break;
    }

    // print the copyright text
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(QRectF(100, 600, 250, 25), "Copyright (C) 2014 Team306");
}

void Game::displayEndFrame(QPainter& painter)
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
        painter.drawText(QRectF(480, 320, 1000, 250), "Player 1 Wins!");
    }
    else
    {
        painter.drawText(QRectF(480, 320, 1000, 250), "Player 2 Wins!");
    }
}

void Game::displayPlayer(QPainter& painter)
{
    // display player here
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);

    QFont fontBig("Consolas", 40, 40, false);
    QFont fontSmall("Consolas", 20, 20, false);
    painter.setFont(fontSmall);

    if (current_player == &player1)
    {
        painter.setFont(fontBig);
        painter.drawText(QRectF(240, 640, 1000, 250), "Player 1");
        painter.setFont(fontSmall);
        painter.drawText(QRectF(860, 660, 1000, 250), "Player 2");    
    }
    else
    {
        painter.setFont(fontSmall);
        painter.drawText(QRectF(300, 660, 1000, 250), "Player 1");
        painter.setFont(fontBig);
        painter.drawText(QRectF(800, 640, 1000, 250), "Player 2");            
    }
}

void Game::displayWaitingFrame(QPainter& painter)
{
    QColor gray(20, 20, 20, 150);
    painter.setPen(gray);
    painter.setBrush(QBrush(gray));
    painter.drawRect(QRectF(0, 0, 1280, 720));

    QFont font("Consolas", 30, 30, false);
    painter.setFont(font);
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);
    painter.drawText(QRectF(360, 320, 1000, 250), "Waiting for connecting...");    
}

void Game::displayConnectChooseFrame(QPainter& painter)
{
    QColor gray(20, 20, 20, 150);
    painter.setPen(gray);
    painter.setBrush(QBrush(gray));
    painter.drawRect(QRectF(0, 0, 1280, 720));

    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);

    QFont font("Consolas", 30, 30, false);
    if (QRect(400, 500, 200, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        painter.setFont(font);
        painter.drawText(QRectF(365, 480, 300, 80), "Start");
    }
    else
    {
        font.setPointSize(30);
        painter.setFont(font);
        painter.drawText(QRectF(400, 500, 200, 50), "Start");
    }

    if (QRect(720, 500, 200, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        font.setPointSize(50);
        painter.setFont(font);
        painter.drawText(QRectF(670, 480, 300, 80), "Connect");
    }
    else
    {
        font.setPointSize(30);
        painter.setFont(font);
        painter.drawText(QRectF(720, 500, 200, 50), "Connect");
    }
}

void Game::displayHitPoint(QPainter& painter)
{
    // Hit Point
    QColor gray(20, 20, 20, 150);
    painter.setPen(gray);
    painter.setBrush(QBrush(gray));
    painter.drawRect(QRectF(0, 0, 1280, 720));

    displayChangeLabel(painter);

    // sth like draw a sphere
    float r = 120;
    Vector2 p(1000, 500);

    QRadialGradient gradient(QPointF(r, r), r, QPointF(r * 0.5, r * 0.5));
    gradient.setColorAt(0, QColor(255, 255, 255, 255));
    gradient.setColorAt(0.05, QColor(255, 255, 255));
    gradient.setColorAt(1, QColor(195, 195, 195));

    painter.save();
    painter.translate(p.getX() - r, p.getY() - r);
    painter.setBrush(QBrush(gradient));
    painter.setPen(QColor(195, 195, 195));
    painter.drawEllipse(0, 0, r * 2, r * 2);
    painter.restore();

    // display red point
    Vector2 redPosition = p + hitPosition;
    r = 10;
    painter.save();
    painter.translate(redPosition.getX() - r, redPosition.getY() - r);
    painter.setBrush(QBrush(QColor(255, 0, 0)));
    painter.setPen(QColor(255, 0, 0));
    painter.drawEllipse(0, 0, r * 2, r * 2);
    painter.restore();

    // display angle rectangle
    // painter.drawText(QRectF(580, 640, 50, 25), QString::number(hitAngle));

}

void Game::displayChangeLabel(QPainter& painter)
{
    QFont font("Consolas", 16, 16, false);
    painter.setFont(font);
    QColor miku_blue(00, 174, 255);
    painter.setPen(miku_blue);
    painter.drawText(QRectF(1050, 680, 200, 30), "Change Hit Point");
}

void Game::checkStartFrameClick()
{
    if (QRect(420, 300, 350, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = FREE_BALL;
        gameMode = PRACTICE_MODE;
        ballsManager.getCueBall().setPosition(Vector2(240, 360));
    }
    if (QRect(420, 400, 350, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = FREE_BALL;
        gameMode = VERSUS_MODE;
        ballsManager.getCueBall().setPosition(Vector2(240, 360));
    }
    if (QRect(420, 500, 350, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = START_AND_CONNECT_CHOOSE;
        gameMode = NETWORK_MODE;
        ballsManager.getCueBall().setPosition(Vector2(240, 360));
    }

    // choose rule
    if (QRect(900, 490, 300, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameRule = EIGHT_BALL;
        table.clear();
        init();
    }
    if (QRect(900, 540, 300, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameRule = NINE_BALL;
        table.clear();
        init();
    }
    if (QRect(900, 590, 300, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameRule = SNOOKER;
        table.clear();
        init();
    }
}

void Game::checkConnectChooseFrame()
{
    if (QRect(400, 500, 200, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = WAIT_FOR_CONNECT;
        // set flag
    }
    if (QRect(720, 500, 200, 50).contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = WAIT_FOR_CONNECT;
        // set flag
    }
}

void Game::changeHitPoint()
{
    Vector2 center(1000, 500);
    Vector2 newHitPosition = mousePosition - center;
    if (newHitPosition.Length() < 120)
    {
        hitPosition = newHitPosition;
    }
}
