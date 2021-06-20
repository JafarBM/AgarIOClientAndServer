//
// Created by jafar on 7/10/17.
//

#ifndef AGARTEST1_LOGIN_H
#define AGARTEST1_LOGIN_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtNetwork/QHostAddress>
#include <QtWidgets/QCheckBox>

class QHostAddress;
class QPushButton;
class QLineEdit;

class Login: public QWidget{
    Q_OBJECT
public:
    Login(int, int, QWidget * = 0);

private:
    QPushButton *LoginButton, * exit;
    QLineEdit *username, *haddress, *port, *player;
    QCheckBox * CPUPlayer, *Viewer;

signals:
    void loginreq(QHostAddress *, quint16, QString*, int);

public slots:
    void reqlogin();
    void View();

};

#endif //AGARTEST1_LOGIN_H
