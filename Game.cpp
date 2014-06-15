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
    client_connected = false;
    //player1.init();
    //player2.init();
    current_player = &player1;
    hitAngle = 0;
}

Game::~Game()
{
}

void Game::init()
{
	// init here
    gameState = START_FRAME;
    gameMode = PRACTICE_MODE;
    client_connected = false;
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
    ballsManager.Update(table, current_player, gameRule);

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
                if(gameMode == PRACTICE_MODE){
                    if(referee.judge(current_player, &ballsManager) == TO_FREE_BALL){
                       gameState = FREE_BALL;
                       current_player->Goon();
                    }
                    else{
                        gameState = WAIT_FOR_STROKE;
                        current_player->Goon();
                    }
                    referee.setTargetname(ballsManager.getBallsList());
                    break;
                }
                switch(referee.judge(current_player, &ballsManager)){
                    case TO_FREE_BALL:
                        referee.setTargetname(ballsManager.getBallsList());
                        gameState = FREE_BALL;
                        PlayerExchange();
                        break;
                    case TO_EXCHANGE:
                        referee.setTargetname(ballsManager.getBallsList());
                        gameState = WAIT_FOR_STROKE;
                        PlayerExchange();
                        break;
                    case TO_GOON:
                        referee.setTargetname(ballsManager.getBallsList());
                        current_player->Goon();
                        gameState = WAIT_FOR_STROKE;
                        break;
                    case TO_END:
                        gameState = END_FRAME;
                        break;
                    default:
                        break;
                }
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
    //table.Draw3D();
    //ballsManager.Draw();

    // only display the cue when gameState == wait for stroke
    switch (gameState)
    {
    	case WAIT_FOR_STROKE:
    		cue.Draw(painter, ballsManager.getCueBall());
            menu.displayPlayer(painter, current_player == &player1);
            menu.displayHitPoint(painter, hitPosition, hitAngle);
            menu.displayBack(painter, mousePosition);
    		break;
        case FREE_BALL:
            menu.displayPlayer(painter, current_player == &player1);
            menu.displayHitPoint(painter, hitPosition, hitAngle);
            menu.displayBack(painter, mousePosition);
            break;
        case BALL_IS_RUNNING:
            menu.displayPlayer(painter, current_player == &player1);
            menu.displayHitPoint(painter, hitPosition, hitAngle);
            menu.displayBack(painter, mousePosition);
            break;
        case END_FRAME:
            menu.displayEndFrame(painter, player1);
            break;
        case START_FRAME:
            // print the start frame
            menu.displayStartFrame(painter, mousePosition, gameRule);
        	break;
        case WAIT_FOR_CONNECT:
            menu.displayWaitingFrame(painter);
            break;
        case CONNECT_FRAME:
            menu.displayConnectFrame(painter, mousePosition);
            menu.displayBack(painter, mousePosition);
            break;
        default:
            break;
    }

    // debug info
    QFont font;
    painter.setFont(font);
    // painter.drawText(QRectF(420, 640, 250, 25), "mouse press elapsed time");
    // painter.drawText(QRectF(580, 640, 50, 25), QString::number(elapsedTime));
    // painter.drawText(QRectF(400, 640, 100, 100),QString::number(current_player->getPlayerflag()));
    // painter.drawText(QRectF(400, 600, 50, 25),QString::number(mousePosition.getX()));
    // painter.drawText(QRectF(440, 600, 50, 25),QString::number(mousePosition.getY()));
    //std::cout<<getPlayerflag()<<std::endl;
}

void Game::Draw3D()
{
    table.Draw3D();
    ballsManager.Draw3D();

    if (gameState == WAIT_FOR_STROKE)
    {
        displayTargetBalls();
    }
}


void Game::setMousePosition(Vector2 position)
{
	mousePosition = position;
    //std::cout<<"mousePosition<<<<<<"<<mousePosition.getX()<<","<<mousePosition.getY()<<std::endl;
}

