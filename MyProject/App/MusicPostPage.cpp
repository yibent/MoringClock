#include "MusicPostPage.h"

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

MusicPostPage* MusicPostPage::create() {
    auto mp = new (std::nothrow) MusicPostPage{};
    if (mp && mp->init()) {
        mp->autorelease();
        return mp;
    }
    return nullptr;
}

bool MusicPostPage::init() {
    if (!BasePage::init()) {
        return false;
    }

    auto l = MusicPostPageLayer0::create();
    this->addChild(l, 2);

    return true;
}

//*****************************************************************
//*****************************************************************
//*****************************************************************

MusicPostPageLayer0::MusicPostPageLayer0() {}

MusicPostPageLayer0::~MusicPostPageLayer0() {
    EventDispatcher::instance->unregist(eventRec);
}

MusicPostPageLayer0* MusicPostPageLayer0::create() {
    auto l = new (std::nothrow) MusicPostPageLayer0{};
    if (l && l->init()) {
        l->autorelease();
        return l;
    }
    return nullptr;
}

bool MusicPostPageLayer0::init() {
    auto visibleSize = Director::instance->getVisibleSize();

    auto bk = Sprite::create(RES_FILE("black_bk.png"));
    bk->setPosition(visibleSize / 2);
    this->addChild(bk);

    auto menu = Menu::create();
    this->addChild(menu, 1);

    auto music_post_bk =
        Sprite::create(RES_FILE("MusicPostPage/music_post_bk.png"));
    music_post_bk->setPosition(Vec2(501, 528));
    this->addChild(music_post_bk, 1);

    auto music_post_icon =
        Sprite::create(RES_FILE("MusicPostPage/music_post_icon.png"));
    music_post_icon->setPosition(Vec2(1298, 710));
    this->addChild(music_post_icon, 1);

    auto start = Sprite::create(RES_FILE("MusicPostPage/start.png"));
    start->setPosition(Vec2(1061, 306));
    this->addChild(start, 1);

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

void MusicPostPageLayer0::touchDown(const Vec2& pos) {}

void MusicPostPageLayer0::touchMove(const Vec2& pos) {}

void MusicPostPageLayer0::touchUp(const Vec2& pos) {}
