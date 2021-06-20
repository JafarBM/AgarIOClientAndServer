//
// Created by jafar on 7/23/17.
//

#include <headers/connection.h>
#include <QTcpSocket>
#include <iostream>
#include <QThread>
using namespace std;

Connection::Connection(QHostAddress *serverAddress, quint16 port) : serverAddress(serverAddress), port(port)
{
    socket = new QTcpSocket;
//    cout << 1 << endl;
    socket -> connectToHost(*serverAddress, port);
//    QThread::msleep(5000);
//    bool connected = (socket->state() == QTcpSocket:: ConnectedState);
//    cout << connected << " " << socket->state() << " 31312313212313"<< serverAddress->toString().toStdString() << endl;
    connect(socket, SIGNAL(readyRead()), this, SLOT(recieve()));
    QString msg = QString::fromStdString("1");
    QByteArray data = &msg.toStdString()[0];
    socket -> write(data);
}

void Connection::recieve()
{
    QString data = socket -> readAll();
    emit datarecieve(data);
}

void Connection::sendMessage(QString message)
{
//    cout << "heu" << endl;
    QByteArray data = &message.toStdString()[0];
    socket -> write(data);
}