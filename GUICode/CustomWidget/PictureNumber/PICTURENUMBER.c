

#include "GUI_Protected.h"
#include "PICTURENUMBER_Private.h"
#include "WIDGET.h"



#if GUI_WINSUPPORT && PICTURENUMBER_SUPPORT


#ifndef PICTURENUMBER_BKCOLOR0_DEFAULT
  #define PICTURENUMBER_BKCOLOR0_DEFAULT 0   /* Not Selected Text Color */
#endif

static GUI_RECT PICTURENUMBER_GetRect(PICTURENUMBER_Handle hObj)
{
	WM_Obj* pWin;
	pWin = WM_H2P(hObj);
	return (pWin->Rect);
}

static void _Paint(PICTURENUMBER_Obj* pObj, PICTURENUMBER_Handle hObj) 
{
	GUI_RECT Rect, cRect;
	char DispNumberBuffer[11] = {0};
	U32  DispNumberLen = 0;
	U32 NumberWidth = 0, NumberHeight = 0;
	U32 RectWidth = 0, RectHeight = 0;
	U32 NumberLen = 0;
	I32 DisXPos = 0, DisYPos = 0;
	U8 i = 0;
	char c = 0;
	if(!WM__IsEnabled(hObj))
	{
		return;
	}
	GUI_sprintf(DispNumberBuffer,"%d",pObj->DispNumber);
	DispNumberLen = GUI_strlen(DispNumberBuffer);
	Rect = PICTURENUMBER_GetRect(hObj);
	NumberWidth = GUI_BMP_GetXSize(pObj->NumberBuffer[0]);
	NumberHeight = GUI_BMP_GetYSize(pObj->NumberBuffer[0]);
	NumberLen = NumberWidth * DispNumberLen;
	RectWidth = Rect.x1 - Rect.x0 + 1;
	RectHeight = Rect.y1 - Rect.y0 + 1;
	DisXPos = RectWidth - NumberLen;
	DisYPos = (RectHeight - NumberHeight)/2;
	GUI_SetBkColor(PICTURENUMBER_BKCOLOR0_DEFAULT);
	if(NumberHeight >= RectHeight)
	{
		DisYPos = 0;
		cRect.x0 = 0;
		cRect.x1 = DisXPos;
		cRect.y0 = 0;
		cRect.y1 = RectHeight;
		GUI_ClearRectEx(&cRect);
	}
	else 
	{
		cRect.x0 = 0;
		cRect.x1 = DisXPos;
		cRect.y0 = 0;
		cRect.y1 = RectHeight;
		GUI_ClearRectEx(&cRect);
		
		cRect.x0 = DisXPos;
		cRect.x1 = RectWidth;
		cRect.y0 = 0;
		cRect.y1 = DisYPos;
		GUI_ClearRectEx(&cRect);
		
		cRect.x0 = DisXPos;
		cRect.x1 = RectWidth;
		cRect.y0 = DisYPos + NumberHeight;
		cRect.y1 = RectHeight;
		GUI_ClearRectEx(&cRect);
	}
	for(i = 0; i < DispNumberLen; i++)
	{
		c = DispNumberBuffer[i] - 0x30;
		if(NULL != pObj->NumberBuffer[c])
		{
			GUI_BMP_Draw(pObj->NumberBuffer[c],DisXPos + NumberWidth * i,DisYPos);
		}
	}
}

static void _OnPictureNumberPressed(PICTURENUMBER_Handle hObj, PICTURENUMBER_Obj* pObj) 
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) 
	{
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}
static void _OnPictureNumberReleased(PICTURENUMBER_Handle hObj, PICTURENUMBER_Obj* pObj, I32 Notification) 
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) 
	{
		WM_NotifyParent(hObj, Notification);
	}
}
static void _OnTouch(PICTURENUMBER_Handle hObj, PICTURENUMBER_Obj* pObj, WM_MESSAGE*pMsg) 
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	if(pMsg->Data.p)
	{
		if(pState->Pressed)
		{
			_OnPictureNumberPressed(hObj,pObj);
		}
		else 
		{
			_OnPictureNumberReleased(hObj,pObj,WM_NOTIFICATION_RELEASED);
		}
	}
	else 
	{
		_OnPictureNumberReleased(hObj,pObj,WM_NOTIFICATION_MOVED_OUT);
	}
}
static void PICTURENUMBER_Callback (WM_MESSAGE *pMsg) 
{
	PICTURENUMBER_Handle hObj;
	PICTURENUMBER_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (PICTURENUMBER_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
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
PICTURENUMBER_Handle PICTURENUMBER_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	PICTURENUMBER_Handle hObj;
	/* Create the window */
	WM_LOCK();
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, PICTURENUMBER_Callback, sizeof(PICTURENUMBER_Obj) - sizeof(WM_Obj));
	if (hObj) 
	{
		PICTURENUMBER_Obj * pObj;
		pObj = (PICTURENUMBER_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, ExFlags);
		/* init member variables */
		PICTURENUMBER_INIT_ID(pObj);
	} 
	else 
	{
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	WM_UNLOCK();
	return hObj;
}


void PICTURENUMBER_SetNumberBitmap(PICTURENUMBER_Handle hObj, void *buffer, U8 number)
{
	PICTURENUMBER_Obj * pObj;
	WM_LOCK();
	pObj = (PICTURENUMBER_Obj *)GUI_ALLOC_h2p(hObj);
	pObj->NumberBuffer[number] = buffer;
	WM_UNLOCK();
}
void PICTURENUMBER_SetNumber(PICTURENUMBER_Handle hObj, U32 number)
{
	PICTURENUMBER_Obj * pObj;
	WM_LOCK();
	pObj = (PICTURENUMBER_Obj *)GUI_ALLOC_h2p(hObj);
	pObj->DispNumber = number;
	WM_Invalidate(hObj);
	WM_UNLOCK();
}

#endif 


