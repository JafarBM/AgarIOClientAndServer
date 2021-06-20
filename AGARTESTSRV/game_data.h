//
// Created by jafar on 7/23/17.
//

#ifndef AGARTESTSRV_GAME_DATA_H
#define AGARTESTSRV_GAME_DATA_H

#include <vector>
#include <math.h>
#include <string>
#include <QtCore/QString>
#include <QList>
#include <QtCore/QObject>

using namespace std;

class user
{

public:
    user(int, int, double);
    int x, y;
    double speedx, speedy, acc, speed;
    double rad;

    void eat_user(double);
    void eat_food();
    void produce_trash();
    void speedchng();
    void move(int, int);
    void eat_trash(double);

};

class fathercell
{

public:
    fathercell(int, int, double);
    vector<user> children;
    void move();
    int Scenecenterx();
    int Scenecentery();
    void split();

};

class Trash
{

public:
    Trash(int, int);
    int x, y;
    const double rad;
};

class Food
{

public:
    int x;
    int y;
    const int rad = 10;
    Food(int, int);
};

class Virus
{

public:
    Virus(int, int);
    int x;
    int y;
    const int rad = 70;
};

class Scene
{

public:
    Scene(int, int);

    vector<Virus> viruses;
    vector<Food> foods;
    vector<fathercell> users;
//    vector<fathercell> Bots;
    vector<fathercell> Viewers;
    vector<Trash> trashes;

    void events(int, int, int);
    void user_events(int, int, int, int);
    QString change_data_to_str();
    void render();
//    void del_trash(int);
};


#endif //AGARTESTSRV_GAME_DATA_H
