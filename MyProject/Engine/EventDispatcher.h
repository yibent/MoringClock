#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include <functional>
#include <map>

#include "Ref.h"
#include "Vec2.h"

class EventReceiver;

//事件分发器
class EventDispatcher final {
public:
    static EventDispatcher *instance;

public:
    void regist(EventReceiver *receiver, int ZOrder);
    void unregist(EventReceiver *receiver);

    void touchDown(const Vec2 &pos);
    void touchMove(const Vec2 &pos);
    void touchUp(const Vec2 &pos);

private:
    std::multimap<int, EventReceiver *> receiverPool;
};

//事件接收器
class EventReceiver final : public Ref {
public:
    static EventReceiver *create();
    EventReceiver();
    virtual ~EventReceiver();

    //返回false将截断以后的所有消息
    std::function<bool(const Vec2 &)> touchDown = [](const Vec2 &) -> bool {
        return true;
    };
    std::function<bool(const Vec2 &)> touchUp = [](const Vec2 &) -> bool {
        return true;
    };
    std::function<bool(const Vec2 &)> touchMove = [](const Vec2 &) -> bool {
        return true;
    };
    int ZOrder = 0;
};

#endif