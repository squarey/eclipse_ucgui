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
File        : WM.C
Purpose     : Windows manager core
----------------------------------------------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
//#include <string.h>           /* required for memset */

#define WM_C
#include "WM_Intern_ConfDep.h"
#include "GUI_Animation.h"
#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*                 Macros for internal use
*
**********************************************************************
*/

#define ASSIGN_IF_LESS(v0,v1) if (v1<v0) v0=v1

/*********************************************************************
*
*              Local typedefs
*
**********************************************************************
*/

typedef struct {
	GUI_RECT ClientRect;
	GUI_RECT CurRect;
	I32 Cnt;
	I32 EntranceCnt;
} WM_IVR_CONTEXT;


typedef struct _WM_InvalidInfo
{
	U8 			Joined;
	GUI_RECT	Rect;
}WM_InvalidInfo;
/*********************************************************************
*
*              global data
*
**********************************************************************
*/

U8                     		WM_IsActive = 0;
U16                    		WM__CreateFlags = WM_CF_SHOW;
WM_HWIN                	WM__hCapture = WM_HWIN_NULL;
WM_HWIN                	WM__hWinFocus = WM_HWIN_NULL;
char                   		WM__CaptureReleaseAuto;
WM_tfPollPID*          	WM_pfPollPID = NULL;
U8                    	 	WM__PaintCallbackCnt = 0;      /* Public for assertions only */
GUI_PID_STATE          	WM_PID__StateLast;


#if WM_SUPPORT_DIAG
  void (*WM__pfShowInvalid)(WM_HWIN hWin);
#endif

/*********************************************************************
*
*              static data
*
**********************************************************************
*/

static WM_IVR_CONTEXT _ClipContext;
static char           	_IsInited;
//static U8				hWinNeedPaint = 0;
static WM_InvalidInfo	InvalidRectInfo[20];
static U8				InvalidRectInfoCnt = 0;
/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
static void _PanitChildren(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect);
static WM_HWIN _CheckNeedPaintWin(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect);
static U8 _CheckParentIsVisable(WM_HWIN hWin, WM_Obj  *pWin);
static WM_HWIN _CheckNeedPaintInBrother(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect);

void WM_AddToInvalidateRectLink(GUI_RECT Rect)
{
	if(0 == InvalidRectInfoCnt){
		InvalidRectInfo[0].Rect = Rect;
		InvalidRectInfoCnt++;
	}else{
		U8 i = 0;
		for(i = 0; i < InvalidRectInfoCnt; i++){
			/*if(InvalidRectInfo[i].Joined){
				InvalidRectInfo[i].Joined = 0;
				continue;
			}*/
			/* 如果需要添加的无效区域在无效区域列表中则不需要添加到无效区域列表中  */
			if(WM_RectIsIn(&Rect, &InvalidRectInfo[i].Rect)){
				if(0 == InvalidRectInfo[i].Joined){
					break;
				}
				/* 如果无效区域列表中的无效区域在即将要设置的无效区域中, 则直接更新无效区域列表中的无效区域 */
			}else if(WM_RectIsIn(&InvalidRectInfo[i].Rect, &Rect)){
				InvalidRectInfo[i].Rect = Rect;
				if(0 == InvalidRectInfo[i].Joined){
					break;
				}
			}else if(GUI_RectsIntersect(&Rect, &InvalidRectInfo[i].Rect)){
				WM_RectToMax(&InvalidRectInfo[i].Rect, &InvalidRectInfo[i].Rect, &Rect);
				InvalidRectInfo[i].Joined = 1;
				i = 0;
				Rect = InvalidRectInfo[i].Rect;

			}else{
				if(InvalidRectInfoCnt < 20){
					InvalidRectInfo[InvalidRectInfoCnt].Rect = Rect;
					InvalidRectInfoCnt++;
					break;
				}
			}
		}
	}
}

static U8 _CheckParentIsVisable(WM_HWIN hWin, WM_Obj  *pWin)
{
	WM_HWIN hParent;
	WM_Obj  *pParent;
	hParent = pWin->hParent;
	if(0 == hParent){
		return 1;
	}
	for(; hParent; hParent = pParent->hParent){
		pParent = WM_H2P(hParent);
		if(WM_SF_ISVIS != (pParent->Status & WM_SF_ISVIS)){
			return 0;
		}
	}
	return 1;
}
/*
static WM_HWIN _ToGetNoTransParent(WM_HWIN hWin)
{
	WM_HWIN hParent = WM_HWIN_NULL;
	WM_Obj *pParent;
	hParent = WM_GetParent(hWin);
	while(hParent){
		pParent = WM_H2P(hParent);
		if(WM_SF_HASTRANS != (pParent->Status & WM_SF_HASTRANS)){
			break;
		}else{
			hParent = pParent->hParent;
		}
	}
	if(0 == hParent){
		return 1;
	}else{
		return hParent;
	}
}
*/
static U8 _CheckNeedToJoinInvalidate(WM_HWIN hWin, WM_Obj *pWin, const GUI_RECT *pRect)
{
	WM_HWIN hNext, hParent, hFind;
	WM_Obj *pNext, *pParent, *pFind;
	hParent = WM_GetParent(hWin);
	for(; hParent; hParent = pParent->hParent){
		pParent = WM_H2P(hParent);
		hNext = pParent->hNext;
		for(; hNext; hNext = pNext->hNext){
			pNext = WM_H2P(hNext);
			hFind = _CheckNeedPaintWin(hNext, pNext, pRect);
			pFind = WM_H2P(hFind);
			if((0 == (pFind->Status & WM_SF_HASTRANS)) && (WM_RectIsIn(&pWin->Rect, &pFind->Rect))){
				return 0;
			}
		}
	}
	if(0 != hParent){
		hFind = _CheckNeedPaintWin(hWin, pWin, pRect);
		if(hFind != hWin){
			return 0;
		}
	}
	return 1;
}
/*********************************************************************
*
*       _CheckCriticalHandles
*
* Purpose:
*   Checks the critical handles and resets the matching one
*/
static void _CheckCriticalHandles(WM_HWIN hWin)
{
	WM_CRITICAL_HANDLE * pCH;
	for (pCH = WM__pFirstCriticalHandle; pCH; pCH = pCH->pNext) {
		if (pCH->hWin == hWin) {
			pCH->hWin = 0;
		}
	}
}

