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
#include "BootPage.h"

#define DEFAULT_PICTURE_BUFFER_SIZE		(1027 * 600 * 4 * 2)
//static int tick_thread(void *data);
static U8 PictureBuffer[DEFAULT_PICTURE_BUFFER_SIZE];
static void ImageDecodeInit(void);

static GUI_COLOR	_WindowBkColor = GUI_GREEN;
static U8 ColorIndex = 0;
void sWin_Callback(WM_MESSAGE *pMsg) {
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_SetBkColor(_WindowBkColor);
			GUI_Clear();
		break;
		case WM_NOTIFY_PARENT:
			if(WM_NOTIFICATION_CLICKED == pMsg->Data.v){
				if(5 == WM_GetId(pMsg->hWinSrc)){
					//ucWM_DeleteWindow(ucWM_GetDialogItem(pMsg->hWin, 10));
					ColorIndex++;
					switch(ColorIndex){
						case 1:
							_WindowBkColor = GUI_BLUE & 0x80ffffff;
						break;
						case 2:
							_WindowBkColor = GUI_RED;
						break;
						case 3:
							_WindowBkColor = GUI_CYAN;
						break;
						case 4:
							_WindowBkColor = GUI_MAGENTA;
						break;
						case 5:
							_WindowBkColor = GUI_YELLOW & 0x40ffffff;
						break;
						case 6:
							_WindowBkColor = GUI_DARKRED;
						break;
						case 7:
							ColorIndex = 0;
							_WindowBkColor = GUI_GREEN;
						break;
						default:
						break;
					}
					GUI_Debug("_WindowBkColor:%x\n", _WindowBkColor);
					WM_InvalidateWindow(pMsg->hWin);

				}
			}
		break;
	}
}
static void WidgetControlTest(void)
{
	U8 i = 0;
	char Buffer[3];
	WM_HMEM hwin;
	WM_HMEM bWin, tWin;
	LISTVIEW_ITEM ItemInfo;
	GUI_Animation_Obj Anim;
	ItemInfo.IconBuffer = NULL;
	GUI_UC_SetEncodeUTF8();

	hwin = WM_CreateWindowAsChild(0, 0, 854, 480, 0, WM_CF_SHOW, sWin_Callback, 0);
	GUI_Debug("hwin parent %d\n", (int)hwin);
	bWin = BUTTON_CreateAsChild(50, 50, 130, 50, hwin, 5, WM_CF_SHOW) ;
	BUTTON_SetText(bWin, "C");
	GUI_Debug("button1 %d\n", (int)bWin);
	bWin = BUTTON_CreateAsChild(50, 110, 100, 50, hwin, 6, WM_CF_SHOW);
	BUTTON_SetText(bWin, "A");
	GUI_Debug("button2 %d\n", (int)bWin);
	bWin = BUTTON_CreateAsChild(50, 170, 100, 50, hwin, 7, WM_CF_SHOW);
	BUTTON_SetText(bWin, "B");
	BUTTON_DisableNewStyle(bWin);
	GUI_Debug("button3 %d\n", (int)bWin);
	bWin = EDIT_CreateAsChild(160, 100, 120, 40, hwin, 8, WM_CF_SHOW, 10);
	EDIT_SetText(bWin, "123456");
	EDIT_SetFont(bWin, &GUI_FontASSIC_YH32);
	tWin = bWin;
	bWin = LISTVIEW_Create(230, 50, 150, 250, hwin, 9, WM_CF_SHOW, 0);
	GUI_Debug("listview win:%d\n", bWin);
	WM_SetAlignWindow(bWin, tWin, OBJ_ALIGN_BROTHER_UNDER_BOTTOM,0,10);
	for(i = 0; i < 20; i++){
		GUI_sprintf(Buffer, "%d", i);
		LISTVIEW_AddItem(bWin, &ItemInfo, Buffer);
	}

	bWin = TEXT_CreateAsChild(20, 240, 120, 40, hwin, 10, WM_CF_SHOW, "Text", 0);
	TEXT_SetText(bWin,"二中科技");
	TEXT_SetFont(bWin, &GUI_FontYH24);

	/*ucGUI_AnimationObjInit(&Anim);
	Anim.Start = 100;
	Anim.End = 200;
	Anim.Time = 1000;
	Anim.Playback = 1;
	Anim.PlaybackDelay = -1000;
	Anim.pFunc = ucWM_SetWindowPosX;
	ucGUI_AnimationCreate(bWin, &Anim);*/
/*	bWin = ucCHECKBOX_Create(300, 50, 100, 100, hwin, 11, ucWM_CF_SHOW);
	ucCHECKBOX_SetText(bWin, "Check");
	ucCHECKBOX_EnableStyleCircle(bWin);
*/
	SimpleKeyboardCreate(400, 200);
	//ucKEYBOARD_CreateEx(300, 50, 350, 210, hwin, ucWM_CF_SHOW, 0, 11);
}
static void RectBorderTest(void)
{
	GUI_RECT Rect, r, r1;
	GUI_BorderStyle Style;
	Rect.x0 = 500;
	Rect.x1 = 700;
	Rect.y0 = 50;
	Rect.y1 = 150;
	Style.Color = 0xff959595;
	Style.Part = GUI_BORDER_FULL;
	Style.Radius = 4;
	Style.Width = 2;
	GUI_Context.ClipRect.x0 = 0;
	GUI_Context.ClipRect.y0 = 0;
	GUI_Context.ClipRect.x1 = 1024;
	GUI_Context.ClipRect.y1 = 600;
	GUI__ReduceRect(&r, &Rect, 1);
	r1 = r;
	r1.y1 = r1.y0 + GUI_RectGetHeight(&r)/2;
	GUI_SetBkColor(0xfff3f3f3);
	GUI_ClearRectEx(&r1);
	r1 = r;
	r1.y0 = r1.y0 + GUI_RectGetHeight(&r)/2;
	GUI_SetBkColor(0xffdfdfdf);
	GUI_ClearRectEx(&r1);
	GUI_DrawRectBorderStraight(&Rect, &Style);
	GUI_DrawRectBorderCorner(&Rect, &Style);
	/*ucGUI_AA_SetFactor(3);
	ucGUI_AA_FillCircle(600, 300, 40);
	ucGUI_AA_DrawArc(600, 300, 60, 60, 0, 360);*/

}
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
#if 0
	WidgetControlTest();
	//ucGUI_SetFont(&ucGUI_FontASSIC_YH32);
	//ucGUI_DispCharAt('A', 100, 100);
	//RectBorderTest();
#else
	BootPageCreate();
#endif

	//SDL_CreateThread(tick_thread, "tick", NULL);
	while(1){
		GUI_Exec();
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
