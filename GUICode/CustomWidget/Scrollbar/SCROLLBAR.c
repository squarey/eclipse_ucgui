/*
 * SCROLLBAR.c
 *
 *  Created on: 2018年6月18日
 *      Author: Administrator
 */
#include "SCROLLBAR.h"
#include "SCROLLBAR_Private.h"
#include "GUI_Animation.h"

static GUI_FullRectStyle SCROLLBAR__DefaultRectStyle =
{
	1,				//.Radius
	0xff,			//.Opacity
	GUI_BLUE,		//.MainColor
	GUI_BLUE		//.GradColor
};
static void _Paint(SCROLLBAR_Obj* pObj, SCROLLBAR_Handle hObj)
{
	GUI_RECT Rect;
	I16 Height = 0;
	I32 Temp = 0;
	Rect.x0 = 0;

	Rect.x1 = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	Temp = (pObj->Offest << 10)/pObj->ActualLength;
	Temp = ((Temp * Height) >> 10);
	Rect.y0 = Temp;
	if(pObj->ActualLength <= Height){
		Rect.y1 = WM_GetWindowSizeY(hObj) + Rect.y0;
	}else{
		Temp = (Height << 10)/pObj->ActualLength;
		Temp = ((Temp * Height) >> 10);
		Rect.y1 = Temp + 1 + Rect.y0;
	}
	//GUI_SetColor((pObj->RectStyle.MainColor & 0x00ffffff) | (pObj->RectStyle.Opacity << 24));
	//GUI_FillRectEx(&Rect);
	GUI_DrawRectMainCorner(&Rect, &pObj->RectStyle);
	GUI_DrawRectMainMiddle(&Rect, &pObj->RectStyle);
}

static void SCROLLBAR_Callback(WM_MESSAGE *pMsg)
{
	SCROLLBAR_Handle hObj = pMsg->hWin;
	SCROLLBAR_Obj * pObj = (SCROLLBAR_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_TOUCH:
			//_OnTouch(hObj, pObj, pMsg);
		return;      /* Message handled. Do not call WM_DefaultProc, because the window may have been destroyed */
		case WM_PAINT:
			_Paint(pObj, hObj);
		return;
		case WM_DELETE:
//			_Delete(pObj);
		break;       /* No return here ... WM_DefaultProc needs to be called */
		default:
		break;
	}
	WM_DefaultProc(pMsg);
}
SCROLLBAR_Handle SCROLLBAR_CreateAttached(WM_HWIN hParent, I32 SpecialFlags)
{
	SCROLLBAR_Handle hObj;
	/* Create the window */
	I32 WinFlags = 0;
	WinFlags = WM_CF_HASTRANS | WM_CF_SHOW;
	hObj = WM_CreateWindowAsChild(0, 0, 6, WM_GetWindowSizeY(hParent),
			hParent, WinFlags, SCROLLBAR_Callback, sizeof(SCROLLBAR_Obj) - sizeof(WM_Obj));
	if (hObj) {
		/* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		SCROLLBAR_Obj * pObj = (SCROLLBAR_Obj *)GUI_ALLOC_h2p(hObj);
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, 0, 0);
		pObj->RectStyle = SCROLLBAR__DefaultRectStyle;
		pObj->Align = OBJ_ALIGN_PARENT_RIGHT;
		pObj->ActualLength = WM_GetWindowSizeY(hParent);
		WM_SetAlignParent(hObj, pObj->Align, 0, 0);
		WM_HideWindow(hObj);
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SCROLLBAR_Create failed")
	}
	return hObj;
}

void SCROLLBAR_SetActualLength(SCROLLBAR_Handle hObj, I32 Length)
{
	if(hObj){
		SCROLLBAR_Obj * pObj = (SCROLLBAR_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->ActualLength != Length){
			if(Length > WM_GetWindowSizeY(hObj)){
				pObj->ActualLength = Length;
				WM_InvalidateWindow(hObj);
			}
		}
	}
}
void SCROLLBAR_SetOffest(SCROLLBAR_Handle hObj, I16 Offest)
{
	if(hObj){
		SCROLLBAR_Obj * pObj = (SCROLLBAR_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->Offest != Offest){
			pObj->Offest = Offest;
			 pObj->RectStyle.Opacity = 0xff;
			WM_ShowWindow(hObj);
			WM_InvalidateWindow(hObj);
		}
	}
}
static void SCROLLBAR_AutoAlpha(SCROLLBAR_Handle hObj, I32 Value)
{
	if(hObj){
		U8 NewAlpha = 0, OldAlpha = 0;
		SCROLLBAR_Obj * pObj = (SCROLLBAR_Obj *)GUI_ALLOC_h2p(hObj);
		OldAlpha = pObj->RectStyle.Opacity;
		NewAlpha = (Value & 0xff);
		if(OldAlpha != NewAlpha){
			pObj->RectStyle.Opacity = NewAlpha;
			WM_InvalidateWindow(hObj);
		}
	}
}
void SCROLLBAR_CreateAlphaAnim(SCROLLBAR_Handle hObj)
{
	if(hObj){
		U8 Alpha = 0;
		GUI_Animation_Obj Anim;
		SCROLLBAR_Obj * pObj = (SCROLLBAR_Obj *)GUI_ALLOC_h2p(hObj);
		Alpha = pObj->RectStyle.Opacity;
		GUI_AnimationObjInit(&Anim);
		Anim.Start = Alpha;
		Anim.End = 0;
		Anim.Time = 1000;
		Anim.pFunc = SCROLLBAR_AutoAlpha;
		Anim.ActTime = -500;
		Anim.pEnd =WM_HideWindow;
		GUI_AnimationCreate(hObj, &Anim);
	}
}
void SCROLLBAR_DeleteAlphaAnim(SCROLLBAR_Handle hObj)
{
	GUI_AnimationDeleteByContext(hObj);
}
