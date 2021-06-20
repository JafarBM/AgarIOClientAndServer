//
// Created by jafar on 7/29/17.
//

#include <headers/GamePage.h>
#include <bits/stdc++.h>
//#include <headers/Client.h>
#include <QVector>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>

using namespace std;

GamePage::GamePage(int width, int height, QString username, int number, QGraphicsView *parent) : username(username)
{
    this -> number = number;
    graphicsScene = new QGraphicsScene;
    bot_flag = 0;
    if((username[0] == 'b') && (username[1] == 'o') && (username[2] == 't'))
        bot_flag = 1;

    if((username[0] == 'v') && (username[1] == 'i') && (username[2] == 'e') && (username[3] == 'w'))
        viewer_flag = 1;

    graphicsScene -> setSceneRect(0, 0, 500, 500);

    QLineF topline(graphicsScene -> sceneRect().topLeft(), graphicsScene -> sceneRect().topRight());
    QLineF leftline(graphicsScene -> sceneRect().topLeft(), graphicsScene -> sceneRect().bottomLeft());
    QLineF bottomline(graphicsScene -> sceneRect().bottomLeft(), graphicsScene -> sceneRect().bottomRight());
    QLineF rightline(graphicsScene -> sceneRect().topRight(), graphicsScene -> sceneRect().bottomRight());

    graphicsScene -> addLine(topline);
    graphicsScene -> addLine(leftline);
    graphicsScene -> addLine(rightline);
    graphicsScene -> addLine(bottomline);

    graphicsScene -> setBackgroundBrush(QBrush(Qt::gray));
    QPen pen;
    setScene(graphicsScene);
    setMouseTracking(true);

//    user_color = new QColor(qBlue());

//    graphicsView = new QGraphicsView;
//    graphicsView -> setScene(graphicsScene);
//    graphicsView -> setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    graphicsView -> setSceneRect(0, 0, width, height);
//    graphicsView -> BoundingRectViewportUpdate;
    show();


}

//void GamePage::omit_user(QString username)
//{
//    for(int i = 0; i < users.size(); ++ i)
//    {
//        if(users[i] == username)
//        {
//            users.erase(users.begin() + i);
//            break;
//        }
//    }
//}

void GamePage::mousePressEvent(QMouseEvent * mouseEvent)
{
//    cout << "press    ed" << endl;
//    graphicsScene -> clear();
    int clicked_point_x = mouseEvent -> pos().x();
    int clicked_point_y = mouseEvent -> pos().y();
//    cout << clicked_point_x << " " << clicked_point_y << endl;
    QString map_data = "";
    map_data += "4";
//    cout << username.toStdString() << " " << users[0].toStdString() << endl;
    string cur_user = to_string(number);
    map_data += QString::fromStdString(cur_user);

    string cur_point = "+" + to_string(clicked_point_x) + "+" + to_string(clicked_point_y);
    map_data += QString::fromStdString(cur_point);

//    cout << map_data.toStdString() << endl;
//    cout << "emits reached" << endl;
    emit(sendMessage(map_data));
}

void GamePage::recieve(QString data)
{
    string map_data = data.toStdString();
    cout << "map_data :  " << map_data << endl;
    //recieve map_data and create it
    string bot_go_x = ""  , bot_go_y = "";
    graphicsScene -> clear();
    int pntr = 0;
    int cur_user = 0;
    for(int i = 0; i < map_data.size(); ++ i)
    {
        if((map_data[i] == 't') && (map_data[i + 1] == 'r') && (map_data[i + 2] == 'a') && (map_data[i + 3] == 's') && (map_data[i + 4] == 'h'))
        {
            pntr = i + 6;
            break;
        }
        else
        {
            if(map_data[i + 1] == ':')
            {
                cur_user = map_data[i] - '0';
                i += 2;
            }
        }

        string item_x = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i = i + j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_x += map_data[i + j];
        }
//        cout << item_x << endl;

        string item_y = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i = i + j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_y += map_data[i + j];
        }

        string item_rad = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '&')
            {
                i = i + j;
                break;
            }
            item_rad += map_data[i + j];
        }
        QPen pen;
        user_cell = graphicsScene -> addEllipse(stoi(item_x),stoi(item_y),stof(item_rad),stof(item_rad), pen, QBrush(Qt::darkGray));
        if(cur_user == number)
        {
            graphicsScene -> setSceneRect(stoi(item_x) , stoi(item_y) , stof(item_rad), stof(item_rad));
        }
        graphicsScene -> update();
