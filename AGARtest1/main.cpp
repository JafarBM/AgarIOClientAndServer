#include <iostream>
#include <headers/Client.h>
#include <QApplication>
using namespace std;


int main(int argc, char **argv) {
    QApplication *app = new QApplication(argc, argv);
    new Client;
    return app -> exec();
}