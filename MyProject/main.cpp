#include "MyApp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyApp myApp;
    myApp.startApp();

    return a.exec();
}
