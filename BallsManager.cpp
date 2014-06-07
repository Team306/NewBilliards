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
	// Update each ball
    /*Vector2 acc = cueBall.getSpeed().getNormalize()*0.3;
    Vector2 temp = cueBall.getSpeed()-acc;
    if(temp.getX()*cueBall.getSpeed().getX()<=0){
        cueBall.setSpeed(Vector2());
    }
    else{
        cueBall.setSpeed(temp);
    }*/
    cueBall.Update();
	for (std::vector<Ball>::iterator iter = ballsList.begin(); iter != ballsList.end(); ++iter)
	{
		iter->Update();
	}

    // detect collision
    if (table.collidesWith(cueBall))
    {
    	// change speed or sth else

    	// test
        //cueBall.setSpeed(Vector2());
        // cueBall.setSpeed(Vector2());
    }
    for (unsigned i = 0; i < ballsList.size(); ++i)
    {
    	// first detect cue ball
		if (cueBall.collidesWith(ballsList[i]))
		{
            if(currentplayer->getHitflag()==0){
                currentplayer->setHitflag(1);
                currentplayer->setFirsthit(ballsList[i].getName());
            }

            // change speed or sth else
			
			// test

            ballsList[i].setSpeed(cueBall.getSpeed());
            cueBall.setSpeed(Vector2());

            // cueBall.setSpeed(Vector2());
		}

		// and then detect the balls with table
		if (table.collidesWith(ballsList[i]))
		{
			// change speed or sth else

		}

		// finally detect other ball
    	for (unsigned j = i + 1; j < ballsList.size(); ++j)
    	{
    		if (ballsList[i].collidesWith(ballsList[j]))
    		{
    			// change speed or sth else
                ballsList[i].setSpeed(ballsList[i].getSpeed()*(-0.7));
                ballsList[j].setSpeed(ballsList[i].getSpeed()*0.6);

    		}
    	}
    }

    // after detect collision, check if the ball is into the pocket
    if (table.checkPockets(cueBall))
    {
    	// call the referee, and next turn game change to free ball
        //cueBall.setSpeed(Vector2((0 - cueBall.getSpeed().getX()), (0 - cueBall.getSpeed().getY())));
        // cueBall.setSpeed(Vector2((0 - cueBall.getSpeed().getX()), (0 - cueBall.getSpeed().getY())));
        cueBall.setSpeed(Vector2(0, 0));
        currentplayer->setCueball_in(1);
    }
    for (unsigned i = 0; i < ballsList.size(); ++i)
    {
    	if (table.checkPockets(ballsList[i]))
    	{
    		// if ball is into the pocket, delete the ball
            currentplayer->setOnpocketlist(ballsList[i].getName());
            if(currentplayer->getBalltype() == NOTDEF){
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
