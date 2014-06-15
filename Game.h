// Copyright (C) 2014 Team306

#ifndef GAME_H
#define GAME_H 


#include <QPainter>
#include "BallsManager.h"
#include "Table.h"
#include "Cue.h"
#include "GameSever.h"
#include "GameClient.h"
#include "Menu.h"

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
	CONNECT_FRAME, 
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
    GameClient *game_client;
    bool client_connected;

	GAME_STATE gameState;
	GAME_MODE gameMode;
    GAME_RULE gameRule;
    NETWORK_RULE network_rule;

    // use in display menu
    Menu menu;

    Vector2 hitPosition;
    int hitAngle;	// from 0 to 85, maybe can set a max value below 90

	// debug variables
	int elapsedTime;

public:
	Game();
	~Game();

	void init(); // do all init here

	// update and draw
	void Update();
	void Draw(QPainter &);
    void Draw3D();
	// deal with mouse event
	void setMousePosition(Vector2);
    void mousePress();

	GAME_STATE getGameState() const;

	void checkStartFrameClick(const Menu &);
	void checkConnectFrameClick(const Menu &);
	bool checkHitPointClick(Vector2, int, int);
	bool checkBack(const Menu &);

    GameSever* getGameSever() const;
    GameClient* getGameClient() const;
    GAME_RULE getGameRule() const;

    PLAYER_FLAG getPlayerFlag() const;
    GAME_MODE getGameMode() const;
    NETWORK_RULE getNetworkRule() const;

    void GameBegin();
    void ClientInit(int _gameRule);
    void setClientConnected(bool);
    bool getClientConnected() const;
	void changeHitPoint();

    bool cuePositionIsLegal();
    void PlayerExchange();

    Cue& getCue();
    void displayTargetBalls();
};


#endif