/*********************************************************************
*
*       _GetTopLevelWindow
*/
#if GUI_NUM_LAYERS > 1
static WM_HWIN _GetTopLevelWindow(WM_HWIN hWin)
{
	WM_Obj* pWin;
	WM_HWIN hTop;
	while (hTop = hWin, pWin = WM_H2P(hWin), (hWin = pWin->hParent) != 0) {
	}
	return hTop;
}
#endif


/*********************************************************************
*
*       _GethDrawWin
*
* Return Window being drawn.
* Normally same as pAWin, except if overlaying transparent window is drawn
*
*/
static WM_HWIN _GethDrawWin(void)
{
	WM_HWIN h;
	h = GUI_Context.hAWin;
	return h;
}

/*********************************************************************
*
*       _SetClipRectUserIntersect
*/
static void _SetClipRectUserIntersect(const GUI_RECT* prSrc)
{
	if (GUI_Context.WM__pUserClipRect == NULL) {
		GUI_Context.ClipRect = GUI_Context.SaveCilpRect;
		//LCD_SetClipRectEx(prSrc);
	} else {
		GUI_RECT r;
		r = *GUI_Context.WM__pUserClipRect;
		WM__Client2Screen(WM_H2P(_GethDrawWin()), &r);     /* Convert User ClipRect into screen coordinates */
		/* Set intersection as clip rect */
		GUI__IntersectRect(&r, prSrc);
		LCD_SetClipRectEx(&r);
	}
}
/*
 * 删除窗口时无效父窗口的对应区域
 * */
static void _DeleteInvalidParentRect(WM_HWIN hWin, WM_Obj *pWin)
{
	WM__InvalidateRectEx(&pWin->Rect, WM_GetParent(hWin));
}
/*********************************************************************
*
*       _DeleteAllChildren
*/
static void _DeleteAllChildren(WM_Obj * pParent)
{
	do {
		WM_DeleteWindow(pParent->hFirstChild);
	} while (pParent->hFirstChild);
}
/*********************************************************************
*
*       _AddToLinList
*/
static void _AddToLinList(WM_HWIN hNew)
{
	WM_Obj* pFirst;
	WM_Obj* pNew;
	WM_HWIN hNext;
	WM_Obj* pNext;
	WM_Obj* pSave;
	if (WM__FirstWin) {
		pFirst = WM_H2P(WM__FirstWin);
		pNew   = WM_H2P(hNew);
		//pNew->hNextLin = pFirst->hNextLin;
		pNew->hNextLin = 0;
		hNext = pFirst->hNextLin;
		pSave = pFirst;
		while(0 != hNext){
			pNext = WM_H2P(hNext);
			pSave = pNext;
			hNext = pNext->hNextLin;
		}
	//pFirst->hNextLin = hNew;
		pSave->hNextLin = hNew;
	} else {
		WM__FirstWin = hNew;
	}
}
/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       WM__ActivateClipRect
*/
void  WM__ActivateClipRect(void)
{
	if (WM_IsActive) {
		_SetClipRectUserIntersect(&_ClipContext.CurRect);
	} else {    /* Window manager disabled, typically because meory device is active */
		GUI_RECT r;
		WM_Obj *pAWin;
		pAWin = WM_H2P(GUI_Context.hAWin);
		r = pAWin->Rect;
	/* Take UserClipRect into account */
		_SetClipRectUserIntersect(&r);
	}
}

/*********************************************************************
*
*       WM__InsertWindowIntoList
*
* Routine describtion
*   This routine inserts the window in the list of child windows for
*   a particular parent window.
*   The window is placed on top of all siblings with the same level.
*/
void WM__InsertWindowIntoList(WM_HWIN hWin, WM_HWIN hParent)
{
	I32 OnTop;
	WM_HWIN hi;
	WM_Obj * pWin;
	WM_Obj * pParent;
	WM_Obj * pi;

	if (hParent) {
		pWin = WM_H2P(hWin);
		pWin->hNext = 0;
		pWin->hParent = hParent;
		pParent = WM_H2P(hParent);
		OnTop   = pWin->Status & WM_CF_STAYONTOP;
		hi = pParent->hFirstChild;
		/* Put it at beginning of the list if there is no child */
		if (hi == 0) {   /* No child yet ... Makes things easy ! */
			pParent->hFirstChild = hWin;
			return;                         /* Early out ... We are done */
		}
		/* Put it at the end of the list or before the last non "STAY-ON-TOP" child */
		while(hi){
			pi = WM_H2P(hi);
			if(0 == pi->hNext){
				if((OnTop) && (pi->Status & WM_SF_STAYONTOP)){
					pi->Status &= ~WM_SF_STAYONTOP;
					pi->hNext = hWin;
				}else if((!OnTop) && (pi->Status & WM_SF_STAYONTOP)){
					WM_HWIN hPrev;
					WM_Obj * pPrev;
					hPrev = WM__GetPrevSibling(hi);
					pPrev = WM_H2P(hPrev);
					pPrev->hNext = hWin;
					pWin->hNext = hi;
				}else{
					pi->hNext = hWin;
				}
				break;
			}else{
				hi = pi->hNext;
			}
		}
#if WM_SUPPORT_NOTIFY_VIS_CHANGED
		WM__NotifyVisChanged(hWin, &pWin->Rect);
#endif
	}
}

