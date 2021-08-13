#ifndef __CLOCK_PAGE_H__
#define __CLOCK_PAGE_H__

#include "BasePage.h"
#include "Engine/EventDispatcher.h"
#include "Engine/Label.h"
#include "Engine/Layer.h"
#include "Engine/Scene.h"
#include "Engine/Sprite.h"
#include "Engine/UI.h"

class ClockPage : public BasePage {
public:
    static ClockPage* create();

    virtual bool init() override;
};

class ClockPageLayer0 : public Layer {
public:
    static ClockPageLayer0* create();
    ClockPageLayer0();
    virtual ~ClockPageLayer0();
    virtual bool init() override;

    void touchDown(const Vec2& pos);
    void touchMove(const Vec2& pos);
    void touchUp(const Vec2& pos);

private:
    //触控按下的坐标位置
    Vec2 downPos;
    EventReceiver* eventRec = nullptr;
};

#endif