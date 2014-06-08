// Copyright (C) 2014 Team306

#include "GameClient.h"

GameClient::GameClient(){
    IP_Address = "255.255.255.255";
    found_flag =false;
}

GameClient::~GameClient(){

}

void GameClient::GameConnect(){
  connectToHost(IP_Address,19999);
}

void GameClient::sendMessage(QByteArray message){
    write(message);
}

QByteArray GameClient::getMessage(){
    return readAll();
}
