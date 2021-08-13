#include "BasePage.h"

#include <chrono>
#include <ctime>
#include <sstream>
#include <string>

#include "Director.h"
#include "Engine/Action.h"
#include "Engine/Default.h"
#include "Engine/Label.h"
#include "Engine/Sprite.h"

using namespace std;
using namespace std::chrono;

BasePage::BasePage() {}

BasePage::~BasePage() {}

void BasePage::release() { EventDispatcher::instance->unregist(eventRec); }

BasePage* BasePage::create() {
    auto bp = new (std::nothrow) BasePage{};
    if (bp && bp->init()) {
        bp->autorelease();
        return bp;
    }
    return nullptr;
}

bool BasePage::init() {
    l0 = BasePageLayer0::create();
    this->addChild(l0, 100);

    // l0->fadeOut();
    l0->fastOut();
    this->startSche();

    eventRec = EventReceiver::create();
    EventDispatcher::instance->regist(eventRec, 0);

    eventRec->touchDown = [&](const Vec2& pos) -> bool {
        if (isShutDown) {
            return false;
        }
        return true;
    };

    eventRec->touchMove = [&](const Vec2& pos) -> bool {
        if (isShutDown) {
            return false;
        }
        return true;
    };

    eventRec->touchUp = [&](const Vec2& pos) -> bool {
        this->unschedule("autoShutDown");
        this->startSche();
        if (isShutDown) {
            l0->fadeOut();
            //////////
            isShutDown = false;
            return false;
        }

        return true;
    };

    return true;
}

void BasePage::startSche() {
    this->scheduleOnce(
        5.0f /*自动出现息屏的时间*/,
        [&]() {
            l0->fadeIn();
            isShutDown = true;
        },
        "autoShutDown");
}

BasePageLayer0* BasePageLayer0::create() {
    auto l = new (std::nothrow) BasePageLayer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool BasePageLayer0::init() {
    auto size = Director::instance->getVisibleSize();

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(size / 2);
    this->addChild(bk, 1);
    controlNodes.push_back(bk);

    auto planet = Sprite::create(RES_FILE("SleepPage/planet.png"));
    planet->setPosition(Vec2(1920 / 2, 1080 * 0.618f));
    this->addChild(planet, 2);
    controlNodes.push_back(planet);

    this->timeShow = Label::create(RES_FILE("DENGB.TTF"));
    timeShow->setPosition(Vec2(1920 / 2 - 110, 1080 / 2 - 200));
    timeShow->setFontSize(56);
    this->addChild(timeShow, 3);
    controlNodes.push_back(timeShow);

    this->schedule(
        0.5f, [&]() { updateTimeShow(); }, "updateTimeShow");
    return true;
}

void BasePageLayer0::fadeIn() {
    for (auto it = controlNodes.begin(); it != controlNodes.end(); ++it) {
        auto& node = *it;
        node->stopAllActions();
        auto f = FadeIn::create(0.8f);
        auto e = EaseAction::create(f, 1.5f, EaseFunction::easeIn);
        node->runAction(e);
    }
}

void BasePageLayer0::fadeOut() {
    for (auto it = controlNodes.begin(); it != controlNodes.end(); ++it) {
        auto& node = *it;
        node->stopAllActions();
        auto f = FadeOut::create(0.8f);
        auto e = EaseAction::create(f, 1.5f, EaseFunction::easeIn);
        node->runAction(e);
    }
}

void BasePageLayer0::fastOut() {
    for (auto it = controlNodes.begin(); it != controlNodes.end(); ++it) {
        auto& node = *it;
        node->setOpacity(0);
    }
}

void BasePageLayer0::updateTimeShow() {
    const auto time = system_clock::to_time_t(system_clock::now());
    const auto localTime = (*localtime(&time));
    const int hour = localTime.tm_hour;
    const int minute = localTime.tm_min;
    stringstream strStream;
    if (hour < 10) {
        strStream << "0" << hour;
    } else {
        strStream << hour;
    }

    strStream << " : ";

    if (minute < 10) {
        strStream << "0" << minute;
    } else {
        strStream << minute;
    }

    timeShow->setString(str2qstr(strStream.str()));
}