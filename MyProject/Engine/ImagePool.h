#ifndef __IMAGE_POOL_H__
#define __IMAGE_POOL_H__

class QImage;
#include <map>
#include <string>

class ImagePool
{
public:
    static ImagePool *instance;

public:
    QImage *loadImage(const std::string &fileName);
    void removeImage(const std::string &fileName);
    QImage *getImage(const std::string &fileName);

private:
    std::map<std::string, QImage *> pool;
};

#endif
