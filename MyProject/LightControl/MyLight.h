#ifndef __MY_LIGHT_H__
#define __MY_LIGHT_H__

#include "GlobalDef.h"
#include "rgb2hsv.h"
#include "ws2811.h"

#if ON_RASPBERRY_PI

extern const int LAMP_TARGET_FREQ = WS2811_TARGET_FREQ;
#define STRIP_TYPE WS2811_STRIP_RGB

#endif

extern const int LAMP_GPIO_PIN = 18;
extern const int LAMP_DMA = 10;

extern const int LAMP_WIDTH = 8;
extern const int LAMP_HEIGHT = 8;
extern const int LAMP_LED_COUNT = LAMP_WIDTH * LAMP_HEIGHT;

namespace Lamp {
//初始化灯,返回是否初始化成功
bool initLight();

//设置颜色
void setColor(int color);
void setColor(const RGB &rgb);
void setColor(const HSV &hsv);

//只有调用此函数,设置的颜色才会生效
void drawColor();

//释放灯
void releaseLight();

};  // namespace Lamp

#endif
