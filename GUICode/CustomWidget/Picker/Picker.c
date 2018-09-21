

#include "GUI_Protected.h"
#include "Picker_Private.h"
#include "WIDGET.h"



#if GUI_WINSUPPORT && PICKER_SUPPORT


static I32 LastTouchYPos = 0;
static char IsFirstTouch = 0;


static GUI_RECT Picker_GetRect(Picker_Handle hObj)
{
	WM_Obj* pWin;
	pWin = WM_H2P(hObj);
	return (pWin->Rect);
}

static void __DrawOwn(Picker_Obj* pObj, U32 PickerWidth, U32 PickerHeight, U32 *LinePos1, U32 *LinePos2, U32 *EndYPos)
{
	GUI_RECT ShowRect;
	I32 FontSizeY = 0;
	char str[5] = "";
	I32 temp = 0;
	ShowRect.x0 = 0;
	ShowRect.x1 = PickerWidth;
	GUI_SetTextMode(GUI_TM_TRANS);
	//large font
	GUI_SetColor(pObj->LargeColor);
	GUI_SetFont(pObj->pLargeFont);
	FontSizeY = GUI_GetFontSizeY();
	ShowRect.y0 = (PickerHeight - FontSizeY)/2;
	ShowRect.y1 = (PickerHeight + FontSizeY)/2;
	*LinePos1 = ShowRect.y0 - 1;
	*LinePos2 = ShowRect.y1 + 1;
	temp = pObj->CurValue;
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	//small font
	GUI_SetColor(pObj->SmallColor);
	GUI_SetFont(pObj->pSmallFont);
	FontSizeY = GUI_GetFontSizeY();
	ShowRect.y0 = 1;
	ShowRect.y1 = FontSizeY + 1;
	temp = pObj->CurValue - 2;
	if(temp < pObj->MinValue)
	{
		temp = pObj->MaxValue - 1;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);

	GUI_SetFont(pObj->pSmallFont);
	FontSizeY = GUI_GetFontSizeY();
	ShowRect.y0 = PickerHeight - FontSizeY;
	ShowRect.y1 = PickerHeight;
	temp = pObj->CurValue + 2;
	if(temp > pObj->MaxValue)
	{
		temp -= pObj->MaxValue;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	*EndYPos = ShowRect.y1;
	//middle font
	GUI_SetColor(pObj->MiddleColor);
	GUI_SetFont(pObj->pMiddleFont);
	FontSizeY = GUI_GetFontSizeY();
	ShowRect.y1 = *LinePos1 - 1;
	ShowRect.y0 = ShowRect.y1 - FontSizeY - 1;
	temp = pObj->CurValue - 1;
	if(temp < pObj->MinValue)
	{
		temp = pObj->MaxValue;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);
	//GUI_DispStringInRectWrap(str, &ShowRect, GUI_TA_HCENTER | GUI_TA_VCENTER, 0);

	GUI_SetFont(pObj->pMiddleFont);
	FontSizeY = GUI_GetFontSizeY();
	ShowRect.y0 = *LinePos2 + 1;
	ShowRect.y1 = ShowRect.y0 + FontSizeY + 1;
	temp = pObj->CurValue + 1;
	if(temp > pObj->MaxValue)
	{
		temp -= pObj->MaxValue;
	}
	GUI_sprintf(str,"%02d",temp);
	GUI_DispStringInRect(str,&ShowRect,GUI_TA_HCENTER | GUI_TA_VCENTER);

}
static void _Paint(Picker_Obj* pObj, Picker_Handle hObj)
{
	if(!WM__IsEnabled(hObj)){
		return;
	}
	if(!WM_GetHasTrans(hObj)){
		GUI_SetBkColor(pObj->BkColor);
		GUI_Clear();
	}
	if(pObj->CustomDraw){
			pObj->CustomDraw(hObj,pObj);
	}else{
		GUI_RECT PickerRect;
		U32	PickerWidth = 0, PickerHeight = 0;
		U32 SaveYPos1 = 0,SaveYPos2 = 0;
		U32 EndYPos = 0;
		PickerRect = Picker_GetRect(hObj);
		PickerWidth = PickerRect.x1 - PickerRect.x0 + 1;
		PickerHeight = PickerRect.y1 - PickerRect.y0 + 1;
		PickerRect.x0 = 0;
		PickerRect.x1 = PickerWidth;
		PickerRect.y0 = 0;
		PickerRect.y1 = PickerHeight;
		__DrawOwn(pObj, PickerWidth, PickerHeight, &SaveYPos1, &SaveYPos2, &EndYPos);
		WM_SetUserClipArea(NULL);
		GUI_DrawHLine(SaveYPos1,0,PickerWidth);
		GUI_DrawHLine(SaveYPos2,0,PickerWidth);
		pObj->TouchVaildDist = (SaveYPos2 - SaveYPos1) >> 2;
	}
}

static void _OnPickerPressed(Picker_Handle hObj, Picker_Obj* pObj)
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS){
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}
static void _OnPickerReleased(Picker_Handle hObj, Picker_Obj* pObj, I32 Notification)
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS){
		WM_NotifyParent(hObj, Notification);
	}
}