/*********************************************************************
*
*       WM__RemoveWindowFromList
*/
void WM__RemoveWindowFromList(WM_HWIN hWin)
{
	WM_HWIN hi, hParent;
	WM_Obj * pWin, * pParent, * pi;

	pWin = WM_H2P(hWin);
	hParent = pWin->hParent;
	if (hParent) {
		pParent = WM_H2P(hParent);
		hi = pParent->hFirstChild;
		if (hi == hWin) {
			pi = WM_H2P(hi);
			pParent->hFirstChild = pi->hNext;
		} else {
			while (hi) {
				pi = WM_H2P(hi);
				if (pi->hNext == hWin) {
					pi->hNext = pWin->hNext;
					break;
				}
				hi = pi->hNext;
			}
		}
	}
}

/*********************************************************************
*
*       WM__DetachWindow
*
* Detaches the given window. The window still exists, it keeps all
* children, but it is no longer visible since it is taken out of
* the tree of the desktop window.
*/
void WM__DetachWindow(WM_HWIN hWin)
{
	WM_Obj* pWin;
	WM_HWIN hParent;
	pWin = WM_H2P(hWin);
	hParent = pWin->hParent;
	if (hParent) {
		//WM__InvalidateRectEx(&pWin->Rect, pWin->hParent, pWin->hNext);
		WM__RemoveWindowFromList(hWin);
		pWin->hParent = 0;
	}
}



/*********************************************************************
*
*             Module internal routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__Client2Screen
*/
void WM__Client2Screen(const WM_Obj* pWin, GUI_RECT *pRect)
{
	GUI_MoveRect(pRect, pWin->Rect.x0, pWin->Rect.y0);
}

/*********************************************************************
*
*       WM__IsWindow
*/
I32 WM__IsWindow(WM_HWIN hWin)
{
	WM_HWIN iWin;
	for (iWin = WM__FirstWin; iWin; iWin = WM_H2P(iWin)->hNextLin) {
		if (iWin == hWin) {
			return 1;
		}
	}
	return 0;
}
/*********************************************************************
*
*         WM__InvalidateRectEx
*
* Parameters
*   pInvalidRect  Rectangle to invalidate in desktop coordinates
*   hWin          Handle of window to be invalidated.
*   hParent       Handle of parent window.
*                 Can be a valid window handle, 0 or WM_UNATTACHED
*   hStop         Handle of window to stop invalidation at.
*                 Can be a valid window handle or 0.
*                 If valid, hParent needs to be the parent of hStop
*
* Function description
*   Invalidates a window (hParent) as well as its children up to the
*   hStop window.
*   If the Parent is transparent, the function calls it self (recursively)
*   to move up one level in the hierarchy and invalidate the "older generation"
*   
*/
void WM__InvalidateRectEx(const GUI_RECT* pRect, WM_HWIN hParent)
{
	GUI_RECT Rect;
	WM_Obj *pParent;
	I32 Status;
	/* Perform some parameter checks and check for "early out" conditions. */
	if (hParent == 0) {
		return;                                                            /* Desktop window or unattached wind. Nothing to do. */
	}
	pParent = WM_H2P(hParent);
	Status  = pParent->Status;
	if ((Status & WM_SF_ISVIS) == 0) {
		return;                                                            /* Window is not visible... we are done */
	}
	if(0 == _CheckParentIsVisable(hParent, pParent)){
		return;
	}
	Rect = *pRect;
	if(WM_RectIntersectLCD(&Rect, &Rect)){
		if(_CheckNeedToJoinInvalidate(hParent, pParent, pRect)){
			WM_AddToInvalidateRectLink(Rect);
		}
	}
}

/*********************************************************************
*
*       WM_RemoveFromLinList
*/

void WM__RemoveFromLinList(WM_HWIN hWin)
{
	WM_Obj* piWin;
	WM_HWIN hiWin;
	WM_HWIN hNext;
	for (hiWin = WM__FirstWin; hiWin; ) {
		piWin = WM_H2P(hiWin);
		hNext = piWin->hNextLin;
		if (hNext == hWin) {
			piWin->hNextLin = WM_H2P(hWin)->hNextLin;
			break;
		}
		hiWin = hNext;
	}
}

/*********************************************************************
*
*       WM__RectIsNZ
*
   Check if the rectangle has some content (is non-zero)
   Returns 0 if the Rectangle has no content, else 1.
*/
I32 WM__RectIsNZ(const GUI_RECT* pr)
{
	if (pr->x0 > pr->x1)
		return 0;
	if (pr->y0 > pr->y1)
		return 0;
	return 1;
}


/*********************************************************************
*
*       Sending messages
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SendMessage
*/
void WM_SendMessage(WM_HWIN hWin, WM_MESSAGE* pMsg)
{
	if (hWin) {
		WM__SendMessage(hWin, pMsg);
	}
}