//        cout << 1 << endl;
    }

    for(int i = pntr; i < map_data.size(); ++ i)
    {
        if((map_data[i] == 'f') && (map_data[i + 1] == 'o') && (map_data[i + 2] == 'o') && (map_data[i + 3] == 'd'))
        {
            pntr = i + 5;
            break;
        }

        string item_x = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i += j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_x += map_data[i + j];
        }

        string item_y = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i += j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_y += map_data[i + j];
        }

        string item_rad = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '&')
            {
                i += j;
                break;
            }
            item_rad += map_data[i + j];
        }

        QPen pen;
        graphicsScene -> addEllipse(stoi(item_x), stoi(item_y), stof(item_rad), stof(item_rad), pen, QBrush(Qt::darkGray));
        graphicsScene -> update();
    }

    for(int i = pntr; i < map_data.size(); ++ i)
    {
        if((map_data[i] == 'v') && (map_data[i + 1] == 'i') && (map_data[i + 2] == 'r') && (map_data[i + 3] == 'u') && (map_data[i + 4] == 's'))
        {
            pntr = i + 6;
            break;
        }

        string item_x = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i += j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_x += map_data[i + j];
        }

        string item_y = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i += j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_y += map_data[i + j];
        }

        string item_rad = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '&')
            {
                i += j;
                break;
            }
            item_rad += map_data[i + j];
        }

        QPen pen;
        graphicsScene -> addEllipse(stoi(item_x), stoi(item_y), stof(item_rad), stof(item_rad), pen, QBrush(Qt::darkRed));
        bot_go_x = item_x;
        bot_go_y = item_y;
        graphicsScene -> update();
    }

    for(int i = pntr; i < map_data.size(); ++ i)
    {
        string item_x = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i += j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_x += map_data[i + j];
        }

        string item_y = "";
        for(int j = 0; ; ++ j)
        {
            if(map_data[i + j] == '+')
            {
                i += j + 1;
                break;
            }
            if((map_data[i + j] >= '0') && (map_data[i + j] <= '9'))
                item_y += map_data[i + j];
        }

        string item_rad = "";
        for(int j = 0; i + j < map_data.size() ; ++ j)
        {

            if(map_data[i + j] == '&')
            {
                i += j;
                break;
            }
            item_rad += map_data[i + j];
        }

        QPen pen;
        graphicsScene -> addEllipse(stoi(item_x), stoi(item_y), stof(item_rad), stof(item_rad), pen, QBrush(Qt::green));
        graphicsScene -> update();
    }

    if(bot_flag)
    {
        QString Bot_map = QString::fromStdString("4");
        string cur_user_number = to_string(number);
        cur_user_number += bot_go_x + "+" + bot_go_y;
        Bot_map += QString::fromStdString(cur_user_number);
        emit(sendMessage(Bot_map));
    }
}

void GamePage::keyPressEvent(QKeyEvent *event){
    QString map_data = "";
//    cout << "keyPressed" << endl;
    switch(event -> key())
    {
        case Qt::Key_S:
        {
            map_data += "6";
            string cur_user = to_string(number);
            map_data += QString::fromStdString(cur_user);
            emit(sendMessage(map_data));
            break;
        }
        case Qt::Key_T:
        {
            map_data += "5";
            string cur_user = to_string(number);
            map_data += QString::fromStdString(cur_user);
            emit(sendMessage(map_data));
            break;
        }
    }
}