static void _CalculateMoveDistanceY(Picker_Handle hObj, Picker_Obj* pObj, I32 TouchPosY)
{
	if(LastTouchYPos - TouchPosY >= pObj->TouchVaildDist){
		LastTouchYPos = TouchPosY;
		pObj->IsMove = 1;
		pObj->CurValue++;
		if(pObj->CurValue > pObj->MaxValue){
			pObj->CurValue = pObj->MinValue;
		}
	}else if(TouchPosY - LastTouchYPos >= pObj->TouchVaildDist){
		LastTouchYPos = TouchPosY;
		pObj->IsMove = 1;
		pObj->CurValue--;
		if(pObj->CurValue < pObj->MinValue){
			pObj->CurValue = pObj->MaxValue;
		}
	}else {
		return;
	}
	WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
	WM_InvalidateWindow(hObj);
}

static void _OnTouchMoveV(Picker_Handle hObj, Picker_Obj* pObj, WM_MESSAGE*pMsg)
{
	//GUI_RECT PickerRect;
	//U32 Width = 0, Height = 0;
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	//PickerRect = Picker_GetRect(hObj);
	//Width = PickerRect.x1 - PickerRect.x0;
	//Height = PickerRect.y1 - PickerRect.y0;
	if(!(pMsg->Data.p)){
		LastTouchYPos = 0;
		IsFirstTouch = 0;
		return;
	}
	if(pState->Pressed){
		WM_SetCapture(hObj,1);
		if(0 == IsFirstTouch){
			IsFirstTouch = 1;
			LastTouchYPos = pState->y;
			return;
		}
	}else {
		WM_ReleaseCapture();
		IsFirstTouch = 0;
		LastTouchYPos = 0;
		pObj->IsMove = 0;
		return;
	}
	_CalculateMoveDistanceY(hObj, pObj, pState->y);
	
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
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
		return;
		case WM_PID_STATE_CHANGED:
			{
				const WM_PID_STATE_CHANGED_INFO* pInfo = (const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p;
				if(!(pInfo->State)){
					_OnPickerReleased(hObj,pObj,WM_NOTIFICATION_RELEASED);
				}else{
					_OnPickerPressed(hObj,pObj);
				}
			}
		break;
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
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, Picker_Callback, sizeof(Picker_Obj) - sizeof(WM_Obj));
	if (hObj){
		Picker_Obj * pObj;
		pObj = (Picker_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
		/* init member variables */
		Picker_INIT_ID(pObj);
		pObj->MaxValue = 99;
		pObj->MinValue = 0;
		pObj->pSmallFont = &GUI_FontASSIC_YH32;
		pObj->pMiddleFont = &GUI_FontNumberYH48;
		pObj->pLargeFont = &GUI_FontNumberYH72;
		pObj->CustomDraw = NULL;
		pObj->LargeColor = GUI_WHITE;
		pObj->MiddleColor = GUI_WHITE;
		pObj->SmallColor = GUI_WHITE;
		pObj->BkColor = GUI_BLACK;
	}else{
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	return hObj;
}

void Picker_SetMaxValue(Picker_Handle hObj, I32 Value)
{
	if (hObj){
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		if(Value != pObj->MaxValue){
			pObj->MaxValue = Value;
			if(pObj->CurValue > pObj->MaxValue){
				pObj->CurValue = pObj->MaxValue;
			}
			WM_Invalidate(hObj);
		}
	}
}
void Picker_SetMinValue(Picker_Handle hObj, I32 Value)
{
	if (hObj){
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		if(Value != pObj->MinValue){
			pObj->MinValue = Value;
			if(pObj->CurValue < pObj->MinValue){
				pObj->CurValue = pObj->MinValue;
			}
			WM_Invalidate(hObj);
		}
	}
}

void Picker_SetValue(Picker_Handle hObj, I32 Value)
{
	if (hObj){
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		if(Value != pObj->CurValue){
			pObj->CurValue = Value;
			WM_Invalidate(hObj);
		}
	}
}

I32 Picker_GetCurValue(Picker_Handle hObj)
{
	I32 r = 0;
	if (hObj){
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		r = pObj->CurValue;
	}
	return r;
}
void Picker_SetCustomDraw(Picker_Handle hObj, void *pDraw)
{
	if (hObj) {
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		pObj->CustomDraw = pDraw;
	}
}

void Picker_SetFont(Picker_Handle hObj, const GUI_FONT *pSmall, const GUI_FONT *pMiddle, const GUI_FONT *pLarge)
{
	if (hObj) {
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		pObj->pSmallFont = pSmall;
		pObj->pMiddleFont = pMiddle;
		pObj->pLargeFont = pLarge;
		WM_Invalidate(hObj);
	}
}
void Picker_SetFontColor(Picker_Handle hObj, GUI_COLOR LargeColor, GUI_COLOR MiddleColor, GUI_COLOR SmallColor)
{
	if (hObj) {
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		pObj->LargeColor = LargeColor;
		pObj->MiddleColor = MiddleColor;
		pObj->SmallColor = SmallColor;
		WM_Invalidate(hObj);
	}
}
void Picker_SetBkColor(Picker_Handle hObj, GUI_COLOR BkColor)
{
	if (hObj) {
		Picker_Obj* pObj;
		pObj = Picker_H2P(hObj);
		if(pObj->BkColor != BkColor){
			pObj->BkColor = BkColor;
			WM_Invalidate(hObj);
		}
	}
}

#endif 


