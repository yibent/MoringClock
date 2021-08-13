#ifndef __BASE_PAGE_H__
#define __BASE_PAGE_H__

#include <vector>

#include "Engine/EventDispatcher.h"
#include "Engine/Label.h"
#include "Engine/Layer.h"
#include "Engine/Scene.h"
#include "Engine/Sprite.h"

class BasePageLayer0;

class BasePage : public Scene {
public:
    static BasePage* create();
    virtual bool init() override;
    virtual void release() override;

    BasePage();
    virtual ~BasePage();

private:
    void startSche();
    bool isShutDown = false;
    EventReceiver* eventRec = nullptr;
    BasePageLayer0* l0 = nullptr;
};

class BasePageLayer0 : public Layer {
public:
    static BasePageLayer0* create();
    virtual bool init() override;

    //渐变显示
    void fadeIn();
    //渐变消失
    void fadeOut();
    //没有渐变的过程,直接消失
    void fastOut();
    //更新时间显示
    void updateTimeShow();

private:
    std::vector<Node*> controlNodes;
    Label* timeShow = nullptr;
};

#endif