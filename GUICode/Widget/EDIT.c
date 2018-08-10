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
File        : EDIT.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>

#define EDIT_C       /* Required to generate intermodule data */

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"
#include "GUI_ReDefine.h"

#if GUI_WINSUPPORT && EDIT_SUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef EDIT_FONT_DEFAULT
#define EDIT_FONT_DEFAULT		GUI_DEFAULT_FONT
#endif

#ifndef EDIT_ALIGN_DEFAULT
  #define EDIT_ALIGN_DEFAULT GUI_TA_LEFT | GUI_TA_VCENTER
#endif

/* Define colors */
#ifndef EDIT_BKCOLOR0_DEFAULT
  #define EDIT_BKCOLOR0_DEFAULT 0xC0C0C0
#endif

#ifndef EDIT_BKCOLOR1_DEFAULT
  #define EDIT_BKCOLOR1_DEFAULT GUI_WHITE
#endif

#ifndef EDIT_TEXTCOLOR0_DEFAULT
  #define EDIT_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef EDIT_TEXTCOLOR1_DEFAULT
  #define EDIT_TEXTCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef EDIT_BORDER_DEFAULT
  #define EDIT_BORDER_DEFAULT 1
#endif

#define BLINK_PERIOD	500		//500MS

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
EDIT_PROPS EDIT__DefaultProps = {
		EDIT_ALIGN_DEFAULT,				//.Align
		EDIT_BORDER_DEFAULT,			//.Border
		EDIT_FONT_DEFAULT,				//.pFont
		EDIT_TEXTCOLOR0_DEFAULT,		//.aTextColor[0]
		EDIT_TEXTCOLOR1_DEFAULT,		//.aTextColor[1]
		EDIT_BKCOLOR0_DEFAULT,			//.aBkColor[0]
		EDIT_BKCOLOR1_DEFAULT			//.aBkColor[1]
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
static void _Paint(EDIT_Obj* pObj, EDIT_Handle hObj)
{
	GUI_RECT rFillRect, rInside, rText, rInvert;
	const char GUI_UNI_PTR * pText = NULL;
	I32 IsEnabled, CursorWidth;
	IsEnabled = WM__IsEnabled(hObj);
	/* Set colors and font */
	//LCD_SetBkColor(pObj->Props.aBkColor[IsEnabled]);
	//LCD_SetColor(pObj->Props.aTextColor[0]);
	GUI_SetFont(pObj->Props.pFont);
	/* Calculate size */
	WIDGET__GetInsideRect(&pObj->Widget, &rFillRect);
	if (pObj->hpText) {
		pText = (const char*) GUI_ALLOC_h2p(pObj->hpText);
	}
	rInside = rFillRect;
	rInside.x0 += pObj->Props.Border + EDIT_XOFF;
	rInside.x1 -= pObj->Props.Border + EDIT_XOFF;
	GUI__CalcTextRect(pText, &rInside, &rText, pObj->Props.Align);
	/* Calculate position and size of cursor */
	if (pObj->Widget.State & WIDGET_STATE_FOCUS){
		I32 NumChars;
		CursorWidth = ((pObj->XSizeCursor > 0) ? (pObj->XSizeCursor) : (1));
		NumChars    = GUI__GetNumChars(pText);
		if (pText){
			U16 Char;
			I32 i, IsRTL = 0;
			if ((pObj->EditMode != GUI_EDIT_MODE_INSERT) || (pObj->SelSize)) {
				if (pObj->CursorPos < NumChars) {
					if (pObj->SelSize) {
						CursorWidth = 0;
						for (i = pObj->CursorPos; i < (I32)(pObj->CursorPos + pObj->SelSize); i++) {
							Char = GUI__GetCursorCharacter(pText, i, NumChars, 0);
							CursorWidth += GUI_GetCharDistX(Char);
						}
						if (!CursorWidth) {
							CursorWidth = 1;
						}
					} else {
						Char = GUI__GetCursorCharacter(pText, pObj->CursorPos, NumChars, &IsRTL);
						CursorWidth = GUI_GetCharDistX(Char);
					}
				}
			}
			rInvert = rText;
			if (IsRTL){
				rInvert.x0 -= CursorWidth;
			}
			rInvert.x0 += GUI__GetCursorPosX(pText, pObj->CursorPos, NumChars);
		}
	}
  /* WM loop */
	/* Set clipping rectangle */
	WM_SetUserClipRect(&rFillRect);
	LCD_SetBkColor(pObj->Props.aBkColor[IsEnabled]);
	//GUI_Clear();
	LCD_SetColor(pObj->Props.aTextColor[0]);
	/* Display text */
	WIDGET__FillStringInRect(pText, &rFillRect, &rInside, &rText);
	/* Display cursor if needed */
	if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
		GUI_RectSet(&pObj->Cursor.Rect, rInvert.x0 , rInvert.y0, rInvert.x0 + CursorWidth - 1, rInvert.y1);
		if(pObj->Cursor.IsShow){
			LCD_SetBkColor(pObj->Props.aTextColor[0]);
			GUI_DrawRectEx(&pObj->Cursor.Rect);
		}
	}
	WM_SetUserClipRect(NULL);
	/* Draw the 3D effect (if configured) */
	//WIDGET__EFFECT_DrawDown(&pObj->Widget);
	pObj->Widget.pEffect->pfDrawUp();
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(EDIT_Obj* pObj)
{
	/*if(pObj->hTimer)
	{
		GUI_TIMER_Delete(pObj->hTimer);
		pObj->hTimer = 0;
	}*/
	GUI_ALLOC_FreePtr(&pObj->hpText);
}

/*********************************************************************
*
*       _IncrementBuffer
*
* Increments the buffer size by AddBytes.
*/
static I32 _IncrementBuffer(EDIT_Obj* pObj, unsigned AddBytes)
{
	WM_HMEM hNew;
	I32 NewSize;
	NewSize = pObj->BufferSize + AddBytes;
	hNew    = GUI_ALLOC_Realloc(pObj->hpText, NewSize);
	if (hNew) {
		if (!(pObj->hpText)) {
			char* pText;
			pText  = (char*) GUI_ALLOC_h2p(hNew);
			*pText = 0;
		}
		pObj->BufferSize = NewSize;
		pObj->hpText     = hNew;
		return 1;
	}
	return 0;
}

/*********************************************************************
*
*       _IsSpaceInBuffer
*
* Checks the available space in the buffer. If there is not enough
* space left this function attempts to get more.
*
* Returns:
*  1 = requested space is available
*  0 = failed to get enough space
*/
static I32 _IsSpaceInBuffer(EDIT_Obj* pObj, I32 BytesNeeded)
{
	I32 NumBytes = 0;
	if (pObj->hpText) {
		NumBytes = GUI_strlen((char*)GUI_ALLOC_h2p(pObj->hpText));
	}
	BytesNeeded = (BytesNeeded + NumBytes + 1) - pObj->BufferSize;
	if (BytesNeeded > 0) {
		if (!_IncrementBuffer(pObj, BytesNeeded + EDIT_REALLOC_SIZE)) {
			return 0;
		}
	}
	return 1;
}

/*********************************************************************
*
*       _IsCharsAvailable
*
* Checks weither the maximum number of characters is reached or not.
*
* Returns:
*  1 = requested number of chars is available
*  0 = maximum number of chars have reached
*/
static I32 _IsCharsAvailable(EDIT_Obj* pObj, I32 CharsNeeded)
{
	if ((CharsNeeded > 0) && (pObj->MaxLen > 0)) {
		I32 NumChars = 0;
		if (pObj->hpText) {
			NumChars = GUI__GetNumChars((char*)GUI_ALLOC_h2p(pObj->hpText));
		}
		if ((CharsNeeded + NumChars) > pObj->MaxLen) {
			return 0;
		}
	}
	return 1;
}

/*********************************************************************
*
*       _DeleteChar
*
* Deletes a character at the current cursor position and moves
* all bytes after the cursor position.
*/
static void _DeleteChar(EDIT_Handle hObj, EDIT_Obj* pObj)
{
	if (pObj->hpText) {
		unsigned CursorOffset;
		char* pText;
		pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
		CursorOffset = GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
		if (CursorOffset < GUI_strlen(pText)) {
			I32 NumBytes;
			pText += CursorOffset;
			NumBytes = GUI_UC_GetCharSize(pText);
			GUI_strcpy(pText, pText + NumBytes);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
		}
	}
}

/*********************************************************************
*
*       _InsertChar
*
* Create space at the current cursor position and inserts a character.
*/
static I32 _InsertChar(EDIT_Handle hObj, EDIT_Obj* pObj, U16 Char)
{
	if (_IsCharsAvailable(pObj, 1)) {
		I32 BytesNeeded;
		BytesNeeded = GUI_UC__CalcSizeOfChar(Char);
		if (_IsSpaceInBuffer(pObj, BytesNeeded)) {
			I32 CursorOffset;
			char* pText;
			pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
			CursorOffset = GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
			pText += CursorOffset;
			GUI_memmove(pText + BytesNeeded, pText, GUI_strlen(pText) + 1);
			GUI_UC_Encode(pText, Char);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
			return 1;
		}
	}
	return 0;
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(EDIT_Handle hObj, EDIT_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	GUI_USE_PARA(pObj);
	if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
		if (pState->Pressed) {
			GUI_DEBUG_LOG1("EDIT_Callback(WM_TOUCH, Pressed, Handle %d)\n",1);
			EDIT_SetCursorAtPixel(hObj, pState->x);
			WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
		} else {
			GUI_DEBUG_LOG1("EDIT_Callback(WM_TOUCH, Released, Handle %d)\n",1);
			WM_NotifyParent(hObj, WM_NOTIFICATION_RELEASED);
		}
	} else {
		GUI_DEBUG_LOG1("EDIT_Callback(WM_TOUCH, Moved out, Handle %d)\n",1);
		WM_NotifyParent(hObj, WM_NOTIFICATION_MOVED_OUT);
	}
}

/*********************************************************************
*
*       _SetValue
*/
static void _SetValue(EDIT_Handle hObj, I32 Value, I32 Unsigned)
{
	EDIT_Obj* pObj;
	if (hObj) {
		pObj = EDIT_H2P(hObj);
		/* Put in min/max range */
		if (Unsigned) {
			if ((unsigned)Value < (unsigned)pObj->Min) {
				Value = pObj->Min;
			}
			if ((unsigned)Value > (unsigned)pObj->Max) {
				Value = pObj->Max;
			}
		} else {
			if (Value < pObj->Min) {
				Value = pObj->Min;
			}
			if (Value > pObj->Max) {
				Value = pObj->Max;
			}
		}
		if (pObj->CurrentValue != (U32)Value) {
			pObj->CurrentValue = Value;
			if (pObj->pfUpdateBuffer) {
				pObj->pfUpdateBuffer(hObj);
			}
			WM_InvalidateWindow(hObj);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
		}
	}
}

/*********************************************************************
*
*       Private routines:
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
EDIT_Obj * EDIT_h2p(EDIT_Handle h)
{
	EDIT_Obj * p = (EDIT_Obj *)GUI_ALLOC_h2p(h);
	if (p) {
		if (p->DebugId != EDIT_ID) {
			GUI_DEBUG_ERROROUT("EDIT.c: Wrong handle type or Object not init'ed");
			return 0;
		}
	}
	return p;
}
#endif

/*********************************************************************
*
*       EDIT__GetCurrentChar
*/
U16 EDIT__GetCurrentChar(EDIT_Obj* pObj)
{
	U16 Char = 0;
	if (pObj->hpText) {
		const char* pText;
		pText  = (const char*) GUI_ALLOC_h2p(pObj->hpText);
		pText += GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
		Char   = GUI_UC_GetCharCode(pText);
	}
	return Char;
}

/*********************************************************************
*
*       EDIT__SetCursorPos
*
* Sets a new cursor position.
*/
void EDIT__SetCursorPos(EDIT_Obj* pObj, I32 CursorPos)
{
	if (pObj->hpText) {
		char* pText;
		I32 NumChars, Offset;
		pText    = (char*) GUI_ALLOC_h2p(pObj->hpText);
		NumChars = GUI__GetNumChars(pText);
		Offset   = (pObj->EditMode == GUI_EDIT_MODE_INSERT) ? 0 : 1;
		if (CursorPos < 0) {
			CursorPos = 0;
		}
		if (CursorPos > NumChars) {
			CursorPos = NumChars;
		}
		if (CursorPos > (pObj->MaxLen - Offset)) {
			CursorPos = pObj->MaxLen - Offset;
		}
		if (pObj->CursorPos != CursorPos) {
			pObj->CursorPos = CursorPos;
		}
		pObj->SelSize = 0;
	}
}

/*********************************************************************
*
*       EDIT__SetValueUnsigned
*/
void EDIT__SetValueUnsigned(EDIT_Handle hObj, I32 Value)
{
	_SetValue(hObj, Value, 1);
}
static void __EditTimercb(GUI_TIMER_MESSAGE* pTM)
{
	EDIT_Obj*   pObj;
	/*WM_Obj * pWin;
	GUI_RECT rect,editrect;*/
	pObj = (EDIT_Obj *)GUI_ALLOC_h2p(pTM->Context);
//	pWin = (WM_Obj *)GUI_ALLOC_h2p(pTM->Context);
//	rect = pObj->Cursor.Rect;
//	editrect = pWin->Rect;
	if(pObj->Cursor.IsShow){
		pObj->Cursor.IsShow = 0;
//		LCD_SetColor(pObj->Props.aTextColor[0]);
	}else{
		pObj->Cursor.IsShow = 1;
//		LCD_SetColor(pObj->Props.aBkColor[1]);
	}
//	if(rect.x1 < editrect.x1){
//		LCD_FillRect(rect.x0,rect.y0,rect.x1,rect.y1);
//	}
	//WM__InvalidateRectEx(&pObj->Cursor.Rect, pTM->Context);
	//WM_InvalidateWindow(pTM->Context);
	WM_InvalidateRect(pTM->Context, &pObj->Cursor.Rect);
	GUI_TIMER_Restart(pObj->hTimer);
}
static void __EditTimerCreat(EDIT_Handle hObj,EDIT_Obj* pObj,WM_MESSAGE * pMsg)
{
	if(0 == pObj->CursorBlink){
		return;
	}
	if(WM_SET_FOCUS == pMsg->MsgId){
		if((1 == pMsg->Data.v) && (!pObj->hTimer)){
			pObj->hTimer = GUI_TIMER_Create(__EditTimercb, WM_TIMER + 1, hObj, 0);
			GUI_TIMER_SetPeriod(pObj->hTimer,BLINK_PERIOD);
			GUI_TIMER_Restart(pObj->hTimer);
		}else if(pObj->hTimer){
			pObj->Cursor.IsShow = 0;
			GUI_TIMER_Delete(pObj->hTimer);
			pObj->hTimer = 0;
		}
	}
}

/*********************************************************************
*
*       Exported routines:  Callback
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_Callback
*/
void EDIT_Callback (WM_MESSAGE * pMsg)
{
	I32 IsEnabled;
	EDIT_Handle hObj;
	EDIT_Obj*   pObj;
	hObj = (EDIT_Handle) pMsg->hWin;
	pObj = (EDIT_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	IsEnabled = WM__IsEnabled(hObj);
	/* Let widget handle the standard messages */
	//eDbug("pMsg Id = %d\n",pMsg->MsgId);
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		__EditTimerCreat(hObj, pObj, pMsg);
		return;
	}
	switch (pMsg->MsgId) {
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
		break;
		case WM_PAINT:
			GUI_DEBUG_LOG("EDIT: _Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
		return;
		case WM_DELETE:
			GUI_DEBUG_LOG("EDIT: _Callback(WM_DELETE)\n");
			_Delete(pObj);
		break;       /* No return here ... WM_DefaultProc needs to be called */
		case WM_KEY:
			if (IsEnabled) {
				if ( ((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt >0) {
					I32 Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
					switch (Key) {
						case GUI_KEY_ENTER:
						case GUI_KEY_ESCAPE:
						case GUI_KEY_TAB:
						case GUI_KEY_BACKTAB:
							break;                    /* Send to parent by not doing anything */
						default:
							EDIT_AddKey(hObj, Key);
							return;
					}
				}
			}
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
*       EDIT_CreateEx
*/
EDIT_Handle EDIT_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 WinFlags, I32 ExFlags,
                          I32 Id, I32 MaxLen)
{
	EDIT_Handle hObj;
	GUI_USE_PARA(ExFlags);
	/* Alloc memory for obj */
	//WinFlags |= WM_CF_LATE_CLIP;    /* Always use late clipping since widget is optimized for it. */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WM_CF_SHOW | WinFlags, EDIT_Callback,
									sizeof(EDIT_Obj) - sizeof(WM_Obj));
	if (hObj) {
		EDIT_Obj* pObj;
		pObj = (EDIT_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
		/* init member variables */
		EDIT_INIT_ID(pObj);
		pObj->Props         = EDIT__DefaultProps;
		pObj->XSizeCursor   = 1;
		pObj->MaxLen        = (MaxLen == 0) ? 8 : MaxLen;
		pObj->BufferSize    = 0;
		pObj->hpText        = 0;
		pObj->CursorBlink	= 1;
		pObj->hTimer		= 0;
		if (_IncrementBuffer(pObj, pObj->MaxLen + 1) == 0) {
			GUI_DEBUG_ERROROUT("EDIT_Create failed to alloc buffer");
			EDIT_Delete(hObj);
			hObj = 0;
		}
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
*       EDIT_SetCursorAtPixel
*/
void EDIT_SetCursorAtPixel(EDIT_Handle hObj, I32 xPos)
{
	if (hObj) {
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		if (pObj->hpText) {
			const GUI_FONT GUI_UNI_PTR *pOldFont;
			I32 xSize, TextWidth, NumChars;
			const char GUI_UNI_PTR * pText;
			pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
			pOldFont = GUI_SetFont(pObj->Props.pFont);
			xSize = WM_GetWindowSizeX(hObj);
			TextWidth = GUI_GetStringDistX(pText);
			switch (pObj->Props.Align & GUI_TA_HORIZONTAL) {
				case GUI_TA_HCENTER:
					xPos -= (xSize - TextWidth + 1) / 2;
				break;
				case GUI_TA_RIGHT:
					xPos -= xSize - TextWidth - (pObj->Props.Border + EDIT_XOFF);
				break;
				default:
					xPos -= (pObj->Props.Border + EDIT_XOFF) + pObj->Widget.pEffect->EffectSize;
			}
			NumChars = GUI__GetNumChars(pText);
			if (xPos < 0) {
				EDIT__SetCursorPos(pObj, 0);
			} else if (xPos > TextWidth) {
				EDIT__SetCursorPos(pObj, NumChars);
			} else {
				EDIT__SetCursorPos(pObj, GUI__GetCursorPosChar(pText, xPos, NumChars));
			}
			GUI_SetFont(pOldFont);
			EDIT_Invalidate(hObj);
		}
	}
}

/*********************************************************************
*
*       EDIT_AddKey
*/
void EDIT_AddKey(EDIT_Handle hObj, I32 Key)
{
	if (hObj) {
		U8 NeedInvalidate = 1;
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		if (pObj) {
			if (pObj->pfAddKeyEx) {
				pObj->pfAddKeyEx(hObj, Key);
			} else {
				switch (Key) {
				case GUI_KEY_UP:
					if (pObj->hpText) {
						char* pText;
						U16 Char;
						pText  = (char*) GUI_ALLOC_h2p(pObj->hpText);
						pText += GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
						Char   = GUI_UC_GetCharCode(pText);
						if (Char < 0x7f) {
							*pText = Char + 1;
							WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
						}
					}
				break;
				case GUI_KEY_DOWN:
					if (pObj->hpText) {
						char* pText;
						U16 Char;
						pText  = (char*) GUI_ALLOC_h2p(pObj->hpText);
						pText += GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
						Char   = GUI_UC_GetCharCode(pText);
						if (Char > 0x20) {
							*pText = Char - 1;
							WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
						}
					}
				break;
				case GUI_KEY_RIGHT:
					EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
				break;
				case GUI_KEY_LEFT:
					EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
				break;
				case GUI_KEY_BACKSPACE:
					EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
					_DeleteChar(hObj, pObj);
				break;
				case GUI_KEY_DELETE:
					_DeleteChar(hObj, pObj);
				break;
				case GUI_KEY_INSERT:
					if (pObj->EditMode == GUI_EDIT_MODE_OVERWRITE) {
						pObj->EditMode = GUI_EDIT_MODE_INSERT;
					} else {
						pObj->EditMode = GUI_EDIT_MODE_OVERWRITE;
						EDIT__SetCursorPos(pObj, pObj->CursorPos);
					}
				break;
				default:
					if (Key >= 0x20) {
						if (pObj->EditMode != GUI_EDIT_MODE_INSERT) {
							_DeleteChar(hObj, pObj);
						}
						if (_InsertChar(hObj, pObj, Key)) {
							EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
						}else{
							NeedInvalidate = 0;
						}
					}
				}
			}
			if(NeedInvalidate){
				EDIT_Invalidate(hObj);
			}
		}
	}
}

/*********************************************************************
*
*       EDIT_SetFont
*/
void EDIT_SetFont(EDIT_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont)
{
	EDIT_Obj* pObj;
	if (hObj == 0)
		return;
	pObj = EDIT_H2P(hObj);
	if (pObj) {
		pObj->Props.pFont = pfont;
		EDIT_Invalidate(hObj);
	}
}

/*********************************************************************
*
*       EDIT_SetBkColor
*/
void EDIT_SetBkColor(EDIT_Handle hObj, U32 Index, GUI_COLOR color)
{
	EDIT_Obj* pObj;
	if (hObj == 0)
		return;
	pObj = EDIT_H2P(hObj);
	if (pObj) {
		if (Index < GUI_COUNTOF(pObj->Props.aBkColor)) {
			pObj->Props.aBkColor[Index] = color;
			EDIT_Invalidate(hObj);
		}
	}
}

/*********************************************************************
*
*       EDIT_SetTextColor
*/
void EDIT_SetTextColor(EDIT_Handle hObj, U32 Index, GUI_COLOR color)
{
	EDIT_Obj* pObj;
	if (hObj == 0)
		return;
	pObj = EDIT_H2P(hObj);
	if (pObj) {
		if (Index < GUI_COUNTOF(pObj->Props.aTextColor)) {
			pObj->Props.aTextColor[Index] = color;
			EDIT_Invalidate(hObj);
		}
	}
}

/*********************************************************************
*
*       EDIT_SetText
*/
void EDIT_SetText(EDIT_Handle hObj, const char* s)
{
	if (hObj) {
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		if (s) {
			I32 NumBytesNew, NumBytesOld = 0;
			I32 NumCharsNew;
			if (pObj->hpText) {
				char* pText;
				pText       = (char*) GUI_ALLOC_h2p(pObj->hpText);
				NumBytesOld = GUI_strlen(pText) + 1;
			}
			NumCharsNew = GUI__GetNumChars(s);
			if (NumCharsNew > pObj->MaxLen) {
				NumCharsNew = pObj->MaxLen;
			}
			NumBytesNew = GUI_UC__NumChars2NumBytes(s, NumCharsNew) + 1;
			if (_IsSpaceInBuffer(pObj, NumBytesNew - NumBytesOld)) {
				char* pText;
				pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
				GUI_memcpy(pText, s, NumBytesNew);
				pObj->CursorPos = NumCharsNew;
				if (pObj->CursorPos == pObj->MaxLen) {
					if (pObj->EditMode == GUI_EDIT_MODE_OVERWRITE) {
						pObj->CursorPos--;
					}
				}
			}
		} else {
			GUI_ALLOC_FreePtr(&pObj->hpText);
			pObj->BufferSize = 0;
			pObj->CursorPos  = 0;
		}
		EDIT_Invalidate(hObj);
	}
}

/*********************************************************************
*
*       EDIT_GetText
*/
void EDIT_GetText(EDIT_Handle hObj, char* sDest, I32 MaxLen)
{
	if (sDest) {
		*sDest = 0;
	if (hObj) {
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		if (pObj->hpText) {
			char* pText;
			I32 NumChars, NumBytes;
			pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
			NumChars = GUI__GetNumChars(pText);
			if (NumChars > MaxLen) {
				NumChars = MaxLen;
			}
			NumBytes = GUI_UC__NumChars2NumBytes(pText, NumChars);
			GUI_memcpy(sDest, pText, NumBytes);
			*(sDest + NumBytes) = 0;
		}
		}
	}
}

/*********************************************************************
*
*       EDIT_GetValue
*/
I32  EDIT_GetValue(EDIT_Handle hObj)
{
	EDIT_Obj* pObj;
	I32 r = 0;
	if (hObj) {
		pObj = EDIT_H2P(hObj);
		r = pObj->CurrentValue;
	}
	return r;
}

/*********************************************************************
*
*       EDIT_SetValue
*/
void EDIT_SetValue(EDIT_Handle hObj, I32 Value)
{
	_SetValue(hObj, Value, 0);
}

/*********************************************************************
*
*       EDIT_SetMaxLen
*/
void EDIT_SetMaxLen(EDIT_Handle  hObj, I32 MaxLen)
{
	if (hObj) {
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		if (MaxLen != pObj->MaxLen) {
			if (MaxLen < pObj->MaxLen) {
				if (pObj->hpText) {
					char* pText;
					I32   NumChars;
					pText    = (char*) GUI_ALLOC_h2p(pObj->hpText);
					NumChars = GUI__GetNumChars(pText);
					if (NumChars > MaxLen) {
						I32 NumBytes;
						NumBytes = GUI_UC__NumChars2NumBytes(pText, MaxLen);
						*(pText + NumBytes) = 0;
					}
				}
			}
			_IncrementBuffer(pObj, MaxLen - pObj->BufferSize + 1);
			pObj->MaxLen = MaxLen;
			EDIT_Invalidate(hObj);
		}
	}
}

/*********************************************************************
*
*       EDIT_SetTextAlign
*/
void EDIT_SetTextAlign(EDIT_Handle hObj, I32 Align)
{
	EDIT_Obj* pObj;
	if (hObj == 0)
		return;
	pObj = EDIT_H2P(hObj);
	if (pObj) {
		pObj->Props.Align = Align;
		EDIT_Invalidate(hObj);
	}
}

void EDIT_EnableCursorBlink(EDIT_Handle hObj)
{
	if (hObj){
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		pObj->CursorBlink = 1;
	}
}

void EDIT_DisableCursorBlink(EDIT_Handle hObj)
{
	if (hObj){
			EDIT_Obj* pObj;
			pObj = EDIT_H2P(hObj);
			pObj->CursorBlink = 0;
			pObj->Cursor.IsShow = 0;
			if(pObj->hTimer){
				GUI_TIMER_Delete(pObj->hTimer);
				pObj->hTimer = 0;
				WM_InvalidateRect(hObj, &pObj->Cursor.Rect);
			}
		}
}
#else  /* avoid empty object files */

void Edit_C(void) {}

#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
