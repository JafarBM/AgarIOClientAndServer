//
// Created by jafar on 7/29/17.
//

#include <headers/InterFace.h>
#include <QHostAddress>
#include <headers/GamePage.h>
#include <headers/Login.h>

int cnt = 0;

InterFace::InterFace(QObject *parent) : QObject(parent)
{
    loginMenu = new Login(400, 400);
    connect(loginMenu, SIGNAL(loginreq(QHostAddress*, quint16, QString*, int)), this, SLOT(login(QHostAddress*, quint16, QString*, int)));
}

void InterFace::login(QHostAddress *serverAddress, quint16 port, QString *username, int number)
{
    //printf("%d", 10);
    gamePage = new GamePage(400, 500, *username, number);
}
