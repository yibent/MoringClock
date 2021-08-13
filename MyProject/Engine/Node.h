#ifndef __NODE_H__
#define __NODE_H__

#include <QPainter>
#include <vector>

#include "Ref.h"
#include "Schedule.h"
#include "Vec2.h"
class Action;

// constexpr int MENU_TAG = 1000;

class Node : public Schedule, public Ref {
public:
    Node();
    virtual ~Node();
    virtual void release()override;
    virtual void update();

public:
    static Node *create();
    //绘制节点
    virtual void draw(QPainter &painter, const Vec2 &vecDelta);

    //旋转的相关操作(图片中心为原点)
    virtual float getRotation() const;
    virtual void setRotation(float rotation);

    //坐标相关操作
    virtual const Vec2 &getPosition() const;
    virtual void setPosition(const Vec2 &position);
    virtual void setPosition(float x, float y);

    //透明度相关操作
    virtual float getOpacity();
    virtual void setOpacity(float opacity);

    //渲染顺序相关操作
    int getZOrder() const;
    void setZOrder(int zOrder);

    //缩放相关操作
    const Vec2 &getScale();
    void setScale(float x, float y);
    void setScale(const Vec2 &scale);

    //执行动作
    void runAction(Action *action);
    void stopAllActions();

    //设置是否显示
    void setVisible(bool v);
    bool isVisible();

    int getTag();
    void setTag(int tag);

    const std::vector<Node *> &getChildren();
    //设置父节点
    virtual void setParent(Node *node);
    //从父节点移除此节点
    virtual void removeFromParent();
    //添加,删除子节点
    virtual void addChild(Node *node);
    virtual void addChild(Node *node, int ZOrder);
    virtual void removeChild(Node *node);

    //获得经过父节点转换后的坐标
    Vec2 convertPosToParent();
    //获得大小
    virtual Vec2 getContentSize() { return Vec2(1, 1); };

protected:
    // tag标识
    int tag = 0;
    //是否显示
    bool visible = true;
    //节点执行的动作
    std::vector<Action *> actions;
    //节点的子节点池
    std::vector<Node *> children;
    //需要从子节点持中删除的节点
    std::vector<Node *> needToErase;
    //节点坐标
    Vec2 position;
    //节点缩放
    Vec2 scale{1, 1};
    //节点的旋转角度
    float rotation = 0;
    //节点的透明度
    float opacity = 1;
    //节点的渲染顺序
    int zOrder = 0;
    //父节点指针
    Node *parent = nullptr;
};

#endif
