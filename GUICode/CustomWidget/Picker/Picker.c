

#include "GUI_Protected.h"
#include "Picker_Private.h"
#include "WIDGET.h"



#if GUI_WINSUPPORT && PICKER_SUPPORT

static GUI_RECT Picker_GetRect(Picker_Handle hObj)
{
	WM_Obj* pWin;
	pWin = WM_H2P(hObj);
	return (pWin->Rect);
}

static void __DrawOwn(Picker_Obj* pObj, Picker_Handle hObj, U32 PickerWidth, U32 *LinePos1, U32 *LinePos2, U32 *EndYPos)
{
	GUI_RECT ShowRect;
	char str[3] = "";
	I8 temp = 0;
	GUI_SetFont(&GUI_FontASSIC_YH32);
	ShowRect.x0 = 0;
	ShowRect.x1 = PickerWidth;
	ShowRect.y0 = 1;
	ShowRect.y1 = 50;
	temp = pObj->CurValue - 2;
	if(temp < 0)
	{
		temp += pObj->MaxValue + 1;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	GUI_SetFont(&GUI_FontD24x32);
	ShowRect.y0 = ShowRect.y1 - 10;
	ShowRect.y1 += 50 - 10;
	temp = pObj->CurValue - 1;
	if(temp < 0)
	{
		temp += pObj->MaxValue + 1;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	GUI_SetFont(&GUI_FontD36x48);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += 50;
	*LinePos1 = ShowRect.y0 - 5;
	*LinePos2 = ShowRect.y1 + 8;
	temp = pObj->CurValue;
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	GUI_SetFont(&GUI_FontD24x32);
	ShowRect.y0 = ShowRect.y1 + 10;
	ShowRect.y1 += 50;
	temp = pObj->CurValue + 1;
	if(temp > pObj->MaxValue)
	{
		temp -= pObj->MaxValue;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	GUI_SetFont(&GUI_FontASSIC_YH32);
	ShowRect.y0 = ShowRect.y1;
	ShowRect.y1 += 50;
	temp = pObj->CurValue + 2;
	if(temp > pObj->MaxValue)
	{
		temp -= pObj->MaxValue;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	*EndYPos = ShowRect.y1;
}
static void _Paint(Picker_Obj* pObj, Picker_Handle hObj)
{
	GUI_RECT PickerRect;
	U32	PickerWidth = 0, PickerHeight = 0;
	U32 SaveYPos1 = 0,SaveYPos2 = 0;
	U32 EndYPos = 0;
	if(!WM__IsEnabled(hObj))
	{
		return;
	}
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	PickerRect = Picker_GetRect(hObj);
	PickerWidth = PickerRect.x1 - PickerRect.x0;
	PickerHeight = PickerRect.y1 - PickerRect.y0;
	PickerRect.x0 = 0;
	PickerRect.x1 = PickerWidth;
	PickerRect.y0 = 0;
	PickerRect.y1 = PickerHeight;
	__DrawOwn(pObj,hObj,PickerWidth,&SaveYPos1,&SaveYPos2,&EndYPos);
	WM_SetUserClipArea(NULL);
	GUI_DrawHLine(SaveYPos1,0,PickerWidth);
	GUI_DrawHLine(SaveYPos2,0,PickerWidth);
	pObj->TouchVaildDist = (SaveYPos2 - SaveYPos1) >> 1;
	GUI_SetFont(&GUI_FontYH24);
	GUI_DispStringAt("min",PickerWidth/2 + 40,SaveYPos2 - GUI_GetFontSizeY());
	PickerRect.x0 = 0;
	PickerRect.x1 = PickerWidth;
	PickerRect.y0 = 0;
	PickerRect.y1 = EndYPos;
	//ShowRect.y1 = PickerHeight;
	//GUI_DispStringInRect(":",&PickerRect,GUI_TA_HCENTER|GUI_TA_VCENTER);
	
}
/*
static void _OnPickerPressed(Picker_Handle hObj, Picker_Obj* pObj)
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) 
	{
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}
static void _OnPickerReleased(Picker_Handle hObj, Picker_Obj* pObj, I32 Notification)
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) 
	{
		WM_NotifyParent(hObj, Notification);
	}
}
*/
static void _OnTouchMoveV(Picker_Handle hObj, Picker_Obj* pObj, WM_MESSAGE*pMsg)
{
	static I32 lastTouchYPos = 0;
	static char isFirstTouch = 0;
	//GUI_RECT PickerRect;
	//U32 Width = 0, Height = 0;
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	//PickerRect = Picker_GetRect(hObj);
	//Width = PickerRect.x1 - PickerRect.x0;
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
		isFirstTouch = 0;
		lastTouchYPos = 0;
		pObj->IsMove = 0;
		return;
	}
	
	if(lastTouchYPos - pState->y >= pObj->TouchVaildDist)
	{
		lastTouchYPos = pState->y;
		pObj->IsMove = 1;
		pObj->CurValue++;
		if(pObj->CurValue > pObj->MaxValue)
		{
			pObj->CurValue = 0;
		}
	}
	else if(pState->y - lastTouchYPos >= pObj->TouchVaildDist)
	{
		lastTouchYPos = pState->y;
		pObj->IsMove = 1;
		pObj->CurValue--;
		if(pObj->CurValue < 0)
		{
			pObj->CurValue = pObj->MaxValue;
		}
	}
	else 
	{
		return;
	}
	WM_InvalidateWindow(hObj);
}
static void _OnTouch(Picker_Handle hObj, Picker_Obj* pObj, WM_MESSAGE*pMsg)
{
	_OnTouchMoveV(hObj,pObj,pMsg);
}

static void Picker_Callback (WM_MESSAGE *pMsg)
{
	Picker_Handle hObj;
	Picker_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (Picker_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
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
	/*	case WM_PID_STATE_CHANGED:
			{
				const WM_PID_STATE_CHANGED_INFO* pInfo = (const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p;
				if(!(pInfo->State))
				{
					_OnPickerReleased(hObj,pObj,WM_NOTIFICATION_RELEASED);
				}
			}
		break;*/
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
Picker_Handle Picker_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	Picker_Handle hObj;
	//WinFlags |= WM_CF_HASTRANS;
	/* Create the window */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, 250, hParent, WinFlags, Picker_Callback, sizeof(Picker_Obj) - sizeof(WM_Obj));
	if (hObj) 
	{
		Picker_Obj * pObj;
		pObj = (Picker_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
		/* init member variables */
		Picker_INIT_ID(pObj);
		pObj->MaxValue = 99;
	} 
	else 
	{
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	return hObj;
}

void Picker_SetMaxValue(Picker_Handle hObj, U8 Value)
{
	if (hObj) 
	{
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		if(Value != pObj->MaxValue)
		{
			pObj->MaxValue = Value;
			WM_Invalidate(hObj);
		}
	}
}

void Picker_SetValue(Picker_Handle hObj, U8 Value)
{
	if (hObj) 
	{
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		if(Value != pObj->CurValue)
		{
			pObj->CurValue = Value;
			WM_Invalidate(hObj);
		}
	}
}

U8 Picker_GetCurValue(Picker_Handle hObj)
{
	U8 r = 0;
	if (hObj) 
	{
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		r = pObj->CurValue;
	}
	return r;
}



#endif 


