// Copyright (C) 2014 Team306

#include <fstream>
#include "Referee.h"

#ifndef EIGHT_BALL_CONFIG_FILENAME
#define EIGHT_BALL_CONFIG_FILENAME "test8_config.txt"
#define NINE_BALL_CONFIG_FILENAME "config1.txt"
#define SNOOKER_CONFIG_FILENAME "config2.txt"
#endif

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
	// read config file
    judge_result = NOTJUDGE;
    game_rule = (GAME_RULE)gameRule;
    std::ifstream fin;
    switch(game_rule){
        case EIGHT_BALL:
            fin.open(EIGHT_BALL_CONFIG_FILENAME);
            break;

        case NINE_BALL:
            fin.open(NINE_BALL_CONFIG_FILENAME);
            break;

        case SNOOKER:
            fin.open(SNOOKER_CONFIG_FILENAME);
            break;

        default:
            fin.open("config.txt");
            break;
     }
    std::string str;
    while (fin >> str)
    {
        if (str == "ballRadius")
        {
            break;
        }
    }
    fin >> ballRadius;
    fin.close();
}

//void Referee::chooseRule(std::string ruleName)
//{
	// change state machine
//}

std::vector<Ball> Referee::getBallsList() const
{
	// use rule here
	// read the file get config info
	std::ifstream fin;
    switch(game_rule){
        case EIGHT_BALL:
            fin.open(EIGHT_BALL_CONFIG_FILENAME);
            break;

        case NINE_BALL:
            fin.open(NINE_BALL_CONFIG_FILENAME);
            break;

        case SNOOKER:
            fin.open(SNOOKER_CONFIG_FILENAME);
            break;

        default:
            fin.open("config.txt");
            break;
     }
	std::string str;
	while (fin >> str)
	{
		if (str == "ballsList")
		{
			break;
		}
	}
	int number;
	fin >> number;
	std::vector<Ball> ballsList;
	for (int i = 0; i < number; ++i)
	{
		float x, y;
		int R, G, B;
		std::string name;
		fin >> x;
		fin >> y;
		fin >> R;
		fin >> G;
		fin >> B;
		fin >> name;
		Ball ball = Ball(Vector2(x, y), ballRadius);
		ball.setColor(QColor(R, G, B));
		ball.setName(name);
		ballsList.push_back(ball);
	}
	fin.close();
	return ballsList;
}

Ball Referee::getCueBall() const
{
	// read config file
	std::ifstream fin;
    switch(game_rule){
        case EIGHT_BALL:
            fin.open(EIGHT_BALL_CONFIG_FILENAME);
            break;

        case NINE_BALL:
            fin.open(NINE_BALL_CONFIG_FILENAME);
            break;

        case SNOOKER:
            fin.open(SNOOKER_CONFIG_FILENAME);
            break;

        default:
            fin.open("config.txt");
            break;
     }
	std::string str;
	while (fin >> str)
	{
		if (str == "cueBall")
		{
			break;
		}
	}
	float x, y;
	int R, G, B;
	fin >> x;
	fin >> y;
	fin >> R;
	fin >> G;
	fin >> B;
	fin.close();
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
                    return TO_END;
                }

                if(_currentplayer->getGameresult() == FAIL){
                    return TO_END;
                }
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
            if(_currentplayer->getCueball_in()){       //cueball in
                return TO_FREE_BALL;
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
            for(int i = 0; i < _currentplayer->getOnpocketlist().size(); i++)
                if(_currentplayer->getOnpocketlist()[i] == "nine")
                {
                    for(int k = 0; k < _currentplayer->getOnpocketlist().size(); k++)
                        if(_currentplayer->getOnpocketlist()[k] == "cueBall")
                        {
                            _currentplayer->setGameresult(FAIL);
                            break;
                        }
                    /*if(_currentplayer->getGameresult() == NOTDEC)
                        if(_currentplayer->getFirsthit() != Targetname)
                        {
                            _currentplayer->setGameresult(FAIL);
                            break;
                        }*/
                    if(_currentplayer->getGameresult() == NOTDEC)
                    {
                        _currentplayer->setGameresult(SUCCESS);
                        break;
                    }
                    return TO_END;
                }

            if(_currentplayer->getCueball_in())       //cueball in
                return TO_FREE_BALL;
            if(_currentplayer->getHitflag() == 0)
                return TO_FREE_BALL;
            /*if(_currentplayer->getFirsthit() != Targetname)
                return TO_FREE_BALL;*/
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
