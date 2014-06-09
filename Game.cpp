// Copyright (C) 2014 Team306

#include "Game.h"
#include <iostream>

// another part about menu in Menu.cpp

Game::Game()
{
	// initialize in init method
    //gameState = FREE_BALL;
    game_sever = new GameSever;
    game_client = new GameClient;
    player1.setPlayerflag(LOCAL);
    player2.setPlayerflag(GUEST);
	gameState = START_FRAME;
    gameRule = EIGHT_BALL;
	elapsedTime = 0;
    //player1.init();
    //player2.init();
    current_player = &player1;
}

Game::~Game()
{
}

void Game::init()
{
	// init here
    gameState = START_FRAME;
    game_client->DisConnect();
    game_sever->StopListen();
    current_player = &player1;
    player1.setPlayerflag(LOCAL);
    player2.setPlayerflag(GUEST);
    elapsedTime = 0;
    player1.init();
    player2.init();
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
            if(current_player == &player1){
                player2.setBalltype(BIG);
            }
            else player1.setBalltype(BIG);
        }
        else{
            if(current_player->getBalltype() == BIG){
                if(current_player == &player1){
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
                // std::cout<<current_player->getCueball_in()<<std::endl;
                if(referee.judge(current_player,ballsManager.getBallsList()) == TO_FREE_BALL){
                    referee.setTargetname(ballsManager.getBallsList());
                    gameState = FREE_BALL;
                    if(current_player == &player1){
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
                    referee.setTargetname(ballsManager.getBallsList());
                    gameState = WAIT_FOR_STROKE;
                    if(current_player == &player1){
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
                    referee.setTargetname(ballsManager.getBallsList());
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
        default:
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
            displayChangeLabel(painter);
    		break;
        case FREE_BALL:
            displayPlayer(painter);
            break;
        case BALL_IS_RUNNING:
            displayPlayer(painter);
            break;
        case END_FRAME:
            displayEndFrame(painter);
            break;
        case START_FRAME:
            // print the start frame
            displayStartFrame(painter);
        	break;
        case WAIT_FOR_CONNECT:
            displayWaitingFrame(painter);
            break;
        case START_AND_CONNECT_CHOOSE:
            displayConnectChooseFrame(painter);
            break;
        case CHANGE_HIT_POINT:
            displayHitPoint(painter);
            break;
        default:
            break;
    }

    // debug info
    QFont font;
    painter.setFont(font);
    painter.drawText(QRectF(420, 640, 250, 25), "mouse press elapsed time");
    painter.drawText(QRectF(580, 640, 50, 25), QString::number(elapsedTime));
    painter.drawText(QRectF(400, 640, 100, 100),QString::number(current_player->getPlayerflag()));
    painter.drawText(QRectF(400, 600, 50, 25),QString::number(mousePosition.getX()));
    painter.drawText(QRectF(440, 600, 50, 25),QString::number(mousePosition.getY()));
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
            if (cuePositionIsLegal())
            {
                gameState = WAIT_FOR_STROKE;
            }
			break;
		case WAIT_FOR_STROKE:
            if (QRect(1050, 680, 200, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
            {
                gameState = CHANGE_HIT_POINT;
                break;
            }

            cue.Stroke(elapsed, ballsManager.getCueBall());
            gameState = BALL_IS_RUNNING;
			break;
        case BALL_IS_RUNNING:
            break;    
        case START_FRAME:
        	// decide game mode
            checkStartFrameClick();
        	break;
        case START_AND_CONNECT_CHOOSE:
            checkConnectChooseFrame();
            break;
        case END_FRAME:
            gameState = START_FRAME;
            init();
            break;
        case CHANGE_HIT_POINT:
            if (QRect(1050, 680, 200, 30).contains(mousePosition.getX(), mousePosition.getY(), false))
            {
                gameState = WAIT_FOR_STROKE;
                break;
            }
            // check other input
            changeHitPoint();
            break;
        default:
            break;
	}
}

GAME_STATE Game::getGameState() const
{
	return gameState;
}


GAME_RULE Game::getGameRule() const
{
    return gameRule;
}

bool Game::cuePositionIsLegal()
{
    std::vector<Ball> ballsList = ballsManager.getBallsList();
    for (unsigned i = 0; i < ballsList.size(); ++i)
    {
        Vector3 cueBallPosition = ballsManager.getCueBall().getPosition();
        if (cueBallPosition.DistanceTo(ballsList[i].getPosition()) < 2 * ballsManager.getCueBall().getRadius())
        {
            return false;
        }
    }
    return true;
}

GameSever* Game::getGameSever() const{
    return game_sever;
}

GameClient* Game::getGameClient() const{
    return game_client;
}

PLAYER_FLAG Game::getPlayerFlag() const{
    return current_player->getPlayerflag();
}

GAME_MODE Game::getGameMode() const{
    return gameMode;
}

NETWORK_RULE Game::getNetworkRule() const{
    return network_rule;
}

void Game::GameBegin() {
    gameState = WAIT_FOR_STROKE;
}

void Game::ClientInit(int _gameRule){
    gameRule = (GAME_RULE)_gameRule;
    referee.init(gameRule);
    table.init(referee);
    ballsManager.init(referee);
    cue.init(referee);
    gameState = WAIT_FOR_STROKE;
}
