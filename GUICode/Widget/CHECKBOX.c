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
File        : CHECKBOX.c
Purpose     : Implementation of checkbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>
#include "GUI_Protected.h"
#include "CHECKBOX_Private.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && CHECKBOX_SUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef   CHECKBOX_FONT_DEFAULT
	#define CHECKBOX_FONT_DEFAULT GUI_DEFAULT_FONT
#endif

/* Define default images */
#ifndef   CHECKBOX_IMAGE0_DEFAULT
  #define CHECKBOX_IMAGE0_DEFAULT &CHECKBOX__abmCheck[0]
#endif

#ifndef   CHECKBOX_IMAGE1_DEFAULT
  #define CHECKBOX_IMAGE1_DEFAULT &CHECKBOX__abmCheck[1]
#endif

/* Define widget background color */
#ifndef   CHECKBOX_BKCOLOR_DEFAULT
  #define CHECKBOX_BKCOLOR_DEFAULT 0xC0C0C0           /* Text background color */
#endif

#ifndef   CHECKBOX_SPACING_DEFAULT
  #define CHECKBOX_SPACING_DEFAULT 4
#endif

#ifndef   CHECKBOX_TEXTCOLOR_DEFAULT
  #define CHECKBOX_TEXTCOLOR_DEFAULT GUI_WHITE
#endif

#ifndef   CHECKBOX_FOCUSCOLOR_DEFAULT
  #define CHECKBOX_FOCUSCOLOR_DEFAULT GUI_BLACK
#endif

#ifndef   CHECKBOX_TEXTALIGN_DEFAULT
  #define CHECKBOX_TEXTALIGN_DEFAULT (GUI_TA_LEFT | GUI_TA_VCENTER)
#endif

#ifndef CHECKBOX_STYLE_CIRCLE_RADIUS_EXT
#define CHECKBOX_STYLE_CIRCLE_RADIUS_EXT 		8
#endif
#ifndef CHECKBOX_STYLE_CIRCLE_RADIUS_IN
#define CHECKBOX_STYLE_CIRCLE_RADIUS_IN 		5
#endif
#ifndef CHECKBOX_STYLE_CIRCLE_COLOR_EXT
#define CHECKBOX_STYLE_CIRCLE_COLOR_EXT 			CHECKBOX_TEXTCOLOR_DEFAULT
#endif
#ifndef CHECKBOX_STYLE_CIRCLE_COLOR_IN
#define CHECKBOX_STYLE_CIRCLE_COLOR_IN 			CHECKBOX_TEXTCOLOR_DEFAULT
#endif
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

