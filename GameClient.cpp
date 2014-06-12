// Copyright (C) 2014 Team306

#include "GameClient.h"

GameClient::GameClient(){
    IP_Address = "10.147.123.27";
    found_flag =false;
}

GameClient::~GameClient(){

}

void GameClient::GameConnect(){
  connectToHost("10.147.123.27",19999);
}

void GameClient::sendMessage(QByteArray message){
    write(message);
}

QByteArray GameClient::getMessage(){
    return readAll();
}
