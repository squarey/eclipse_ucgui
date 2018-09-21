/*
 * main.c
 *
 *  Created on: 2018年4月26日
 *      Author: Administrator
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <monitor.h>
#include <mouse.h>
#include <unistd.h>
#include "GUI.h"
#include "DIALOG.h"
#include "PNGDecode.h"
#include "PageTitleBar.h"
#include "PageMainList.h"
#include "PageMenuBar.h"

#define USE_CONTROL_DEBUG	0

#define DEFAULT_PICTURE_BUFFER_SIZE		(1027 * 600 * 4 * 2)
//static int tick_thread(void *data);
static U8 PictureBuffer[DEFAULT_PICTURE_BUFFER_SIZE];
static void ImageDecodeInit(void);

int main (int argc, char *argv[])
{
	GUI_Driver_t tDriver;
	setbuf(stdout,NULL);
	GUI_DriverInit(&tDriver);
	monitor_init();
	mouse_init();
	ImageDecodeInit();
	tDriver.tLCDDriver.LCD_GetPixel = monitor_get_pixel;
	tDriver.tLCDDriver.LCD_PutPixel = monitor_pixel;
	tDriver.tLCDDriver.LCD_PutRect = monitor_fill;
	tDriver.tLCDDriver.LCD_UpdateAllEnd = sdl_request_refresh;
	tDriver.tTouchDriver = mouse_read;
	GUI_DriverRegister(&tDriver);
	GUI_PicMemoryInit((void *)PictureBuffer, DEFAULT_PICTURE_BUFFER_SIZE);
	GUI_Init();
	GUI_EnableLogOut();
	GUI_UC_SetEncodeUTF8();
	monitor_fill(0, 0, 854, 480, 0xff000000);
#if USE_CONTROL_DEBUG
	//WidgetControlTest();
	//RectBorderTest();
#else
	//BootPageCreate();
	PageTitleBarCreate();
	PageListCreate();
	PageMenuBarCreate();
#endif
	//SDL_CreateThread(tick_thread, "tick", NULL);
	while(1){
		GUI_Exec();
		//RectBorderTest();
		GUI_TimeIncrease(5);
		usleep(5000);
	}
	return 0;
}
static U8 ImageResRelease(ImageViewInfo_t *pInfo)
{
	if(pInfo){
		if(pInfo->pBuffer){
			GUI_PicMemoryFree(pInfo->pBuffer);
			//free(pInfo->pBuffer);
			pInfo->pBuffer = NULL;
		}
	}
	return 0;
}
static void ImageDecodeInit(void)
{
	GUI_ImageDecode_t mMethod;
	GUI_ImageDecodeMethodInit(&mMethod);
	mMethod.PNGDecode = ImageDecodeForPNG;
	mMethod.ImageResRelease = ImageResRelease;
	GUI_ImageDecodeMehtodRegister(&mMethod);
}
//static int tick_thread(void *data)
//{
//    while(1) {
//        SDL_Delay(5);
//    }
//
//    return 0;
//}
