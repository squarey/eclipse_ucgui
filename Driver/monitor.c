/**
 * @file monitor.c
 * 
 */

/*********************
 *      INCLUDES
 *********************/
#include <monitor.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define SDL_REFR_PERIOD	    20	/*ms*/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static int sdl_refr(void * param);

/***********************
 *   GLOBAL PROTOTYPES
 ***********************/
#define USE_MOUSE 1

#define MONITOR_HOR_RES  1024
#define MONITOR_VER_RES   600

#if USE_MOUSE
void mouse_handler(SDL_Event *event);
#endif

#if USE_KEYBOARD
void keyboard_handler(SDL_Event *event);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static SDL_Window * window;
static SDL_Renderer * renderer;
static SDL_Texture * texture;
static __u32 tft_fb[MONITOR_HOR_RES * MONITOR_VER_RES];
static __u32 tmp_fb[MONITOR_HOR_RES * MONITOR_VER_RES];
static volatile bool sdl_inited = false;
static volatile bool sdl_refr_qry = false;
static volatile bool sdl_quit_qry = false;

int quit_filter (void *userdata, SDL_Event * event);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the monitor
 */
void monitor_init(void)
{
	SDL_CreateThread(sdl_refr, "sdl_refr", NULL);

	while(sdl_inited == false); /*Wait until 'sdl_refr' initializes the SDL*/
}


/**
 * Flush a buffer to the display. Calls 'LV_FlushReady()' when finished
 * @param x1 left coordinate
 * @param y1 top coordinate
 * @param x2 right coordinate
 * @param y2 bottom coordinate
 * @param color_p array of colors to be flushed
 */
void monitor_flush(__s32 x1, __s32 y1, __s32 x2, __s32 y2, __u32 color_p)
{

}


/**
 * Fill out the marked rect with a color
 * @param x1 left coordinate
 * @param y1 top coordinate
 * @param x2 right coordinate
 * @param y2 bottom coordinate
 * @param color fill color
 */
void monitor_fill(__s32 x1, __s32 y1, __s32 x2, __s32 y2, __u32 color)
{
    /*Return if the rect is out the screen*/
    if(x2 < 0) return;
    if(y2 < 0) return;
    if(x1 > MONITOR_HOR_RES - 1) return;
    if(y1 > MONITOR_VER_RES - 1) return;

    /*Truncate the rect to the screen*/
    __s32 act_x1 = x1 < 0 ? 0 : x1;
    __s32 act_y1 = y1 < 0 ? 0 : y1;
    __s32 act_x2 = x2 > MONITOR_HOR_RES - 1 ? MONITOR_HOR_RES - 1 : x2;
    __s32 act_y2 = y2 > MONITOR_VER_RES - 1 ? MONITOR_VER_RES - 1 : y2;

	__s32 x;
	__s32 y;
	for(y = act_y1; y <= act_y2; y++){
		for(x = act_x1; x <= act_x2; x++){
			tmp_fb[y * MONITOR_HOR_RES + x] = color;
		}
	}
}
void monitor_pixel(__s32 x, __s32 y, __u32 color)
{
    /*Return if the rect is out the screen*/
    if(x < 0) return;
    if(y < 0) return;
    if(x > MONITOR_HOR_RES - 1) return;
    if(y > MONITOR_VER_RES - 1) return;
    tmp_fb[y * MONITOR_HOR_RES + x] = color;
}
__u32 monitor_get_pixel(__s32 x, __s32 y)
{
	return tmp_fb[y * MONITOR_HOR_RES + x];
}
/**
 * Put a color map to the marked rect
 * @param x1 left coordinate
 * @param y1 top coordinate
 * @param x2 right coordinate
 * @param y2 bottom coordinate
 * @param color_p an array of colors
 */


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * SDL main thread. All SDL related task have to be handled here!
 * It initializes SDL, handles drawing and the mouse.
 */
static __u32 SystemTime = 0;
__u32 GetSystemTime(void)
{
	return SystemTime;
}
static int sdl_refr(void * param)
{
    (void)param;

	/*Initialize the SDL*/
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetEventFilter(quit_filter, NULL);

	window = SDL_CreateWindow("TFT Simulator",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		MONITOR_HOR_RES, MONITOR_VER_RES, 0);       /*last param. SDL_WINDOW_BORDERLESS to hide borders*/

	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, MONITOR_HOR_RES, MONITOR_VER_RES);

	/*Initialize the frame buffer to gray (77 is an empirical value) */
	memset(tft_fb, 77, MONITOR_HOR_RES * MONITOR_VER_RES * sizeof(__u32));
	memset(tmp_fb, 77, MONITOR_HOR_RES * MONITOR_VER_RES * sizeof(__u32));
	SDL_UpdateTexture(texture, NULL, tft_fb, MONITOR_HOR_RES * sizeof(__u32));
	sdl_refr_qry = true;
	sdl_inited = true;

	/*Run until quit event not arrives*/
	while(sdl_quit_qry == false) {

		/*Refresh handling*/
		if(sdl_refr_qry != false) {
            sdl_refr_qry = false;
            memcpy(tft_fb, tmp_fb, MONITOR_HOR_RES * MONITOR_VER_RES * sizeof(__u32));
            SDL_UpdateTexture(texture, NULL, tft_fb, MONITOR_HOR_RES * sizeof(__u32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
		}

	    SDL_Event event;
	    while(SDL_PollEvent(&event)) {
#if USE_MOUSE != 0
            mouse_handler(&event);
#endif

#if USE_KEYBOARD
            keyboard_handler(&event);
#endif
	    }

		/*Sleep some time*/
		SDL_Delay(SDL_REFR_PERIOD);
		SystemTime += 50;
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	exit(0);

	return 0;
}

int quit_filter (void *userdata, SDL_Event * event)
{
    (void)userdata;

	if(event->type == SDL_QUIT) {
		sdl_quit_qry = true;
	}

	return 1;
}
void sdl_request_refresh(void)
{
	sdl_refr_qry = true;
}
