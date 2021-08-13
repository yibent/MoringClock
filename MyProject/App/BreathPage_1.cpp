#include "BreathPage_1.h"

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

BreathPage_1* BreathPage_1::create() {
    auto mp = new (std::nothrow) BreathPage_1{};
    if (mp && mp->init()) {
        mp->autorelease();
        return mp;
    }
    return nullptr;
}

bool BreathPage_1::init() {
    if (!BasePage::init()) {
        return false;
    }

    auto l = BreathPage_1Layer0::create();
    this->addChild(l, 2);

    return true;
}

//*****************************************************************
//*****************************************************************
//*****************************************************************

BreathPage_1Layer0::BreathPage_1Layer0() {}

BreathPage_1Layer0::~BreathPage_1Layer0() {
    EventDispatcher::instance->unregist(eventRec);
}

BreathPage_1Layer0* BreathPage_1Layer0::create() {
    auto l = new (std::nothrow) BreathPage_1Layer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool BreathPage_1Layer0::init() {
    auto visibleSize = Director::instance->getVisibleSize();

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(visibleSize / 2);
    this->addChild(bk);

    auto menu = Menu::create();
    this->addChild(menu, 1);



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

void BreathPage_1Layer0::touchDown(const Vec2& pos) {}

void BreathPage_1Layer0::touchMove(const Vec2& pos) {}

void BreathPage_1Layer0::touchUp(const Vec2& pos) {}