/*********************************************************************
*
*       WM__SendMsgNoData
*/
void WM__SendMsgNoData(WM_HWIN hWin, U8 MsgId)
{
	WM_MESSAGE Msg;
	Msg.hWin  = hWin;
	Msg.MsgId = MsgId;
	WM__SendMessage(hWin, &Msg);
}

/*********************************************************************
*
*       WM__GetClientRectWin
*
  Get client rectangle in windows coordinates. This means that the
  upper left corner is always at (0,0). 
*/
void WM__GetClientRectWin(const WM_Obj* pWin, GUI_RECT* pRect)
{
	pRect->x0 = pRect->y0 = 0;
	pRect->x1 = pWin->Rect.x1 - pWin->Rect.x0;
	pRect->y1 = pWin->Rect.y1 - pWin->Rect.y0;
}

void WM_GetClipRect(GUI_RECT *pRect)
{
	*pRect = GUI_Context.ClipRect;
}

/*********************************************************************
*
*       Invalidation functions
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_InvalidateRect
*
*  Invalidate a section of the window. The optional rectangle
*  contains client coordinates, which are independent of the
*  position of the window on the logical desktop area.
*/
void WM_InvalidateRect(WM_HWIN hWin, const GUI_RECT*pRect)
{
	GUI_RECT r;
	WM_Obj* pWin;
	I32 Status;
	if (hWin) {
		pWin = WM_H2P(hWin);
		Status = pWin->Status;
		if (Status & WM_SF_ISVIS) {
			if(0 == _CheckParentIsVisable(hWin, pWin)){
				return;
			}
			if(pRect){
				GUI_RECT rPara;
				rPara = *pRect;
				WM__Client2Screen(pWin, &rPara);
				r = rPara;
			}else{
				r = pWin->Rect;
			}
			if(WM_RectIntersectLCD(&r, &r)){
				if(_CheckNeedToJoinInvalidate(hWin, pWin, &r)){
					WM_AddToInvalidateRectLink(r);
				}
			}
		}
	}
}

/*********************************************************************
*
*        WM_InvalidateWindow
*
  Invalidates an entire window.
*/
void WM_InvalidateWindow(WM_HWIN hWin)
{
	if(hWin){
		WM_Obj *pWin;
		pWin = WM_H2P(hWin);
		if(WM_SF_ISVIS != (pWin->Status & WM_SF_ISVIS)){
			return;
		}else{
			//if(WM_SF_INVALID != (pWin->Status & WM_SF_INVALID)){
			GUI_RECT r;
			if(0 == _CheckParentIsVisable(hWin, pWin)){
				return;
			}
			r = pWin->Rect;
			if(WM_RectIntersectLCD(&r, &r)){
				if(_CheckNeedToJoinInvalidate(hWin, pWin, &r)){
					WM_AddToInvalidateRectLink(r);
				}
			}
			/*if(pWin->Status & WM_CF_HASTRANS){
				_ToInvaildNoTransParent(hWin);
			}*/
		}
	}
}

/*********************************************************************
*
*       manage windows stack
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_CreateWindowAsChild
*/
WM_HWIN WM_CreateWindowAsChild( I32 x0, I32 y0, I32 width, I32 height
                               ,WM_HWIN hParent, U16 Style, WM_CALLBACK* cb
                               ,I32 NumExtraBytes)
{
	WM_Obj* pWin;
	WM_HWIN hWin;
	WM_ASSERT_NOT_IN_PAINT();
	Style |= WM__CreateFlags;
	/* Default parent is Desktop 0 */
	if (!hParent) {
		if (WM__NumWindows) {
#if GUI_NUM_LAYERS == 1
			hParent = WM__ahDesktopWin[0];
#else
			hParent = WM__ahDesktopWin[GUI_Context.SelLayer];
#endif
		}
	}
	if (hParent == WM_UNATTACHED) {
		hParent = WM_HWIN_NULL;
	}
	if (hParent) {
		WM_Obj* pParent = WM_H2P(hParent);
		x0 += pParent->Rect.x0;
		y0 += pParent->Rect.y0;
		if (width==0) {
			width = pParent->Rect.x1 - pParent->Rect.x0+1;
		}
		if (height==0) {
			height = pParent->Rect.y1 - pParent->Rect.y0+1;
		}
	}
	if ((hWin = (WM_HWIN) GUI_ALLOC_AllocZero(NumExtraBytes + sizeof(WM_Obj))) == 0) {
		GUI_DEBUG_ERROROUT("WM_CreateWindow: No memory to create window");
	} else {
		WM__NumWindows++;
		pWin = WM_H2P(hWin);
		pWin->Rect.x0 = x0;
		pWin->Rect.y0 = y0;
		pWin->Rect.x1 = x0 + width - 1;
		pWin->Rect.y1 = y0 + height - 1;
		pWin->cb = cb;
		/* Copy the flags which can simply be accepted */
		pWin->Status |= (Style & (WM_CF_SHOW |
									WM_SF_MEMDEV |
									WM_CF_MEMDEV_ON_REDRAW |
									WM_SF_STAYONTOP |
									WM_CF_DISABLED |
									WM_SF_CONST_OUTLINE |
									WM_SF_HASTRANS |
									WM_CF_ANCHOR_RIGHT |
									WM_CF_ANCHOR_BOTTOM |
									WM_CF_ANCHOR_LEFT |
									WM_CF_ANCHOR_TOP |
									WM_CF_LATE_CLIP));
		/* Add to linked lists */
		_AddToLinList(hWin);
		WM__InsertWindowIntoList(hWin, hParent);
		/* Activate window if WM_CF_ACTIVATE is specified */
		if (Style & WM_CF_ACTIVATE) {
			WM_SelectWindow(hWin);  /* This is not needed if callbacks are being used, but it does not cost a lot and makes life easier ... */
		}
		/* Handle the Style flags, one at a time */
		if (Style & WM_CF_BGND) {
			WM_BringToBottom(hWin);
		}
		if (Style & WM_CF_SHOW) {
			pWin->Status |= WM_SF_ISVIS;  /* Set Visibility flag */
			WM_InvalidateWindow(hWin);    /* Mark content as invalid */
		}
		WM__SendMsgNoData(hWin, WM_CREATE);
	}
	return hWin;
}

