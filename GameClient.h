// Copyright (C) 2014 Team306

#ifndef GAMECLIENT_H
#define GAMECLIENT_H
#include <QTcpSocket>
#include <QByteArray>
#include <QStringList>
#include <QTimer>
#include <QHostAddress>
#include <QHostInfo>

class GameClient: public QTcpSocket{
public:
    GameClient();
    ~GameClient();
    void GameConnect();
    void DisConnect();
    void sendMessage(QByteArray);
    QByteArray getMessage();

private:
    QString IP_Address;
    QStringList Host_IP;
    int counter1;
    int counter2;
};

#endif // GAMECLIENT_H
