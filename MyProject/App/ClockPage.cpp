#include "ClockPage.h"

#include <chrono>
#include <cmath>
#include <sstream>

#include "Director.h"
#include "Engine/Action.h"
#include "Engine/Audio.h"
#include "Engine/Default.h"
#include "Engine/Node.h"
#include "Engine/Sprite.h"
using namespace std;
using namespace std::chrono;

ClockPage* ClockPage::create() {
    auto mp = new (std::nothrow) ClockPage{};
    if (mp && mp->init()) {
        mp->autorelease();
        return mp;
    }
    return nullptr;
}

bool ClockPage::init() {
    if (!BasePage::init()) {
        return false;
    }

    auto l = ClockPageLayer0::create();
    this->addChild(l, 2);

    return true;
}

//*****************************************************************
//*****************************************************************
//*****************************************************************

ClockPageLayer0::ClockPageLayer0() {}

ClockPageLayer0::~ClockPageLayer0() {
    EventDispatcher::instance->unregist(eventRec);
}

ClockPageLayer0* ClockPageLayer0::create() {
    auto l = new (std::nothrow) ClockPageLayer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool ClockPageLayer0::init() {
    auto visibleSize = Director::instance->getVisibleSize();

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(visibleSize / 2);
    this->addChild(bk);

    auto menu = Menu::create();
    this->addChild(menu, 1);

    auto lastSleepBk = Sprite::create(RES_FILE("Clock/last_sleep_bk.png"));
    lastSleepBk->setPosition(Vec2(800, 562));
    this->addChild(lastSleepBk, 1);

    auto lastSleepIcon =
        Sprite::create(RES_FILE("Clock/last_sleep_icon.png"));
    lastSleepIcon->setPosition(Vec2(799, 537));
    this->addChild(lastSleepIcon, 1);

    auto setClockBk =
        Sprite::create(RES_FILE("Clock/set_clock_bk.png"));
    setClockBk->setPosition(Vec2(1586, 420));
    this->addChild(setClockBk, 1);

    auto setClockIcon =
        Sprite::create(RES_FILE("Clock/set_clock_icon.png"));
    setClockIcon->setPosition(Vec2(1589, 412));
    this->addChild(setClockIcon, 1);

     auto smartClockBk =
        Sprite::create(RES_FILE("Clock/smart_clock_bk.png"));
    smartClockBk->setPosition(Vec2(800, 252));
    this->addChild(smartClockBk, 1);

    auto smartClockIcon =
        Sprite::create(RES_FILE("Clock/smart_clock_icon.png"));
    smartClockIcon->setPosition(Vec2(806, 248));
    this->addChild(smartClockIcon, 1);

    //创建消息接收器
    auto eventRec = EventReceiver::create();
    EventDispatcher::instance->regist(eventRec, 1);

    eventRec->touchDown = [&](const Vec2& pos) -> bool {
        touchDown(pos);
        return true;
    };

    eventRec->touchMove = [&](const Vec2& pos) -> bool {
        touchMove(pos);
        return true;
    };

    eventRec->touchUp = [&](const Vec2& pos) -> bool {
        touchUp(pos);
        return true;
    };

    return true;
}

void ClockPageLayer0::touchDown(const Vec2& pos) {}

void ClockPageLayer0::touchMove(const Vec2& pos) {}

void ClockPageLayer0::touchUp(const Vec2& pos) {}
