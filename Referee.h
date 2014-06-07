// Copyright (C) 2014 Team306

#ifndef REFEREE_H
#define REFEREE_H 


#include <string>
#include <vector>
#include "Ball.h"
#include "Player.h"

// define rule in it
// maybe can use embedded scripts to implement
enum GAME_RULE {EIGHT_BALL, NINE_BALL, SNOOKER};
enum JUDGE_RESULT {NOTJUDGE, TO_FREE_BALL, TO_EXCHANGE, TO_GOON, TO_END};

class Referee
{
private:
	// in referee is a state machine, log the game state
	float ballRadius;
    GAME_RULE game_rule;
    JUDGE_RESULT judge_result;
    int scoreToadd;
    bool judgeSelfball(Player *, std::string);

public:
	Referee();
	~Referee();

	// init method

    void init(int gameRule);

	// get rule
	std::vector<Ball> getBallsList() const;
	Ball getCueBall() const;
	float getBallRadius() const;
    JUDGE_RESULT judge(Player*,std::vector<Ball>);
    int getScoreToadd() const;
    void clearjudgeResult();
 };


#endif
