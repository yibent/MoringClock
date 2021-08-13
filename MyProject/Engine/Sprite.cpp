#include "Sprite.h"

#include <QSize>

#include "Director.h"
#include "ImagePool.h"

using namespace std;

Sprite *Sprite::create(const string &fileName) {
    auto sp = new (std::nothrow) Sprite{fileName};
    if (sp) {
        sp->autorelease();
        return sp;
    }
    return nullptr;
}

Sprite::Sprite(const string &fileName) {
    this->image = ImagePool::instance->loadImage(fileName);
}

Sprite::~Sprite() {}

void Sprite::draw(QPainter &painter, const Vec2 &vecDelta) {
    if (!isVisible()) {
        return;
    }
    auto size = this->getContentSize();
    auto pos = this->getPosition();
    pos = Director::instance->convertPosition(pos + vecDelta);
    auto scale = this->getScale();
    //监测scale
    if (scale.x <= 0) scale.x = 0.000001;  //不能为0
    if (scale.y <= 0) scale.y = 0.000001;  //不能为0
    float x = -size.x / 2;
    float y = -size.y / 2;

    //渲染前准备
    painter.setOpacity(this->getOpacity());
    painter.translate(pos.x, pos.y);
    painter.scale(scale.x, scale.y);
    painter.rotate(this->getRotation());

    //*****
    painter.drawImage(x, y, *image);
    //*****

    //渲染后复原
    painter.rotate(-this->getRotation());
    painter.scale(1 / scale.x, 1 / scale.y);
    painter.translate(-pos.x, -pos.y);
    painter.setOpacity(1);
}

Vec2 Sprite::getContentSize() {
    auto s = image->size();
    return Vec2(s.width(), s.height());
}
