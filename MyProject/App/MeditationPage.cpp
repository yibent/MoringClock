#include "MeditationPage.h"

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

MeditationPage* MeditationPage::create() {
    auto mp = new (std::nothrow) MeditationPage{};
    if (mp && mp->init()) {
        mp->autorelease();
        return mp;
    }
    return nullptr;
}

bool MeditationPage::init() {
    if (!BasePage::init()) {
        return false;
    }

    auto l = MeditationPageLayer0::create();
    this->addChild(l, 2);

    return true;
}

//*****************************************************************
//*****************************************************************
//*****************************************************************

MeditationPageLayer0::MeditationPageLayer0() {}

MeditationPageLayer0::~MeditationPageLayer0() {
    EventDispatcher::instance->unregist(eventRec);
}

MeditationPageLayer0* MeditationPageLayer0::create() {
    auto l = new (std::nothrow) MeditationPageLayer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool MeditationPageLayer0::init() {
    auto visibleSize = Director::instance->getVisibleSize();

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(visibleSize / 2);
    this->addChild(bk);

    auto menu = Menu::create();
    this->addChild(menu, 1);

    auto today_med_bk =
        Sprite::create(RES_FILE("Meditation/today_med_bk.png"));
    today_med_bk->setPosition(Vec2(415, 545));
    this->addChild(today_med_bk, 1);

    auto today_med_icon =
        Sprite::create(RES_FILE("Meditation/today_med_icon.png"));
    today_med_icon->setPosition(Vec2(417, 525));
    this->addChild(today_med_icon, 1);

    auto fast_start_bk =
        Sprite::create(RES_FILE("Meditation/fast_start_bk.png"));
    fast_start_bk->setPosition(Vec2(1467, 413));
    this->addChild(fast_start_bk, 1);

    auto fast_start_icon =
        Sprite::create(RES_FILE("Meditation/fast_start_icon.png"));
    fast_start_icon->setPosition(Vec2(1404, 495));
    this->addChild(fast_start_icon, 1);

    auto last_med_bk =
        Sprite::create(RES_FILE("Meditation/last_med_bk.png"));
    last_med_bk->setPosition(Vec2(906, 545));
    this->addChild(last_med_bk, 1);

    auto last_med_icon =
        Sprite::create(RES_FILE("Meditation/last_med_icon.png"));
    last_med_icon->setPosition(Vec2(912, 525));
    this->addChild(last_med_icon, 1);

     auto block_1 =
        Sprite::create(RES_FILE("Meditation/block_1.png"));
    block_1->setPosition(Vec2(661, 225));
    this->addChild(block_1, 1);


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

void MeditationPageLayer0::touchDown(const Vec2& pos) {}

void MeditationPageLayer0::touchMove(const Vec2& pos) {}

void MeditationPageLayer0::touchUp(const Vec2& pos) {}
