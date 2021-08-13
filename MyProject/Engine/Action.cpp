#include "Action.h"

#include <cmath>

#include "Default.h"
#include "Node.h"
#include "Vec2.h"
using namespace std;

void Action::setNode(Node *node) { this->node = node; }

bool Action::isRunFinish() { return runFinish; }

//**********************************************************************************

ActionInterval::ActionInterval(float duration) { this->duration = duration; }

ActionInterval::~ActionInterval() {}

void ActionInterval::step(float time) {
    if (firstCall) {
        firstCall = false;
        pastTime = 0;
    } else
        pastTime += time;

    float updateDt = max(0.0f, min(1.0f, pastTime / duration));

    this->update(updateDt);

    if (pastTime >= duration) runFinish = true;
}

float ActionInterval::getDuration() { return duration; }

//**********************************************************************************

Sequence *Sequence::create(const std::vector<Action *> &actions) {
    auto s = new (std::nothrow) Sequence{actions};
    if (s) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

Sequence::Sequence(const vector<Action *> &actions) {
    for (auto &act : actions) {
        act->retain();
        this->actions.push(act);
    }
}

Sequence::~Sequence() {
    while (!actions.empty()) {
        auto &act = actions.front();
        act->release();
        actions.pop();
    }
}

void Sequence::step(float time) {
    auto &act = actions.front();
    act->step(time);
    if (act->isRunFinish()) {
        act->release();
        actions.pop();
    }
    if (actions.empty()) {
        runFinish = true;
    }
}

void Sequence::setNode(Node *node) {
    //遍历一遍队列
    if (actions.empty()) {
        return;
    }
    auto &firstAct = actions.front();
    firstAct->setNode(node);
    actions.pop();
    actions.push(firstAct);
    while (actions.front() != firstAct) {
        auto &act = actions.front();
        act->setNode(node);
        actions.pop();
        actions.push(act);
    }
}

void Sequence::update(float time) {}

//**********************************************************************************

Spawn *Spawn::create(const vector<Action *> &actions) {
    auto s = new (std::nothrow) Spawn{actions};
    if (s) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

Spawn::Spawn(const vector<Action *> &actions) {
    this->actions = actions;
    for (auto &act : this->actions) {
        act->retain();
    }
}

Spawn::~Spawn() {
    for (auto &act : actions) {
        act->release();
    }
}

void Spawn::step(float time) {
    bool allFinish = true;
    for (auto &act : actions) {
        act->step(time);
        if (!act->isRunFinish()) {
            allFinish = false;
        }
    }
    if (allFinish) {
        runFinish = true;
    }
}

void Spawn::setNode(Node *node) {
    for (auto &act : actions) {
        act->setNode(node);
    }
}

void Spawn::update(float time) {}

//**********************************************************************************

DelayTime *DelayTime::create(float duration) {
    auto d = new (std::nothrow) DelayTime{duration};
    if (d) {
        d->autorelease();
        return d;
    }
    return nullptr;
}

DelayTime::DelayTime(float duration) { this->duration = duration; }

DelayTime::~DelayTime() {}

void DelayTime::step(float time) {
    pastTime += time;
    if (pastTime >= duration) {
        runFinish = true;
    }
}

void DelayTime::update(float time) {}

//**********************************************************************************

CallFunc *CallFunc::create(const function<void()> &func) {
    auto c = new (std::nothrow) CallFunc{func};
    if (c) {
        c->autorelease();
        return c;
    }
    return nullptr;
}

CallFunc::CallFunc(const function<void()> &func) { this->func = func; }

CallFunc::~CallFunc() {}

void CallFunc::step(float time) {
    func();
    runFinish = true;
}

void CallFunc::update(float time) {}

//**********************************************************************************

CallFuncN *CallFuncN::create(const function<void(Node *)> &func) {
    auto c = new (std::nothrow) CallFuncN{func};
    if (c) {
        c->autorelease();
        return c;
    }
    return nullptr;
}

CallFuncN::CallFuncN(const function<void(Node *)> &func) { this->func = func; }

CallFuncN::~CallFuncN() {}

void CallFuncN::step(float time) {
    func(node);
    runFinish = true;
}

void CallFuncN::update(float time) {}

//**********************************************************************************

const function<float(float, float)> EaseFunction::easeIn =
    [](float time, float rate) -> float { return pow(time, rate); };

const function<float(float, float)> EaseFunction::easeOut =
    [](float time, float rate) -> float { return pow(time, 1 / rate); };

const function<float(float, float)> EaseFunction::easeInOut =
    [](float time, float rate) -> float {
    if ((time *= 2) < 1) return 0.5f * pow(time, rate);
    return (1.0f - 0.5f * pow(2 - time, rate));
};

//**********************************************************************************

EaseAction *EaseAction::create(ActionInterval *action, float rate,
                               const function<float(float, float)> &func) {
    auto eio = new (std::nothrow) EaseAction{action, rate, func};
    if (eio) {
        eio->autorelease();
        return eio;
    }
    return nullptr;
}

EaseAction::EaseAction(ActionInterval *action, float rate,
                       const function<float(float, float)> &func)
    : ActionInterval(action->getDuration()) {
    this->action = action;
    this->rate = rate;
    this->easeFunc = func;
    action->retain();
}

EaseAction::~EaseAction() { action->release(); }

void EaseAction::update(float time) { action->update(easeFunc(time, rate)); }

void EaseAction::setNode(Node *node) { action->setNode(node); }

//**********************************************************************************

MoveBy *MoveBy::create(float time, const Vec2 &deltaPos) {
    auto move = new (std::nothrow) MoveBy{time, deltaPos};
    if (move) {
        move->autorelease();
        return move;
    }
    return nullptr;
}

MoveBy::MoveBy(float time, const Vec2 &deltaPos) : ActionInterval(time) {
    this->deltaPos = deltaPos;
}

MoveBy::~MoveBy() {}

void MoveBy::update(float time) {
    auto &nowPos = node->getPosition();
    auto di = nowPos - lastPos;
    startPos = startPos + di;
    auto newPos = startPos + deltaPos * time;
    node->setPosition(newPos);
    lastPos = newPos;
}

void MoveBy::setNode(Node *node) {
    startPos = lastPos = node->getPosition();
    ActionInterval::setNode(node);
}

//**********************************************************************************

MoveTo *MoveTo::create(float time, const Vec2 &toPos) {
    auto move = new (std::nothrow) MoveTo{time, toPos};
    if (move) {
        move->autorelease();
        return move;
    }
    return nullptr;
}

MoveTo::MoveTo(float time, const Vec2 &toPos) : MoveBy(time, Vec2{}) {
    this->toPos = toPos;
}

MoveTo::~MoveTo() {}

void MoveTo::setNode(Node *node) {
    auto &nodePos = node->getPosition();
    deltaPos = toPos - nodePos;
    ActionInterval::setNode(node);
}

//**********************************************************************************

FadeIn *FadeIn::create(float time) {
    auto fi = new (std::nothrow) FadeIn{time};
    if (fi) {
        fi->autorelease();
        return fi;
    }
    return nullptr;
}

FadeIn::~FadeIn() {}

FadeIn::FadeIn(float time) : ActionInterval(time) {}

void FadeIn::update(float time) { node->setOpacity(startOp + deltaOp * time); }

void FadeIn::setNode(Node *node) {
    startOp = node->getOpacity();
    deltaOp = 1.0f - startOp;
    ActionInterval::setNode(node);
}

//**********************************************************************************

FadeOut *FadeOut::create(float time) {
    auto fi = new (std::nothrow) FadeOut{time};
    if (fi) {
        fi->autorelease();
        return fi;
    }
    return nullptr;
}

FadeOut::~FadeOut() {}

FadeOut::FadeOut(float time) : ActionInterval(time) {}

void FadeOut::update(float time) { node->setOpacity(startOp - deltaOp * time); }

void FadeOut::setNode(Node *node) {
    startOp = node->getOpacity();
    deltaOp = startOp;
    ActionInterval::setNode(node);
}

//**********************************************************************************

FadeTo *FadeTo::create(float time, float opacity) {
    auto f = new (std::nothrow) FadeTo{time, opacity};
    if (f) {
        f->autorelease();
        return f;
    }
    return nullptr;
}

FadeTo::FadeTo(float time, float opacity) : ActionInterval(time) {
    endOp = opacity;
}

FadeTo::~FadeTo() {}

void FadeTo::update(float time) { node->setOpacity(startOp + deltaOp * time); }

void FadeTo::setNode(Node *node) {
    startOp = node->getOpacity();
    deltaOp = endOp - startOp;
    ActionInterval::setNode(node);
}

//**********************************************************************************

RotateBy *RotateBy::create(float time, float rotation) {
    auto r = new (std::nothrow) RotateBy{time, rotation};
    if (r) {
        r->autorelease();
        return r;
    }
    return nullptr;
}

RotateBy::RotateBy(float time, float rotation) : ActionInterval(time) {
    deltaRotation = rotation;
}

RotateBy::~RotateBy() {}

void RotateBy::update(float time) {
    node->setRotation(startRotation + deltaRotation * time);
}

void RotateBy::setNode(Node *node) {
    startRotation = node->getRotation();
    ActionInterval::setNode(node);
}

//**********************************************************************************

ScaleTo *ScaleTo::create(float time, float scale) {
    auto s = new (std::nothrow) ScaleTo{time, scale};
    if (s) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

ScaleTo::ScaleTo(float time, float scale) : ActionInterval(time) {
    endScale = scale;
}

ScaleTo::~ScaleTo() {}

void ScaleTo::update(float time) {
    float s = startScale.x + deltaScale * time;
    node->setScale(s, s);
}

void ScaleTo::setNode(Node *node) {
    startScale = node->getScale();
    deltaScale = endScale - startScale.x;
    ActionInterval::setNode(node);
}