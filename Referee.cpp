// Copyright (C) 2014 Team306

// #include <fstream>
#include "Referee.h"
#include "BallsManager.h"

// allow using lua script
extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

// debug 
#include <iostream>

Referee::Referee()
{
    scoreToadd = 0;
    judge_result = NOTJUDGE;
}

Referee::~Referee()
{
}

void Referee::init(int gameRule)
{
    // use lua when config
    // init lua virtual machine
    lua_State *s = luaL_newstate();
    luaL_openlibs(s);
    luaL_dofile(s, "config.lua");
    // get radius
    lua_getglobal(s, "getConfigData");
    lua_pushnumber(s, gameRule + 1);
    lua_pushstring(s, "ballRadius");
    lua_call(s, 2, 1);
    ballRadius = (float)lua_tonumber(s, -1);
    lua_pop(s, 1);
    // close lua virtual machine
    lua_close(s);

	// read config file
    judge_result = NOTJUDGE;
    Targetname = "one";
    game_rule = (GAME_RULE)gameRule;
}

float Referee::getBallRadius() const
{
	return ballRadius;
}

JUDGE_RESULT Referee::judge(Player *_currentplayer, BallsManager* ballsManager){
    std::vector<Ball> _ballslist = ballsManager->getBallsList();
    std::vector<std::string> onPocketlist = _currentplayer->getOnpocketlist();
    int eightball_selfball=0;
    switch(game_rule){
        case EIGHT_BALL:
        //eight on pocket
        for(unsigned i=0; i<onPocketlist.size(); i++){
            if(onPocketlist[i] == "eight"){
                //std::cout<<"8"<<std::endl;
                if(_currentplayer->getBalltype() == NOTDEF){
                    _currentplayer->setGameresult(FAIL);
                }

                for(unsigned j=0; j<_ballslist.size(); j++){
                    if(judgeSelfball(_currentplayer, _ballslist[j].getName())){
                         _currentplayer->setGameresult(FAIL);
                         break;
                    }
                }

                if(_currentplayer->getGameresult() == NOTDEC){
                    for(unsigned k=0; k<onPocketlist.size(); k++){
                        if(judgeSelfball(_currentplayer, onPocketlist[k])||onPocketlist[k]=="cueBall"){
                            _currentplayer->setGameresult(FAIL);
                            break;
                        }
                    }

                    if(_currentplayer->getGameresult() == NOTDEC){
                        _currentplayer->setGameresult(SUCCESS);
                    }
                }
                return TO_END;

            }

            if(judgeSelfball( _currentplayer,onPocketlist[i])){
                      eightball_selfball = 1;
            }

        }

        if(_currentplayer->getBalltype() == NOTDEF && _currentplayer->getCueball_in() ==0 ){
            return TO_EXCHANGE;
        }

        if(_currentplayer->getCueball_in()){       //cueball in
            return TO_FREE_BALL;
        }

        //first hit other's ball
        if(judgeSelfball(_currentplayer,_currentplayer->getFirsthit())==false){
            return TO_FREE_BALL;
        }


        //hit no ball
        if(_currentplayer->getHitflag()==0){
            return TO_FREE_BALL;
        }

        if(eightball_selfball ==0){       //no selfball
            return TO_EXCHANGE;
        }


        return TO_GOON;
        break;

        case NINE_BALL:
        for(unsigned i = 0; i < onPocketlist.size(); i++)
        {

            if(onPocketlist[i] == "nine")
            {
                for(unsigned k = 0; k < onPocketlist.size(); k++)
                {
                    if(onPocketlist[k] == "cueBall")
                    {
                        // _currentplayer->setGameresult(FAIL);
                        // break;
                        Ball& ball = ballsManager->getBall("nine");
                        if (ball.getName() == "nine")
                        {
                            Vector3 spotPosition(820, 300);
                            setBallAtSpots(ball, spotPosition, _ballslist);
                            return TO_FREE_BALL;
                        }
                    }
                }
                if(_currentplayer->getGameresult() == NOTDEC)
                {
                    if(_currentplayer->getFirsthit() != Targetname)
                    {
                        // _currentplayer->setGameresult(FAIL);
                        Ball& ball = ballsManager->getBall("nine");
                        if (ball.getName() == "nine")
                        {
                            Vector3 spotPosition(820, 300);
                            setBallAtSpots(ball, spotPosition, _ballslist);
                            return TO_EXCHANGE;
                        }
                    }
                    else
                        _currentplayer->setGameresult(SUCCESS);

                }
                return TO_END;
            }
        }

        if(_currentplayer->getCueball_in())       //cueball in
            return TO_FREE_BALL;
        if(_currentplayer->getHitflag() == 0)
            return TO_FREE_BALL;
        if(_currentplayer->getFirsthit() != Targetname)
        {
            //std::cout<<Targetname<<std::endl;
            return TO_FREE_BALL;
        }
        if(_currentplayer->getOnpocketlist().size() != 0)
            return TO_GOON;
        return TO_EXCHANGE;
    }
}

