/*
 * TOTAST.c
 *
 *  Created on: 2018年6月19日
 *      Author: Administrator
 */

#include "TOTAST.h"
#include "TOTAST_Private.h"
#include "GUI_StyleDraw.h"

static TOTAST_Handle hStaticTotast = WM_HWIN_NULL;

static void _TotastTimer_cb(GUI_TIMER_MESSAGE* pTM);

static void _Paint(TOTAST_Handle hObj, TOTAST_Obj* pObj)
{
	const char * s;
	GUI_RECT Rect;
	GUI_FullRectStyle Style;

	Rect.x0 = 0;
	Rect.y0 = 0;
	Rect.x1 = WM_GetWindowSizeX(hObj);
	Rect.y1 = WM_GetWindowSizeY(hObj);
	Style.Radius	= 6;
	Style.Opacity	= 0xff;
	Style.MainColor = pObj->Props.BkColor;
	Style.GradColor = pObj->Props.BkColor;
	GUI_DrawRectMainMiddle(&Rect, &Style);
	GUI_DrawRectMainCorner(&Rect, &Style);
	if (pObj->hpText) {
		s = (const char*) GUI_ALLOC_h2p(pObj->hpText);
		GUI_SetFont(pObj->Props.pFont);
		GUI_SetColor(pObj->Props.TextColor);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_DispStringInRect(s, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
	}
}

static void TOTAST_Callback (WM_MESSAGE* pMsg)
{
	TOTAST_Handle hObj;
	TOTAST_Obj * pObj;
	hObj = pMsg->hWin;
	pObj = (TOTAST_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			_Paint(hObj, pObj);
			return;
		case WM_DELETE:
			GUI_ALLOC_FreePtr(&pObj->hpText);
			break;
		default:
		break;
	}
	WM_DefaultProc(pMsg);
}

TOTAST_Handle TOTAST_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                          I32 WinFlags, I32 ExFlags, I32 Id, const char* pText)
{
	TOTAST_Handle hObj;
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, TOTAST_Callback,
							sizeof(TOTAST_Obj) - sizeof(WM_Obj));
	if (hObj) {
		TOTAST_Obj* pObj;
		WM_HMEM hMem = 0;
		pObj = (TOTAST_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		/* init member variables */
		if (pText) {
			hMem = GUI_ALLOC_AllocZero(GUI_strlen(pText) + 1);
			if (hMem) {
				GUI_strcpy((char*) GUI_ALLOC_h2p(hMem), pText);
			}
		}
		pObj->hpText = hMem;
		pObj->Props.BkColor		= 0xff404040;
		pObj->Props.TextColor 	= GUI_WHITE;
		pObj->Props.pFont		= &GUI_FontASSIC_YH32;

		pObj->hTimer = GUI_TIMER_Create(_TotastTimer_cb, 0, hObj, 0);
		GUI_TIMER_SetPeriod(pObj->hTimer, 3000);
		GUI_TIMER_Restart(pObj->hTimer);
	} else {
			GUI_DEBUG_ERROROUT_IF(hObj==0, "TEXT_Create failed")
	}
	return hObj;
}
void TOTAST_SetText(TOTAST_Handle hObj, const char *pTest)
{
	if (hObj) {
		TOTAST_Obj* pObj;
		pObj = GUI_ALLOC_h2p(hObj);
		if (GUI__SetText(&pObj->hpText, pTest)) {
			WM_Invalidate(hObj);
		}
	}
}
void TOTAST_SetFont(TOTAST_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont)
{
	if (hObj) {
		TOTAST_Obj* pObj;
		pObj = GUI_ALLOC_h2p(hObj);
		if (pObj->Props.pFont != pFont) {
			pObj->Props.pFont = pFont;
			WM_Invalidate(hObj);
		}
	}
}
void TOTAST_SetColor(TOTAST_Handle hObj, GUI_COLOR BkColor, GUI_COLOR TextColor)
{
	if (hObj) {
		TOTAST_Obj* pObj;
		pObj = GUI_ALLOC_h2p(hObj);
		if ((pObj->Props.BkColor != BkColor) || (pObj->Props.TextColor != TextColor)) {
			pObj->Props.BkColor = BkColor;
			pObj->Props.TextColor = TextColor;
			WM_Invalidate(hObj);
		}
	}
}
static void _TotastTimer_cb(GUI_TIMER_MESSAGE* pTM)
{
	if(hStaticTotast == pTM->Context){
		hStaticTotast = WM_HWIN_NULL;
	}
	WM_DeleteWindow(pTM->Context);
}
TOTAST_Handle TOTAST_StaticShow(const char *pTest, const GUI_FONT *pFont)
{
	if(WM_HWIN_NULL == hStaticTotast){
		TOTAST_Handle hObj;
		I32 xLineSize;
		I32 LineLen;
		I16 FontYSize = 0;
		if(NULL != pFont){
			GUI_SetFont(pFont);
		}
		LineLen = GUI__GetLineNumChars(pTest, 0x7fff);
		xLineSize = GUI__GetLineDistX(pTest, LineLen);
		FontYSize = GUI_GetFontSizeY() + 20;
		hObj = TOTAST_CreateEx(0,0, xLineSize + 20, FontYSize, WM_GetDesktopWindow(), WM_CF_SHOW, 0, 0, pTest);
		WM_SetAlignParent(hObj, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, -10);
		if(NULL != pFont){
			TOTAST_SetFont(hObj, pFont);
		}
		hStaticTotast = hObj;
		WM_BringToTop(hStaticTotast);
		return hObj;
	}else{
		TOTAST_Obj* pObj;
		pObj = GUI_ALLOC_h2p(hStaticTotast);
		GUI_TIMER_Restart(pObj->hTimer);
		if(NULL != pFont){
			TOTAST_SetFont(hStaticTotast, pFont);
		}
		TOTAST_StaticSetText(pTest, pFont);
		return hStaticTotast;
	}
}
void TOTAST_StaticSetText(const char *pTest, const GUI_FONT *pFont)
{
	if (hStaticTotast) {
		TOTAST_Obj* pObj;
		I32 xLineSize;
		I32 LineLen;
		I16 FontYSize = 0;
		if(NULL != pFont){
			GUI_SetFont(pFont);
		}
		LineLen = GUI__GetLineNumChars(pTest, 0x7fff);
		xLineSize = GUI__GetLineDistX(pTest, LineLen);
		FontYSize = GUI_GetFontSizeY() + 20;
		pObj = GUI_ALLOC_h2p(hStaticTotast);
		WM_SetXSize(hStaticTotast, xLineSize);
		WM_SetYSize(hStaticTotast, FontYSize);
		if (GUI__SetText(&pObj->hpText, pTest)) {
			GUI_TIMER_Restart(pObj->hTimer);
			WM_Invalidate(hStaticTotast);
		}
	}
}
void TOTAST_StaticSetFont(const GUI_FONT GUI_UNI_PTR * pFont)
{
	if (hStaticTotast) {
		TOTAST_Obj* pObj;
		pObj = GUI_ALLOC_h2p(hStaticTotast);
		if (pObj->Props.pFont != pFont) {
			pObj->Props.pFont = pFont;
			GUI_TIMER_Restart(pObj->hTimer);
			WM_Invalidate(hStaticTotast);
		}
	}
}
void TOTAST_StaticSetColor(GUI_COLOR BkColor, GUI_COLOR TextColor)
{
	if (hStaticTotast) {
		TOTAST_Obj* pObj;
		pObj = GUI_ALLOC_h2p(hStaticTotast);
		if ((pObj->Props.BkColor != BkColor) || (pObj->Props.TextColor != TextColor)) {
			pObj->Props.BkColor = BkColor;
			pObj->Props.TextColor = TextColor;
			GUI_TIMER_Restart(pObj->hTimer);
			WM_Invalidate(hStaticTotast);
		}
	}
}
