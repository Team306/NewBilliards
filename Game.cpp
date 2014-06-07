// Copyright (C) 2014 Team306

#include "Game.h"
#include <iostream>

Game::Game()
{
	// initialize in init method
	// gameState = FREE_BALL;
	gameState = START_FRAME;
    gameRule = EIGHT_BALL;
	elapsedTime = 0;
    player1.init();
    player2.init();
    player1.setPlayerflag(LOCAL);
    player2.setPlayerflag(GUEST);
    current_player = &player1;
}

Game::~Game()
{
}

void Game::init()
{
	// init here

    referee.init(gameRule);
    table.init(referee);
	ballsManager.init(referee);
	cue.init(referee);
}

void Game::Update()
{
	// update
	cue.Update(gameState, mousePosition);
    ballsManager.Update(table, current_player);

    if(player1.getBalltype() == NOTDEF || player2.getBalltype() == NOTDEF){
        if(current_player->getBalltype() == SMALL){
            if(current_player->getPlayerflag() == LOCAL){
                player2.setBalltype(BIG);
            }
            else player1.setBalltype(BIG);
        }
        else{
            if(current_player->getBalltype() == BIG){
                if(current_player->getPlayerflag() == LOCAL){
                    player2.setBalltype(SMALL);
                }
                else player1.setBalltype(SMALL);
            }
        }
    }



	switch (gameState)
	{
		case FREE_BALL:
			// check before set position
            if(table.positionIsLegal(mousePosition,referee))
            {
                ballsManager.getCueBall().setPosition(mousePosition);
            }
			break;
		case BALL_IS_RUNNING:
			if (!ballsManager.isRunning())
			{
                if(referee.judge(current_player,ballsManager.getBallsList()) == TO_FREE_BALL){
                    gameState = FREE_BALL;
                    if(current_player->getPlayerflag() == LOCAL){
                        current_player->Exchange();
                        current_player = &player2;
                        break;
                    }
                    else{
                        current_player->Exchange();
                        current_player = &player1;
                        break;
                    }
                }

                if(referee.judge(current_player,ballsManager.getBallsList()) == TO_EXCHANGE){
                    gameState = WAIT_FOR_STROKE;
                    if(current_player->getPlayerflag() == LOCAL){
                        current_player->Exchange();
                        current_player = &player2;
                        break;
                    }
                    else{
                        current_player->Exchange();
                        current_player = &player1;
                        break;
                    }
                }

                if(referee.judge(current_player,ballsManager.getBallsList()) == TO_GOON){
                    current_player->Goon();
                    gameState = WAIT_FOR_STROKE;
                    break;
                }

                if(referee.judge(current_player,ballsManager.getBallsList()) == TO_END){
                    gameState = END_FRAME;
                    break;
                }

				// call the referee
			}
			break;
        case WAIT_FOR_STROKE:
            break;
        case START_FRAME:
        	break;
	}
}

void Game::Draw(QPainter& painter)
{
	// draw all thing 
    table.Draw(painter);
    ballsManager.Draw(painter);

    // only display the cue when gameState == wait for stroke
    switch (gameState)
    {
    	case WAIT_FOR_STROKE:
    		cue.Draw(painter, ballsManager.getCueBall());
            displayPlayer(painter);
    		break;
        case FREE_BALL:
            displayPlayer(painter);
            break;
        case BALL_IS_RUNNING:
            displayPlayer(painter);
            break;
        case END_FRAME:
            //painter.setFont(font);
            if(player1.getGameresult() == SUCCESS){
                painter.drawText(QRectF(108, 88, 1000, 250), "PLAY1 WIN!!!");
            }
            else{
                painter.drawText(QRectF(108, 88, 1000, 250), "PLAY2 WIN!!!");
            }
            displayEndFrame(painter);
            break;
        case START_FRAME:
            // print the title
            displayStartFrame(painter);
        	break;
    }

    // debug info
    QFont font;
    painter.setFont(font);
    painter.drawText(QRectF(420, 640, 250, 25), "mouse press elapsed time");
    painter.drawText(QRectF(580, 640, 50, 25), QString::number(elapsedTime));
    painter.drawText(QRectF(400, 640, 100, 100),QString::number(current_player->getPlayerflag()));
    painter.drawText(QRectF(400, 600, 50, 25),QString::number(current_player->getBalltype()));
    painter.drawText(QRectF(500, 600, 50, 25),QString::number(current_player->getHitflag()));
    //std::cout<<getPlayerflag()<<std::endl;

}

void Game::setMousePosition(Vector2 position)
{
	mousePosition = position;
}

void Game::mousePress(int elapsed)
{
	// use in debug
	elapsedTime = elapsed;
	// do else thing
	switch (gameState)
	{
		case FREE_BALL:
			gameState = WAIT_FOR_STROKE;
			break;
		case WAIT_FOR_STROKE:
            cue.Stroke(elapsed, ballsManager.getCueBall());
            gameState = BALL_IS_RUNNING;
			break;
        case BALL_IS_RUNNING:
            break;    
        case START_FRAME:
        	// decide game mode
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
                gameState = FREE_BALL;
                gameMode = NETWORK_MODE;
                ballsManager.getCueBall().setPosition(Vector2(240, 360));
            }

            // choose rule
            if (QRect(900, 500, 300, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
            {
                gameRule = EIGHT_BALL;
                init();
            }
            if (QRect(900, 550, 300, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
            {
                gameRule = NINE_BALL;
                init();
            }
            if (QRect(900, 600, 300, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
            {
                gameRule = SNOOKER;
                init();
            }

        	break;
	}
}

GAME_STATE Game::getGameState() const
{
	return gameState;
}

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
    painter.drawText(QRectF(900, 500, 300, 30), "Eight Ball");
    painter.drawText(QRectF(900, 550, 300, 30), "Nine Ball");
    painter.drawText(QRectF(900, 600, 300, 30), "Snooker");

    switch (gameRule)
    {
        case EIGHT_BALL:
            painter.drawText(QRectF(860, 500, 300, 30), "√");
            break;
        case NINE_BALL:
            painter.drawText(QRectF(860, 550, 300, 30), "√");
            break;
        case SNOOKER:
            painter.drawText(QRectF(860, 600, 300, 30), "√");
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
        painter.drawText(QRectF(880, 670, 1000, 250), "Player 2");    
    }
    else
    {
        painter.setFont(fontSmall);
        painter.drawText(QRectF(300, 670, 1000, 250), "Player 1");
        painter.setFont(fontBig);
        painter.drawText(QRectF(820, 640, 1000, 250), "Player 2");            
    }
}
