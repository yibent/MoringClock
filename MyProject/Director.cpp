#include "Director.h"

#include <chrono>

#include "Engine/Default.h"
#include "Engine/Ref.h"
#include "Engine/Scene.h"
#include "ui_Director.h"
using namespace std;
using namespace std::chrono;

#include <QFont>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QTImer>
#include <QTimerEvent>

Director *Director::instance = nullptr;

Director::Director(QWidget *parent) : QWidget(parent), ui(new Ui::Director) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint |
                         Qt::WindowCloseButtonHint);
    // this->showFullScreen();
    // this->startTimer(Def::updateDelay * 1000, Qt::TimerType::PreciseTimer);

    timer = new QTimer();
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    timer->setInterval(Def::updateDelay * 1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start();

    // initLight();
}

Director::~Director() { delete ui; }

void Director::runWithScene(Scene *scene) {
    lastScene = this->scene;
    this->scene = scene;
    scene->retain();
}

Scene *Director::getScene() { return scene; }

Vec2 Director::getVisibleSize() {
    auto s = size();
    return Vec2(s.width(), s.height());
}

void Director::setWindowSize(int w, int h) {
    setFixedSize(w, h);
    resize(w, h);
}

Vec2 Director::convertPosition(const Vec2 &pos) {
    return Vec2(pos.x, size().height() - pos.y);
}

void Director::timerUpdate() {
    constexpr int duration = Def::updateDelay * 1000;
    auto t0 = steady_clock::now();
    instance->repaint();
    auto t1 = steady_clock::now();
    auto d = duration_cast<milliseconds>(t1 - t0);
    int c = duration - d.count();
    if (c < 0) {
        c = 0;
    }
    timer->setInterval(c);
}

void Director::mousePressEvent(QMouseEvent *event) {
    if (scene) scene->touchDown(Vec2(event->x(), event->y()));
}

void Director::mouseReleaseEvent(QMouseEvent *event) {
    if (scene) scene->touchUp(Vec2(event->x(), event->y()));
}

void Director::mouseMoveEvent(QMouseEvent *event) {
    if (scene) scene->touchMove(Vec2(event->x(), event->y()));
}

void Director::paintEvent(QPaintEvent *) {
    if (!scene) {
        return;
    }
    scene->update();
    /*
    if(isLeftDown())
    {
        setColor(0x00FFC80F);
    }
    else
    {
        setColor(0x00000000);
    }
    drawColor();
    */
    if (lastScene) {
        lastScene->release();
        lastScene = nullptr;
    }
    //****************************************************
    QPixmap pixmap{size()};
    QPainter painter{&pixmap};

    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    scene->draw(painter);

    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, pixmap);
}

void Director::timerEvent(QTimerEvent *) { /*this->repaint();*/
}
