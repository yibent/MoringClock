#ifndef __MAIN_PAGE_H__
#define __MAIN_PAGE_H__

#include "BasePage.h"
#include "Engine/EventDispatcher.h"
#include "Engine/Label.h"
#include "Engine/Layer.h"
#include "Engine/Scene.h"
#include "Engine/Sprite.h"
#include "Engine/UI.h"

class MainPage : public BasePage {
public:
    static MainPage* create();

    virtual bool init() override;
};

class MainPageLayer0 : public Layer {
public:
    static MainPageLayer0* create();
    MainPageLayer0();
    virtual ~MainPageLayer0();
    virtual void release() override;
    virtual bool init() override;

    void touchDown(const Vec2& pos);
    void touchMove(const Vec2& pos);
    void touchUp(const Vec2& pos);

    void breathPageTurn();
    void clockPageTurn();
    void meditationPageTurn();
    void breathPage_1Turn();
    void musicPostPageTurn();

private:
    /*触控按下的坐标位置*/
    Vec2 downPos;

    /*触摸按下时slideBar的原坐标位置*/
    Vec2 orgPos;

    /*是否正在滑动,如果如果滑动,所有的按钮失效*/
    bool onSlide = false;

    /*是否在跳转界面,在转换页面时,
    所有的按钮都将失效*/
    bool onPageTurn = false;

    EventReceiver* eventRec = nullptr;
    Button* breathBk = nullptr;
    Button* clockBk = nullptr;
    Button* meditationBk = nullptr;
    Node* slideBar = nullptr;
};

#endif