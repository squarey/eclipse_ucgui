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
File        : IMAGEVIEW.c
Purpose     : Implementation of slider widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>
#include "GUI_Protected.h"
#include "IMAGEVIEW_Private.h"
#include "GUI_ImageRotate.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && IMAGEVIEW_SUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/


/* Define colors */
#ifndef   IMAGEVIEW_BKCOLOR0_DEFAULT
  #define IMAGEVIEW_BKCOLOR0_DEFAULT   GUI_RED
#endif

#ifndef   IMAGEVIEW_COLOR0_DEFAULT
  #define IMAGEVIEW_COLOR0_DEFAULT     0
#endif

#ifndef   IMAGEVIEW_FOCUSCOLOR_DEFAULT
  #define IMAGEVIEW_FOCUSCOLOR_DEFAULT 0
#endif

typedef struct
{
	U32 DrawHeight;
	U32 DrawWidth;
	U32 StartX;
	U32 StartY;
	U32 OffestX;
	U32 OffestY;
	U8  AlphaValue;
	ImageViewInfo_t ViewInfo;
}_DrawInfo;
/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
static U8 __ImageDecode(ImageViewInfo_t* pInfo)
{
	ImageViewFormat_em ImageFormat = IMAGEVIEW_FORMAT_ERROR;
	ImageFormat = GUI_ImageGetFormat(pInfo->pFile);
	if(IMAGEVIEW_FORMAT_PNG == ImageFormat){
		GUI_ImageDecodePNG(pInfo);
	}else if(IMAGEVIEW_FORMAT_BMP == ImageFormat){
		GUI_ImageDecodeBMP(pInfo);
	}else if(IMAGEVIEW_FORMAT_JPG == ImageFormat){
		GUI_ImageDecodeJPG(pInfo);
	}else{
		//GUI_Debug("image format is error, %s\n", pInfo->pFile);
		return 0;
	}
	return 1;
}
/*********************************************************************
*
*       _Paint
*/
static void _DrawImage(_DrawInfo *pInfo)
{
	const U8 *pBuffer = NULL;
	U8 Red = 0, Green = 0, Blue = 0;
	U8 Alpha = 0;
	U32 BytesPerLine = 0;
	I32 DrawPosX = 0, DrawPosY = 0;
	U32 x = 0, y = 0;
	GUI_COLOR Color = 0;
	pBuffer = pInfo->ViewInfo.pBuffer;
	if(IMAGEVIEW_COLOR_TYPE_ARGB == pInfo->ViewInfo.ColorType){
		BytesPerLine = ((32 * pInfo->ViewInfo.Width + 31) >> 5) << 2;
		for(y = pInfo->StartY; y < pInfo->DrawHeight; y++){
			pBuffer = pInfo->ViewInfo.pBuffer + y * BytesPerLine + pInfo->StartX * 4;
			for(x = pInfo->StartX; x < pInfo->DrawWidth; x++){
				if(1 == pInfo->ViewInfo.IsChangeColor){
					Red = pInfo->ViewInfo.Color & 0xff;
					Green = (pInfo->ViewInfo.Color >> 8) & 0xff;
					Blue = (pInfo->ViewInfo.Color >> 16) & 0xff;
					pBuffer += 3;
				}else{
					Red 		= *pBuffer++;
					Green 		= *pBuffer++;
					Blue 		= *pBuffer++;
				}
				Alpha		= *pBuffer++;
				Alpha 			= (Alpha * pInfo->AlphaValue) >> 8;
#if (24 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Color = (Alpha << 24) | ((U32)Red << 16) | (Green << 8) | Blue;
#elif (16 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Color = ((Red & 0xf8) << 8) | ((Green & 0xfc) << 3) | ((Blue & 0xf8) >> 3);
				//Color = LCD_L0_Color2Index(((U32)Red << 16) | (Green << 8) | Blue);
#endif
				LCD_SetPixelIndex(DrawPosX + pInfo->OffestX, DrawPosY + pInfo->OffestY, Color, Alpha);
				//LCD_L0_SetPixelIndex(DrawPosX + pInfo->OffestX, DrawPosY + pInfo->OffestY, Color, Alpha);
				DrawPosX++;
			}
			DrawPosX = 0;
			DrawPosY++;
		}
	}else if(IMAGEVIEW_COLOR_TYPE_RGB == pInfo->ViewInfo.ColorType){
		if(24 == pInfo->ViewInfo.ColorDepth){
			BytesPerLine = pInfo->ViewInfo.Width * 3;
			for(y = pInfo->StartY; y < pInfo->DrawHeight; y++){
				pBuffer = pInfo->ViewInfo.pBuffer + y * BytesPerLine + pInfo->StartX * 3;
				for(x = pInfo->StartX; x < pInfo->DrawWidth; x++){
					if(1 == pInfo->ViewInfo.IsChangeColor){
						Color = pInfo->ViewInfo.Color;
						Alpha = (Color >> 24) & 0xff;;
					}else{
						Red 		= *pBuffer++;
						Green 		= *pBuffer++;
						Blue 		= *pBuffer++;
					}
#if (24 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Color = (Alpha << 24) | ((U32)Red << 16) | (Green << 8) | Blue;
#elif (16 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Color = ((Red & 0xf8) << 8) | ((Green & 0xfc) << 3) | ((Blue & 0xf8) >> 3);
				//Color = LCD_L0_Color2Index(((U32)Red << 16) | (Green << 8) | Blue);
#endif
					LCD_SetPixelIndex(DrawPosX + pInfo->OffestX, DrawPosY + pInfo->OffestY, Color, pInfo->AlphaValue);
					DrawPosX++;
				}
				DrawPosX = 0;
				DrawPosY++;
			}
		}
	}
}
static void _CalculationDrawInfo(IMAGEVIEW_Handle hObj, _DrawInfo *pInfo, U8 Flag)
{
	ImageViewInfo_t tViewInfo;
	GUI_RECT ViewRect, InvailRect;
	GUI_RECT ViewDrawRect, IntersectRect;
	I32 ViewWidth = 0, ViewHeight = 0;
	I32 OffestX = 0, OffestY = 0;
	I32 DrawWidth = 0, DrawHeight = 0;
	I32 StoreX = 0, y = 0;
	tViewInfo = pInfo->ViewInfo;
	if((0 == tViewInfo.Width) || (0 == tViewInfo.Height)){
		return;
	}
	ViewWidth = WM_GetWindowSizeX(hObj);
	ViewHeight = WM_GetWindowSizeY(hObj);
	if(ViewWidth >= tViewInfo.Width){
		OffestX = ViewWidth/2 - tViewInfo.Width/2;
		DrawWidth = tViewInfo.Width;
	}else{
		DrawWidth = ViewWidth;
	}
	if(ViewHeight >= tViewInfo.Height){
		OffestY = ViewHeight/2 - tViewInfo.Height/2;
		DrawHeight = tViewInfo.Height;
	}else{
		DrawHeight = ViewHeight;
	}
	if(Flag){
		pInfo->OffestX = OffestX;
		pInfo->OffestY = OffestY;
		return;
	}
	WM_GetInvalidRect(hObj, &InvailRect);
	WM_GetWindowRectEx(hObj, &ViewRect);
	WM_RectSet(&ViewDrawRect, ViewRect.x0 + OffestX, ViewRect.y0 + OffestY,
			ViewRect.x0 + OffestX + DrawWidth - 1, ViewRect.y0 + OffestY + DrawHeight - 1);
	WM_RectIntersect(&IntersectRect, &InvailRect, &ViewDrawRect);
	OffestX = IntersectRect.x0;
	OffestY = IntersectRect.y0;
	if(ViewDrawRect.x0 >= InvailRect.x0){
		StoreX = 0;
	}else{
		StoreX = InvailRect.x0 - ViewDrawRect.x0;
	}
	if(ViewDrawRect.y0 >= InvailRect.y0){
		y = 0;
	}else{
		y = InvailRect.y0 - ViewDrawRect.y0;
	}
	DrawWidth = GUI_RectGetWidth(&IntersectRect) + StoreX;
	DrawHeight = GUI_RectGetHeight(&IntersectRect) + y;
	pInfo->DrawHeight = DrawHeight;
	pInfo->DrawWidth = DrawWidth;
	pInfo->OffestX = OffestX;
	pInfo->OffestY = OffestY;
	pInfo->StartX = StoreX;
	pInfo->StartY = y;
	pInfo->ViewInfo = tViewInfo;
}
#define USE_PRINTF_DRAW_TAKE_TIME 		0
#if USE_PRINTF_DRAW_TAKE_TIME
static long RecodeTime = 0;
static long get_system_time_us(void)
{
	struct timeval tv;
	long time;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return time;
}
#endif
static void _Paint(IMAGEVIEW_Obj* pObj, IMAGEVIEW_Handle hObj) {
	WM_Obj *pWin;
	pWin = WM_H2P(hObj);
#if USE_PRINTF_DRAW_TAKE_TIME
	RecodeTime = get_system_time_us();
#endif
	if(pWin->Status & WM_SF_ISVIS)
	{
		ImageViewInfo_t tViewInfo;

		if(pObj->BackgroundColor & 0xff000000){
			GUI_SetBkColor(pObj->BackgroundColor);
			GUI_Clear();
		}
		if(IMAGEVIEW_COLOR_TYPE_BITMAP == pObj->ImageViewInfo.ColorType){
			U8 PreMode;
			_DrawInfo Info;
			if(pObj->RotateAngle){
				goto DRAW_ROTAT;
			}
			Info.ViewInfo = pObj->ImageViewInfo;
			Info.AlphaValue = pObj->AlphaValue;
			PreMode = GUI_GetDrawBitmapHasTrans();
			_CalculationDrawInfo(hObj, &Info, 1);
			if(IMAGE_BITMAP_HAS_TRANS == (pObj->Status & IMAGE_BITMAP_HAS_TRANS)){
				GUI_SetDrawBitmapHasTrans(1);
				GUI_SetDrawBitmapTransColor(pObj->BitmapTransColor);
			}
			if(1 == Info.ViewInfo.IsChangeColor){
				GUI_SetBitmapChangeColor(Info.ViewInfo.Color);
			}
			GUI_SetBitmapAlpha(Info.AlphaValue);
			GUI_DrawBitmap((GUI_BITMAP *)Info.ViewInfo.pExt, Info.OffestX, Info.OffestY);
			GUI_SetDrawBitmapHasTrans(PreMode);
#if USE_PRINTF_DRAW_TAKE_TIME
			GUI_Debug("Draw bitmap size %dx%d take time:%u us\n", Info.ViewInfo.Width, Info.ViewInfo.Height, get_system_time_us() - RecodeTime);
#endif
			return;
		}
		if(IMAGE_IS_MAPPING == (IMAGE_IS_MAPPING & pObj->Status)){

		}else if(IMAGE_DECODE_SAVE != (IMAGE_DECODE_SAVE & pObj->Status)){
			__ImageDecode(&pObj->ImageViewInfo);
		}

		tViewInfo = pObj->ImageViewInfo;
		if(tViewInfo.pBuffer){
DRAW_ROTAT:
			if(pObj->RotateAngle){
				ImageRotateInfo Info;
				I32 ViewWidth = 0, ViewHeight = 0;
				ViewWidth = WM_GetWindowSizeX(hObj);
				ViewHeight = WM_GetWindowSizeY(hObj);
				if(IMAGEVIEW_COLOR_TYPE_BITMAP == pObj->ImageViewInfo.ColorType){
					tViewInfo = pObj->ImageViewInfo;
					GUI_BITMAP *tBitmap = (GUI_BITMAP *)tViewInfo.pExt;
					Info.ImageWidth = tBitmap->XSize;
					Info.ImageHeight = tBitmap->YSize;
					Info.ImageColorDepth = tBitmap->BitsPerPixel;
					Info.pImageData = tBitmap->pData;
					if(16 == Info.ImageColorDepth){
						Info.PixelFormat = ROTATE_PIXEL_FORMAT_RGB565;
					}else if(24 == Info.ImageColorDepth){
						Info.PixelFormat = ROTATE_PIXEL_FORMAT_ARGB8565;
					}
				}else{
					Info.ImageWidth = tViewInfo.Width;
					Info.ImageHeight = tViewInfo.Height;
					Info.ImageColorDepth = tViewInfo.ColorDepth;
					Info.pImageData = tViewInfo.pBuffer;
					if(24 == Info.ImageColorDepth){
						Info.PixelFormat = ROTATE_PIXEL_FORMAT_RGB888;
					}else if(32 == Info.ImageColorDepth){
						Info.PixelFormat = ROTATE_PIXEL_FORMAT_ARGB8888;
					}
				}
				Info.DstWidth = ViewWidth;
				Info.DstHeight = ViewHeight;
				Info.RotatAngle = pObj->RotateAngle;
				Info.RotatX = 0;
				Info.RotatY = 0;
				GUI_ImageDrawRotate(pObj->Widget.Win.Rect.x0, pObj->Widget.Win.Rect.y0, &Info);
			}else{
				_DrawInfo Info;
				Info.ViewInfo = tViewInfo;
				Info.AlphaValue = pObj->AlphaValue;
				_CalculationDrawInfo(hObj, &Info, 0);
				_DrawImage(&Info);
			}
		}
		if(IMAGE_DECODE_SAVE != (IMAGE_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->ImageViewInfo);
		}
#if USE_PRINTF_DRAW_TAKE_TIME
		//GUI_Debug("Draw size %dx%d take time:%u us\n", Info.ViewInfo.Width, Info.ViewInfo.Height, get_system_time_us() - RecodeTime);
#endif
	}
}

