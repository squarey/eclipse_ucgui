/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : SLIDER.c
Purpose     : Implementation of slider widget
---------------------------END-OF-HEADER-------------------------------	9
*/

#include <stdlib.h>
//#include <string.h>
#include "GUI_Protected.h"
#include "SLIDER_Private.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && SLIDER_SUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/


/* Define colors */
#ifndef   SLIDER_BKCOLOR0_DEFAULT
  #define SLIDER_BKCOLOR0_DEFAULT   0xc0c0c0
#endif

#ifndef   SLIDER_COLOR0_DEFAULT
  #define SLIDER_COLOR0_DEFAULT     GUI_WHITE
#endif

#ifndef   SLIDER_FOCUSCOLOR_DEFAULT
  #define SLIDER_FOCUSCOLOR_DEFAULT GUI_GREEN
#endif

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

SLIDER_PROPS SLIDER__DefaultProps = {
  SLIDER_BKCOLOR0_DEFAULT,
  SLIDER_COLOR0_DEFAULT,
  SLIDER_FOCUSCOLOR_DEFAULT
};

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _Paint
*/
static void _Paint(SLIDER_Obj* pObj, WM_HWIN hObj)
{
	I32 Height, Width;
	I32 DistPox, XPos, YPos;
	GUI_RECT Rect;
	GUI_FullRectStyle Style;
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	Rect.y0 = (Height - pObj->Width)/2;
	Rect.y1 = (Height + pObj->Width)/2;
	Rect.x0 = 0;
	Rect.x1 = Width - 1;
	Style.MainColor = pObj->Props.Color;
	Style.GradColor = pObj->Props.Color;
	Style.Radius = 2;
	Style.Opacity = 0xff;
	GUI_DrawRectMainMiddle(&Rect, &Style);
	GUI_DrawRectMainCorner(&Rect, &Style);

	DistPox = ((pObj->v << 12) * Width)/(pObj->Max - pObj->Min);
	DistPox >>= 12;

	Rect.x1 = DistPox;
	if(WM_IsEnabled(hObj)){
		GUI_SetColor(pObj->Props.FocusColor);
		Style.MainColor = pObj->Props.FocusColor;
		Style.GradColor = pObj->Props.FocusColor;
	}else{
		GUI_SetColor(pObj->Props.Color);
		Style.MainColor = pObj->Props.Color;
		Style.GradColor = pObj->Props.Color;
	}
	GUI_DrawRectMainMiddle(&Rect, &Style);
	GUI_DrawRectMainCorner(&Rect, &Style);


	YPos = Height/2 - 1;
	XPos = DistPox - YPos;
	if(XPos < YPos){
		XPos = YPos;
	}else{
		if(XPos + YPos >= Width){
			XPos = Width - YPos;
		}
	}
	GUI_AA_FillCircle(XPos, YPos, Height/2 - 1);
}

/*********************************************************************
*
*       _SliderPressed
*/
static void _SliderPressed(SLIDER_Handle hObj, SLIDER_Obj* pObj)
{
	WIDGET_OrState(hObj, SLIDER_STATE_PRESSED);
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}

/*********************************************************************
*
*       _SliderReleased
*/
static void _SliderReleased(SLIDER_Handle hObj, SLIDER_Obj* pObj)
{
	WIDGET_AndState(hObj, SLIDER_STATE_PRESSED);
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, WM_NOTIFICATION_RELEASED);
	}
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(SLIDER_Handle hObj, SLIDER_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
		if (pState->Pressed) {
			I32 x0, xsize, x, Sel, Range;
			Range = (pObj->Max - pObj->Min);
			x0    = 0;
			x     = (pObj->Widget.State & WIDGET_STATE_VERTICAL) ? pState->y : pState->x;
			x    -= x0;
			xsize = WIDGET__GetWindowSizeX(hObj) - 2 * x0;
			if (x <= 0) {
				Sel = pObj->Min;
			} else if (x >= xsize) {
				Sel = pObj->Max;
			} else {
				I32 Div;
				Div = xsize ? xsize : 1;     /* Make sure we do not divide by 0, even though xsize should never be 0 in this case anyhow */
				Sel = pObj->Min + ((U32)Range * (U32)x + Div / 2) / Div;
			}
			if (WM_IsFocussable(hObj)) {
				WM_SetFocus(hObj);
			}
			WM_SetCapture(hObj, 1);
			WM_SetCaptureHWin(hObj);
			SLIDER_SetValue(hObj, Sel);
			if ((pObj->Widget.State & SLIDER_STATE_PRESSED) == 0){
				_SliderPressed(hObj, pObj);
			}
		} else {
			/* React only if button was pressed before ... avoid problems with moving / hiding windows above (such as dropdown) */
			if (pObj->Widget.State & SLIDER_STATE_PRESSED) {
				_SliderReleased(hObj, pObj);
			}
		}
	}
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(SLIDER_Handle hObj, WM_MESSAGE*pMsg)
{
	const WM_KEY_INFO* pKeyInfo;
	I32 Key;
	pKeyInfo = (const WM_KEY_INFO*)(pMsg->Data.p);
	Key = pKeyInfo->Key;
	if (pKeyInfo->PressedCnt > 0) {
		switch (Key) {
			case GUI_KEY_RIGHT:
				SLIDER_Inc(hObj);
				break;                    /* Send to parent by not doing anything */
			case GUI_KEY_LEFT:
				SLIDER_Dec(hObj);
				break;                    /* Send to parent by not doing anything */
			default:
				return;
		}
	}
}

