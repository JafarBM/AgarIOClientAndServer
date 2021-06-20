//
// Created by jafar on 7/10/17.
//

#include <headers/Client.h>
#include <headers/Login.h>
using namespace std;
#include <bits/stdc++.h>
#include <iostream>
#include <QHostAddress>
#include <QWidget>
#include <QObject>
#include <QApplication>

Client::Client()
{
    interFace = new InterFace(this);
    connect(interFace -> loginMenu, SIGNAL(loginreq(QHostAddress * , quint16, QString*, int)), this,
            SLOT(comunicate(QHostAddress *, quint16, QString*, int)));
}

void Client::comunicate(QHostAddress *hostAddress, quint16 port, QString *username, int number)
{
    this -> username = username;
    connection = new Connection(hostAddress, port);
//    cout << 1143124 << " "<< (hostAddress->toString()).toStdString() << endl;
    connect(interFace -> gamePage, SIGNAL(sendMessage(QString)), connection, SLOT(sendMessage(QString)));
    connect(connection, SIGNAL(datarecieve(QString)), interFace -> gamePage, SLOT(recieve(QString)));
}