#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include <functional>
#include <map>
#include <string>

class Schedule
{
public:
    //调度器更新
    void updateSche();

    //调度器相关操作,时间单位:秒
    void schedule(float interval, int times, const std::function<void(void)>& func, const std::string& key);
    void schedule(float interval, const std::function<void(void)>& func, const std::string& key);
    void scheduleOnce(float delay, const std::function<void(void)>& func, const std::string& key);

    void unschedule(const std::string& key);
private:
    struct FuncPack
    {
        std::function<void(void)> func;
        float interval = 0;
        int times = 0;
        //距离上一次更新已经经过的时间
        float realTime = 0;
    };

    std::map<std::string, FuncPack> schedulePool;
};




#endif
