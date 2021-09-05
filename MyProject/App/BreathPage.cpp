#include "BreathPage.h"

#include <chrono>
#include <cmath>
#include <sstream>

#include "Director.h"
#include "Engine/Action.h"
#include "Engine/Audio.h"
#include "Engine/Default.h"
#include "Engine/Node.h"
#include "Engine/Sprite.h"
#include "MainPage.h"
using namespace std;
using namespace std::chrono;

BreathPage* BreathPage::create()
{
    auto mp = new (std::nothrow) BreathPage{};
    if (mp && mp->init()) {
        mp->autorelease();
        return mp;
    }
    return nullptr;
}

bool BreathPage::init()
{
    if (!BasePage::init()) {
        return false;
    }

    auto l = BreathPageLayer0::create();
    this->addChild(l, 2);

    return true;
}

//*****************************************************************
//*****************************************************************
//*****************************************************************

BreathPageLayer0::BreathPageLayer0() {}

BreathPageLayer0::~BreathPageLayer0()
{
    EventDispatcher::instance->unregist(eventRec);
}

BreathPageLayer0* BreathPageLayer0::create()
{
    auto l = new (std::nothrow) BreathPageLayer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool BreathPageLayer0::init()
{
    auto visibleSize = Director::instance->getVisibleSize();

    auto pageTurn = Sprite::create(RES_FILE("BreathPage/page_turn.png"));
    pageTurn->setPosition(visibleSize / 2);
    pageTurn->setScale(Vec2(1.5f, 1.5f));
    this->addChild(pageTurn, 3);
    auto pageTurn_fadeOut = FadeOut::create(0.2f);
    auto pagrTurn_vis =
        CallFuncN::create([](Node* node) { node->setVisible(false); });
    auto pageTurn_seq = Sequence::create({pageTurn_fadeOut, pagrTurn_vis});
    pageTurn->runAction(pageTurn_seq);

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(visibleSize / 2);
    this->addChild(bk);

    auto menu = Menu::create();
    this->addChild(menu, 1);

    auto todayBreathBk =
        Sprite::create(RES_FILE("BreathPage/today_breath_bk.png"));
    todayBreathBk->setPosition(Vec2(415, 544));
    this->addChild(todayBreathBk, 1);

    auto todayBreathIcon =
        Sprite::create(RES_FILE("BreathPage/today_breath_icon.png"));
    todayBreathIcon->setPosition(Vec2(417, 524));
    this->addChild(todayBreathIcon, 2);

    auto lastBreathBk =
        Sprite::create(RES_FILE("BreathPage/last_breath_bk.png"));
    lastBreathBk->setPosition(Vec2(905, 544));
    this->addChild(lastBreathBk, 1);

    auto lastBreathIcon =
        Sprite::create(RES_FILE("BreathPage/last_breath_icon.png"));
    lastBreathIcon->setPosition(Vec2(912, 514));
    this->addChild(lastBreathIcon, 2);

    auto fastStartBk = Sprite::create(RES_FILE("BreathPage/fast_start_bk.png"));
    fastStartBk->setPosition(Vec2(1467, 413));
    this->addChild(fastStartBk, 1);

    auto tempBk = Sprite::create(RES_FILE("BreathPage/temp_bk.png"));
    tempBk->setPosition(Vec2(661, 224));
    this->addChild(tempBk, 1);

    auto fastStartIcon =
        Sprite::create(RES_FILE("BreathPage/fast_start_icon.png"));
    fastStartIcon->setPosition(Vec2(1404, 494));
    this->addChild(fastStartIcon, 2);

    //创建消息接收器
    auto eventRec = EventReceiver::create();
    EventDispatcher::instance->regist(eventRec, 1);

    auto returnButton =
        Button::create(RES_FILE(""), RES_FILE(""), RES_FILE(""));
    returnButton->setPosition(Vec2());
    returnButton->setCallBack([&](basic_Button* button) {
        auto s = MainPage::create();
        Director::instance->runWithScene(s);
    });
    this->addChild(returnButton, 2);

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

void BreathPageLayer0::touchDown(const Vec2& pos) {}

void BreathPageLayer0::touchMove(const Vec2& pos) {}

void BreathPageLayer0::touchUp(const Vec2& pos) {}
