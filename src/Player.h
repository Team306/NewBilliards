// Copyright (C) 2014 Team306

#ifndef PLAYER_H
#define PLAYER_H 

#include "Ball.h"

enum PLAYER_FLAG { LOCAL, GUEST};
enum EIGHTBALL_TYPE { NOTDEF, SMALL, BIG};
enum SNOOKER_BALLTYPE {RED, COLOR};
enum GAME_RESULT {NOTDEC, SUCCESS, FAIL};

class Player
{
public:
	Player();
	~Player();
    void Goon();
    void Exchange();
    void init();
    std::string getFirsthit() const;
    void setFirsthit(std::string);
    int getHitflag() const;
    void setHitflag(int);

    std::vector<std::string> getOnpocketlist() const;
    void setOnpocketlist(std::string);

    EIGHTBALL_TYPE getBalltype() const;
    void setBalltype(int);

    PLAYER_FLAG getPlayerflag() const;
    void setPlayerflag(int);

    int getCueball_in() const;
    void setCueball_in(int);

    int getScore() const;
    void scoreAdd(int);

    GAME_RESULT getGameresult() const;
    void setGameresult(int);

private:
    PLAYER_FLAG player_flag;
    EIGHTBALL_TYPE eightball_type;
    SNOOKER_BALLTYPE toHit_balltype;
    int hit_flag;
    std::string first_hit;
    std::vector<std::string>  on_pocket_list;
    GAME_RESULT game_result;
    int cueball_in;
    int score;
};


#endif
