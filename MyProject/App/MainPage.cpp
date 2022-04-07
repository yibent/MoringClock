#include "MainPage.h"

#include <chrono>
#include <cmath>
#include <sstream>

#include "BreathPage.h"
#include "BreathPage_1.h"
#include "ClockPage.h"
#include "Director.h"
#include "Engine/Action.h"
#include "Engine/Audio.h"
#include "Engine/Default.h"
#include "Engine/Node.h"
#include "Engine/Sprite.h"
#include "MeditationPage.h"
#include "MusicPostPage.h"
using namespace std;
using namespace std::chrono;

MainPage* MainPage::create()
{
    auto mp = new (std::nothrow) MainPage{};
    if (mp && mp->init()) {
        mp->autorelease();
        return mp;
    }
    return nullptr;
}

bool MainPage::init()
{
    if (!BasePage::init()) {
        return false;
    }

    auto l = MainPageLayer0::create();
    this->addChild(l, 2);

    return true;
}

//*****************************************************************
//*****************************************************************
//*****************************************************************

MainPageLayer0::MainPageLayer0() {}

MainPageLayer0::~MainPageLayer0() {}

void MainPageLayer0::release()
{
    EventDispatcher::instance->unregist(eventRec);
    Node::release();
}

MainPageLayer0* MainPageLayer0::create()
{
    auto l = new (std::nothrow) MainPageLayer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool MainPageLayer0::init()
{
    auto visibleSize = Director::instance->getVisibleSize();

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(visibleSize / 2);
    this->addChild(bk);

    slideBar = Node::create();
    this->addChild(slideBar, 1);

    auto menu = Menu::create();
    slideBar->addChild(menu);

    auto musicPost = Sprite::create(RES_FILE("MainPage/music_post.png"));
    musicPost->setPosition(Vec2(465, 425));
    slideBar->addChild(musicPost, 1);

    this->clockBk = Button::create(RES_FILE("MainPage/clock_bk.png"),
                                   RES_FILE("MainPage/clock_bk.png"),
                                   RES_FILE("MainPage/clock_bk.png"));
    clockBk->setPosition(Vec2(979, 509));
    clockBk->setCallBack([&](basic_Button* button) { clockPageTurn(); });
    menu->addButton(clockBk);

    auto clockIcon = Sprite::create(RES_FILE("MainPage/clock_icon.png"));
    clockIcon->setPosition(Vec2(883, 545));
    slideBar->addChild(clockIcon, 1);

    auto musicBk = Button::create(RES_FILE("MainPage/music_bk.png"),
                                  RES_FILE("MainPage/music_bk.png"),
                                  RES_FILE("MainPage/music_bk.png"));
    musicBk->setPosition(Vec2(979, 226));
    musicBk->setCallBack([&](basic_Button* button) {
        if (!onSlide) {
            musicPostPageTurn();
        }
    });
    menu->addButton(musicBk);

    this->meditationBk = Button::create(RES_FILE("MainPage/meditation_bk.png"),
                                        RES_FILE("MainPage/meditation_bk.png"),
                                        RES_FILE("MainPage/meditation_bk.png"));
    meditationBk->setPosition(Vec2(1437, 509));
    meditationBk->setCallBack([&](basic_Button* button) {
        if (!onSlide) {
            meditationPageTurn();
        }
    });
    menu->addButton(meditationBk);

    auto meditationIcon =
        Sprite::create(RES_FILE("MainPage/meditation_icon.png"));
    meditationIcon->setPosition(Vec2(1338, 555));
    slideBar->addChild(meditationIcon, 1);

    auto weatherBk = Button::create(RES_FILE("MainPage/weather_bk.png"),
                                    RES_FILE("MainPage/weather_bk.png"),
                                    RES_FILE("MainPage/weather_bk.png"));
    weatherBk->setPosition(Vec2(1427, 226));
    weatherBk->setCallBack([&](basic_Button* button) {
        if (!onSlide) {
        }
    });
    menu->addButton(weatherBk);

    auto optionBk = Button::create(RES_FILE("MainPage/option_bk.png"),
                                   RES_FILE("MainPage/option_bk.png"),
                                   RES_FILE("MainPage/option_bk.png"));
    optionBk->setPosition(Vec2(1875, 583));
    optionBk->setCallBack([&](basic_Button* button) {
        if (!onSlide) {
        }
    });
    menu->addButton(optionBk);

    this->breathBk = Button::create(RES_FILE("MainPage/breath_bk.png"),
                                    RES_FILE("MainPage/breath_bk.png"),
                                    RES_FILE("MainPage/breath_bk.png"));
    breathBk->setPosition(Vec2(1875, 300));
    breathBk->setCallBack([&](basic_Button* button) {
        if (!onSlide) {
            breathPageTurn();
        }
    });
    menu->addButton(breathBk);

    auto breathIcon = Sprite::create(RES_FILE("MainPage/breath_icon.png"));
    breathIcon->setPosition(Vec2(1865, 309));
    slideBar->addChild(breathIcon, 1);

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

    auto sss = Sound::create(R"(C:\Users\Bang\Desktop\123123.wav)");
    sss->play();
    sss->setVolume(0.5f);
    sss->retain();

    return true;
}

void MainPageLayer0::touchDown(const Vec2& pos)
{
    downPos = pos;
    orgPos = slideBar->getPosition();
}

void MainPageLayer0::touchMove(const Vec2& pos)
{
    float flag = 1;
    float dis = pos.x - downPos.x;
    if (dis < 0) {
        flag = -1;
        dis = abs(dis);
    }
    if (dis > 10) {
        onSlide = true;
    }
    slideBar->setPosition(orgPos + Vec2(pow(dis, 0.8f) * flag, 0));
}

void MainPageLayer0::touchUp(const Vec2& pos)
{
    onSlide = false;
    Vec2 stopP0(0, 0);
    Vec2 stopP1(-350, 0);

    ActionInterval* runAct = nullptr;
    float d = pos.x - downPos.x;
    if (d < -50) {
        runAct = MoveTo::create(0.15f, stopP1);
    } else if (d > 50) {
        runAct = MoveTo::create(0.15f, stopP0);
    }
    if (!runAct) {
        return;
    }
    auto e = EaseAction::create(runAct, 1.5f, EaseFunction::easeInOut);

    slideBar->stopAllActions();
    slideBar->runAction(runAct);
}

void MainPageLayer0::breathPageTurn()
{
    if (onPageTurn) {
        return;
    }
    auto visibleSize = Director::instance->getVisibleSize();

    auto turnBk = Sprite::create(RES_FILE("BreathPage/page_turn.png"));
    this->addChild(turnBk, 2);

    auto pos = breathBk->convertPosToParent();
    turnBk->setPosition(pos);

    float scale = breathBk->getContentSize().x / turnBk->getContentSize().x;
    turnBk->setScale(scale, scale);

    auto a0 = MoveTo::create(0.2f, visibleSize / 2);
    auto a1 = ScaleTo::create(0.4f, 1.5f);
    auto e0 = EaseAction::create(a0, 2.0f, EaseFunction::easeInOut);
    auto e1 = EaseAction::create(a1, 2.0f, EaseFunction::easeInOut);
    auto spa = Spawn::create({e0, e1});
    auto callFunc = CallFunc::create([&]() {
        auto s = BreathPage::create();
        Director::instance->runWithScene(s);
    });
    auto s = Sequence::create({spa, callFunc});
    turnBk->runAction(s);
    onPageTurn = true;
}

void MainPageLayer0::clockPageTurn()
{
    if (onPageTurn) {
        return;
    }
    auto visibleSize = Director::instance->getVisibleSize();

    auto turnBk = Sprite::create(RES_FILE("Clock/page_turn.png"));
    this->addChild(turnBk, 2);

    auto pos = clockBk->convertPosToParent();
    turnBk->setPosition(pos);

    float scale = clockBk->getContentSize().x / turnBk->getContentSize().x;
    turnBk->setScale(scale, scale);

    auto a0 = MoveTo::create(0.2f, visibleSize / 2);
    auto a1 = ScaleTo::create(0.4f, 1.8f);
    auto e0 = EaseAction::create(a0, 2.0f, EaseFunction::easeInOut);
    auto e1 = EaseAction::create(a1, 2.0f, EaseFunction::easeInOut);
    auto spa = Spawn::create({e0, e1});
    auto callFunc = CallFunc::create([&]() {
        auto s = ClockPage::create();
        Director::instance->runWithScene(s);
    });
    auto s = Sequence::create({spa, callFunc});
    turnBk->runAction(s);
    onPageTurn = true;
}

void MainPageLayer0::meditationPageTurn()
{
    if (onPageTurn) {
        return;
    }
    auto visibleSize = Director::instance->getVisibleSize();

    auto turnBk = Sprite::create(RES_FILE("Meditation/page_turn.png"));
    this->addChild(turnBk, 2);

    auto pos = meditationBk->convertPosToParent();
    turnBk->setPosition(pos);

    float scale = meditationBk->getContentSize().x / turnBk->getContentSize().x;
    turnBk->setScale(scale, scale);

    auto a0 = MoveTo::create(0.2f, visibleSize / 2);
    auto a1 = ScaleTo::create(0.4f, 1.8f);
    auto e0 = EaseAction::create(a0, 2.0f, EaseFunction::easeInOut);
    auto e1 = EaseAction::create(a1, 2.0f, EaseFunction::easeInOut);
    auto spa = Spawn::create({e0, e1});
    auto callFunc = CallFunc::create([&]() {
        auto s = MeditationPage::create();
        Director::instance->runWithScene(s);
    });
    auto s = Sequence::create({spa, callFunc});
    turnBk->runAction(s);
    onPageTurn = true;
}

void MainPageLayer0::breathPage_1Turn()
{
    if (onPageTurn) {
        return;
    }
    auto s = BreathPage_1::create();
    Director::instance->runWithScene(s);
    onPageTurn = true;
}

void MainPageLayer0::musicPostPageTurn()
{
    if (onPageTurn) {
        return;
    }
    auto s = MusicPostPage::create();
    Director::instance->runWithScene(s);
    onPageTurn = true;
}
