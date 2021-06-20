//
// Created by jafar on 7/22/17.
//
#include <server.h>
#include <bits/stdc++.h>
#include <QString>
#include <QTimer>

using namespace std;

Server::Server(QHostAddress *serverAddress, quint16 serverPort) : serverAddress(serverAddress), serverPort(serverPort)
{
    clients = new QList<QTcpSocket*>();
    GameScene = new Scene(1000, 1000);
    server = new QTcpServer(this);
    server -> listen(*serverAddress, serverPort);
//    cout << 1 << endl;
//    cout << serverAddress->toString().toStdString() << endl;
    connect(server, SIGNAL(newConnection()), this, SLOT(createConnection()));
    animate = new QTimer;
    connect(animate, SIGNAL(timeout()), this, SLOT(render()));
    animate -> start(100);
}

void Server::createConnection(){
//    cout << 2 << endl;
    QTcpSocket *client = server -> nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(read()));
//    cout << client->waitForReadyRead();
    clients -> append(client);
//    GameScene -> events(1, 1000, 1000);
}

void Server::read()
{
//    cout << 3 << endl;
    for(int i = 0; i < clients -> size(); ++ i)
    {
        if(clients -> at(i) -> bytesAvailable() > 0)
        {
//            cout << "data:  " << (clients -> at(i) -> readAll()).toStdString() << endl;
            read(clients -> at(i));
        }
    }
}

void Server::read(QTcpSocket * sender)
{
//    cout << 4 << endl;
    string data = (sender -> readAll()).toStdString();//the problem for segment fault is here
//    cout << data << endl;
    if(data[0] == '1')
    {
//        cout << 1 << endl;
        GameScene -> events(1, 2000, 2000);
//        cout << 2 << endl;
//        GameScene -> render();
    }
    else if(data[0] == '2')
    {
        GameScene -> events(2, 2000, 2000);
    }
    else if(data[0] == '3')
    {
        GameScene -> events(3, 2000, 2000);
    }
    else if(data[0] == '4')
    {
//        cout << "clicked" << endl;
        int cnt = 0, des_x = 0, des_y = 0, player_num = data[1] - '0', j = 0;
        for(int i = 0; i < data.size(); ++ i)
        {
            if(data[i] == '+')
            {
                j = i;
                break;
            }
        }
//        cout << player_num << endl;
        for(int i = j + 1; i < data.size(); ++ i)
        {
            if(data[i] == '+')
            {
                cnt ++;
                continue;
            }
            if(cnt >= 3)
                break;

            int a = data[i] - '0';
//            cout << cnt << endl;
            if(cnt == 0)
                des_x = des_x * 10 + a;
            else
                des_y = des_y * 10 + a;
        }
//        cout << des_x << " :: " << des_y << endl;
        GameScene -> user_events(4, des_x, des_y, player_num);
    }
    else if(data[0] == '5')
    {
        int cnt = 0, pos_x = 0, pos_y = 0, player_num = data[1] - '0';
        for(int i = 3; i < data.size(); ++ i)
        {
            if(data[i] == '+')
            {
                cnt ++;
                continue;
            }
            if(cnt >= 3)
                break;

            int a = data[i] - '0';
            if(cnt == 0)
                pos_x *= 10 + a;
            else
                pos_y *= 10 + a;
        }
        GameScene -> user_events(5, pos_x, pos_y, player_num);
    }
    else
    {
        int cnt = 0, pos_x = 0, pos_y = 0, player_num = data[1] - '0';
        for(int i = 3; i < data.size(); ++ i)
        {
            if(data[i] == '+')
            {
                cnt ++;
                continue;
            }
            if(cnt >= 3)
                break;

            int a = data[i] - '0';
            if(cnt == 0)
                pos_x *= 10 + a;
            else
                pos_y *= 10 + a;
        }
        GameScene -> user_events(6, pos_x, pos_y, player_num);
    }

//    cout << 5 << endl;
//    cout << 5 << endl;
//    cout << 131312 << endl;
    for(int i = 0; i < clients -> size(); ++ i)
    {
        QByteArray datafeed = &(GameScene -> change_data_to_str()).toStdString()[0];
        clients -> at(i) -> write(datafeed);
    }
}

void Server::render()
{
    GameScene -> render();
    for(int i = 0; i < clients -> size(); ++ i)
    {
        QByteArray datafeed = &(GameScene -> change_data_to_str()).toStdString()[0];
        clients -> at(i) -> write(datafeed);
    }
}