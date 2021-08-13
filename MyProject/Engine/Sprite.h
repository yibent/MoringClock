#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>

#include "Node.h"

class Sprite : public Node {
public:
    static Sprite *create(const std::string &fileName);
    Sprite(const std::string &fileName);
    virtual ~Sprite();

public:
    virtual void draw(QPainter &painter, const Vec2 &vecDelta) override;
    virtual Vec2 getContentSize() override;

private:
    QImage *image = nullptr;
};

#endif
