#include "MyLight.h"

#include "GlobalDef.h"
#include "rgb2hsv.h"

#if ON_RASPBERRY_PI

#include <signal.h>

#include <cstdlib>

extern const int LAMP_TARGET_FREQ;
extern const int LAMP_GPIO_PIN;
extern const int LAMP_DMA;

extern const int LAMP_WIDTH;
extern const int LAMP_HEIGHT;
extern const int LAMP_LED_COUNT;

ws2811_t ledstring;
ws2811_led_t *matrix = nullptr;

static bool finishInit = false;

static void ctrl_c_handler(int signum) { (void)(signum); }

bool Lamp::initLight() {
    //已经初始化,释放原来的,进行现在的初始
    if (finishInit) releaseLight();

    ledstring.freq = LAMP_TARGET_FREQ;
    ledstring.dmanum = LAMP_DMA;

    ledstring.channel[0].gpionum = LAMP_GPIO_PIN;
    ledstring.channel[0].count = LAMP_LED_COUNT;
    ledstring.channel[0].invert = 0;
    ledstring.channel[0].brightness = 255;
    ledstring.channel[0].strip_type = STRIP_TYPE;

    ledstring.channel[1].gpionum = 0;
    ledstring.channel[1].count = 0;
    ledstring.channel[1].invert = 0;
    ledstring.channel[1].brightness = 0;

    auto result = ws2811_init(&ledstring);
    if (result != WS2811_SUCCESS) {
        return false;
    }

    matrix =
        (ws2811_led_t *)malloc(sizeof(ws2811_led_t) * LAMP_WIDTH * LAMP_HEIGHT);

    struct sigaction sa = {ctrl_c_handler};

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    finishInit = true;
    return true;
}

void Lamp::setColor(int color) {
    if (!finishInit) return;
    for (int y = 0; y < LAMP_HEIGHT; ++y) {
        for (int x = 0; x < LAMP_WIDTH; ++x) {
            matrix[y * LAMP_WIDTH + x] = color;
        }
    }
}

void Lamp::setColor(const RGB &rgb) { setColor(rgb2_16bit(rgb)); }

void Lamp::setColor(const HSV &hsv) { setColor(hsv2rgb(hsv)); }

void drawColor() {
    if (!finishInit) return;
    for (int x = 0; x < LAMP_WIDTH; x++) {
        for (int y = 0; y < LAMP_HEIGHT; y++) {
            ledstring.channel[0].leds[(y * LAMP_WIDTH) + x] =
                matrix[y * LAMP_WIDTH + x];
        }
    }
    ws2811_render(&ledstring);
}

void Lamp::releaseLight() {
    setColor(0x00000000);
    drawColor();

    ws2811_fini(&ledstring);
    free(matrix);
    matrix = nullptr;
    finishInit = false;
}

#else

bool Lamp::initLight() { return true; }

void Lamp::setColor(int color) {}

void Lamp::setColor(const RGB &rgb) {}

void Lamp::setColor(const HSV &hsv) {}

void drawColor() {}

void Lamp::releaseLight() {}

#endif
