// Copyright (C) 2014 Team306

#include "BallsManager.h"

// allow using lua script
extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

BallsManager::BallsManager()
{
}

BallsManager::~BallsManager()
{
}

void BallsManager::init(Referee& referee)
{
    // init lua virtual machine
    lua_State *s = luaL_newstate();
    luaL_openlibs(s);
    luaL_dofile(s, "config.lua");
    // get ball number
    lua_getglobal(s, "getConfigData");
    lua_pushnumber(s, referee.getRule() + 1);
    lua_pushstring(s, "ballsNumber");
    lua_call(s, 2, 1);
    int number = (int)lua_tonumber(s, -1);
    lua_pop(s, 1);

    // init ball list
    if (ballsList.size() > 0)
    {
        ballsList.clear();
    }

    for (int i = 0; i < number; ++i)
    {
        lua_getglobal(s, "getConfigData");
        lua_pushnumber(s, referee.getRule() + 1);
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
        Ball ball = Ball(Vector2(x, y), referee.getBallRadius());
        ball.setColor(QColor(R, G, B));
        ball.setName(name);
        ballsList.push_back(ball);
    }

    // init cue ball
    lua_getglobal(s, "getConfigData");
    lua_pushnumber(s, referee.getRule() + 1);
    lua_pushstring(s, "cueBall");
    lua_call(s, 2, 5);
    float x = (float)lua_tonumber(s, -5);
    float y = (float)lua_tonumber(s, -4);
    int R = (int)lua_tonumber(s, -3);
    int G = (int)lua_tonumber(s, -2);
    int B = (int)lua_tonumber(s, -1);
    lua_pop(s, 5);

    // generate cue ball
    Ball newCueBall(Vector2(x, y), referee.getBallRadius());
    newCueBall.setColor(QColor(R, G, B));
    newCueBall.setName("cueBall");
    cueBall = newCueBall;

    // close lua virtual machine
    lua_close(s);
}

void BallsManager::Update(Table& table, Player *currentplayer, int gameRule)
{
    //move balls
    cueBall.Move();
	for (std::vector<Ball>::iterator iter = ballsList.begin(); iter != ballsList.end(); ++iter)
	{
        iter->Move();
	}

    //detect cueball's table collision
    this->collideengine.TableCollision(table,cueBall);

    for (unsigned i = 0; i < ballsList.size(); ++i)
    {
        // first detect cueball collision
        if (this->collideengine.DectBallToBallCollision(cueBall,ballsList[i]))
		{
            if(currentplayer->getHitflag()==0){
                currentplayer->setHitflag(1);
                currentplayer->setFirsthit(ballsList[i].getName());
            }
            collideengine.ProcessBallToBallCollision(cueBall,ballsList[i]);
		}

        //then detect table collision
        this->collideengine.TableCollision(table,ballsList[i]);

		// finally detect other ball
    	for (unsigned j = i + 1; j < ballsList.size(); ++j)
    	{
            if (this->collideengine.DectBallToBallCollision(ballsList[i],ballsList[j]))
    		{
    			// change speed or sth else
                this->collideengine.ProcessBallToBallCollision(ballsList[i],ballsList[j]);
    		}
    	}
    }

    // after detect collision, check if the ball is into the pocket
    if (table.checkPockets(cueBall))
    {
    	// call the referee, and next turn game change to free ball
        //cueBall.setSpeed(Vector2((0 - cueBall.getSpeed().getX()), (0 - cueBall.getSpeed().getY())));
        // cueBall.setSpeed(Vector2((0 - cueBall.getSpeed().getX()), (0 - cueBall.getSpeed().getY())));
        cueBall.setSpeed(Vector3(0, 0,0));
        cueBall.setBallState(STILL);
        cueBall.setPosition(Vector2(-100,-100));
        currentplayer->setCueball_in(1);
        currentplayer->setOnpocketlist(cueBall.getName());
        cueBall.setPosition(Vector2(-100, -100));
        cueBall.setBallState(STILL);
    }
    for (unsigned i = 0; i < ballsList.size(); ++i)
    {
    	if (table.checkPockets(ballsList[i]))
    	{
    		// if ball is into the pocket, delete the ball
            currentplayer->setOnpocketlist(ballsList[i].getName());
            if(currentplayer->getBalltype() == NOTDEF && currentplayer->getFirsthit() != "eight"){
                if(ballsList[i].getName() == "one" || ballsList[i].getName() == "two" || ballsList[i].getName() == "three"
                        || ballsList[i].getName() == "four"||ballsList[i].getName() == "five" ||ballsList[i].getName() == "six" ||ballsList[i].getName() == "seven"){
                    currentplayer->setBalltype(SMALL);
                }
                else{
                    if(ballsList[i].getName() == "eight"){
                        currentplayer->setGameresult(FAIL);
                    }
                    else{
                       currentplayer->setBalltype(BIG);
                    }
                }
            }

            // if in nine ball and the ball is nine, do not pop the ball
            if (gameRule == NINE_BALL && ballsList[i].getName() == "nine")
            {
                ballsList[i].setSpeed(Vector3(0, 0, 0));
                ballsList[i].setPosition(Vector3(-200, -200, 0));
                continue;
            }

    		ballsList[i] = ballsList[ballsList.size() - 1];
    		ballsList.pop_back();
    	}
    }

}

void BallsManager::Draw(QPainter& painter)
{
	for (std::vector<Ball>::iterator iter = ballsList.begin(); iter != ballsList.end(); ++iter)
	{
		// Draw each ball here;
		iter->Draw(painter);
	}
    cueBall.Draw(painter);
}

Ball& BallsManager::getCueBall()
{
	return cueBall;
}

bool BallsManager::isRunning() const
{
	int flag = 0;
    for (unsigned i = 0; i < ballsList.size(); ++i)
	{
		if (ballsList[i].getBallState() == RUNNING)
		{
			flag = 1;
		}
	}
	if (cueBall.getBallState() == RUNNING)
	{
		flag = 1;
	}
	if (flag == 0)
	{
		return false;
	}
	return true;
}

std::vector<Ball> BallsManager::getBallsList() const{
    return ballsList;
}

Ball& BallsManager::getBall(std::string name)
{
    for (int i = 0; i < ballsList.size(); ++i)
    {
        if (ballsList[i].getName() == name)
        {
            return ballsList[i];
        }
    }
    return cueBall;
}
