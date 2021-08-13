#ifndef __BREATH_PAGE_1_H__
#define __BREATH_PAGE_1_H__

#include "BasePage.h"
#include "Engine/EventDispatcher.h"
#include "Engine/Label.h"
#include "Engine/Layer.h"
#include "Engine/Scene.h"
#include "Engine/Sprite.h"
#include "Engine/UI.h"

class BreathPage_1 : public BasePage {
public:
    static BreathPage_1* create();

    virtual bool init() override;
};

class BreathPage_1Layer0 : public Layer {
public:
    static BreathPage_1Layer0* create();
    BreathPage_1Layer0();
    virtual ~BreathPage_1Layer0();
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