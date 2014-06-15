// Copyright (C) 2014 Team306

#include "GameClient.h"
#include <iostream>

GameClient::GameClient(){
    IP_Address = "255.255.255.255";
    counter1 = 0;
    counter2 = 0;
}

GameClient::~GameClient(){

}

void GameClient::GameConnect(){
    DisConnect();
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol){
             QString hostip_addr = address.toString();
             Host_IP = hostip_addr.split(".");
         }

    }
    IP_Address.clear();
    IP_Address.append(Host_IP[0]);
    IP_Address.append(QString("."));
    IP_Address.append(Host_IP[1]);
    IP_Address.append(QString("."));
    IP_Address.append(Host_IP[2]);
    IP_Address.append(QString("."));
    IP_Address.append(QString::number(counter1));
    std::cout<<IP_Address.toStdString()<<std::endl;
    connectToHost(IP_Address,19999);
    waitForConnected(30);
    counter1++;
    counter1 =counter1%256;
}

void GameClient::DisConnect(){
    //disconnectFromHost();
    close();
    //if(ConnectingState){
       //waitForDisconnected(5);
    //}
}

void GameClient::sendMessage(QByteArray message){
    write(message);
    //waitForBytesWritten();
}

QByteArray GameClient::getMessage(){
    return readLine();
}



