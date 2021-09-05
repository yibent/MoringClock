#ifndef __REF_H__
#define __REF_H__

#include <vector>

class Ref;

class AutoReleasePool {
public:
    static AutoReleasePool *instance;
    void updatePool();

private:
    void addToPool(Ref *ref);
    friend class Ref;

    std::vector<Ref *> pool;
};

using ARP = AutoReleasePool;

class Ref {
public:
    Ref() {}
    virtual ~Ref() {}

    virtual void retain() { ++count; }
    virtual void release()
    {
        --count;
        if (count == 0) delete this;
    }
    int getCount() { return count; }
    void autorelease()
    {
        ARP::instance->addToPool(this);
        ++count;
    }

private:
    int count = 0;
};

#endif