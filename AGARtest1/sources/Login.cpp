//
// Created by jafar on 7/10/17.
//

#include <headers/Login.h>
#include <QApplication>
#include <QSpinBox>
#include <QDesktopWidget>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QHostAddress>

Login::Login(int width, int height, QWidget *parent) : QWidget(parent){

    QRect rec = QApplication::desktop() -> screenGeometry();
    this -> setGeometry(rec.width() * 2 / 5, rec.height() / 3, width, height );

    exit = new QPushButton("EXIT", this);
    LoginButton = new QPushButton("LOGIN", this);
    QDialogButtonBox *buttons = new QDialogButtonBox;
    buttons -> addButton(exit, QDialogButtonBox::RejectRole);
    buttons -> addButton(LoginButton, QDialogButtonBox::AcceptRole);

    username = new QLineEdit();
    QLabel *userlabel = new QLabel("Username : ");
    QHBoxLayout *user = new QHBoxLayout;
    user -> addWidget(userlabel);
    user -> addWidget(username);

    player = new QLineEdit();
    QLabel *playerlabel = new QLabel("Player Number : ");
    QHBoxLayout *playerbox = new QHBoxLayout;
    playerbox -> addWidget(playerlabel);
    playerbox -> addWidget(player);


    port = new QLineEdit("9933");
    QLabel *portlabel = new QLabel("Port : ");
    QHBoxLayout *portnum = new QHBoxLayout;
    portnum -> addWidget(portlabel);
    portnum -> addWidget(port);

    haddress = new QLineEdit("0.0.0.0");
    QLabel *hostaddresslabel = new QLabel("Host IP Address : ");
    QHBoxLayout *hostaddress = new QHBoxLayout;
    hostaddress -> addWidget(hostaddresslabel);
    hostaddress -> addWidget(haddress);

    CPUPlayer = new QCheckBox("Bot");
    Viewer = new QCheckBox("Viewer");
    QHBoxLayout *playertype = new QHBoxLayout;
    playertype -> addWidget(CPUPlayer);
    playertype -> addWidget(Viewer);
//    connect(CPUPlayer, SIGNAL(isChecked()), this, SLOT(Bot()));
 //   connect(Viewer, SIGNAL(isChecked()), this, SLOT(View()));

    QVBoxLayout *main = new QVBoxLayout;
    main -> addLayout(user);
    main -> addLayout(playerbox);
    main -> addLayout(portnum);
    main -> addLayout(hostaddress);
    main -> addLayout(playertype);
    main -> addWidget(buttons);

    setLayout(main);

    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(LoginButton, SIGNAL(clicked()), this, SLOT(reqlogin()));

    show();
}

void Login::reqlogin() {
    QString serveradd = haddress -> text() == "127.0.0.1" ? "LocalHost":haddress -> text();
    this -> hide();
    if(CPUPlayer -> isChecked())
            emit loginreq(new QHostAddress(serveradd), port -> text().toUShort(), new QString("bot" + username -> text()), player -> text().toUShort());
    else if(Viewer -> isChecked())
            emit loginreq(new QHostAddress(serveradd), port -> text().toUShort(), new QString("view" + username -> text()), player -> text().toUShort());
    emit loginreq(new QHostAddress(serveradd), port -> text().toUShort(), new QString(username -> text()), player -> text().toUShort());
}

void Login::View()
{

}