CHECKBOX_PROPS CHECKBOX__DefaultProps =
{
	CHECKBOX_FONT_DEFAULT,					//.pFont
	CHECKBOX_BKCOLOR0_DEFAULT,				//.aBkColorBox[0]
	CHECKBOX_BKCOLOR1_DEFAULT,				//.aBkColorBox[1]
	CHECKBOX_BKCOLOR_DEFAULT,				//.BkColor
	CHECKBOX_TEXTCOLOR_DEFAULT,				//.TextColor
	CHECKBOX_FOCUSCOLOR_DEFAULT,			//.FocusColor
	CHECKBOX_TEXTALIGN_DEFAULT,				//.Align
	CHECKBOX_SPACING_DEFAULT,				//.Spacing
	0,										//.StyleCircleUsed
	CHECKBOX_STYLE_CIRCLE_RADIUS_EXT,		//.StyleCircle.RadiusExt
	CHECKBOX_STYLE_CIRCLE_RADIUS_IN,		//.StyleCircle.RadiusIn
	CHECKBOX_STYLE_CIRCLE_COLOR_EXT,		//.StyleCircle.ColorExt
	CHECKBOX_STYLE_CIRCLE_COLOR_IN,			//.StyleCircle.ColorIn
	NULL,									//.apBm[0]
	NULL,									//.apBm[1]
	CHECKBOX_IMAGE0_DEFAULT,				//.apBm[2]
	CHECKBOX_IMAGE1_DEFAULT,				//.apBm[3]
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
static void _Paint(CHECKBOX_Obj* pObj, CHECKBOX_Handle hObj)
{
	GUI_RECT RectBox = {0};
	I32 ColorIndex, EffectSize, Index;
	EffectSize = pObj->Widget.pEffect->EffectSize;
	ColorIndex = WM__IsEnabled(hObj);
	/* Clear inside ... Just in case      */
	/* Fill with parents background color */
	if (pObj->Props.BkColor == GUI_INVALID_COLOR) {
		LCD_SetBkColor(WIDGET__GetBkColor(hObj));
	} else {
		LCD_SetBkColor(pObj->Props.BkColor);
	}
	GUI_Clear();
	if(pObj->Props.StyleCircleUsed){
		I16 BoxHeight = 0;
		BoxHeight = WM_GetWindowSizeY(hObj);
		GUI_SetColor(pObj->Props.StyleCircle.ColorExt);
		GUI_AA_DrawArc(pObj->Props.StyleCircle.RadiusExt + 3, BoxHeight/2, pObj->Props.StyleCircle.RadiusExt,
				pObj->Props.StyleCircle.RadiusExt, 0, 360);
		if(pObj->CurrentState){
			GUI_SetColor(pObj->Props.StyleCircle.ColorIn);
			GUI_AA_FillCircle(pObj->Props.StyleCircle.RadiusExt + 3, BoxHeight/2, pObj->Props.StyleCircle.RadiusIn);
		}
		RectBox.x1 = pObj->Props.StyleCircle.RadiusExt * 2 + 3;
	}else{
		/* Get size from bitmap */
		RectBox.x1 = pObj->Props.apBm[CHECKBOX_BI_ACTIV]->XSize - 1 + 2 * EffectSize;
		RectBox.y1 = pObj->Props.apBm[CHECKBOX_BI_ACTIV]->YSize - 1 + 2 * EffectSize;
		WM_SetUserClipRect(&RectBox);
		/* Clear inside  ... Just in case */
		LCD_SetBkColor(pObj->Props.aBkColorBox[ColorIndex]);
		GUI_Clear();
		Index = pObj->CurrentState * 2 + ColorIndex;
		if (pObj->Props.apBm[Index]) {
			GUI_DrawBitmap(pObj->Props.apBm[Index], EffectSize, EffectSize);
		}
		/* Draw the effect arround the box */
		WIDGET__EFFECT_DrawDownRect(&pObj->Widget, &RectBox);
		WM_SetUserClipRect(NULL);
	}
	/* Draw text if needed */
	if (pObj->hpText) {
		const char * s;
		GUI_RECT RectText;
		/* Draw the text */
		s = (const char *) GUI_ALLOC_h2p(pObj->hpText);
		WM_GetClientRect(&RectText);
		RectText.x0 += RectBox.x1 + 1 + pObj->Props.Spacing;
		GUI_SetTextMode(GUI_TM_TRANS);
		LCD_SetColor(pObj->Props.TextColor);
		GUI_SetFont(pObj->Props.pFont);
		GUI_DispStringInRect(s, &RectText, pObj->Props.Align);
		/* Draw focus rectangle */
		if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
			I32 xSizeText = GUI_GetStringDistX(s);
			I32 ySizeText = GUI_GetFontSizeY();
			GUI_RECT RectFocus = RectText;
			switch (pObj->Props.Align & ~(GUI_TA_HORIZONTAL)) {
				case GUI_TA_VCENTER:
					RectFocus.y0 = (RectText.y1 - ySizeText + 1) / 2;
				break;
				case GUI_TA_BOTTOM:
					RectFocus.y0 = RectText.y1 - ySizeText;
				break;
			}
			switch (pObj->Props.Align & ~(GUI_TA_VERTICAL)) {
				case GUI_TA_HCENTER:
					RectFocus.x0 += ((RectText.x1 - RectText.x0) - xSizeText) / 2;
				break;
				case GUI_TA_RIGHT:
					RectFocus.x0 += (RectText.x1 - RectText.x0) - xSizeText;
				break;
			}
			RectFocus.x1 = RectFocus.x0 + xSizeText - 1;
			RectFocus.y1 = RectFocus.y0 + ySizeText - 1;
			LCD_SetColor(pObj->Props.FocusColor);
			//GUI_DrawFocusRect(&RectFocus, -1);
		}
	}
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(CHECKBOX_Handle hObj, CHECKBOX_Obj* pObj, WM_MESSAGE*pMsg)
{
	I32 Notification = 0;
	I32 Hit = 0;
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
		if (!WM_HasCaptured(hObj)) {
			if (pState->Pressed) {
				WM_SetCapture(hObj, 1);
				CHECKBOX_SetState(hObj, (pObj->CurrentState + 1) % pObj->NumStates);
				Notification = WM_NOTIFICATION_CLICKED;
			} else {
				Hit =1;
				Notification = WM_NOTIFICATION_RELEASED;
			}
		}
	} else {
		Notification = WM_NOTIFICATION_MOVED_OUT;
	}
	WM_NotifyParent(hObj, Notification);
	if (Hit == 1) {
		GUI_DEBUG_LOG("CHECKBOX: Hit\n");
		GUI_StoreKey(pObj->Widget.Id);
	}
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(CHECKBOX_Handle hObj, CHECKBOX_Obj * pObj, WM_MESSAGE * pMsg)
{
	WM_KEY_INFO * pKeyInfo;
	if (WM__IsEnabled(hObj)) {
		pKeyInfo = (WM_KEY_INFO *)(pMsg->Data.p);
		if (pKeyInfo->PressedCnt > 0) {
			switch (pKeyInfo->Key) {
			case GUI_KEY_SPACE:
				CHECKBOX_SetState(hObj, (pObj->CurrentState + 1) % pObj->NumStates);
				break;                    /* Send to parent by not doing anything */
			}
		}
	}
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(CHECKBOX_Obj * pObj)
{
	/* Delete attached objects (if any) */
	GUI_DEBUG_LOG("CHECKBOX: Delete() Deleting attached items");
	GUI_ALLOC_FreePtr(&pObj->hpText);
}

/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
CHECKBOX_Obj * CHECKBOX_h2p(CHECKBOX_Handle h)
{
	CHECKBOX_Obj * p = (CHECKBOX_Obj *)GUI_ALLOC_h2p(h);
	if (p) {
		if (p->DebugId != CHECKBOX_ID) {
			GUI_DEBUG_ERROROUT("CHECKBOX.c: Wrong handle type or Object not init'ed");
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
*       CHECKBOX_Callback
*/
void CHECKBOX_Callback (WM_MESSAGE *pMsg)
{
	CHECKBOX_Handle hObj;
	CHECKBOX_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (CHECKBOX_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_KEY:
			_OnKey(hObj, pObj, pMsg);
		break;
		case WM_PAINT:
			GUI_DEBUG_LOG("CHECKBOX: _Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
		return;
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
		break;
		case WM_DELETE:
			GUI_DEBUG_LOG("CHECKBOX: _Callback(WM_DELETE)\n");
			_Delete(pObj);
		break;       /* No return here ... WM_DefaultProc needs to be called */
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
*       CHECKBOX_CreateEx
*/
CHECKBOX_Handle CHECKBOX_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                    I32 WinFlags, I32 ExFlags, I32 Id)
{
	CHECKBOX_Handle hObj;
	GUI_USE_PARA(ExFlags);
	/* Calculate size if needed */
	if ((xsize == 0) || (ysize == 0)) {
		I32 EffectSize;
		EffectSize = WIDGET_GetDefaultEffect()->EffectSize;
		if (xsize == 0) {
			xsize = CHECKBOX__DefaultProps.apBm[CHECKBOX_BI_ACTIV]->XSize + 2 * EffectSize;
		}
		if (ysize == 0) {
			ysize = CHECKBOX__DefaultProps.apBm[CHECKBOX_BI_ACTIV]->YSize + 2 * EffectSize;
		}
	}
	/* Create the window */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, CHECKBOX_Callback,
	                    sizeof(CHECKBOX_Obj) - sizeof(WM_Obj));
	if (hObj) {
		CHECKBOX_Obj* pObj = (CHECKBOX_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
		CHECKBOX_INIT_ID(pObj);
		/* init member variables */
		pObj->Props = CHECKBOX__DefaultProps;
		pObj->NumStates   = 2; /* Default behaviour is 2 states: checked and unchecked */
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "CHECKBOX_Create failed")
	}
	return hObj;
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_C(void);
  void CHECKBOX_C(void) {}
#endif  /* #if GUI_WINSUPPORT */


	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
