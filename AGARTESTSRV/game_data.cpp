//
// Created by jafar on 7/23/17.
//

#include <game_data.h>
#include <bits/stdc++.h>
using namespace std;

const double food_eat_add = 1;
const double init_rad = 30;

Food::Food(int centerx, int centery)
{
    x = centerx;
    y = centery;
}

Virus::Virus(int centerx, int centery)
{
    x = centerx;
    y = centery;
}

user::user(int centerx, int centery, double radious)
{
    x = centerx;
    y = centery;
    rad = radious;
//    cout << radious << endl;
    acc = 0;
    speedx = 0;
    speedy = 0;
}

void user::eat_food()
{
    rad += food_eat_add;
}

void user::eat_user(double eat_r)
{
    rad = sqrt(eat_r * eat_r + rad * rad);
}

void user::produce_trash()
{
    rad = sqrt(pow(rad, 2) - pow(15, 2));
}

void user::speedchng()
{
//    speedx = (double)500 / (rad);
    speed = 500 / rad;
//    speedy = (double)(500) / (rad);
}

void user::eat_trash(double radious)
{
    rad = sqrt(pow(rad, 2) + pow(radious, 2));
}

void user::move(int des_x, int des_y)
{

//    cout << angel << endl;
//    cout << x << " " << y << endl;
    speedx = (des_x - x) / sqrt(pow(des_x - x, 2) + pow(des_y - y, 2));
    speedy = (des_y - y) / sqrt(pow(des_x - x, 2) + pow(des_y - y, 2));
    x += speedx * speed;
    y += speedy * speed;

//    cout << "new ones" << x << " " << y << endl;

    if(x < 0)
        x = 0;
    if(x > 2000)
        x = 2000;
    if(y < 0)
        y = 0;
    if(y > 2000)
        y = 2000;
}

fathercell::fathercell(int x, int y , double rad)
{
    user newfather(x, y, rad);
    children.push_back(newfather);
//    cout << children[0].rad << endl;
}

int fathercell::Scenecenterx()
{
    int cnterx = 0;
    for(int i = 0; i < children.size(); ++ i)
        cnterx += children[i].x;
    return cnterx / children.size();
}

int fathercell::Scenecentery()
{
    int cntery = 0;
    for(int i = 0; i < children.size(); ++ i)
    {
        cntery += children[i].y;
    }
    return cntery / children.size();
}


void fathercell::move()
{
    for(int i = 0; i < children.size(); ++ i)
    {
        children[i].move(2 * children[i].speedx + children[i].x, 2 * children[i].speedy + children[i].y);
    }
}

void fathercell::split()
{
//    cout << "thefaq" << endl;
    for(int i = 0; i < children.size(); ++ i)
    {
        if(children.size() == 16)
            continue;
        if(children[i].rad > 50)
        {
            user splited_child(children[i].x + 100, children[i].y + 100, sqrt(2) / 2 * children[i].rad);
            children[i].rad = sqrt(2) / 2 * children[i].rad;
            children[i].speedchng();
            splited_child.speedchng();
            children.push_back(splited_child);
//            cout << 111 << endl;
        }
    }
}

Trash::Trash(int newx, int newy) : rad(15)
{
    x = newx;
    y = newy;
}

Scene::Scene(int Scenewidth, int Sceneheight)
{
//    srand(time(0));
    for (int i = 0; i < 1000; ++i) {
        if (foods.size() >= 1000)
            break;
        Food newfood(rand() % Scenewidth, rand() % Sceneheight);
        foods.push_back(newfood);
    }

    for (int i = 0; i < 30; ++i) {
        if (viruses.size() >= 30)
            break;
        Virus newvirus(rand() % Scenewidth, rand() % Sceneheight);
        viruses.push_back(newvirus);
    }
}

void Scene::events(int event_type, int SceneWidth, int SceneHeight)
{
//    srand(time(0));
    //event_type == 1 --> add new player
    if(event_type == 1)
    {
        fathercell newuser(rand() % SceneWidth, rand() % SceneHeight, init_rad);
//        cout << init_rad << endl;
        users.push_back(newuser);
    }

    //event_type == 2 --> add new Bot
    if(event_type == 2)
    {
        fathercell newBot(rand() % SceneWidth, rand() % SceneHeight, init_rad);
//        Bots.push_back(newBot);
    }

    //event_type == 3 --> add new viewer
    if(event_type == 3)
    {
        fathercell newViewer(rand() % SceneWidth, rand() % SceneHeight, init_rad);
        Viewers.push_back(newViewer);
    }
}

void Scene::user_events(int event_type, int des_x, int des_y, int player_num)
{
    //event_type == 4 --> move
    if(event_type == 4)
    {
//        cout << des_x << " " << des_y << endl;

        for(int i = 0; i < users[player_num].children.size(); ++ i)
        {
//            cout << player_num << endl;
            users[player_num].children[i].speedchng();
            users[player_num].children[i].move(des_x, des_y);
//            cout << des_x << " " << des_y << endl;
        }
    }

    //event_type == 5 --> create_trash
    else if(event_type == 5)
    {
        int child_num = 0;
        for(int i = 0; i < users[player_num].children.size(); ++ i)
        {
            if(users[player_num].children[i].rad > 50)
            {
                child_num = i + 1;
                users[player_num].children[i].speedchng();
                break;
            }

        }

        if(child_num)
        {
            child_num --;
            int trash_x = users[player_num].Scenecenterx() + 2 * users[player_num].children[child_num].rad;
            int trash_y = users[player_num].Scenecentery() + 2 * users[player_num].children[child_num].rad;
            users[player_num].children[child_num].produce_trash();
            Trash newTrash(trash_x, trash_y);
            trashes.push_back(newTrash);
        }
    }

    //event_type == 6 --> split
    else
    {
        users[player_num].split();
    }
}

