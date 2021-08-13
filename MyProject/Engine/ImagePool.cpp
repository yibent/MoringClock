#include "ImagePool.h"

#include <QImage>
using namespace std;

ImagePool *ImagePool::instance = new ImagePool{};

QImage *ImagePool::loadImage(const std::string &fileName) {
    auto iter = pool.find(fileName);
    if (iter != pool.end()) return iter->second;
    QImage *image = new QImage{fileName.c_str()};
    pool.insert({fileName, image});
    return image;
}

void ImagePool::removeImage(const string &fileName) { pool.erase(fileName); }

QImage *ImagePool::getImage(const string &fileName) {
    auto iter = pool.find(fileName);
    if (iter != pool.end()) return iter->second;
    return nullptr;
}