void Game::mousePress(int elapsed)
{
	// use in debug
	elapsedTime = elapsed;
	// do else thing
	switch (gameState)
	{
		case FREE_BALL:
            if (checkBack(menu))
            {
                break;
            }

            if (cuePositionIsLegal())
            {
                gameState = WAIT_FOR_STROKE;
            }
			break;
		case WAIT_FOR_STROKE:
            if (checkBack(menu))
            {
                break;
            }
            if (checkHitPointClick(menu.getHitCenterPosition(), menu.getHitRadius(), menu.getAngleRadius()))
            {
                break;
            }
            // if do not change hit point continue
            cue.Stroke(elapsed, ballsManager.getCueBall(),mousePosition, hitPosition, hitAngle);
            gameState = BALL_IS_RUNNING;
			break;
        case BALL_IS_RUNNING:
            break;    
        case START_FRAME:
        	// decide game mode
            checkStartFrameClick(menu);
        	break;
        case CONNECT_FRAME:
            checkBack(menu);
            checkConnectFrameClick(menu);
            break;
        case END_FRAME:
            gameState = START_FRAME;
            init();
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
    gameState = FREE_BALL;
}

void Game::ClientInit(int _gameRule){
    gameRule = (GAME_RULE)_gameRule;
    referee.init(gameRule);
    table.init(referee);
    ballsManager.init(referee);
    cue.init(referee);
    gameState = FREE_BALL;
}


void Game::setClientConnected(bool connect_flag){
    client_connected = connect_flag;
}

bool Game::getClientConnected() const {
    return client_connected;
}

void Game::checkStartFrameClick(const Menu& menu)
{
    if (menu.getPracticeChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = FREE_BALL;
        gameMode = PRACTICE_MODE;
        ballsManager.getCueBall().setPosition(Vector2(300, 300));
    }
    if (menu.getVersusChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = FREE_BALL;
        gameMode = VERSUS_MODE;
        ballsManager.getCueBall().setPosition(Vector2(300, 300));
    }
    if (menu.getNetworkChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = CONNECT_FRAME;
        gameMode = NETWORK_MODE;
        ballsManager.getCueBall().setPosition(Vector2(300, 300));
    }

    // choose rule
    if (menu.getEightBallChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameRule = EIGHT_BALL;
        table.clear();
        init();
    }
    if (menu.getNineBallChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameRule = NINE_BALL;
        table.clear();
        init();
    }
    if (menu.getSnookerChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameRule = SNOOKER;
        table.clear();
        init();
    }
}

void Game::checkConnectFrameClick(const Menu& menu)
{
    if (menu.getStartChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = WAIT_FOR_CONNECT;
        game_sever->GameListen();
        network_rule = SERVER;
    }
    if (menu.getConnectChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        gameState = WAIT_FOR_CONNECT;
        game_client->GameConnect();
        network_rule = CLIENT;
        player1.setPlayerflag(GUEST);
        player2.setPlayerflag(LOCAL);
    }
}

bool Game::checkHitPointClick(Vector2 center, int hitRadius, int angleRadius)
{
    const float PI = 3.141593;

    // check hit point
    Vector2 newHitPosition = mousePosition - center;
    if (newHitPosition.Length() < hitRadius)
    {
        hitPosition = newHitPosition;
        return true;
    }

    // check hit angle
    if (newHitPosition.Length() > hitRadius && newHitPosition.Length() < angleRadius)
    {
        // if in the angle, change the hit angle and return true, else return false;
        float x = newHitPosition.getX();
        float y = -newHitPosition.getY();
        float angle = atan(y / x) / PI * 180;
        if (angle >= 0 && angle <= 85)
        {
            hitAngle = (int)angle;
            return true;
        }
    }
    return false;
}


void Game::PlayerExchange(){
    if(current_player == &player1){
        current_player->Exchange();
        current_player = &player2;
        return;
    }
    else{
        current_player->Exchange();
        current_player = &player1;
        return;
    }
}

bool Game::checkBack(const Menu& menu)
{
    if (menu.getBackChosen().contains(mousePosition.getX(), mousePosition.getY(), false))
    {
        if(gameMode == NETWORK_MODE){
            QByteArray tosend;
            tosend.clear();
            tosend.append(QString("O"));
            tosend.append(QString("#"));
            tosend.append(QString::number(1));
            tosend.append(QString("#"));
            if(network_rule == SERVER){
                getGameSever()->sendMessage(tosend);
            }
            else{
                getGameClient()->sendMessage(tosend);
            }
        }
        gameState = START_FRAME;
        table.clear();
        init();
        return true;
    }
    return false;
}

Cue& Game::getCue()
{
    return cue;
}

void Game::displayTargetBalls()
{
    // 3d display target balls here
    std::vector<Ball> remainBallsListCopy = ballsManager.getBallsList();
    // get current player and judge self balls 
    // and then set then to the right position and angle
    // directly draw them in this methods
    std::string targetName;
    int index;
    std::vector<int> targetIndexs;
    switch (gameRule)
    {
        case EIGHT_BALL:
            // if not decide ball type
            if (current_player->getBalltype() == NOTDEF)
            {
                break;
            }

            // if decide and display
            for (unsigned i = 0; i < remainBallsListCopy.size(); ++i)
            {
                if (referee.judgeSelfball(current_player, remainBallsListCopy[i].getName()))
                {
                    targetIndexs.push_back(i);
                }
            }

            if (targetIndexs.size() == 0)
            {
                // only remain eight ball
                for (unsigned i = 0; i < remainBallsListCopy.size(); ++i)
                {
                    if (remainBallsListCopy[i].getName() == "eight")
                    {
                        index = i;
                        break;
                    }
                }
                if (current_player == &player1)
                {
                    remainBallsListCopy[index].setPosition(Vector2(200 + 10, 660));
                    remainBallsListCopy[index].setRadius(10);
                    remainBallsListCopy[index].Draw3D();
                }
                else
                {
                    // draw under player1
                    remainBallsListCopy[index].setPosition(Vector2(630 + 10, 660));
                    remainBallsListCopy[index].setRadius(10);
                    remainBallsListCopy[index].Draw3D();
                }
            }
            else
            {
                // draw all potential target ball
                for (unsigned i = 0; i < targetIndexs.size(); ++i)
                {
                    index = targetIndexs[i];
                    if (current_player == &player1)
                    {
                        remainBallsListCopy[index].setPosition(Vector2(200 + 10 + i * 30, 660));
                        remainBallsListCopy[index].setRadius(10);
                        remainBallsListCopy[index].Draw3D();
                    }
                    else
                    {
                        // draw under player1
                        remainBallsListCopy[index].setPosition(Vector2(630 + 10 + i * 30, 660));
                        remainBallsListCopy[index].setRadius(10);
                        remainBallsListCopy[index].Draw3D();
                    }
                }
            }

            break;
        case NINE_BALL:
            targetName = referee.getTargetName();
            for (unsigned i = 0; i < remainBallsListCopy.size(); ++i)
            {
                if (remainBallsListCopy[i].getName() == targetName)
                {
                    index = i;
                    break;
                }
            }
            // just put the target ball at the center under the player name
            if (current_player == &player1)
            {
                // draw under player1
                remainBallsListCopy[index].setPosition(Vector2(200, 660));
                remainBallsListCopy[index].setRadius(10);
                remainBallsListCopy[index].Draw3D();
            }
            else
            {
                // draw under player1
                remainBallsListCopy[index].setPosition(Vector2(630, 660));
                remainBallsListCopy[index].setRadius(10);
                remainBallsListCopy[index].Draw3D();
            }
            break;
        default:
            break;
    }
}