void Scene::del_trash(int index)
{
//    trashes.erase(trashes.begin() + index);
}

void Scene::render()
{
    for(int i = 0; i < users.size(); ++ i)
    {
        users[i].move();
    }

//    cout << users[0].children[0].rad << endl;
//    cout << "users size : " << users.size() << endl;

//    cout << "users move done" << endl;

    for(int i = 0; i < users.size(); ++ i)
    {
        for(int j = 0; j < users[i].children.size(); ++ j)
        {
            double r1 = users[i].children[j].rad;
            int x1 = users[i].children[j].x, y1 = users[i].children[j].y;

            for(int k = 0; k < viruses.size(); ++ k)
            {
                int r2 = viruses[k].rad, x2 = viruses[k].x, y2 = viruses[k].y;

                if((r2 - r1) > 10)
                    continue;
                else if((r2 + r1) > sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))
                {
                    viruses[k].x = rand() % 2000;
                    viruses[k].y = rand() % 2000;
                    while (users[i].children.size() < 16)
                    {
                        bool flag = 1;
                        for(int m = 0; m < users[i].children.size(); ++ m)
                        {
                            if(users[i].children[m].rad > 50)
                                flag = 0;
                        }
                        if(flag)
                            break;
                        users[i].split();
                    }
                }
                //dont know exactly what happens
                //something will be splited
                //the parts are still user's, not trash
                //
                //


            }
        }
    }


//    cout << "users hit virus" << endl;
//    cout << users[0].children[0].rad << endl;

    for(int i = 0; i < users.size(); ++ i)
    {
        for(int j = 0; j < users.size(); ++ j)
        {
            if(i == j)
                continue;
            for(int k = 0; k < users[i].children.size(); ++ k)
            {
                double r1 = users[i].children[k].rad;
                int x1 = users[i].children[k].x, y1 = users[i].children[k].y;

                for(int m = 0; m < users[j].children.size(); ++ m)
                {
                    double r2 = users[j].children[m].rad;
                    int x2 = users[j].children[m].x, y2 = users[j].children[m].y;

                    if((r2 + r1) > (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))))
                    {
                        if((r2 - r1) > 10)
                        {
                            users[j].children[m].eat_user(r1);
                            users[i].children.erase(users[i].children.begin() + k);
                        }
                        else if((r1 - r2) > 10)
                        {
                            users[i].children[k].eat_user(r2);
                            users[j].children.erase(users[j].children.begin() + m);
                        }
                    }
                }
            }
        }
    }


//    cout << "users eat eachother" << endl;
//    cout << users[0].children[0].rad << endl;

    int eatedcnt = 0;

    for(int i = 0; i < users.size(); ++ i)
    {
        for(int j = 0; j < users[i].children.size(); ++ j)
        {
            double r1 = users[i].children[j].rad;
            int x1 = users[i].children[j].x, y1 = users[i].children[j].y;

            for(int k = 0; k < foods.size(); ++ k)
            {
                int r2 = (foods[k]).rad, x2 = (foods[k]).x, y2 = (foods[k]).y;

                if(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) < (r1 + r2))
                {
                    users[i].children[j].eat_food();
                    foods[k].x = rand() % 2000;
                    foods[k].y = rand() % 2000;
                    eatedcnt ++;
                }
            }
        }
    }

//    cout << "users eat food" << endl;
//    cout << users[0].children[0].rad << endl;

    for(int i = 0; i < users.size(); ++ i)
    {
        for(int j = 0; j < users[i].children.size(); ++ j)
        {
            double r1 = users[i].children[j].rad;
            int x1 = users[i].children[j].x, y1 = users[i].children[j].y;

            for(int k = 0; k < trashes.size(); ++ k)
            {
                double r2 = trashes[k].rad;
                int x2 = trashes[k].x, y2 = trashes[k].y;

                if((r2 + r1) > sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))
                {
                    users[i].children[j].eat_trash(r2);
                   // del_trash(k);
                }
            }
        }
    }
//
//    cout << "users eat trash" << endl;
//    cout << users[0].children[0].rad << endl;

}

QString Scene::change_data_to_str()
{
    // player_number:child_x+child_y+child_rad&
    string ans = "";

//    cout << users[0].children[0].rad << endl;
    for(int i = 0; i < users.size(); ++ i)
    {
        string cur_user = to_string(i) + ":";
        ans += cur_user;
        for(int j = 0; j < users[i].children.size(); ++ j)
        {
            string cur_child = to_string(users[i].children[j].x) + "+" + to_string(users[i].children[j].y) + "+";
            cur_child += to_string(users[i].children[j].rad) + "&";
            ans += cur_child;
        }
    }

    //trash:trash_x+trash_y+trash_rad+&
    ans += "trash:";
    for(int i = 0; i < trashes.size(); ++ i)
    {
        string cur_trash = to_string(trashes[i].x) + "+" + to_string(trashes[i].y) + "+" + to_string(trashes[i].rad) + "&";
        ans += cur_trash;
    }

    //food:food_x+food_y+food_rad&
    ans += "food:";
    for(int i = 0; i < foods.size(); ++ i)
    {
        string cur_food = to_string(foods[i].x) + "+" + to_string(foods[i].y) + "+" + to_string(foods[i].rad) + "&";
        ans += cur_food;
    }

    ans +="virus:";
    for(int i = 0; i < viruses.size(); ++ i)
    {
        string cur_virus = to_string(viruses[i].x) + "+" + to_string(viruses[i].y) + "+" + to_string(viruses[i].rad) + "&";
        ans += cur_virus;
    }

    QString map = QString::fromStdString(ans);
    return map;
}