static void _NotifyOwner(IMAGEVIEW_Handle hObj, I32 Notification)
{
	WM_MESSAGE Msg = {0};
	WM_HMEM hOwner;
	hOwner = WM_GetParent(hObj);
	Msg.MsgId  = WM_NOTIFY_PARENT;
	Msg.Data.v = Notification;
	Msg.hWinSrc= hObj;
	WM__SendMessage(hOwner, &Msg);
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(IMAGEVIEW_Handle hObj, IMAGEVIEW_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	/* Something happened in our area (pressed or released) */
	if (pMsg->Data.p) {
		if (pState->Pressed == 0) {
			_NotifyOwner(hObj, WM_NOTIFICATION_RELEASED);
		}else{
			_NotifyOwner(hObj, WM_NOTIFICATION_CLICKED);
		}
	}else{
		/* Touch up */
		_NotifyOwner(hObj, WM_NOTIFICATION_MOVED_OUT);
	}
}


/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(IMAGEVIEW_Handle hObj, WM_MESSAGE*pMsg)
{
	const WM_KEY_INFO* pKeyInfo;
	I32 Key;
	pKeyInfo = (const WM_KEY_INFO*)(pMsg->Data.p);
	Key = pKeyInfo->Key;
	if (pKeyInfo->PressedCnt > 0) {
		switch (Key) {
			case GUI_KEY_RIGHT:

			break;                    /* Send to parent by not doing anything */
			case GUI_KEY_LEFT:

			break;                    /* Send to parent by not doing anything */
			default:
			return;
		}
	}
}
static void _OnDelete(IMAGEVIEW_Obj *pObj)
{
	if(IMAGEVIEW_COLOR_TYPE_BITMAP == pObj->ImageViewInfo.ColorType){
		return;
	}
	if(IMAGE_DECODE_SAVE == (IMAGE_DECODE_SAVE & pObj->Status)){
		GUI_ImageResRelease(&pObj->ImageViewInfo);
	}
	if(pObj->hpText){
		GUI_ALLOC_FreePtr(&pObj->hpText);
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
*       IMAGEVIEW_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
IMAGEVIEW_Obj * IMAGEVIEW_h2p(IMAGEVIEW_Handle h)
{
	IMAGEVIEW_Obj * p = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(h);
	if (p) {
		if (p->DebugId != IMAGEVIEW_ID) {
			GUI_DEBUG_ERROROUT("IMAGEVIEW.c: Wrong handle type or Object not init'ed");
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
*       IMAGEVIEW_Callback
*/
void IMAGEVIEW_Callback (WM_MESSAGE *pMsg)
{
	IMAGEVIEW_Handle hObj;
	IMAGEVIEW_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			GUI_DEBUG_LOG("IMAGEVIEW: _Callback(WM_PAINT)\n");
			_Paint(pObj, hObj);
		return;
		case WM_PID_STATE_CHANGED:
			GUI_DEBUG_LOG("TEXT: _Callback(WM_PID_STATE_CHANGED)\n");
			{
				const WM_PID_STATE_CHANGED_INFO* pInfo = (const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p;
				if (pInfo->State) {
					_NotifyOwner(hObj, WM_NOTIFICATION_CLICKED);
				}
			}
		return;
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
			return;
		case WM_MOVE:
			GUI_DEBUG_LOG("IMAGEVIEW: _Callback(WM_MOVE)\n");
		return;
		case WM_DELETE:
			GUI_DEBUG_LOG("IMAGEVIEW: _Callback(WM_DELETE)\n");
			_OnDelete(pObj);
		break;
		case WM_KEY:
			_OnKey(hObj, pMsg);
		return;
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

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */

/*********************************************************************
*
*       IMAGEVIEW_CreateEx
*/
IMAGEVIEW_Handle IMAGEVIEW_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	IMAGEVIEW_Handle hObj;
	/* Create the window */
	/*
	#if IMAGEVIEW_SUPPORT_TRANSPARENCY
	WinFlags |= WM_CF_HASTRANS;
	#endif
	*/
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, IMAGEVIEW_Callback, sizeof(IMAGEVIEW_Obj) - sizeof(WM_Obj));
	if (hObj) {
		IMAGEVIEW_Obj * pObj;
		//U16 InitState;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		//InitState = WIDGET_STATE_FOCUSSABLE;
		//if (ExFlags & IMAGEVIEW_CF_VERTICAL) {
		//	InitState |= WIDGET_CF_VERTICAL;
		//}
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		pObj->ImageViewInfo.pFile = NULL;
		pObj->AlphaValue = 0xff;
		/* init member variables */
		IMAGEVIEW_INIT_ID(pObj);
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "IMAGEVIEW_Create failed")
	}
	return hObj;
}
void IMAGEVIEW_SetFile(IMAGEVIEW_Handle hObj, const char *pFile, U8 Flag)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		U8 Res = 0;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		if(GUI__SetText(&pObj->hpText, pFile)){
			char *pText = (char *)GUI_ALLOC_h2p(pObj->hpText);
			pObj->ImageViewInfo.pFile = pText;
			Res = 1;
		}else{
			return;
		}
		pObj->ImageViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_NONE;
		pObj->Status &= ~IMAGE_IS_MAPPING;
		if((1 == Flag) && (IMAGE_DECODE_SAVE != (IMAGE_DECODE_SAVE & pObj->Status))){
			pObj->Status |= IMAGE_DECODE_SAVE;
			__ImageDecode(&pObj->ImageViewInfo);
		}else if((1 == Flag) && (IMAGE_DECODE_SAVE == (IMAGE_DECODE_SAVE & pObj->Status))){
			GUI_ImageResRelease(&pObj->ImageViewInfo);
			__ImageDecode(&pObj->ImageViewInfo);
		}else if((0 == Flag) && (IMAGE_DECODE_SAVE == (IMAGE_DECODE_SAVE & pObj->Status))){
			pObj->Status &= ~IMAGE_DECODE_SAVE;
			GUI_ImageResRelease(&pObj->ImageViewInfo);
		}

		if(Res){
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEVIEW_SetBitmap(IMAGEVIEW_Handle hObj, const GUI_BITMAP *pBitmap)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->hpText){
			GUI_ALLOC_FreePtr(&pObj->hpText);
		}
		if(IMAGE_DECODE_SAVE == (IMAGE_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->ImageViewInfo);
		}
		pObj->Status = IMAGE_DECODE_NONE;
		if(pObj->ImageViewInfo.pExt != (void *)pBitmap){
			GUI_memset(&pObj->ImageViewInfo, 0, sizeof(ImageViewInfo_t));
			pObj->ImageViewInfo.pExt = (void *)pBitmap;
			pObj->ImageViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_BITMAP;
			pObj->ImageViewInfo.Width =  pBitmap->XSize;
			pObj->ImageViewInfo.Height = pBitmap->YSize;
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEVIEW_SetBitmapHasTrans(IMAGEVIEW_Handle hObj, GUI_COLOR TransColor)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->BitmapTransColor = TransColor;
		pObj->Status |= IMAGE_BITMAP_HAS_TRANS;
	}
}
void IMAGEVIEW_ClearBitmapHasTrans(IMAGEVIEW_Handle hObj)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->Status &= ~IMAGE_BITMAP_HAS_TRANS;
	}
}

void IMAGEVIEW_SetChangeColor(IMAGEVIEW_Handle hObj, GUI_COLOR Color)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		if((pObj->ImageViewInfo.Color != Color) || (0 == pObj->ImageViewInfo.IsChangeColor)){
			pObj->ImageViewInfo.IsChangeColor = 1;
			pObj->ImageViewInfo.Color = Color;
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEVIEW_SetBkColor(IMAGEVIEW_Handle hObj,GUI_COLOR color)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->BackgroundColor != color){
			pObj->BackgroundColor = color;
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEVIEW_SetRotateAngle(IMAGEVIEW_Handle hObj, I16 Angle)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->RotateAngle != Angle){
			I32 Width, Height;
			I32 x, y, MidX, MidY;
			Width = WM_GetWindowSizeX(hObj);
			Height = WM_GetWindowSizeY(hObj);
			x = WM_GetWindowOrgX(hObj);
			y = WM_GetWindowOrgY(hObj);
			MidX = x + (Width >> 1);
			MidY = y + (Height >> 1);
			Width = GUI_MATH_MAX(Width, Height);
			pObj->RotateAngle = Angle%360;
			WM_SetWindowPosAndSize(hObj, MidX - Width/2, MidY - Width/2, Width, Width);
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEVIEW_SetAlpha(IMAGEVIEW_Handle hObj, U8 Alpha)
{
	if(hObj){
		IMAGEVIEW_Obj* pObj;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->AlphaValue != Alpha){
			pObj->AlphaValue = Alpha;
			WM_InvalidateWindow(hObj);
		}
	}
}
/*
 * Only when hMap IMAGE_DECODE_SAVE is vaild to copy
 * */
void IMAGEVIEW_SetMapping(IMAGEVIEW_Handle hObj, IMAGEVIEW_Handle hMap)
{
	if(hObj && hMap){
		IMAGEVIEW_Obj *pObj, *pMap;
		pObj = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hObj);
		pMap = (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(hMap);
		if(IMAGE_DECODE_SAVE != (pMap->Status & IMAGE_DECODE_SAVE)){
			return;
		}
		pObj->Status |= IMAGE_IS_MAPPING;
		if(IMAGE_DECODE_SAVE == (IMAGE_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->ImageViewInfo);
		}
		if(pObj->hpText){
			GUI_ALLOC_FreePtr(&pObj->hpText);
			pObj->hpText = WM_HWIN_NULL;
		}
		GUI_memcpy(&pObj->ImageViewInfo, &pObj->ImageViewInfo, sizeof(ImageViewInfo_t));
	}
}
//void SetDefaultImageViewDraw()

#else /* avoid empty object files */

void IMAGEVIEW_C(void);
void IMAGEVIEW_C(void){}

#endif  /* #if GUI_WINSUPPORT */


	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
