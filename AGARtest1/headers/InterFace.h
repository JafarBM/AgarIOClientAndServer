//
// Created by jafar on 7/29/17.
//

#ifndef AGARTEST1_INTERFACE_H
#define AGARTEST1_INTERFACE_H

#include <QObject>
#include <QHostAddress>

class Login;
class GamePage;

class InterFace : public QObject
{
Q_OBJECT

public:
    InterFace(QObject * = 0);
    Login *loginMenu;
    GamePage *gamePage;

public slots:
    void login(QHostAddress*, quint16, QString*, int);
};


#endif //AGARTEST1_INTERFACE_H
