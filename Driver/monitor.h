/**
 * @file monitor.h
 *
 */

#ifndef MONITOR_H
#define MONITOR_H

#include "GUI.h"
/*********************
 *      DEFINES
 *********************/
#ifndef __s8
#define __s8	signed char
#endif
#ifndef __u8
#define __u8	unsigned char
#endif
#ifndef __s16
#define __s16	short
#endif
#ifndef __u16
#define __u16	unsigned short
#endif
#ifndef __s32
#define __s32	int
#endif
#ifndef __u32
#define __u32	unsigned int
#endif
#ifndef __s64
#define __s64	long long
#endif
#ifndef __u64
#define __u64	unsigned long long
#endif
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void monitor_init(void);
void monitor_flush(__s32 x1, __s32 y1, __s32 x2, __s32 y2, __u32 color_p);
void monitor_fill(__s32 x1, __s32 y1, __s32 x2, __s32 y2, __u32 color);
void monitor_pixel(__s32 x, __s32 y, __u32 color);
__u32 monitor_get_pixel(__s32 x, __s32 y);
void sdl_request_refresh(void);
__u32 GetSystemTime(void);
/**********************
 *      MACROS
 **********************/

#endif

