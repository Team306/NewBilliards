// Copyright (C) 2014 Team306

#ifndef REFEREE_H
#define REFEREE_H 


#include <string>
#include <vector>
#include "Ball.h"
#include "Player.h"

class BallsManager;

// define rule in it
// maybe can use embedded scripts to implement
enum GAME_RULE {EIGHT_BALL, NINE_BALL, SNOOKER};
enum JUDGE_RESULT {NOTJUDGE, TO_FREE_BALL, TO_EXCHANGE, TO_GOON, TO_END};

class Referee
{
private:
	float ballRadius;
    GAME_RULE game_rule;
    JUDGE_RESULT judge_result;
    int scoreToadd;
    bool judgeSelfball(Player *, std::string);
    std::string Targetname;

public:
	Referee();
	~Referee();

	// init method
    void init(int gameRule);

	float getBallRadius() const;
    JUDGE_RESULT judge(Player*, BallsManager *);
    int getScoreToadd() const;
    void clearjudgeResult();
    void setTargetname(std::vector<Ball>);
    int getRule() const;

    void setBallAtSpots(Ball& ball, Vector3 spotPosition, std::vector<Ball> ballsList);
};


#endif
