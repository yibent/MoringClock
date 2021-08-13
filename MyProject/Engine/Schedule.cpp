#include "Schedule.h"

#include <vector>

#include "Default.h"
using namespace std;

void Schedule::updateSche() {
    vector<string> needToErase;
    for (auto it = schedulePool.begin(); it != schedulePool.end(); ++it) {
        auto &ob = it->second;
        ob.realTime += Def::updateDelay;
        if (ob.realTime >= ob.interval) {
            ob.realTime -= ob.interval;
            ob.func();
            if (ob.times != -1) ob.times -= 1;
            if (ob.times == 0) needToErase.push_back(it->first);
        }
    }

    for (auto it = needToErase.begin(); it != needToErase.end(); ++it) {
        schedulePool.erase(*it);
    }
}

void Schedule::schedule(float interval, int times, const function<void()> &func,
                        const std::string &key) {
    if (times == 0) {
        return;
    }
    FuncPack pack;
    pack.func = func;
    pack.interval = interval;
    pack.times = times;
    pack.realTime = pack.interval;
    schedulePool.insert({key, pack});
}

void Schedule::schedule(float interval, const function<void()> &func,
                        const string &key) {
    this->schedule(interval, -1, func, key);
}

void Schedule::scheduleOnce(float delay, const function<void()> &func,
                            const string &key) {
    FuncPack pack;
    pack.func = func;
    pack.interval = delay;
    pack.realTime = 0;
    pack.times = 1;
    schedulePool.insert({key, pack});
}

void Schedule::unschedule(const string &key) {
    auto it = schedulePool.find(key);
    if (it != schedulePool.end()) schedulePool.erase(it);
}