/*********************************************************************
*
*       WM_CreateWindow
*/
WM_HWIN WM_CreateWindow(I32 x0, I32 y0, I32 width, I32 height, U16 Style, WM_CALLBACK* cb, I32 NumExtraBytes)
{
	return WM_CreateWindowAsChild(x0,y0,width,height, 0 /* No parent */,  Style, cb, NumExtraBytes);
}

/*********************************************************************
*
*       Delete window
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_DeleteWindow
*/
void WM_DeleteWindow (WM_HWIN hWin)
{
	WM_Obj* pWin;
	if (!hWin) {
		return;
	}
	WM_ASSERT_NOT_IN_PAINT();
	if (WM__IsWindow(hWin)) {
		pWin = WM_H2P(hWin);
		GUI_TIMER_DeleteByContext(hWin);
		GUI_AnimationDeleteByContext(hWin);
		_DeleteInvalidParentRect(hWin, pWin);
		/* Make sure that focus is set to an existing window */
		if (WM__hWinFocus == hWin) {
			WM__hWinFocus = 0;
		}
		if (WM__hCapture == hWin) {
			WM__hCapture = 0;
		}
		/* check if critical handles are affected. If so, reset the window handle to 0 */
		_CheckCriticalHandles(hWin);
		/* Inform parent */
		WM_NotifyParent(hWin, WM_NOTIFICATION_CHILD_DELETED);
		/* Delete all children */
		_DeleteAllChildren(pWin);
#if WM_SUPPORT_NOTIFY_VIS_CHANGED
		WM__SendMsgNoData(hWin, WM_NOTIFY_VIS_CHANGED);             /* Notify window that visibility may have changed */
#endif
		/* Send WM_DELETE message to window in order to inform window itself */
		WM__SendMsgNoData(hWin, WM_DELETE);     /* tell window about it */
		WM__DetachWindow(hWin);
		/* Remove window from window stack */
		WM__RemoveFromLinList(hWin);
		/* Free window memory */
		WM__NumWindows--;
		GUI_ALLOC_Free(hWin);
		/* Select a valid window */
		WM_SelectWindow(WM__FirstWin);
	} else {
		GUI_DEBUG_WARN("WM_DeleteWindow: Invalid handle");
	}
}

/*********************************************************************
*
*       WM_SelectWindow
*
*  Sets the active Window. The active Window is the one that is used for all
*  drawing (and text) operations.
*/
WM_HWIN WM_SelectWindow(WM_HWIN  hWin)
{
	WM_HWIN hWinPrev;
	WM_Obj* pObj;

	WM_ASSERT_NOT_IN_PAINT();
	hWinPrev = GUI_Context.hAWin;
	if (hWin == 0) {
		hWin = WM__FirstWin;
	}
	/* Select new window */
	GUI_Context.hAWin = hWin;
#if GUI_NUM_LAYERS > 1
	{
		WM_HWIN hTop;
		I32 LayerIndex;
		hTop = _GetTopLevelWindow(hWin);
		LayerIndex = _DesktopHandle2Index(hTop);
		if (LayerIndex >= 0) {
			GUI_SelectLayer(LayerIndex);
		}
	}
#endif
	pObj = WM_H2P(hWin);
	LCD_SetClipRectMax();             /* Drawing operations will clip ... If WM is deactivated, allow all */
	GUI_Context.xOff = pObj->Rect.x0;
	GUI_Context.yOff = pObj->Rect.y0;
	return hWinPrev;
}

/*********************************************************************
*
*       WM_GetActiveWindow
*/
WM_HWIN WM_GetActiveWindow(void)
{
	return GUI_Context.hAWin;
}

/*********************************************************************
*
*       WM_SetDefault
*
  This routine sets the defaults for WM and the layers below.
  It is used before a drawing routine is called in order to
  make sure that defaults are set (in case the default settings
  had been altered before by the application)
*/
void WM_SetDefault(void)
{
	GL_SetDefault();
	GUI_Context.WM__pUserClipRect = NULL;   /* No add. clipping */
}

/*********************************************************************
*
*       _Paint1
*/

static void __SendWinPanitMessage(WM_HWIN hWin, WM_Obj* pWin, GUI_RECT Rect)
{
	if((pWin->Status & WM_SF_ISVIS)/* && (pWin->Status & WM_SF_INVALID)*/){
		WM_MESSAGE Msg;
		Msg.hWin   = hWin;
		Msg.MsgId  = WM_PAINT;
		Msg.Data.p = (GUI_RECT*)&Rect;
		pWin->InvalidRect = Rect;
		WM_SetDefault();
		WM_SelectWindow(hWin);
		GUI_Context.ClipRect = Rect;
		GUI_Context.SaveCilpRect = Rect;
		_ClipContext.CurRect = Rect;
		WM__SendMessage(hWin, &Msg);
		pWin->Status &= ~WM_SF_INVALID;
	}
}
static void _PanitBrother(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect)
{
	WM_HWIN hBrother;
	WM_Obj* pBrother;
	GUI_RECT r;
	for (hBrother = pWin->hNext; hBrother; hBrother = pBrother->hNext) {
		pBrother = WM_H2P(hBrother);
		if (pBrother->Status & WM_SF_ISVIS) {
			if(WM_RectIntersect(&r, pRect, &pBrother->Rect)){
				GUI_Debug("To paint brother win %d\n", hBrother);
				__SendWinPanitMessage(hBrother, pBrother, r);
				_PanitChildren(hBrother, pBrother, &r);
			}
		}
	}
}
static WM_HWIN _CheckNeedPaintInBrother(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect)
{
	WM_HWIN hNext = WM_HWIN_NULL, hFind = WM_HWIN_NULL;
	WM_Obj *pNext;
	for(hNext = pWin->hNext; hNext; hNext = pNext->hNext){
		pNext = WM_H2P(hNext);
		if((pNext->Status & WM_SF_ISVIS) && (WM_SF_HASTRANS != (pNext->Status & WM_SF_HASTRANS))){
			if(WM_RectIsIn(pRect, &pNext->Rect)){
				hFind = hNext;
			}
		}
	}
	return hFind;
}
static WM_HWIN _CheckNeedPaintInChildren(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect)
{
	WM_HWIN hChild;
	WM_HWIN hSaveWin = WM_HWIN_NULL;
	WM_Obj *pChild;
	hChild = pWin->hFirstChild;
	if(WM_HWIN_NULL == hChild){
		return WM_HWIN_NULL;
	}
	for(; hChild; hChild = pChild->hNext){
		pChild = WM_H2P(hChild);
		if((WM_SF_HASTRANS != (pChild->Status & WM_SF_HASTRANS)) && (WM_RectIsIn(pRect, &pChild->Rect))){
			hSaveWin = hChild;
		}
	}
	return hSaveWin;
}

