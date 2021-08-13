#include "UI.h"

#include "Director.h"
#include "ImagePool.h"
#include "Vec2.h"

using namespace std;

#include <QImage>

static bool inRect(const Rect &rect, const Vec2 &pos) {
    return (pos.x >= rect.leftBottom.x && pos.y >= rect.leftBottom.y &&
            pos.x <= rect.rightTop.x && pos.y <= rect.rightTop.y);
};

//*********************************************************************************

void basic_Button::setEnable(bool en) { enable = en; }

bool basic_Button::isEnable() { return enable; }

int basic_Button::getStatus() { return status; }

void basic_Button::setCallBack(const function<void(basic_Button *)> &func) {
    this->func = func;
}

//*********************************************************************************

const int Button::NORMAL{0};
const int Button::PUSH_DOWN{1};
const int Button::DISABLE{2};

Button *Button::create(const string &normal, const string &pushDown,
                       const string &disable) {
    auto b = new (std::nothrow) Button{normal, pushDown, disable};
    if (b) {
        b->autorelease();
        return b;
    }
    return nullptr;
}

Button::Button(const string &normal, const string &pushDown,
               const string &disable) {
    auto imgPool = ImagePool::instance;
    images[NORMAL] = imgPool->loadImage(normal);
    images[PUSH_DOWN] = imgPool->loadImage(pushDown);
    images[DISABLE] = imgPool->loadImage(disable);
    this->status = NORMAL;
}

Button::~Button() {}

void Button::draw(QPainter &painter, const Vec2 &vecDelta) {
    if (!isVisible()) return;
    auto size = images[NORMAL]->size();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(pos + vecDelta);
    auto scale = this->getScale();
    //监测scale
    if (scale.x <= 0) scale.x = 0.000001;  //不能为0
    if (scale.y <= 0) scale.y = 0.000001;  //不能为0
    float x = -size.width() / 2;
    float y = -size.height() / 2;

    //渲染前准备
    painter.setOpacity(this->getOpacity());
    painter.translate(pos.x, pos.y);
    painter.scale(scale.x, scale.y);
    painter.rotate(this->getRotation());

    QImage *drawImage = nullptr;
    if (!enable)
        drawImage = images[DISABLE];
    else if (status == NORMAL)
        drawImage = images[NORMAL];
    else
        drawImage = images[PUSH_DOWN];

    //*****
    painter.drawImage(x, y, *drawImage);
    //*****

    //渲染后复原
    painter.rotate(-this->getRotation());
    painter.scale(1 / scale.x, 1 / scale.y);
    painter.translate(-pos.x, -pos.y);
    painter.setOpacity(1);
}

void Button::setEnable(bool en) {
    if (en && !enable) status = NORMAL;
    basic_Button::setEnable(en);
}

void Button::touchDown(const Vec2 &pos) {
    auto rect = getButtonRect();
    if (inRect(rect, pos) && enable) status = PUSH_DOWN;
}

void Button::touchUp(const Vec2 &pos) {
    if (enable && status == PUSH_DOWN) {
        auto rect = getButtonRect();
        if (inRect(rect, pos)) func(this);
        status = NORMAL;
    }
}

void Button::touchMove(const Vec2 &pos) {
    auto rect = getButtonRect();
    if (inRect(rect, pos) && enable)
        status = PUSH_DOWN;
    else
        status = NORMAL;
}

Rect Button::getButtonRect() {
    Rect rect;
    auto pos = this->convertPosToParent();
    auto size = images[NORMAL]->size();
    auto p1 = Vec2(size.width(), size.height());
    rect.leftBottom = Vec2(pos - p1 / 2);
    rect.rightTop = Vec2(pos + p1 / 2);
    return rect;
}

Vec2 Button::getContentSize() {
    auto s = images[NORMAL]->size();
    return Vec2(s.width(), s.height());
}

//*********************************************************************************

const int ToggleButton::NORMAL_0{0};
const int ToggleButton::PUSH_DOWN_0{1};
const int ToggleButton::NORMAL_1{2};
const int ToggleButton::PUSH_DOWN_1{3};
const int ToggleButton::DISABLE_0{4};
const int ToggleButton::DISABLE_1{5};

ToggleButton *ToggleButton::create(const std::string &normal_0,
                                   const std::string &pushDown_0,
                                   const std::string &normal_1,
                                   const std::string &pushDown_1,
                                   const std::string &disable_0,
                                   const std::string &disable_1) {
    auto tb = new (std::nothrow) ToggleButton{
        normal_0, pushDown_0, normal_1, pushDown_1, disable_0, disable_1};
    if (tb) {
        tb->autorelease();
        return tb;
    }
    return nullptr;
}

ToggleButton::ToggleButton(const std::string &normal_0,
                           const std::string &pushDown_0,
                           const std::string &normal_1,
                           const std::string &pushDown_1,
                           const std::string &disable_0,
                           const std::string &disable_1) {
    auto imgPool = ImagePool::instance;
    images[NORMAL_0] = imgPool->loadImage(normal_0);
    images[PUSH_DOWN_0] = imgPool->loadImage(pushDown_0);
    images[NORMAL_1] = imgPool->loadImage(normal_1);
    images[PUSH_DOWN_1] = imgPool->loadImage(pushDown_1);
    images[DISABLE_0] = imgPool->loadImage(disable_0);
    images[DISABLE_1] = imgPool->loadImage(disable_1);
    this->status = NORMAL_0;
}

ToggleButton::~ToggleButton() {}

