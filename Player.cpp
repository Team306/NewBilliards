#include "Player.h"

Player::Player(){
    hit_flag = 0;
    cueball_in = 0;
    score = 0;
    toHit_balltype = RED;
    eightball_type = NOTDEF;
    game_result = NOTDEC;
    on_pocket_list.clear();
}

Player::~Player(){

}

void Player::Goon(){
    hit_flag = 0;
    cueball_in = 0;

    if(toHit_balltype == RED){
        toHit_balltype = COLOR;
    }
    else{
      toHit_balltype = RED;
    }

    on_pocket_list.clear();
    first_hit = "";
}

void Player::Exchange(){
    hit_flag = 0;
    cueball_in = 0;
    toHit_balltype = RED;
    on_pocket_list.clear();
    first_hit = "";
}


std::string Player::getFirsthit() const{
    return first_hit;
}

void Player::setFirsthit(std::string _ballname){
    first_hit = _ballname;
}

int Player::getHitflag() const{
    return hit_flag;
}

void Player::setHitflag(int _hitflag){
    hit_flag = _hitflag;
}

std::vector<std::string> Player::getOnpocketlist() const{
    return on_pocket_list;
}

void Player::setOnpocketlist(std::string _onpocket){
    on_pocket_list.push_back(_onpocket);
}

EIGHTBALL_TYPE Player::getBalltype() const {
    return eightball_type;
}

void Player::setBalltype(int type){
    eightball_type = (EIGHTBALL_TYPE)type;
}

PLAYER_FLAG Player::getPlayerflag() const{
    return player_flag;
}

void Player::setPlayerflag(int player){
    player_flag = (PLAYER_FLAG)player;
}


void Player::init(){
    eightball_type = NOTDEF;
    game_result = NOTDEC;
    hit_flag = 0;
    cueball_in = 0;
    score = 0;
    toHit_balltype = RED;
    on_pocket_list.clear();
    first_hit = "";
}

int Player::getCueball_in() const {
    return cueball_in;
}

void Player::setCueball_in(int _cueball_in){
    cueball_in = _cueball_in;
}

int Player::getScore() const {
    return score;
}

void Player::scoreAdd(int _score) {
    score += _score;
}

GAME_RESULT Player::getGameresult() const{
    return game_result;
}

void Player::setGameresult(int _result){
    game_result = (GAME_RESULT) _result;
}

