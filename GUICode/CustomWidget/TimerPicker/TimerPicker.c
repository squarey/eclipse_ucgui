

#include "GUI_Protected.h"
#include "TimerPicker_Private.h"
#include "WIDGET.h"



#if GUI_WINSUPPORT && TIMERPICKER_SUPPORT

static GUI_RECT TimerPicker_GetRect(TimerPicker_Handle hObj)
{
	WM_Obj* pWin;
	pWin = WM_H2P(hObj);
	return (pWin->Rect);
}

static void __DrawLeft(TimerPicker_Obj* pObj, TimerPicker_Handle hObj, U32 PickerWidth, U32 *LinePos1, U32 *LinePos2, U32 *EndYPos)
{
	GUI_RECT ShowRect;
	char str[3] = "";
	I8 temp = 0;
	GUI_SetFont(&GUI_FontYH24);
	ShowRect.x0 = 0;
	ShowRect.x1 = PickerWidth >> 1;
	ShowRect.y0 = 0;
	ShowRect.y1 = GUI_GetFontSizeY() + 4;
	temp = pObj->CurHours - 2;
	if(temp < 0)
	{
		temp += 24;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontASSIC_YH32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	temp = pObj->CurHours - 1;
	if(temp < 0)
	{
		temp += 24;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontD24x32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	*LinePos1 = ShowRect.y0 - 4;
	*LinePos2 = ShowRect.y1;
	temp = pObj->CurHours;
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontASSIC_YH32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	temp = pObj->CurHours + 1;
	if(temp > 23)
	{
		temp -= 24;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontYH24);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	temp = pObj->CurHours + 2;
	if(temp > 23)
	{
		temp -= 24;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	*EndYPos = ShowRect.y1;
}
static void __DrawRight(TimerPicker_Obj* pObj, TimerPicker_Handle hObj, U32 PickerWidth, U32 *LinePos1, U32 *LinePos2, U32 *EndYPos)
{
	GUI_RECT ShowRect;
	char str[3] = "";
	I8 temp = 0;
	GUI_SetFont(&GUI_FontYH24);
	ShowRect.x0 = PickerWidth >> 1;
	ShowRect.x1 = PickerWidth;
	ShowRect.y0 = 0;
	ShowRect.y1 = GUI_GetFontSizeY() + 4;
	temp = pObj->CurMinutes- 2;
	if(temp < 0)
	{
		temp += 60;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontASSIC_YH32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	temp = pObj->CurMinutes- 1;
	if(temp < 0)
	{
		temp += 60;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontD24x32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	*LinePos1 = ShowRect.y0 - 4;
	*LinePos2 = ShowRect.y1;
	temp = pObj->CurMinutes;
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontASSIC_YH32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	temp = pObj->CurMinutes + 1;
	if(temp > 59)
	{
		temp -= 60;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	GUI_SetFont(&GUI_FontYH24);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += GUI_GetFontSizeY() + 4;
	temp = pObj->CurMinutes + 2;
	if(temp > 59)
	{
		temp -= 60;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER);
	*EndYPos = ShowRect.y1;
}
static void _Paint(TimerPicker_Obj* pObj, TimerPicker_Handle hObj) 
{
	GUI_RECT PickerRect;
	U32	PickerWidth = 0, PickerHeight = 0;
	U32 SaveYPos1 = 0,SaveYPos2 = 0;
	U32 EndYPos = 0;
	if(!WM__IsEnabled(hObj))
	{
		return;
	}
	GUI_SetBkColor(0);
	
	
	PickerRect = TimerPicker_GetRect(hObj);
	PickerWidth = PickerRect.x1 - PickerRect.x0;
	PickerHeight = PickerRect.y1 - PickerRect.y0;
	PickerRect.x0 = 0;
	PickerRect.x1 = PickerWidth;
	PickerRect.y0 = 0;
	PickerRect.y1 = PickerHeight;
	if(0x10 == pObj->TouchFlag)
	{
		/* Draw Left */
		PickerRect.x1 = PickerWidth/2;
		WM_SetUserClipArea(&PickerRect);
		GUI_Clear();
		__DrawLeft(pObj,hObj,PickerWidth,&SaveYPos1,&SaveYPos2,&EndYPos);
	}
	else if(0x01 == pObj->TouchFlag)
	{
		/* Draw Right */
		PickerRect.x0 = PickerWidth/2;
		WM_SetUserClipArea(&PickerRect);
		GUI_Clear();
		__DrawRight(pObj,hObj,PickerWidth,&SaveYPos1,&SaveYPos2,&EndYPos);
	}
	else 
	{
		/* Draw Both */
		WM_SetUserClipArea(&PickerRect);
		GUI_Clear();
		__DrawLeft(pObj,hObj,PickerWidth,&SaveYPos1,&SaveYPos2,&EndYPos);
		__DrawRight(pObj,hObj,PickerWidth,&SaveYPos1,&SaveYPos2,&EndYPos);
	}
	WM_SetUserClipArea(NULL);
	GUI_DrawHLine(SaveYPos1,0,PickerWidth);
	GUI_DrawHLine(SaveYPos2,0,PickerWidth);
	pObj->TouchVaildDist = SaveYPos2 >> 2;
	GUI_SetFont(&GUI_FontD24x32);
	PickerRect.x0 = 0;
	PickerRect.x1 = PickerWidth;
	PickerRect.y0 = 0;
	PickerRect.y1 = EndYPos;
	//ShowRect.y1 = PickerHeight;
	GUI_DispStringInRect(":",&PickerRect,GUI_TA_HCENTER|GUI_TA_VCENTER);
	
}


static void _OnTouchMoveV(TimerPicker_Handle hObj, TimerPicker_Obj* pObj, WM_MESSAGE*pMsg)
{
	static I32 lastTouchYPos = 0;
	static char isFirstTouch = 0;
	U32 Width = 0;
	//U32 Height = 0;
	GUI_RECT PickerRect;
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	PickerRect = TimerPicker_GetRect(hObj);
	Width = PickerRect.x1 - PickerRect.x0;
	//Height = PickerRect.y1 - PickerRect.y0;
	if(!(pMsg->Data.p))
	{
		lastTouchYPos = 0;
		isFirstTouch = 0;
		return;
	}
	if(pState->Pressed)
	{
		WM_SetCapture(hObj,1);
		WM_SetCaptureVWin(hObj);
		if(0 == pObj->TouchFlag)
		{
			if(pState->x <= (Width >> 1))
			{
				pObj->TouchFlag |= 0x10;
			}
			else 
			{
				pObj->TouchFlag |= 0x01;
			}
		}
		
		if(0 == isFirstTouch)
		{
			isFirstTouch = 1;
			lastTouchYPos = pState->y;
			return;
		}
	}
	else 
	{
		WM_ReleaseCapture();
		pObj->TouchFlag = 0;
		isFirstTouch = 0;
		lastTouchYPos = 0;
		return;
	}
	
	if(lastTouchYPos - pState->y >= pObj->TouchVaildDist)
	{
		lastTouchYPos = pState->y;
		if(0x10 == pObj->TouchFlag)
		{
			pObj->CurHours++;
			if(pObj->CurHours > 23)
			{
				pObj->CurHours = 0;
			}
		}
		else if(0x01 == pObj->TouchFlag)
		{
			pObj->CurMinutes++;
			if(pObj->CurMinutes > 59)
			{
				pObj->CurMinutes = 0;
			}
		}
	}
	else if(pState->y - lastTouchYPos >= pObj->TouchVaildDist)
	{
		lastTouchYPos = pState->y;
		if(0x10 == pObj->TouchFlag)
		{
			pObj->CurHours--;
			if(pObj->CurHours < 0)
			{
				pObj->CurHours = 23;
			}
		}
		else if(0x01 == pObj->TouchFlag)
		{
			pObj->CurMinutes--;
			if(pObj->CurMinutes < 0)
			{
				pObj->CurMinutes = 59;
			}
		}
	}
	else 
	{
		return;
	}
	WM_InvalidateWindow(hObj);
}
static void _OnTouch(TimerPicker_Handle hObj, TimerPicker_Obj* pObj, WM_MESSAGE*pMsg) 
{
	_OnTouchMoveV(hObj,pObj,pMsg);
}

static void TimerPicker_Callback (WM_MESSAGE *pMsg) 
{
	TimerPicker_Handle hObj;
	TimerPicker_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (TimerPicker_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) 
	{
		return;
	}
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
		return;
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
		break;
		case WM_DELETE:
			//_OnDelete(hObj);
		break;
		case WM_KEY:
		break;
	}
	WM_DefaultProc(pMsg);
}
TimerPicker_Handle TimerPicker_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	TimerPicker_Handle hObj;
	/* Create the window */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, TimerPicker_Callback, sizeof(TimerPicker_Obj) - sizeof(WM_Obj));
	if (hObj) 
	{
		TimerPicker_Obj * pObj;
		pObj = (TimerPicker_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
		/* init member variables */
		TimerPicker_INIT_ID(pObj);
	} 
	else 
	{
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	return hObj;
}


#endif 