int Referee::getScoreToadd() const{
    return scoreToadd;
}

bool Referee::judgeSelfball(Player *_currentplayer, std::string ballname){
    if(_currentplayer->getBalltype() == SMALL){
        if(ballname == "one" || ballname == "two" || ballname == "three"
                ||ballname == "four" || ballname == "five" || ballname == "six"
                ||ballname == "seven"){
            return true;
        }
        else{
            return false;
        }
    }

    if(_currentplayer->getBalltype() == BIG){
        if(ballname == "nine" || ballname == "ten" || ballname == "eleven"
                ||ballname == "twelve" || ballname == "thirteen" || ballname == "fourteen"
                ||ballname == "fifteen"){
            return true;
        }
        else{
            return false;
        }
    }
}

void Referee::clearjudgeResult(){
    judge_result = NOTJUDGE;
}

void Referee::setTargetname(std::vector<Ball> _ballslist)
{
    std::vector<std::string> ballname;
    ballname.push_back("one");
    ballname.push_back("two");
    ballname.push_back("three");
    ballname.push_back("four");
    ballname.push_back("five");
    ballname.push_back("six");
    ballname.push_back("seven");
    ballname.push_back("eight");
    ballname.push_back("nine");
    for(unsigned i = 0; i < ballname.size(); i++)
    {
        int foundflag = 0;
        for(unsigned j = 0; j < _ballslist.size(); j++)
            if(_ballslist[j].getName() == ballname[i])
            {
                Targetname = ballname[i];
                foundflag = 1;
                break;
            }
        if(foundflag == 1)
            break;
    }
}

int Referee::getRule() const
{
    return game_rule;
}

// the method has a bug that if until the left cushion a number of balls in the line
// and there is no space to put the "nine", and finally will put it outside the table
void Referee::setBallAtSpots(Ball& ball, Vector3 spotPosition, std::vector<Ball> ballsList)
{
    for (unsigned i = 0; i < ballsList.size(); ++i)
    {
        if (ballsList[i].getName() == "nine")
        {
            continue;
        }

        float distance = (spotPosition - ballsList[i].getPosition()).Length();
        if (distance < ballRadius * 2)
        {
            // calc new position
            Vector3 ballPosition = ballsList[i].getPosition();
            Vector3 temp = ballPosition - spotPosition;
            Vector2 pointTo = Vector2(temp.getX(), temp.getY());

            float height = ballPosition.getY() - spotPosition.getY();
            float hypotenuse = 2 * ballRadius;
            float weight = sqrt(hypotenuse * hypotenuse + height * height);

            float deltaX = ballPosition.getX() - spotPosition.getX();
            float delta = weight + deltaX;

            Vector3 newSpotPosition(spotPosition.getX() + delta, spotPosition.getY());

            // recursive call
            setBallAtSpots(ball, newSpotPosition, ballsList);

            return;
        }
    }

    // if not ball intersect with spotPosition
    // set ball position
    ball.setPosition(spotPosition);

    // debug info 
    // std::cout << "set ball at spot " << spotPosition.getX() << ", " << spotPosition.getY() << std::endl;
    return;
}

std::string Referee::getTargetName() const
{
    return Targetname;
}
