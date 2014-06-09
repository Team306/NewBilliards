// Copyright (C) 2014 Team306

#ifndef GAMECLIENT_H
#define GAMECLIENT_H
#include <QTcpSocket>
#include <QByteArray>
#include <QStringList>

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
    bool found_flag;
};

#endif // GAMECLIENT_H