/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       SLIDER_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
SLIDER_Obj * SLIDER_h2p(SLIDER_Handle h)
{
	SLIDER_Obj * p = (SLIDER_Obj *)GUI_ALLOC_h2p(h);
	if (p) {
		if (p->DebugId != SLIDER_ID) {
			GUI_DEBUG_ERROROUT("SLIDER.c: Wrong handle type or Object not init'ed");
			return 0;
		}
	}
	return p;
}
#endif

/*********************************************************************
*
*       Exported routines:  Callback
*
**********************************************************************
*/
/*********************************************************************
*
*       SLIDER_Callback
*/
void SLIDER_Callback (WM_MESSAGE *pMsg)
{
	SLIDER_Handle hObj;
	SLIDER_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (SLIDER_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
			return;
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
			break;
		case WM_KEY:
			_OnKey(hObj, pMsg);
			break;
	}
	WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */

/*********************************************************************
*
*       SLIDER_CreateEx
*/
SLIDER_Handle SLIDER_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	SLIDER_Handle hObj;
	/* Create the window */
//#if _SUPPORT_TRANSPARENCY
	WinFlags |= WM_CF_HASTRANS;
//#endif
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, SLIDER_Callback, sizeof(SLIDER_Obj) - sizeof(WM_Obj));
	if (hObj) {
		SLIDER_Obj * pObj;
		U16 InitState;
		pObj = (SLIDER_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		InitState = WIDGET_STATE_FOCUSSABLE;
		if (ExFlags & SLIDER_CF_VERTICAL) {
			InitState |= WIDGET_CF_VERTICAL;
		}
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, InitState);
		/* init member variables */
		SLIDER_INIT_ID(pObj);
		pObj->Props = SLIDER__DefaultProps;
		pObj->Width       = 8;
		pObj->Max         = 100;
		pObj->Min         = 0;
		pObj->NumTicks    = -1;
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	return hObj;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       SLIDER_Dec
*/
void SLIDER_Dec(SLIDER_Handle hObj)
{
	SLIDER_Obj* pObj;
	if (hObj) {
		pObj = SLIDER_H2P(hObj);
		if (pObj->v > pObj->Min) {
			pObj->v--;
			WM_InvalidateWindow(hObj);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
		}
	}
}

/*********************************************************************
*
*       SLIDER_Inc
*/
void SLIDER_Inc(SLIDER_Handle hObj)
{
	SLIDER_Obj* pObj;
	if (hObj) {
		pObj = SLIDER_H2P(hObj);
		if (pObj->v < pObj->Max) {
			pObj->v++;
			WM_InvalidateWindow(hObj);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
		}
	}
}

/*********************************************************************
*
*       SLIDER_SetWidth
*/
void SLIDER_SetWidth(SLIDER_Handle hObj, I32 Width)
{
	SLIDER_Obj* pObj;
	if (hObj) {
		pObj = SLIDER_H2P(hObj);
		if (pObj->Width != Width) {
			pObj->Width = Width;
			WM_InvalidateWindow(hObj);
		}
	}
}

/*********************************************************************
*
*       SLIDER_SetValue
*/
void SLIDER_SetValue(SLIDER_Handle hObj, I32 v)
{
	SLIDER_Obj* pObj;
	if (hObj) {
		pObj = SLIDER_H2P(hObj);
		/* Put in min/max range */
		if (v < pObj->Min) {
			v = pObj->Min;
		}
		if (v > pObj->Max) {
			v = pObj->Max;
		}
		if (pObj->v != v) {
			pObj->v = v;
			WM_InvalidateWindow(hObj);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
		}
	}
}

/*********************************************************************
*
*       SLIDER_SetRange
*/
void SLIDER_SetRange(SLIDER_Handle hObj, I32 Min, I32 Max)
{
	if (hObj) {
		SLIDER_Obj* pObj;
		pObj = SLIDER_H2P(hObj);
		if (Max < Min) {
			Max = Min;
		}
		pObj->Min = Min;
		pObj->Max = Max;
		if (pObj->v < Min) {
			pObj->v = Min;
		}
		if (pObj->v > Max) {
			pObj->v = Max;
		}
		WM_InvalidateWindow(hObj);
	}
}

/*********************************************************************
*
*       SLIDER_SetNumTicks
*/
void SLIDER_SetNumTicks(SLIDER_Handle hObj, I32 NumTicks)
{
	if (hObj && (NumTicks >= 0)) {
		SLIDER_Obj* pObj;
		pObj = SLIDER_H2P(hObj);
		pObj->NumTicks = NumTicks;
		WM_InvalidateWindow(hObj);
	}
}

/*********************************************************************
*
*       SLIDER_SetBkColor
*/
void SLIDER_SetBkColor(SLIDER_Handle hObj, GUI_COLOR Color)
{
	if (hObj) {
		SLIDER_Obj * pObj;
		pObj = SLIDER_H2P(hObj);
		pObj->Props.BkColor = Color;
		WM_InvalidateWindow(hObj);
	}
}

/*********************************************************************
*
*       SLIDER_SetDefaultBkColor
*/
void SLIDER_SetDefaultBkColor(GUI_COLOR Color)
{
	SLIDER__DefaultProps.BkColor = Color;
}

/*********************************************************************
*
*       Query state
*
**********************************************************************
*/
/*********************************************************************
*
*       SLIDER_GetValue
*/
I32 SLIDER_GetValue(SLIDER_Handle hObj)
{
	I32 r = 0;
	SLIDER_Obj* pObj;
	if (hObj) {
		pObj = SLIDER_H2P(hObj);
		r = pObj->v;
	}
	return r;
}


#else /* avoid empty object files */

void SLIDER_C(void);
void SLIDER_C(void){}

#endif  /* #if GUI_WINSUPPORT */


	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
