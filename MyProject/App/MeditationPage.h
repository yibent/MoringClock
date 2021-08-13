#ifndef __MEDITATION_PAGE_H__
#define __MEDITATION_PAGE_H__

#include "BasePage.h"
#include "Engine/EventDispatcher.h"
#include "Engine/Label.h"
#include "Engine/Layer.h"
#include "Engine/Scene.h"
#include "Engine/Sprite.h"
#include "Engine/UI.h"

class MeditationPage : public BasePage {
public:
    static MeditationPage* create();

    virtual bool init() override;
};

class MeditationPageLayer0 : public Layer {
public:
    static MeditationPageLayer0* create();
    MeditationPageLayer0();
    virtual ~MeditationPageLayer0();
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