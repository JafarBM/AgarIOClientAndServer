#include <iostream>
#include <QApplication>
#include <server.h>

using namespace std;


int main(int argc, char **argv)
{
    QApplication *app = new QApplication(argc, argv);
    Server *AgarSRV = new Server();
    app -> exec();
    
    return 0;
}
