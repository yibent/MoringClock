#ifndef __WS2811_H__
#define __WS2811_H__

#include "GlobalDef.h"

#if ON_RASPBERRY_PI

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "rpihw.h"
#include "pwm.h"


#define WS2811_TARGET_FREQ                       800000   // Can go as low as 400000

// 4 color R, G, B and W ordering
#define SK6812_STRIP_RGBW                        0x18100800
#define SK6812_STRIP_RBGW                        0x18100008
#define SK6812_STRIP_GRBW                        0x18081000
#define SK6812_STRIP_GBRW                        0x18080010
#define SK6812_STRIP_BRGW                        0x18001008
#define SK6812_STRIP_BGRW                        0x18000810
#define SK6812_SHIFT_WMASK                       0xf0000000

// 3 color R, G and B ordering
#define WS2811_STRIP_RGB                         0x00100800
#define WS2811_STRIP_RBG                         0x00100008
#define WS2811_STRIP_GRB                         0x00081000
#define WS2811_STRIP_GBR                         0x00080010
#define WS2811_STRIP_BRG                         0x00001008
#define WS2811_STRIP_BGR                         0x00000810

// predefined fixed LED types
#define WS2812_STRIP                             WS2811_STRIP_GRB
#define SK6812_STRIP                             WS2811_STRIP_GRB
#define SK6812W_STRIP                            SK6812_STRIP_GRBW

struct ws2811_device;

typedef uint32_t ws2811_led_t;                   //< 0xWWRRGGBB
typedef struct ws2811_channel_t
{
    int gpionum;                                 //< GPIO Pin with PWM alternate function, 0 if unused
    int invert;                                  //< Invert output signal
    int count;                                   //< Number of LEDs, 0 if channel is unused
    int strip_type;                              //< Strip color layout -- one of WS2811_STRIP_xxx constants
    ws2811_led_t *leds;                          //< LED buffers, allocated by driver based on count
    uint8_t brightness;                          //< Brightness value between 0 and 255
    uint8_t wshift;                              //< White shift value
    uint8_t rshift;                              //< Red shift value
    uint8_t gshift;                              //< Green shift value
    uint8_t bshift;                              //< Blue shift value
    uint8_t *gamma;                              //< Gamma correction table
} ws2811_channel_t;

typedef struct ws2811_t
{
    uint64_t render_wait_time;                   //< time in µs before the next render can run
    struct ws2811_device *device;                //< Private data for driver use
    const rpi_hw_t *rpi_hw;                      //< RPI Hardware Information
    uint32_t freq;                               //< Required output frequency
    int dmanum;                                  //< DMA number _not_ already in use
    ws2811_channel_t channel[RPI_PWM_CHANNELS];
} ws2811_t;

#define WS2811_RETURN_STATES(X)                                                             \
            X(0, WS2811_SUCCESS, "Success"),                                                \
            X(-1, WS2811_ERROR_GENERIC, "Generic failure"),                                 \
            X(-2, WS2811_ERROR_OUT_OF_MEMORY, "Out of memory"),                             \
            X(-3, WS2811_ERROR_HW_NOT_SUPPORTED, "Hardware revision is not supported"),     \
            X(-4, WS2811_ERROR_MEM_LOCK, "Memory lock failed"),                             \
            X(-5, WS2811_ERROR_MMAP, "mmap() failed"),                                      \
            X(-6, WS2811_ERROR_MAP_REGISTERS, "Unable to map registers into userspace"),    \
            X(-7, WS2811_ERROR_GPIO_INIT, "Unable to initialize GPIO"),                     \
            X(-8, WS2811_ERROR_PWM_SETUP, "Unable to initialize PWM"),                      \
            X(-9, WS2811_ERROR_MAILBOX_DEVICE, "Failed to create mailbox device"),          \
            X(-10, WS2811_ERROR_DMA, "DMA error"),                                          \
            X(-11, WS2811_ERROR_ILLEGAL_GPIO, "Selected GPIO not possible"),                \
            X(-12, WS2811_ERROR_PCM_SETUP, "Unable to initialize PCM"),                     \
            X(-13, WS2811_ERROR_SPI_SETUP, "Unable to initialize SPI"),                     \
            X(-14, WS2811_ERROR_SPI_TRANSFER, "SPI transfer error")                         \

#define WS2811_RETURN_STATES_ENUM(state, name, str) name = state
#define WS2811_RETURN_STATES_STRING(state, name, str) str

typedef enum {
    WS2811_RETURN_STATES(WS2811_RETURN_STATES_ENUM),

    WS2811_RETURN_STATE_COUNT
} ws2811_return_t;

ws2811_return_t ws2811_init(ws2811_t *ws2811);                                  //< Initialize buffers/hardware
void ws2811_fini(ws2811_t *ws2811);                                             //< Tear it all down
ws2811_return_t ws2811_render(ws2811_t *ws2811);                                //< Send LEDs off to hardware
ws2811_return_t ws2811_wait(ws2811_t *ws2811);                                  //< Wait for DMA completion
const char * ws2811_get_return_t_str(const ws2811_return_t state);              //< Get string representation of the given return state
void ws2811_set_custom_gamma_factor(ws2811_t *ws2811, double gamma_factor);     //< Set a custom Gamma correction array based on a gamma correction factor

#ifdef __cplusplus
}
#endif

#endif

#endif /* __WS2811_H__ */
