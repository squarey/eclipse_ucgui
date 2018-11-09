/*
 * WidgetControlTest.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#include "WidgetControlTest.h"
#include <math.h>

static GUI_COLOR	_WindowBkColor = GUI_GRAY;

static U8 ToRectBorderTest = 0;
static I32 CurrentValue = 0;
static void sWin_Callback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_SetBkColor(_WindowBkColor);
			GUI_Clear();
			GUI_Debug("Window paint\n");
		break;
		case WM_NOTIFY_PARENT:
			if(WM_NOTIFICATION_CLICKED == pMsg->Data.v){
				if(3 == WM_GetId(pMsg->hWinSrc)){
					if(CurrentValue > 100){
						CurrentValue = 0;
					}
					CurrentValue += 3;
					SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, 2), CurrentValue);
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}
/*
static GUI_POINT aPointer[] =
{
		{0, 0}, {10, 0}, {10, 55}, {0, 55}, {0, 0}
};*/
static GUI_POINT aPointer[] =
{
		{0, 0}, {55, 0}, {55, 10}, {0, 10}
};
#define AA_FACTOR		4
static void _SilderSelfDraw(WM_HWIN hWin, I32 CurValue, I32 MaxValue, I32 MinValue)
{
	GUI_POINT rPointer[5];
	U32 i = 0;
	float fAngle = 0, fSin = 0, fCos = 0;
	I32 ValuePercent = 0;
	I32 AnglePercent = 0;
	I32 Temp1 = 0, Temp2 = 0;
	I32 CenterX = 0, CenterY = 0;
	GUI_Debug("CurValue:%d, MaxValue:%d, MinValue:%d\n", CurValue, MaxValue, MinValue);
	GUI_SetBkColor(GUI_CYAN);
	GUI_Clear();
	GUI_SetColor(GUI_RED);
	GUI_AA_SetFactor(4);
	GUI_AA_EnableHiRes();
	//GUI_AA_FillPolygon(aPointer, 5, 50, 50);
	Temp1 = (CurValue - MinValue) * 1000;
	Temp2 = (MaxValue - MinValue) * 1000;
	ValuePercent = (Temp1 * 100)/Temp2;
	AnglePercent = (ValuePercent * 360)/100;
	GUI_RotatePolygon(rPointer, aPointer, 4, 0);
	GUI_Debug("AnglePercent:%d\n", AnglePercent);
	for(i = 0; i < 360;){
		fAngle = (3.1415926 * i)/180;//Angle * 0.0174;
		GUI_RotatePolygon(rPointer, rPointer, 4, fAngle);
		fSin = sin(fAngle);
		fCos = cos(fAngle);
		CenterY = fSin * 50 + 0.5;
		CenterX = fCos * 50 + 0.5;

		//CenterX = 100 * AA_FACTOR + (rPointer[3].x/* + rPointer[2].x/2*/) * AA_FACTOR;
		//CenterY = 100 * AA_FACTOR + (rPointer[3].y/* + rPointer[2].y/2*/ + 1) * AA_FACTOR;
		CenterX = (100 + CenterX);// * AA_FACTOR;
		CenterY = (100 + CenterY);// * AA_FACTOR;
		if(i >= 360 - AnglePercent){
			GUI_SetColor(GUI_YELLOW);
		}else{
			GUI_SetColor(GUI_RED);
		}
		GUI_Debug("CenterX:%d, CenterY:%d\n", CenterX, CenterY);
		//GUI_AA_FillPolygon(rPointer, 4, CenterX, CenterY);
		GUI_DrawPoint(CenterX, CenterY);
		i += 6;
	}
}

void WidgetControlTest(void)
{
	WM_HMEM hWin, hMainWin;

	hMainWin = WM_CreateWindowAsChild(0, 0, 854, 480, 0, WM_CF_SHOW, sWin_Callback, 0);

	hWin = SLIDER_Create(100, 50, 200, 200, hMainWin, 2, WM_CF_SHOW, 0);

	SLIDER_SetUserDrawMethod(hWin, _SilderSelfDraw);
	SLIDER_SetRange(hWin, 0, 100);
	WM_DisableWindow(hWin);

	hWin = BUTTON_CreateAsChild(150, 300, 100, 50, hMainWin, 3, WM_CF_SHOW);
	BUTTON_SetText(hWin, "Button");
	GUI_Debug("Button visible %d\n", WM_IsVisible(hWin));
}
/*
void RectBorderTest(void)
{
	GUI_RECT Rect, r, r1;
	GUI_BorderStyle Style;
	if(ToRectBorderTest){
		return;
	}
	ToRectBorderTest = 1;
	Rect.x0 = 500;
	Rect.x1 = 540;
	Rect.y0 = 50;
	Rect.y1 = 90;
	Style.Color = 0xff959595;
	Style.Part = GUI_BORDER_FULL;
	Style.Radius = 49;
	Style.Width = 2;
	GUI_Context.ClipRect.x0 = 0;
	GUI_Context.ClipRect.y0 = 0;
	GUI_Context.ClipRect.x1 = 1024;
	GUI_Context.ClipRect.y1 = 600;

	GUI_SetColor(GUI_GREEN);

	//GUI_SetFont(&GUI_FontNumberYH48);
	//GUI_SetFontScale(2);
	//GUI_DispStringAt("0123456789", 100, 190);

	GUI_ShadowStyle ShadowStyle;
	ShadowStyle.Color = GUI_RED;
	ShadowStyle.Opacity = 0xFF;
	ShadowStyle.Radius = 21;
	ShadowStyle.Type = GUI_SHADOW_FULL;
	ShadowStyle.Width = 10;
	GUI_DrawRectShadow(&Rect, &ShadowStyle);

}
*/