void ToggleButton::draw(QPainter &painter, const Vec2 &vecDelta) {
    if (!isVisible()) {
        return;
    }
    auto size = images[NORMAL_0]->size();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(pos + vecDelta);
    auto scale = this->getScale();
    //监测scale
    if (scale.x <= 0) scale.x = 0.000001;  //不能为0
    if (scale.y <= 0) scale.y = 0.000001;  //不能为0
    float x = -size.width() / 2;
    float y = -size.height() / 2;

    //渲染前准备
    painter.setOpacity(this->getOpacity());
    painter.translate(pos.x, pos.y);
    painter.scale(scale.x, scale.y);
    painter.rotate(this->getRotation());

    QImage *drawImage = nullptr;
    if (!enable) {
        if (status == NORMAL_0 || status == PUSH_DOWN_0)
            drawImage = images[DISABLE_0];
        else if (status == NORMAL_1 || status == PUSH_DOWN_1)
            drawImage = images[DISABLE_1];
    } else {
        switch (status) {
            case NORMAL_0:
                drawImage = images[NORMAL_0];
                break;
            case NORMAL_1:
                drawImage = images[NORMAL_1];
                break;
            case PUSH_DOWN_0:
                drawImage = images[PUSH_DOWN_0];
                break;
            case PUSH_DOWN_1:
                drawImage = images[PUSH_DOWN_1];
                break;
        }
    }

    //*****
    painter.drawImage(x, y, *drawImage);
    //*****

    //渲染后复原
    painter.rotate(-this->getRotation());
    painter.scale(1 / scale.x, 1 / scale.y);
    painter.translate(-pos.x, -pos.y);
    painter.setOpacity(1);
}

void ToggleButton::touchDown(const Vec2 &pos) {
    auto rect = getButtonRect();
    if (inRect(rect, pos) && enable) {
        if (status == NORMAL_0) status = PUSH_DOWN_0;
        if (status == NORMAL_1) status = PUSH_DOWN_1;
    }
}

void ToggleButton::touchUp(const Vec2 &pos) {
    if (enable && (status == PUSH_DOWN_0 || status == PUSH_DOWN_1)) {
        auto rect = getButtonRect();
        bool isInRect = inRect(rect, pos);
        if (status == PUSH_DOWN_0) {
            status = NORMAL_1;
            if (isInRect) toggle_func(this, 1);
        }
        if (status == PUSH_DOWN_1) {
            status = NORMAL_0;
            if (isInRect) toggle_func(this, 0);
        }
    }
}

void ToggleButton::touchMove(const Vec2 &pos) {
    auto rect = getButtonRect();
    if (inRect(rect, pos) && enable) {
        if (status == NORMAL_0) status = PUSH_DOWN_0;
        if (status == NORMAL_1) status = PUSH_DOWN_1;
    } else {
        if (status == PUSH_DOWN_0) status = NORMAL_0;
        if (status == PUSH_DOWN_1) status = NORMAL_1;
    }
}

Rect ToggleButton::getButtonRect() {
    Rect rect;
    auto pos = this->convertPosToParent();
    auto size = images[NORMAL_0]->size();
    auto p1 = Vec2(size.width(), size.height());
    rect.leftBottom = Vec2(pos - p1 / 2);
    rect.rightTop = Vec2(pos + p1 / 2);
    return rect;
}

Vec2 ToggleButton::getContentSize() {
    auto s = images[NORMAL_0]->size();
    return Vec2(s.width(), s.height());
}

void ToggleButton::setEnable(bool en) {
    if (en && !enable) {
        if (status == PUSH_DOWN_0) status = NORMAL_0;
        if (status == PUSH_DOWN_1) status = NORMAL_1;
    }
    basic_Button::setEnable(en);
}

void ToggleButton::setCallBack(
    const function<void(ToggleButton *, int)> &callBack) {
    toggle_func = callBack;
}

//*********************************************************************************

Menu *Menu::create() {
    auto m = new (std::nothrow) Menu();
    if (m) {
        m->autorelease();
        return m;
    }
    return nullptr;
}

Menu::Menu() {
    eventRec = EventReceiver::create();
    EventDispatcher::instance->regist(eventRec, 1);

    eventRec->touchDown = [&](const Vec2 &pos) -> bool {
        for (auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->touchDown(pos);
        return true;
    };

    eventRec->touchMove = [&](const Vec2 &pos) -> bool {
        for (auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->touchMove(pos);
        return true;
    };

    eventRec->touchUp = [&](const Vec2 &pos) -> bool {
        for (auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->touchUp(pos);
        return true;
    };
}

Menu::~Menu() {}

void Menu::release() {
    EventDispatcher::instance->unregist(eventRec);
    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->release();
    }
    Node::release();
}

void Menu::draw(QPainter &painter, const Vec2 &vecDelta) {
    if (!isVisible()) {
        return;
    }

    //升序排序<由下向上绘制
    auto comp = [&](const Node *ob1, const Node *ob2) -> bool {
        return ob1->getZOrder() < ob2->getZOrder();
    };

    /*使用稳定的排序,保证ZOrder相等的元素的渲染顺序不改变
     */
    stable_sort(buttons.begin(), buttons.end(), comp);

    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->draw(painter, vecDelta);
    }
}

void Menu::update() {
    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        auto &node = *it;
        node->update();
    }
}

void Menu::addButton(basic_Button *button) {
    button->retain();
    button->setParent(this);
    buttons.push_back(button);
}

void Menu::removeButton(basic_Button *button) {
    buttons.erase(remove(buttons.begin(), buttons.end(), button),
                  buttons.end());
    button->release();
}
