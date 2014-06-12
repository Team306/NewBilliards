// Copyright (C) 2014 Team306

#include <fstream>
#include "Referee.h"

// allow using lua script
extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

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

std::vector<Ball> Referee::getBallsList() const
{
    // use lua when config
    // init lua virtual machine
    lua_State *s = luaL_newstate();
    luaL_openlibs(s);
    luaL_dofile(s, "config.lua");
    // get ball number
    lua_getglobal(s, "getConfigData");
    lua_pushnumber(s, game_rule + 1);
    lua_pushstring(s, "ballsNumber");
    lua_call(s, 2, 1);
    int number = (int)lua_tonumber(s, -1);
    lua_pop(s, 1);

    // get ball list
    std::vector<Ball> ballsList;
    for (int i = 0; i < number; ++i)
    {
        lua_getglobal(s, "getConfigData");
        lua_pushnumber(s, game_rule + 1);
        lua_pushstring(s, "ballsList");
        lua_pushnumber(s, i + 1);
        lua_call(s, 3, 6);
        float x = (float)lua_tonumber(s, -6);
        float y = (float)lua_tonumber(s, -5);
        int R = (int)lua_tonumber(s, -4);
        int G = (int)lua_tonumber(s, -3);
        int B = (int)lua_tonumber(s, -2);
        std::string name = lua_tostring(s, -1);
        lua_pop(s, 6);
        // generate ball
        Ball ball = Ball(Vector2(x, y), ballRadius);
        ball.setColor(QColor(R, G, B));
        ball.setName(name);
        ballsList.push_back(ball);
    }
    // close lua virtual machine
    lua_close(s);

	return ballsList;
}

Ball Referee::getCueBall() const
{
    // use lua when config
    // init lua virtual machine
    lua_State *s = luaL_newstate();
    luaL_openlibs(s);
    luaL_dofile(s, "config.lua");
    lua_getglobal(s, "getConfigData");
    lua_pushnumber(s, game_rule + 1);
    lua_pushstring(s, "cueBall");
    lua_call(s, 2, 5);
    float x = (float)lua_tonumber(s, -5);
    float y = (float)lua_tonumber(s, -4);
    int R = (int)lua_tonumber(s, -3);
    int G = (int)lua_tonumber(s, -2);
    int B = (int)lua_tonumber(s, -1);
    lua_pop(s, 5);
    // close lua virtual machine
    lua_close(s);
    // generate ball
    Ball cueBall(Vector2(x, y), ballRadius);
    cueBall.setColor(QColor(R, G, B));
    cueBall.setName("cueBall");
    return cueBall;
}

float Referee::getBallRadius() const
{
	return ballRadius;
}

JUDGE_RESULT Referee::judge(Player *_currentplayer, std::vector<Ball> _ballslist){
    std::vector<std::string> onPocketlist = _currentplayer->getOnpocketlist();
    int eightball_selfball=0;
    switch(game_rule){
        case EIGHT_BALL:
        //eight on pocket
        for(int i=0; i<onPocketlist.size(); i++){
            if(onPocketlist[i] == "eight"){
                //std::cout<<"8"<<std::endl;
                if(_currentplayer->getBalltype() == NOTDEF){
                    _currentplayer->setGameresult(FAIL);
                }

                for(int j=0; j<_ballslist.size(); j++){
                    if(judgeSelfball(_currentplayer, _ballslist[j].getName())){
                         _currentplayer->setGameresult(FAIL);
                         break;
                    }
                }

                if(_currentplayer->getGameresult() == NOTDEC){
                    for(int k=0; k<onPocketlist.size(); k++){
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


            if(_currentplayer->getCueball_in()){       //cueball in
                return TO_FREE_BALL;
            }

            if(eightball_selfball ==0){       //no selfball
                return TO_EXCHANGE;
            }

            //first hit other's ball
            if(judgeSelfball(_currentplayer,_currentplayer->getFirsthit())==false){
                return TO_EXCHANGE;
            }

            if(_currentplayer->getBalltype() == SMALL && _currentplayer->getFirsthit() != "one" && _currentplayer->getFirsthit() != "two"
                    && _currentplayer->getFirsthit() != "three" && _currentplayer->getFirsthit() != "four" && _currentplayer->getFirsthit() != "five"
                    &&_currentplayer->getFirsthit() != "six" &&_currentplayer->getFirsthit() != "seven"){
                return TO_EXCHANGE;
            }

            //hit no ball
            if(_currentplayer->getHitflag()==0){
                return TO_EXCHANGE;
            }
            return TO_GOON;
            break;

       case NINE_BALL:
        for(int i = 0; i < onPocketlist.size(); i++)
        {

            if(onPocketlist[i] == "nine")
            {
                for(int k = 0; k < onPocketlist.size(); k++)
                {
                    if(onPocketlist[k] == "cueBall")
                    {
                        _currentplayer->setGameresult(FAIL);
                        break;
                    }
                }
                if(_currentplayer->getGameresult() == NOTDEC)
                {
                    if(_currentplayer->getFirsthit() != Targetname)
                        _currentplayer->setGameresult(FAIL);
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
            std::cout<<Targetname<<std::endl;
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
    for(int i = 0; i < ballname.size(); i++)
    {
        int foundflag = 0;
        for(int j = 0; j < _ballslist.size(); j++)
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
