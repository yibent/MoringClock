#include "MyApp.h"

#include "App/MainPage.h"

#include "App/MyDefault.h"

#include <chrono>
using namespace std;
using namespace std::chrono;

void MyApp::startApp()
{
    Director::instance = new Director();
    Director::instance->setWindowSize(1920, 1080);
    //Director::instance->setGeometry(QRect(0, 0, 600, 400));
    Director::instance->setWindowTitle("Clock");
    //*************************************************
    auto s = MainPage::create();
    Director::instance->runWithScene(s);
    //*************************************************

    Director::instance->show();
}
