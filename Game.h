// Copyright (C) 2014 Team306

#ifndef GAME_H
#define GAME_H 


#include <QPainter>
#include "BallsManager.h"
#include "Table.h"
#include "Cue.h"
#include "GameSever.h"
#include "GameClient.h"

// control all logic in this class
// such as initialize a new game
// change game state, etc.

enum GAME_STATE 
{ 
	WAIT_FOR_STROKE, 
	FREE_BALL, 
	BALL_IS_RUNNING, 
	START_FRAME, 
	END_FRAME, 
	WAIT_FOR_CONNECT, 
	START_AND_CONNECT_CHOOSE, 
};

enum GAME_MODE 
{ 
	PRACTICE_MODE,
	VERSUS_MODE, 
	NETWORK_MODE, 
};

enum NETWORK_RULE
{
    SERVER,
    CLIENT,
};

class Game
{
private:
	BallsManager ballsManager;
	Table table;
	Referee referee;
	Cue cue;
    Vector2 mousePosition;
    Player player1;
    Player player2;
    Player *current_player;
    GameSever *game_sever;
    QTcpSocket *server_client;
    GameClient *game_client;

	GAME_STATE gameState;
	GAME_MODE gameMode;
    GAME_RULE gameRule;
    NETWORK_RULE network_rule;

	// debug variables
	int elapsedTime;

public:
	Game();
	~Game();

	void init(); // do all init here

	// update and draw
	void Update();
	void Draw(QPainter &);

	// deal with mouse event
	void setMousePosition(Vector2);
	void mousePress(int elapsed);

	GAME_STATE getGameState() const;

	void displayStartFrame(QPainter &);
	void displayEndFrame(QPainter &);
	void displayPlayer(QPainter &);
	void displayWaitingFrame(QPainter &);
	void displayConnectChooseFrame(QPainter &);

	void checkStartFrameClick();
	void checkConnectChooseFrame();

    GameSever* getGameSever() const;
    GameClient* getGameClient() const;
    GAME_RULE getGameRule() const;

    PLAYER_FLAG getPlayerFlag() const;
    GAME_MODE getGameMode() const;
    NETWORK_RULE getNetworkRule() const;
    void GameBegin();
    void ClientInit(int _gameRule);
};


#endif
