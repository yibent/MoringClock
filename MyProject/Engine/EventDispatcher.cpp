#include "EventDispatcher.h"

using namespace std;

EventDispatcher* EventDispatcher::instance = new EventDispatcher{};

void EventDispatcher::regist(EventReceiver* receiver, int ZOrder) {
    if (!receiver) {
        return;
    }
    receiver->retain();
    receiver->ZOrder = ZOrder;
    receiverPool.insert({ZOrder, receiver});
}

void EventDispatcher::unregist(EventReceiver* receiver) {
    if (!receiver) {
        return;
    }
    auto low = receiverPool.lower_bound(receiver->ZOrder);
    auto up = receiverPool.upper_bound(receiver->ZOrder);
    auto it = low;
    bool find = false;
    for (; it != up; ++it) {
        if (it->second == receiver) {
            find = true;
            break;
        }
    }
    if (find) {
        receiverPool.erase(it);
    }

    receiver->release();
}

void EventDispatcher::touchDown(const Vec2& pos) {
    for (auto it = receiverPool.begin(); it != receiverPool.end(); ++it) {
        auto& rec = *it;
        if (!rec.second->touchDown(pos)) {
            break;
        }
    }
}

void EventDispatcher::touchMove(const Vec2& pos) {
    for (auto it = receiverPool.begin(); it != receiverPool.end(); ++it) {
        auto& rec = *it;
        if (!rec.second->touchMove(pos)) {
            break;
        }
    }
}

void EventDispatcher::touchUp(const Vec2& pos) {
    for (auto it = receiverPool.begin(); it != receiverPool.end(); ++it) {
        auto& rec = *it;
        if (!rec.second->touchUp(pos)) {
            break;
        }
    }
}

//******************************************************************
//******************************************************************
//******************************************************************

EventReceiver* EventReceiver::create() {
    auto rec = new (std::nothrow) EventReceiver{};
    if (rec) {
        rec->autorelease();
        return rec;
    }
    return nullptr;
}

EventReceiver::EventReceiver() {}

EventReceiver::~EventReceiver() {}
