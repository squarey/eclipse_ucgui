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
File        : BUTTON.c
Purpose     : Implementation of button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>
#include "BUTTON_Private.h"


#if GUI_WINSUPPORT && BUTTON_SUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef   BUTTON_FONT_DEFAULT
    #define BUTTON_FONT_DEFAULT GUI_DEFAULT_FONT
#endif

/* Support for 3D effects */
#ifndef   BUTTON_USE_3D
  #define BUTTON_USE_3D 1
#endif

#ifndef   BUTTON_3D_MOVE_X
  #define BUTTON_3D_MOVE_X 1
#endif
#ifndef   BUTTON_3D_MOVE_Y
  #define BUTTON_3D_MOVE_Y 1
#endif

/* Define colors */
#ifndef   BUTTON_BKCOLOR0_DEFAULT
  #define BUTTON_BKCOLOR0_DEFAULT   GUI_GREEN
#endif

#ifndef   BUTTON_BKCOLOR1_DEFAULT
  #define BUTTON_BKCOLOR1_DEFAULT   GUI_WHITE//GUI_WHITE
#endif

#ifndef   BUTTON_BKCOLOR2_DEFAULT
  #define BUTTON_BKCOLOR2_DEFAULT   GUI_LIGHTGRAY
#endif

#ifndef   BUTTON_TEXTCOLOR0_DEFAULT
  #define BUTTON_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef   BUTTON_TEXTCOLOR1_DEFAULT
  #define BUTTON_TEXTCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef   BUTTON_TEXTCOLOR2_DEFAULT
  #define BUTTON_TEXTCOLOR2_DEFAULT GUI_DARKGRAY
#endif

#ifndef   BUTTON_FOCUSCOLOR_DEFAULT
  #define BUTTON_FOCUSCOLOR_DEFAULT GUI_BLACK
#endif

#ifndef   BUTTON_REACT_ON_LEVEL
  #define BUTTON_REACT_ON_LEVEL 0
#endif

#ifndef   BUTTON_ALIGN_DEFAULT
  #define BUTTON_ALIGN_DEFAULT GUI_TA_HCENTER | GUI_TA_VCENTER
#endif

