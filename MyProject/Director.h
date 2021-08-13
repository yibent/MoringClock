#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <QPainter>
#include <QSize>
#include <QWidget>
//#include <QtMultimedia/QSound>

QT_BEGIN_NAMESPACE
namespace Ui {
class Director;
}
QT_END_NAMESPACE

#include <map>
#include <mutex>
#include <string>
#include <thread>

#define RES_FILE(file) ":/Resources/" file

class Node;
class Scene;
class QMouseEvent;
class QPaintEvent;
class QTimerEvent;

#include "Engine/Vec2.h"

class Director : public QWidget {
    Q_OBJECT
public:
    static Director *instance;

public:
    Director(QWidget *parent = nullptr);
    ~Director();

    void runWithScene(Scene *scene);
    Scene *getScene();
    Vec2 getVisibleSize();
    void setWindowSize(int w, int h);
    //屏幕坐标转数学坐标
    Vec2 convertPosition(const Vec2 &pos);
public slots:
    void timerUpdate();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void paintEvent(QPaintEvent *) override;
    virtual void timerEvent(QTimerEvent *) override;

private:
    Ui::Director *ui = nullptr;
    QTimer *timer = nullptr;

private:
    Scene *scene = nullptr;
    Scene *lastScene = nullptr;
};

#endif  // DIRECTOR_H
