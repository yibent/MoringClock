#ifndef __LAYER_H__
#define __LAYER_H__

#include "Node.h"

class Layer : public Node {
public:
    virtual bool init() {}
    virtual void release();
};

#endif