#define BUTTON_STYLE_RADIUS_DEF					6
#define BUTTON_STYLE_OPACITY_DEF					0xFF
#define BUTTON_STYLE_PRESS_MAIN_COLOR_DEF			GUI_WHITE
#define BUTTON_STYLE_PRESS_GRAD_COLOR_DEF			GUI_DARKGRAY
#define BUTTON_STYLE_REL_MAIN_COLOR_DEF			GUI_WHITE
#define BUTTON_STYLE_REL_GRAD_COLOR_DEF			GUI_BLUE


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#if 0
BUTTON_PROPS BUTTON__DefaultProps = {
	.aBkColor[0] = BUTTON_BKCOLOR0_DEFAULT,		//.aBkColor[0]
	.aBkColor[1] = BUTTON_BKCOLOR1_DEFAULT,		//.aBkColor[1]
	.aBkColor[2] = BUTTON_BKCOLOR2_DEFAULT,		//.aBkColor[2]
	.aTextColor[0] = BUTTON_TEXTCOLOR0_DEFAULT,		//.aTextColor[0]
	.aTextColor[1] = BUTTON_TEXTCOLOR1_DEFAULT,		//.aTextColor[1]
	.aTextColor[2] = BUTTON_TEXTCOLOR2_DEFAULT,		//.aTextColor[2]
	.FocusColor = BUTTON_FOCUSCOLOR_DEFAULT,		//.FocusColor
	.pFont = BUTTON_FONT_DEFAULT,			//.pFont
	.Align = BUTTON_ALIGN_DEFAULT			//.Align
};
#else
BUTTON_PROPS BUTTON__DefaultProps = {
	BUTTON_BKCOLOR0_DEFAULT,		//.aBkColor[0]
	BUTTON_BKCOLOR1_DEFAULT,		//.aBkColor[1]
	BUTTON_BKCOLOR2_DEFAULT,		//.aBkColor[2]
	BUTTON_TEXTCOLOR0_DEFAULT,		//.aTextColor[0]
	BUTTON_TEXTCOLOR1_DEFAULT,		//.aTextColor[1]
	BUTTON_TEXTCOLOR2_DEFAULT,		//.aTextColor[2]
	BUTTON_FOCUSCOLOR_DEFAULT,		//.FocusColor
	BUTTON_FONT_DEFAULT,			//.pFont
	BUTTON_ALIGN_DEFAULT			//.Align
};
#endif
BUTTON_STYLE BUTTON_DefaultPressStyle = {
	BUTTON_STYLE_RADIUS_DEF,				//.Radius
	BUTTON_STYLE_OPACITY_DEF,				//.Opacity
	BUTTON_STYLE_PRESS_MAIN_COLOR_DEF,		//.MainColor
	BUTTON_STYLE_PRESS_GRAD_COLOR_DEF,		//.GradColor
};
BUTTON_STYLE BUTTON_DefaultRelStyle = {
	BUTTON_STYLE_RADIUS_DEF,				//.Radius
	BUTTON_STYLE_OPACITY_DEF,				//.Opacity
	BUTTON_STYLE_REL_MAIN_COLOR_DEF,		//.MainColor
	BUTTON_STYLE_REL_GRAD_COLOR_DEF,		//.GradColor
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
static void _Paint(BUTTON_Obj* pObj, BUTTON_Handle hObj)
{
	const char* s = NULL;
	I32 State, PressedState, ColorIndex;
	GUI_RECT rClient, rInside, rButton, iRect;
	State = pObj->Widget.State;
	PressedState = (State & BUTTON_STATE_PRESSED) ? 1 : 0;
	ColorIndex   = (WM__IsEnabled(hObj)) ? PressedState : 2;
	//WM_GetInvalidRect(hObj, &iRect);
	GUI_SetFont(pObj->Props.pFont);
	if (pObj->hpText) {
		s = (const char*) GUI_ALLOC_h2p(pObj->hpText);
	}
	GUI_GetClientRect(&rClient);
	WM_GetClientRectEx(hObj, &rButton);
	/* Start drawing */
	rInside = rClient;
	/* Draw the 3D effect (if configured) */
	#if BUTTON_USE_3D
	{
		I32 EffectSize;
		if(!WM_GetHasTrans(hObj)){
			if (PressedState == 0) {
				if(pObj->NewStyle){
					GUI_DrawRectMainMiddle(&rButton, &pObj->Style[0]);
					GUI_DrawRectMainCorner(&rButton, &pObj->Style[0]);
				}else{
					pObj->Widget.pEffect->pfDrawUp();  /* _WIDGET_EFFECT_3D_DrawUp(); */
				}
				EffectSize = pObj->Widget.pEffect->EffectSize;
			}else{
				if(pObj->NewStyle){
					GUI_DrawRectMainMiddle(&rButton, &pObj->Style[1]);
					GUI_DrawRectMainCorner(&rButton, &pObj->Style[1]);
				}else{
					pObj->Widget.pEffect->pfDrawDown();
				}
				EffectSize = 1;
			}
		}else{
			if (PressedState == 0) {
				EffectSize = pObj->Widget.pEffect->EffectSize;
			}else{
				EffectSize = 1;
			}
		}
		GUI__ReduceRect(&rInside, &rInside, EffectSize);
	}
	#endif
	/* Draw background */
	//LCD_SetBkColor (pObj->Props.aBkColor[ColorIndex]);
	if((0 == pObj->NewStyle) && (!WM_GetHasTrans(hObj))){
		I16 RectHeight = 0;
		GUI__ReduceRect(&iRect, &rButton, pObj->Widget.pEffect->EffectSize);
		RectHeight = GUI_RectGetHeight(&rButton);
		LCD_SetBkColor(0xfff3f3f3);
		GUI_ClearRect(iRect.x0, iRect.y0, iRect.x1, iRect.y0 + RectHeight/2);
		LCD_SetBkColor(0xffdfdfdf);
		GUI_ClearRect(iRect.x0, iRect.y0 + RectHeight/2, iRect.x1, iRect.y1);
		//WM_SetUserClipRect(&rInside);
		//GUI_Clear();
	}
	/* Draw the actual button (background and text) */
	{
		GUI_RECT r;
		r = rInside;
	#if BUTTON_USE_3D
		if (PressedState) {
			GUI_MoveRect(&r, BUTTON_3D_MOVE_X,BUTTON_3D_MOVE_Y);
		}
	#endif
		LCD_SetColor   (pObj->Props.aTextColor[ColorIndex]);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_DispStringInRect(s, &r, pObj->Props.Align);
	}
	/* Draw focus */
	if (State & BUTTON_STATE_FOCUS) {
	//LCD_SetColor(pObj->Props.FocusColor);
	//GUI_DrawFocusRect(&rClient, 2);
	}
	//WM_SetUserClipRect(NULL);
}

/*********************************************************************
*
*       _Delete
*
* Delete attached objects (if any)
*/
static void _Delete(BUTTON_Obj* pObj)
{
	GUI_ALLOC_FreePtr(&pObj->hpText);
}

/*********************************************************************
*
*       _OnButtonPressed
*/
static void _OnButtonPressed(BUTTON_Handle hObj, BUTTON_Obj* pObj)
{
	WIDGET_OrState(hObj, BUTTON_STATE_PRESSED);
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}

/*********************************************************************
*
*       _OnButtonReleased
*/
static void _OnButtonReleased(BUTTON_Handle hObj, BUTTON_Obj* pObj, I32 Notification)
{
	WIDGET_AndState(hObj, BUTTON_STATE_PRESSED);
	if (Notification == WM_NOTIFICATION_RELEASED) {
		GUI_DEBUG_LOG("BUTTON: Hit\n");
		GUI_StoreKey(pObj->Widget.Id);
	}
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, Notification);
	}
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(BUTTON_Handle hObj, BUTTON_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
#if BUTTON_REACT_ON_LEVEL
	if (!pMsg->Data.p) {  /* Mouse moved out */
		_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_MOVED_OUT);
	} else if ((!pState->Pressed) && (pObj->Widget.State & BUTTON_STATE_PRESSED)) {
		_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_MOVED_OUT);
	}
