#ifndef __RPIHW_H__
#define __RPIHW_H__

#include "GlobalDef.h"

#if ON_RASPBERRY_PI

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    uint32_t type;
#define RPI_HWVER_TYPE_UNKNOWN                   0
#define RPI_HWVER_TYPE_PI1                       1
#define RPI_HWVER_TYPE_PI2                       2
#define RPI_HWVER_TYPE_PI4                       3
    uint32_t hwver;
    uint32_t periph_base;
    uint32_t videocore_base;
    char *desc;
} rpi_hw_t;


const rpi_hw_t *rpi_hw_detect(void);

#ifdef __cplusplus
}
#endif

#endif

#endif /* __RPIHW_H__ */
