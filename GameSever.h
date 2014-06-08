// Copyright (C) 2014 Team306
#ifndef GAMESEVER_H
#define GAMESEVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QStringList>
class GameSever: public QTcpServer{
public:
    GameSever();
    ~GameSever();
    void setClient();
    void GameListen();
    void sendMessage(QByteArray);
    QByteArray getMessage();
    QTcpSocket* getClient() const;

private:
    QTcpSocket *client;

};

#endif // GAMESEVER_H