#else
	if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
		if (pState->Pressed) {
			if ((pObj->Widget.State & BUTTON_STATE_PRESSED) == 0){
				_OnButtonPressed(hObj, pObj);
			}
		} else {
			/* React only if button was pressed before ... avoid problems with moving / hiding windows above (such as dropdown) */
			if (pObj->Widget.State & BUTTON_STATE_PRESSED) {
				_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
			}
		}
	} else {
		_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_MOVED_OUT);
	}
#endif
}

/*********************************************************************
*
*       _OnPidStateChange
*/
#if BUTTON_REACT_ON_LEVEL
static void _OnPidStateChange(BUTTON_Handle hObj, BUTTON_Obj * pObj, WM_MESSAGE * pMsg)
{
	const WM_PID_STATE_CHANGED_INFO * pState = (const WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
	if ((pState->StatePrev == 0) && (pState->State == 1)) {
		if ((pObj->Widget.State & BUTTON_STATE_PRESSED) == 0){
			_OnButtonPressed(hObj, pObj);
		}
	} else if ((pState->StatePrev == 1) && (pState->State == 0)) {
		if (pObj->Widget.State & BUTTON_STATE_PRESSED) {
			_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
		}
	}
}
#endif

/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
BUTTON_Obj * BUTTON_h2p(BUTTON_Handle h)
{
	BUTTON_Obj * p = (BUTTON_Obj *)GUI_ALLOC_h2p(h);
	if (p) {
		if (p->DebugId != BUTTON_ID) {
			GUI_DEBUG_ERROROUT("BUTTON.c: Wrong handle type or Object not init'ed");
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
*       BUTTON_Callback
*/
void BUTTON_Callback(WM_MESSAGE *pMsg)
{
	I32 PressedCnt, Key;
	BUTTON_Handle hObj = pMsg->hWin;
	BUTTON_Obj * pObj = (BUTTON_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
#if BUTTON_REACT_ON_LEVEL
		case WM_PID_STATE_CHANGED:
			_OnPidStateChange(hObj, pObj, pMsg);
		return;      /* Message handled. Do not call WM_DefaultProc, because the window may have been destroyed */
#endif
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
		return;      /* Message handled. Do not call WM_DefaultProc, because the window may have been destroyed */
		case WM_PAINT:
			GUI_DEBUG_LOG("BUTTON: _BUTTON_Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
		return;
		case WM_DELETE:
			GUI_DEBUG_LOG("BUTTON: _BUTTON_Callback(WM_DELETE)\n");
			_Delete(pObj);
		break;       /* No return here ... WM_DefaultProc needs to be called */
		case WM_KEY:
			PressedCnt = ((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt;
			Key        = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
			switch (Key) {
				case GUI_KEY_ENTER:
					if (PressedCnt > 0) {
						_OnButtonPressed(hObj, pObj);
						_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
						return;
					}
				break;
				case GUI_KEY_SPACE:
					if (PressedCnt > 0) {
						_OnButtonPressed(hObj, pObj);
					} else {
						_OnButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
					}
				return;
				default:
				break;
			}
		break;
		default:
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
/*********************************************************************
*
*       BUTTON_CreateEx
*/
BUTTON_Handle BUTTON_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 WinFlags, I32 ExFlags, I32 Id)
{
	BUTTON_Handle hObj;
	GUI_USE_PARA(ExFlags);
	/* Create the window */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, BUTTON_Callback,
									sizeof(BUTTON_Obj) - sizeof(WM_Obj));
	if (hObj) {
		BUTTON_Obj * pObj = (BUTTON_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		/* init member variables */
		BUTTON_INIT_ID(pObj);
		pObj->Props = BUTTON__DefaultProps;
		pObj->Style[0] = BUTTON_DefaultPressStyle;
		pObj->Style[1] = BUTTON_DefaultRelStyle;
		pObj->NewStyle = 0;
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "BUTTON_Create failed")
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
*       BUTTON_SetText
*/
void BUTTON_SetText(BUTTON_Handle hObj, const char* s)
{
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		if (GUI__SetText(&pObj->hpText, s)) {
			BUTTON_Invalidate(hObj);
		}
	}
}

/*********************************************************************
*
*       BUTTON_SetFont
*/
void BUTTON_SetFont(BUTTON_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont)
{
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		pObj->Props.pFont = pfont;
		BUTTON_Invalidate(hObj);
	}
}

/*********************************************************************
*
*       BUTTON_SetBkColor
*/
void BUTTON_SetBkColor(BUTTON_Handle hObj,U32 Index, GUI_COLOR Color)
{
	if (hObj && (Index <= 2)) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		pObj->Props.aBkColor[Index] = Color;
		BUTTON_Invalidate(hObj);
	}
}

/*********************************************************************
*
*       BUTTON_SetTextColor
*/
void BUTTON_SetTextColor(BUTTON_Handle hObj,U32 Index, GUI_COLOR Color)
{
	if (hObj && (Index <= 2)) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		pObj->Props.aTextColor[Index] = Color;
		BUTTON_Invalidate(hObj);
	}
}

/*********************************************************************
*
*       BUTTON_SetState
*/
void BUTTON_SetState(BUTTON_Handle hObj, I32 State)
{
	WIDGET_SetState(hObj, State);
}

/*********************************************************************
*
*       BUTTON_SetPressed
*/
void BUTTON_SetPressed(BUTTON_Handle hObj, I32 State)
{
	if (State) {
		WIDGET_OrState(hObj, BUTTON_STATE_PRESSED);
	} else {
		WIDGET_AndState(hObj, BUTTON_STATE_PRESSED);
	}
}

/*********************************************************************
*
*       BUTTON_SetFocussable
*/
void BUTTON_SetFocussable(BUTTON_Handle hObj, I32 State)
{
	if (State) {
		WIDGET_OrState(hObj, WIDGET_STATE_FOCUSSABLE);
	} else {
		WIDGET_AndState(hObj, WIDGET_STATE_FOCUSSABLE);
	}
}

void BUTTON_EnableNewStyle(BUTTON_Handle hObj)
{
	if (hObj) {
	    BUTTON_Obj* pObj;
	    pObj = BUTTON_H2P(hObj);
	    if(1 != pObj->NewStyle){
	    	pObj->NewStyle = 1;
	    	BUTTON_Invalidate(hObj);
	    }
	  }
}
void BUTTON_DisableNewStyle(BUTTON_Handle hObj)
{
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		if(0 != pObj->NewStyle){
			pObj->NewStyle = 0;
			BUTTON_Invalidate(hObj);
		}
	  }
}

void BUTTON_SetPressNewStyle(BUTTON_Handle hObj, GUI_FullRectStyle *pStyle)
{
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		if((pObj->Style[0].Radius != pStyle->Radius) ||
				(pObj->Style[0].MainColor != pStyle->MainColor) ||
				(pObj->Style[0].GradColor != pStyle->GradColor)){
			pObj->Style[0].Radius = pStyle->Radius;
			pObj->Style[0].MainColor = pStyle->MainColor;
			pObj->Style[0].GradColor = pStyle->GradColor;
			BUTTON_Invalidate(hObj);
		}
	}
}
void BUTTON_SetRelNewStyle(BUTTON_Handle hObj, GUI_FullRectStyle *pStyle)
{
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		if((pObj->Style[1].Radius != pStyle->Radius) ||
				(pObj->Style[1].MainColor != pStyle->MainColor) ||
				(pObj->Style[1].GradColor != pStyle->GradColor)){
			pObj->Style[1].Radius = pStyle->Radius;
			pObj->Style[1].MainColor = pStyle->MainColor;
			pObj->Style[1].GradColor = pStyle->GradColor;
			BUTTON_Invalidate(hObj);
		}
	}
}
#else                            /* Avoid problems with empty object modules */
  void BUTTON_C(void) {}
#endif /* GUI_WINSUPPORT */



	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
