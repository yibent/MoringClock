#include "Scene.h"

#include <QDebug>

#include "Director.h"
#include "EventDispatcher.h"
#include "Node.h"
#include "Ref.h"
#include "UI.h"

using namespace std;

void Scene::update() {
    this->updateSche();

    for (auto it = children.begin(); it != children.end(); ++it) {
        auto &node = *it;
        node->update();
    }

    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        auto &node = *it;
        children.erase(remove(children.begin(), children.end(), node),
                       children.end());
        node->release();
    }
    needToErase.clear();

    //自动释放池更新
    ARP::instance->updatePool();
}

void Scene::draw(QPainter &painter) {
    //升序排序<由下向上绘制
    auto comp = [&](const Node *ob1, const Node *ob2) -> bool {
        return ob1->getZOrder() < ob2->getZOrder();
    };

    /*使用稳定的排序,保证ZOrder相等的元素的渲染顺序不改变
     */
    stable_sort(children.begin(), children.end(), comp);

    for (auto it = children.begin(); it != children.end(); ++it) {
        (*it)->draw(painter, Vec2(0, 0));
    }
}

void Scene::touchDown(const Vec2 &pos) {
    auto cpos = Director::instance->convertPosition(pos);
    touchPressed = true;
    EventDispatcher::instance->touchDown(cpos);

    qDebug() << "(" << cpos.x << ", " << cpos.y << ")";
}

void Scene::touchMove(const Vec2 &pos) {
    if (touchPressed) {
        auto cpos = Director::instance->convertPosition(pos);
        EventDispatcher::instance->touchMove(cpos);
    }
}

void Scene::touchUp(const Vec2 &pos) {
    auto cpos = Director::instance->convertPosition(pos);
    touchPressed = false;
    EventDispatcher::instance->touchUp(cpos);
}