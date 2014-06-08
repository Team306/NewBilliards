// Copyright (C) 2014 Team306

#ifndef GAMECLIENT_H
#define GAMECLIENT_H
#include <QTcpSocket>
#include <QByteArray>

class GameClient: public QTcpSocket{
public:
    GameClient();
    ~GameClient();
    void gameConnect();
    void sendMessage(QByteArray);
    QByteArray getMessage();

private:
    QString IP_Address;
};

#endif // GAMECLIENT_H
