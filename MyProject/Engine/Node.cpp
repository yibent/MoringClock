#include "Node.h"

#include "Action.h"
#include "Default.h"
using namespace std;

Node *Node::create() {
    auto n = new (std::nothrow) Node{};
    if (n) {
        n->autorelease();
        return n;
    }
    return nullptr;
}

void Node::update() {
    this->updateSche();

    //更新Action
    vector<Action *> actionNeedToErase;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        auto &act = (*it);
        if (!act->isRunFinish()) {
            act->step(Def::updateDelay);
        } else {
            actionNeedToErase.push_back(act);
        }
    }

    //移除执行结束的action
    for (auto it = actionNeedToErase.begin(); it != actionNeedToErase.end();
         ++it) {
        auto &act = *it;
        actions.erase(remove(actions.begin(), actions.end(), act),
                      actions.end());
        act->release();
    }

    //更新节点
    for (auto it = children.begin(); it != children.end(); ++it) {
        auto &node = *it;
        node->update();
    }

    //移除节点
    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        auto &node = *it;
        children.erase(remove(children.begin(), children.end(), node),
                       children.end());
        node->release();
    }
    needToErase.clear();
}

Node::Node() {}

Node::~Node() {}

void Node::release() {
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        (*it)->release();
    }
    for (auto it = children.begin(); it != children.end(); ++it) {
        auto &node = *it;
        node->release();
    }
    Ref::release();
}

void Node::draw(QPainter &painter, const Vec2 &vecDelta) {
    if (!visible) {
        return;
    }

    //升序排序<由下向上绘制
    auto comp = [&](const Node *ob1, const Node *ob2) -> bool {
        return ob1->getZOrder() < ob2->getZOrder();
    };

    /*使用稳定的排序,保证ZOrder相等的元素的渲染顺序不改变
     */
    stable_sort(children.begin(), children.end(), comp);

    for (auto it = children.begin(); it != children.end(); ++it) {
        auto &node = *it;
        node->draw(painter, vecDelta + position);
    }
}

float Node::getRotation() const { return rotation; }

void Node::setRotation(float rotation) { this->rotation = rotation; }

const Vec2 &Node::getPosition() const { return position; }

void Node::setPosition(const Vec2 &position) { this->position = position; }

void Node::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

float Node::getOpacity() { return this->opacity; }

void Node::setOpacity(float opacity) { this->opacity = opacity; }

int Node::getZOrder() const { return zOrder; }

void Node::setZOrder(int zOrder) { this->zOrder = zOrder; }

const Vec2 &Node::getScale() { return scale; }

void Node::setScale(float x, float y) {
    scale.x = x;
    scale.y = y;
}

void Node::setScale(const Vec2 &scale) { this->scale = scale; }

void Node::runAction(Action *action) {
    action->setNode(this);
    actions.push_back(action);
    action->retain();
}

void Node::stopAllActions() {
    for (auto &act : actions) {
        act->release();
    }
    actions.clear();
}

void Node::setVisible(bool v) { visible = v; }

bool Node::isVisible() { return visible; }

int Node::getTag() { return tag; }

void Node::setTag(int tag) { this->tag = tag; }

const vector<Node *> &Node::getChildren() { return children; }

void Node::setParent(Node *node) { parent = node; }

void Node::removeFromParent() { parent->removeChild(this); }

Vec2 Node::convertPosToParent() {
    if (parent == nullptr) {
        return position;
    }
    return position + parent->convertPosToParent();
}

void Node::addChild(Node *node) {
    node->retain();
    node->setParent(this);
    children.push_back(node);
}

void Node::addChild(Node *node, int ZOrder) {
    node->setZOrder(ZOrder);
    this->addChild(node);
}

void Node::removeChild(Node *node) { needToErase.push_back(node); }
