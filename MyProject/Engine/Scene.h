#ifndef __SCENE_H__
#define __SCENE_H__

class Node;
class Menu;
#include <QPainter>
#include <functional>
#include <vector>

#include "Node.h"
#include "Schedule.h"
#include "Vec2.h"

class Scene : public Node {
public:
    Scene() {}
    virtual ~Scene() {}

    virtual void update();

    virtual void draw(QPainter &painter);
    virtual bool init() { return true; }

    //点击的消息
    void touchDown(const Vec2 &pos);
    void touchMove(const Vec2 &pos);
    void touchUp(const Vec2 &pos);

private:
    virtual void setParent(Node *) override final {}
    virtual void removeFromParent() override final {}

    //触摸位置
    Vec2 touchPos;
    //是否按下
    bool touchPressed;
};

#endif
