// Copyright (C) 2014 Team306

#include "GameClient.h"

GameClient::GameClient(){
    IP_Address = "10.147.123.28";
}

GameClient::~GameClient(){

}

void GameClient::gameConnect(){
    connectToHost(IP_Address,19999);
}

void GameClient::sendMessage(QByteArray message){
    write(message);
}

QByteArray GameClient::getMessage(){
    return readAll();
}
