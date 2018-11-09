/*
 * KEYBOARD_SHOW.c
 *
 *  Created on: 2018年5月17日
 *      Author: Administrator
 */

#include "SimpleKeyboard.h"

#define DEFAULT_KEYBOARD_WIDTH		400
#define DEFAULT_KEYBOARD_HEIGHT		300

#define DEFAULT_SIMPLE_KEYBOARD_BKCOLOR	GUI_DARKGRAY

static KEYBOARD_Handle hKeyboard = WM_HWIN_NULL;

static void _DeleteKeyboard(KEYBOARD_Handle hObj)
{
	GUI_Debug("To delete keyboard\n");
	//KEYBOARD_ResetStatus(hKeyboard);
	WM_DeleteWindow(hKeyboard);
	hKeyboard = WM_HWIN_NULL;
}

void SimpleKeyboardCreate(I32 x0, I32 y0)
{
	if(WM_HWIN_NULL == hKeyboard){
		hKeyboard = KEYBOARD_CreateEx(x0, y0, DEFAULT_KEYBOARD_WIDTH, DEFAULT_KEYBOARD_HEIGHT, 0, WM_CF_SHOW, 0, GUI_ID_KEYBOARD);
		WM_SetStayOnTop(hKeyboard, 1);
		KEYBOARD_SetNoticeDeleteCb(hKeyboard, _DeleteKeyboard);
		KEYBOARD_SetBkColor(hKeyboard, DEFAULT_SIMPLE_KEYBOARD_BKCOLOR);
	}else{
		GUI_RECT Rect;
		WM_GetWindowRectEx(hKeyboard, &Rect);
		if((Rect.x0 != x0) || (Rect.y0 != y0)){
			WM_MoveTo(hKeyboard, x0, y0);
		}
		WM_ShowWindow(hKeyboard);
	}
	GUI_Debug("hKeyboard:%d\n", hKeyboard);
}
void SimpleKeyboardDelete(void)
{
	WM_DeleteWindow(hKeyboard);
	hKeyboard = WM_HWIN_NULL;
}
void SimpleKeyboardSetPos(I32 x0, I32 y0)
{
	GUI_RECT Rect;
	WM_GetWindowRectEx(hKeyboard, &Rect);
	if((Rect.x0 != x0) || (Rect.y0 != y0)){
		WM_MoveTo(hKeyboard, x0, y0);
	}
}
void SimpleKeyboardReSize(I32 Width, I32 Height)
{
	WM_SetSize(hKeyboard, Width, Height);
}
void SimpleKeyboardShow(void)
{
	if(hKeyboard){
		WM_ShowWindow(hKeyboard);
	}else{
		I32 LCDWidht, LCDHeight;
		GUI_RECT LCDRect;
		LCD_L0_GetRect(&LCDRect);
		LCDWidht = WM_GetRectSizeX(LCDRect);
		LCDHeight = WM_GetRectSizeY(LCDRect);
		SimpleKeyboardCreate((LCDWidht - DEFAULT_KEYBOARD_WIDTH)/2, LCDHeight - DEFAULT_KEYBOARD_HEIGHT);
	}

}
void SimpleKeyboardHide(void)
{
	WM_HideWindow(hKeyboard);
}
void SimpleKeyboardSetStyle(U8 Style)
{
	KEYBOARD_SetStyle(hKeyboard, Style);
}
void SimpleKeyboardLockStyle(void)
{
	KEYBOARD_LockStyle(hKeyboard);
}
void SimpleKeyboardUnLockStyle(void)
{
	KEYBOARD_UnLockStyle(hKeyboard);
}
void SimpleKeyboardReportNumberOnly(void)
{
	KEYBOARD_SetReportNumberOnly(hKeyboard);
}
void SimpleKeyboardClearReportNumberOnly(void)
{
	KEYBOARD_ClearReportNumberOnly(hKeyboard);
}
void SimpleKeyboardSetBkColor(GUI_COLOR BkColor)
{
	KEYBOARD_SetBkColor(hKeyboard, BkColor);
}
void SimpleKeyboardSetPressStyle(GUI_FullRectStyle Style)
{
	KEYBOARD_SetPressStyle(hKeyboard, Style);
}
void SimpleKeyboardSetReleaseStyle(GUI_FullRectStyle Style)
{
	KEYBOARD_SetReleaseStyle(hKeyboard, Style);
}
void SimpleKeyboardSetEnterCb(_cb_Enter pCb)
{
	KEYBOARD_SetNoticeEnterCb(hKeyboard, pCb);
}
