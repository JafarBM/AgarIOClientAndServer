//
// Created by jafar on 7/23/17.
//

#ifndef AGARTEST1_CONNECTION_H
#define AGARTEST1_CONNECTION_H

#include <QObject>
#include <QHostAddress>

class QTcpSocket;

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QHostAddress * = new QHostAddress("127.0.0.1"), quint16 = 9933);

private:
    QTcpSocket *socket;
    QHostAddress *serverAddress;
    quint16 port;

public slots:
    void recieve();
    void sendMessage(QString);

signals:
    void datarecieve(QString);
};


#endif //AGARTEST1_CONNECTION_H
