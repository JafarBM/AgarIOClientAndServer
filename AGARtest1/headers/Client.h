//
// Created by jafar on 7/10/17.
//

#ifndef AGARTEST1_CLIENT_H
#define AGARTEST1_CLIENT_H

#include <QObject>
#include <QWidget>
#include <QtNetwork/QHostAddress>
#include <QPainter>
#include <QPaintEvent>
#include <QPaintDevice>
#include <QtWidgets/QGraphicsScene>
#include <QHostAddress>
#include <bits/stdc++.h>
#include <vector>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QGraphicsView>
#include <headers/connection.h>
#include <headers/GamePage.h>
#include <headers/InterFace.h>

using namespace std;
//QGraphicsScene *graphicsScene;

class Connection;
class QTextEdit;
class QPushButton;
class QHostAddress;
class Login;
class InterFace;

class Client : public QObject
{
    Q_OBJECT
public:
    Client();

private:
    QString* username;
    InterFace* interFace;
    Connection* connection;

//public slots:
//    void CreateClient(QHostAddress *, quint16, QString*);

public slots:
    void comunicate(QHostAddress *, quint16, QString*, int);

};


#endif //AGARTEST1_CLIENT_H
