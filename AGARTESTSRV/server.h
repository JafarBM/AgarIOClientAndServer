//
// Created by jafar on 7/22/17.
//

#ifndef AGARTESTSRV_SERVER_H
#define AGARTESTSRV_SERVER_H

#include <QtCore/QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <game_data.h>

class QTimer;
class QHostAddress;
class QDialog;
class QTcpSocket;
class QTcpServer;

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QHostAddress * = new QHostAddress("127.0.0.1"), quint16 = 9933);
    QTimer *animate;

public slots:
    void createConnection();
    void read();
    void render();

private:
    QHostAddress *serverAddress;
    quint16 serverPort;
    QTcpServer *server;
    QList<QTcpSocket*> *clients;

    void read(QTcpSocket*);
   // void write(QByteArray*);
    Scene *GameScene;

};

#endif //AGARTESTSRV_SERVER_H
