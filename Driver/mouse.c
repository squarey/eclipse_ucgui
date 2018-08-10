/**
 * @file mouse.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "mouse.h"



#if USE_MOUSE != 0

#include <SDL2/SDL.h>
#include "GUIType.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static U8 left_button_down = 0;
static __s16 last_x = 0;
static __s16 last_y = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the mouse
 */
void mouse_init(void)
{

}

/**
 * Get the current position and state of the mouse
 * @param data store the mouse data here
 * @return false: because the points are not buffered, so no more data to be read
 */
/*
bool mouse_read(LV_InputDeviceData_t * data)
{
    data->Data.Point.x = last_x;
    data->Data.Point.y = last_y;
    data->State = left_button_down ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    return false;
}
*/
/**
 * It will be called from the main SDL thread
 */
void mouse_handler(SDL_Event *event)
{
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT)
                left_button_down = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                left_button_down = 1;
                last_x = event->motion.x;
                last_y = event->motion.y;
            }
            break;
        case SDL_MOUSEMOTION:
            last_x = event->motion.x;
            last_y = event->motion.y;

            break;
    }

}
U8 mouse_read(int *TouchX, int *TouchY, unsigned char *pState, unsigned char TouchId)
{
    /*Store the collected data*/
	*TouchX = last_x;
	*TouchY = last_y;
	*pState = left_button_down;
    return 1;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif
