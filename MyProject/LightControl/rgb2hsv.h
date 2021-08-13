#ifndef __RGB2HSV_H__
#define __RGB2HSV_H__

typedef struct _RGB {
    int r;
    int g;
    int b;
} RGB;

typedef struct _HSV {
    int h;
    float s;
    float v;
} HSV;

HSV rgb2hsv(const RGB& rgb);
RGB hsv2rgb(const HSV& hsv);
int rgb2_16bit(const RGB& rgb);

#endif