/* 查找所需绘制的窗口  如果没有找到所需绘制的窗口则返回hWin */
static WM_HWIN _CheckNeedPaintWin(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect)
{
	WM_HWIN hFindWin = WM_HWIN_NULL;
	WM_HWIN hSaveWin = WM_HWIN_NULL;
	WM_Obj *pFindWin, *pSaveWin;
	//GUI_RECT Rect;
	/*if(0 == WM_RectIntersectLCD(&Rect, &pWin->Rect)){
		return WM_HWIN_NULL;
	}*/
	/* 先找所需绘制的同级窗口, 再找其所需绘制的子窗口  */
	/* 查找在同类窗口中所需要绘制的窗口   */
	hFindWin = _CheckNeedPaintInBrother(hWin, pWin, pRect);
	while(WM_HWIN_NULL != hFindWin){
		/* 如果找到需要绘制的同类窗口  */
		hSaveWin = hFindWin;
		pFindWin = WM_H2P(hFindWin);
		/* 再寻找此窗口在其子窗口所需绘制的窗口  */
		hFindWin = _CheckNeedPaintInChildren(hFindWin, pFindWin, pRect);
		if(WM_HWIN_NULL != hFindWin){
			hSaveWin = hFindWin;
			pFindWin = WM_H2P(hFindWin);
			hFindWin = _CheckNeedPaintInBrother(hFindWin, pFindWin, pRect);
		}else{
			/* 如果没有找到所需绘制同级窗口则在找到的基础上再找所需绘制的子窗口 */
			pSaveWin = WM_H2P(hSaveWin);
			hFindWin = _CheckNeedPaintInChildren(hSaveWin, pSaveWin, pRect);
		}
	}
	if(WM_HWIN_NULL != hSaveWin){
		return hSaveWin;
	}
	/* 先找所需绘制的子窗口, 再找所需绘制的同级窗口  */
	hFindWin = _CheckNeedPaintInChildren(hWin, pWin, pRect);
	while(WM_HWIN_NULL != hFindWin){
		hSaveWin = hFindWin;
		pFindWin = WM_H2P(hFindWin);
		hFindWin = _CheckNeedPaintInBrother(hFindWin, pFindWin, pRect);
		hFindWin = WM_HWIN_NULL;
		if(WM_HWIN_NULL != hFindWin){
			hSaveWin = hFindWin;
			pFindWin = WM_H2P(hFindWin);
			hFindWin = _CheckNeedPaintInChildren(hFindWin, pFindWin, pRect);
		}else{
			pSaveWin = WM_H2P(hSaveWin);
			hFindWin = _CheckNeedPaintInChildren(hSaveWin, pSaveWin, pRect);
		}
	}
	if(WM_HWIN_NULL == hSaveWin){
		return hWin;
	}else{
		return hSaveWin;
	}
}
#if 0
static void _PanitChildren(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect)
{
	WM_HWIN hChild;
	WM_Obj* pChild;
	if (pWin->Status & WM_SF_ISVIS) {
		GUI_RECT r;
		WM_HWIN hPaintWin = WM_HWIN_NULL;
		WM_HWIN hLastPaintWin = WM_HWIN_NULL;
		WM_Obj *pPaintWin;
		for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
			pChild = WM_H2P(hChild);
			hPaintWin = _CheckNeedPaintWin(hChild, pChild, pRect);
			/* 如果所需绘制的与上一次的相同  则此次不需要绘制  */
			if((hLastPaintWin == hPaintWin) || (WM_HWIN_NULL == hPaintWin)){
				continue;
			}
			pPaintWin = WM_H2P(hPaintWin);
			LastPaintRect = *pRect;
			//GUI_Debug("hChild:%d, hPaintWin:%d, Child status:%x, PaintWin status:%x\n", hChild, hPaintWin, pChild->Status, pPaintWin->Status);
			if(WM_RectIntersect(&r, pRect, &pPaintWin->Rect)){
				__SendWinPanitMessage(hPaintWin, pPaintWin, r);
				_PanitChildren(hPaintWin, pPaintWin, &r);
				_PanitBrother(hPaintWin, pPaintWin, &r);
			}
			hLastPaintWin = hPaintWin;
		}
	}
}
#else
static void _PanitChildren(WM_HWIN hWin, WM_Obj* pWin, const GUI_RECT* pRect)
{
	WM_HWIN hChild;
	WM_Obj* pChild;
	if (pWin->Status & WM_SF_ISVIS) {
		GUI_RECT r;
		WM_HWIN hFind = WM_HWIN_NULL;
		//WM_Obj *pFind;
		for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
			pChild = WM_H2P(hChild);
			hFind = _CheckNeedPaintInBrother(hChild, pChild, &pChild->Rect);
			if(WM_HWIN_NULL != hFind){
				continue;
			}
			/*if(WM_HWIN_NULL != hFind){
				pFind = WM_H2P(hFind);
				if(WM_RectIntersect(&r, pRect, &pChild->Rect)){
					__SendWinPanitMessage(hChild, pChild, r);
					_PanitChildren(hChild, pChild, &r);
					_PanitBrother(hChild, pChild, &r);
				}
				break;
			}*/
			/*hFind = _CheckNeedPaintInChildren(hChild, pChild, pRect);
			if(WM_HWIN_NULL != hFind){
				pFind = WM_H2P(hFind);
				__SendWinPanitMessage(hFind, pFind, *pRect);
				_PanitChildren(hFind, pFind, pRect);
				_PanitBrother(hFind, pFind, pRect);
				break;
			}*/
			if(WM_RectIntersect(&r, pRect, &pChild->Rect)){
				__SendWinPanitMessage(hChild, pChild, r);
				_PanitChildren(hChild, pChild, &r);
				//_PanitBrother(hChild, pChild, &r);
			}

		}
	}
}
#endif
/*

static void _ToPaintSelfAndAllChildren(WM_HWIN hWin, WM_Obj* pWin, GUI_RECT* pRect)
{
	WM_HWIN hChild;
	WM_Obj* pChild;
	__SendWinPanitMessage(hWin, pWin, *pRect);
	for
}*/
static void _Paint1(WM_HWIN hWin, WM_Obj* pWin) {
	I32 Status = pWin->Status;
	/* Send WM_PAINT if window is visible and a callback is defined */
	if ((pWin->cb != NULL)  && (Status & WM_SF_ISVIS)) {
		WM_MESSAGE Msg;
		WM__PaintCallbackCnt++;
		if (Status & WM_SF_LATE_CLIP) {
			Msg.hWin   = hWin;
			Msg.MsgId  = WM_PAINT;
			Msg.Data.p = (GUI_RECT*)&pWin->InvalidRect;
			WM_SetDefault();
			WM__SendMessage(hWin, &Msg);
		} else {
			WM_HWIN hFind;
			WM_Obj *pFind;
			hFind = _CheckNeedPaintWin(hWin, pWin, &pWin->InvalidRect);
			if(hFind == hWin){
				__SendWinPanitMessage(hWin, pWin, pWin->InvalidRect);
				_PanitChildren(hWin, pWin, &pWin->InvalidRect);
			}else{
				pFind = WM_H2P(hFind);
				//GUI_Debug("To paint win %d\n", hFind);
				//GUI_Debug("InvalidRect :%d, %d, %d, %d\n", pWin->InvalidRect.x0, pWin->InvalidRect.y0,
						//pWin->InvalidRect.x1, pWin->InvalidRect.y1);
				__SendWinPanitMessage(hFind, pFind, pWin->InvalidRect);
				_PanitChildren(hFind, pFind, &pWin->InvalidRect);
				_PanitBrother(hFind, pFind, &pWin->InvalidRect);
			}
			//__SendWinPanitMessage(hWin, pWin, pWin->InvalidRect);
			//GUI_Debug("hWin:%d, hWinNeedPaint:%d\n", hWin, hWinNeedPaint);

			//_PanitBrother(hWin, pWin, &pWin->InvalidRect);
		}
		WM__PaintCallbackCnt--;
	}
}

/*********************************************************************
*
*       _DrawNext
*/
static void _DrawNext(void)
{
	GUI_CONTEXT ContextOld;
	WM_Obj* pWin;
	WM_HWIN hWin;
	U8 i = 0;
	if(0 == InvalidRectInfoCnt){
		return;
	}
	GUI_SaveContext(&ContextOld);
	for(i = 0; i < InvalidRectInfoCnt; i++){
		hWin = WM__ahDesktopWin[0];
		pWin = WM_H2P(hWin);
		pWin->InvalidRect = InvalidRectInfo[i].Rect;
		_Paint1(hWin, pWin);
		WM_UpdateRectEnd(InvalidRectInfo[i].Rect.x0, InvalidRectInfo[i].Rect.y0,
				InvalidRectInfo[i].Rect.x1, InvalidRectInfo[i].Rect.y1);
	}
	WM_UpdateAllEnd();
	InvalidRectInfoCnt = 0;
	GUI_memset(InvalidRectInfo, 0, sizeof(InvalidRectInfo));
	GUI_RestoreContext(&ContextOld);
}
/*********************************************************************
*
*       WM_Exec1
*/
I32 WM_Exec1(void)
{
	/* Poll PID if necessary */
	if (WM_pfPollPID) {
		WM_pfPollPID();
	}
	if (WM_pfHandlePID) {
		if (WM_pfHandlePID()){
			//GUI_Debug("here has been return\n");
			return 1;               /* We have done something ... */
		}
	}
	if (WM_IsActive) {
		if (GUI_PollKeyMsg()) {
			return 1;               /* We have done something ... */
		}
	}
	/*
	#ifdef WIN32
	if (WM_PollSimMsg()) {
	return 1;
	}
	#endif
	*/
#if 0
	if (WM_IsActive && WM__NumInvalidWindows) {
		WM_LOCK();
		_DrawNext();
		WM_UNLOCK();
		return 1;               /* We have done something ... */
	}
#else
	if (WM_IsActive){
		_DrawNext();
	}
#endif
  return 0;                  /* There was nothing to do ... */
}

