// Copyright (C) 2014 Team306

#include "GameSever.h"

GameSever::GameSever(){
    //listen(QHostAddress::Any,19999);
    client = new QTcpSocket;
}

GameSever::~GameSever(){

}

void GameSever::GameListen(){
    listen(QHostAddress::Any,19999);
    waitForNewConnection();
}

void GameSever::StopListen(){
    close();
}

void GameSever::setClient(){
    client = nextPendingConnection();
}

void GameSever::sendMessage(QByteArray message){
    client->write(message);
    //client->waitForBytesWritten();
}

QByteArray GameSever::getMessage(){
    return client->readLine();
}

QTcpSocket* GameSever::getClient() const{
    return client;
}
