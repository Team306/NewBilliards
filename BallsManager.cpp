// Copyright (C) 2014 Team306

#include "BallsManager.h"

BallsManager::BallsManager()
{
}

BallsManager::~BallsManager()
{
}

void BallsManager::init(Referee& referee)
{
	// call referee for balls' info
	ballsList = referee.getBallsList();
	cueBall = referee.getCueBall();
}

void BallsManager::reset(Referee& referee)
{
	// reset and init maybe the same
}

void BallsManager::Update(Table& table, Player *currentplayer)
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
    		ballsList[i] = ballsList[ballsList.size() - 1];
    		ballsList.pop_back();
    		// call the referee

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