/*********************************************************************
*
*       WM_Exec
*/
I32 WM_Exec(void)
{
	I32 r = 0;
	while (WM_Exec1()) {
		r = 1;                  /* We have done something */
	}
	return r;
}

/*********************************************************************
*
*       cbBackWin
*
* Purpose
*   Callback for background window
*
*/
static void cbBackWin( WM_MESSAGE* pMsg)
{
	const WM_KEY_INFO* pKeyInfo;
	switch (pMsg->MsgId) {
		case WM_KEY:
			pKeyInfo = (const WM_KEY_INFO*)pMsg->Data.p;
			if (pKeyInfo->PressedCnt == 1) {
				GUI_StoreKey(pKeyInfo->Key);
			}
		break;
		case WM_PAINT:
		{
			I32 LayerIndex;
#if GUI_NUM_LAYERS > 1
			LayerIndex = _DesktopHandle2Index(pMsg->hWin);
#else
			LayerIndex = 0;
#endif
			//if (WM__aBkColor[LayerIndex] != GUI_INVALID_COLOR) {
				GUI_SetBkColor(WM__aBkColor[LayerIndex]);
				GUI_Clear();
			//}
		}
		break;
		default:
			WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
*
*       WM_Activate
*/
void WM_Activate(void)
{
	WM_IsActive = 1;       /* Running */
}

/*********************************************************************
*
*       WM_Deactivate
*/
void WM_Deactivate(void)
{
	WM_IsActive = 0;       /* No clipping performed by WM */
	LCD_SetClipRectMax();
}

/*********************************************************************
*
*       WM_DefaultProc
*
* Purpose
*   Default callback for windows
*   Any window should call this routine in the "default" part of the
*   its callback function for messages it does not handle itself.
*
*/
void WM_DefaultProc(WM_MESSAGE* pMsg)
{
	WM_HWIN hWin = pMsg->hWin;
	const void *p = pMsg->Data.p;
	WM_Obj* pWin = WM_H2P(hWin);
	/* Exec message */
	switch (pMsg->MsgId) {
		case WM_GET_INSIDE_RECT:      /* return client window in absolute (screen) coordinates */
			WM__GetClientRectWin(pWin, (GUI_RECT*)p);
		break;
		case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
			pMsg->Data.v = (I32)hWin;
		return;                       /* Message handled */
		case WM_KEY:
			WM_SendToParent(hWin, pMsg);
		return;                       /* Message handled */
		case WM_GET_BKCOLOR:
			pMsg->Data.Color = GUI_INVALID_COLOR;
		return;                       /* Message handled */
		case WM_NOTIFY_ENABLE:
			WM_InvalidateWindow(hWin);
		return;                       /* Message handled */
	}
	/* Message not handled. If it queries something, we return 0 to be on the safe side. */
	pMsg->Data.v = 0;
	pMsg->Data.p = 0;
}

/*********************************************************************
*
*       WM_Init
*/
void WM_Init(void)
{
	if (!_IsInited) {
		WM__FirstWin = WM_HWIN_NULL;
		GUI_Context.WM__pUserClipRect = NULL;
		WM__NumWindows = 0;
		/* Make sure we have at least one window. This greatly simplifies the
			drawing routines as they do not have to check if the window is valid.
		 */
#if GUI_NUM_LAYERS == 1
		WM__ahDesktopWin[0] = WM_CreateWindow(0, 0, LCD_XSIZE, LCD_YSIZE, WM_CF_SHOW, cbBackWin, 0);
		WM__aBkColor[0] = 0;//GUI_INVALID_COLOR;
		WM_InvalidateWindow(WM__ahDesktopWin[0]); /* Required because a desktop window has no parent. */
#else
		{
			I32 i;
			for (i = 0; i < GUI_NUM_LAYERS; i++) {
				WM__ahDesktopWin[i] = WM_CreateWindowAsChild(0, 0, GUI_XMAX, GUI_YMAX, WM_UNATTACHED, WM_CF_SHOW, cbBackWin, 0);
				WM__aBkColor[i] = GUI_INVALID_COLOR;
				WM_InvalidateWindow(WM__ahDesktopWin[i]); /* Required because a desktop window has no parent. */
			}
		}
#endif
		/* Register the critical handles ... Note: This could be moved into the module setting the Window handle */
		WM__AddCriticalHandle(&WM__CHWinModal);
		WM__AddCriticalHandle(&WM__CHWinLast);

		WM_SelectWindow(WM__ahDesktopWin[0]);
		WM_Activate();
		_IsInited =1;
	}
}


#else
  void WM(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
