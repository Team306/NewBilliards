// Copyright (C) 2014 Team306

#ifndef BALLSMANAGER_H
#define BALLSMANAGER_H 


#include <vector>
#include "Ball.h"
#include "Referee.h"
#include "Table.h"
#include "Player.h"
#include "CollideEngine.h"

// detect all collisions in this class
class BallsManager
{
private:
	std::vector<Ball> ballsList;
    Ball cueBall;
    CollideEngine collideengine;

public:
	BallsManager();
	~BallsManager();

	// init methods
	void init(Referee &);

	// update and draw
    void Update(Table &, Player *, int gameRule);
    void Draw3D();


	// get and set
	Ball& getCueBall();
    std::vector<Ball> getBallsList() const;

	bool isRunning() const;

	Ball& getBall(std::string name);
};


#endif
