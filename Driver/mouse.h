/**
 * @file mouse.h
 *
 */

#ifndef MOUSE_H
#define MOUSE_H

/*********************
 *      INCLUDES
 *********************/
#include "monitor.h"


#define USE_MOUSE 1
#if USE_MOUSE

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the mouse
 */
void mouse_init(void);
__s16 mouse_get_touch_x(void);
__s16 mouse_get_touch_y(void);
U8 mouse_read(int *TouchX, int *TouchY, unsigned char *pState, unsigned char TouchId);
/**
 * Get the current position and state of the mouse
 * @param data store the mouse data here
 * @return false: because the points are not buffered, so no more data to be read
 */

/**********************
 *      MACROS
 **********************/

#endif

#endif
