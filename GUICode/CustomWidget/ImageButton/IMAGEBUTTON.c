

#include "GUI_Protected.h"
#include "IMAGEBUTTON_Private.h"
#include "WIDGET.h"



#if GUI_WINSUPPORT && IMAGEBUTTON_SUPPORT

#ifndef   IMAGEBUTTON_BKCOLOR0_DEFAULT
  #define IMAGEBUTTON_BKCOLOR0_DEFAULT   GUI_RED
#endif

typedef struct
{
	U32 DrawHeight;
	U32 DrawWidth;
	U32 StartX;
	U32 StartY;
	U32 OffestX;
	U32 OffestY;
	ImageViewInfo_t ViewInfo;
}_DrawInfo;

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
		GUI_Debug("image format is error, %s\n", pInfo->pFile);
		return 0;
	}
	return 1;
}

static void _DrawImage(_DrawInfo *pInfo)
{
	const U8 *pBuffer = NULL;
	U8 Red = 0, Green = 0, Blue = 0;
	U8 Alpha = 0;
	U32 BytesPerLine = 0;
	I32 DrawPosX = 0, DrawPosY = 0;
	I32 x = 0, y = 0;
	GUI_COLOR Color = 0;
	pBuffer = pInfo->ViewInfo.pBuffer;
	if(IMAGEVIEW_COLOR_TYPE_ARGB == pInfo->ViewInfo.ColorType){
		BytesPerLine = ((32 * pInfo->ViewInfo.Width + 31) >> 5) << 2;
		for(y = pInfo->StartY; y < pInfo->DrawHeight; y++){
			pBuffer = pInfo->ViewInfo.pBuffer + y * BytesPerLine + pInfo->StartX * 4;
			for(x = pInfo->StartX; x < pInfo->DrawWidth; x++){
				Red 		= *pBuffer++;
				Green 		= *pBuffer++;
				Blue 		= *pBuffer++;
				Alpha		= *pBuffer++;

				//Color = LCD_Color2Index((Alpha << 24) | ((U32)Blue << 16) | (Green << 8) | Red);
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
					Red 		= *pBuffer++;
					Green 		= *pBuffer++;
					Blue 		= *pBuffer++;
					//Color = LCD_Color2Index((0xff << 24) | ((U32)Blue << 16) | (Green << 8) | Red);
					//Color = (Alpha << 24) | ((U32)Red << 16) | (Green << 8) | Blue;
#if (24 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Color = (Alpha << 24) | ((U32)Red << 16) | (Green << 8) | Blue;
#elif (16 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Color = ((Red & 0xf8) << 8) | ((Green & 0xfc) << 3) | ((Blue & 0xf8) >> 3);
				//Color = LCD_L0_Color2Index(((U32)Red << 16) | (Green << 8) | Blue);
#endif
					LCD_SetPixelIndex(DrawPosX + pInfo->OffestX, DrawPosY + pInfo->OffestY, Color, 0xff);
					DrawPosX++;
				}
				DrawPosX = 0;
				DrawPosY++;
			}
		}
	}
}
static void _CalculationDrawInfo(IMAGEBUTTON_Handle hObj, _DrawInfo *pInfo, U8 Flag)
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
static void _Paint(IMAGEBUTTON_Obj* pObj, IMAGEBUTTON_Handle hObj) 
{
	WM_Obj *pWin;
	/*if(!WM__IsEnabled(hObj)){
			return;
	}*/
	pWin = WM_H2P(hObj);
	if(pWin->Status & WM_SF_ISVIS)
	{
		I32 PressState;
		U8 DecodeFlag = 0;
		ImageViewInfo_t tViewInfo;
		_DrawInfo Info;
		PressState = (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED) ? 1 : 0;
		if(pObj->BkColor & 0xff000000){
			GUI_SetBkColor(pObj->BkColor);
			GUI_Clear();
		}
		if(PressState){
			if(IMAGEVIEW_COLOR_TYPE_BITMAP == pObj->FocusViewInfo.ColorType){
				U8 PreMode;
				Info.ViewInfo = pObj->FocusViewInfo;
				PreMode = GUI_GetBitmapHasTrans();
				if(IMAGE_BITMAP_FOCUS_HAS_TRANS == (pObj->Status & IMAGE_BITMAP_FOCUS_HAS_TRANS)){
					GUI_SetBitmapHasTrans(1);
					GUI_SetBitmapTransColor(pObj->FocusBitmapTransColor);
				}
				_CalculationDrawInfo(hObj, &Info, 1);
				GUI_DrawBitmap((GUI_BITMAP *)Info.ViewInfo.pExt, Info.OffestX, Info.OffestY);
				GUI_SetBitmapHasTrans(PreMode);
				return;
			}
			if(IMAGE_FOCUS_DECODE_SAVE != (IMAGE_FOCUS_DECODE_SAVE & pObj->Status)){
				DecodeFlag = 1;
				__ImageDecode(&pObj->FocusViewInfo);
			}
			tViewInfo = pObj->FocusViewInfo;
		}else{
			if(IMAGEVIEW_COLOR_TYPE_BITMAP == pObj->UnFocusViewInfo.ColorType){
				U8 PreMode;
				Info.ViewInfo = pObj->UnFocusViewInfo;
				PreMode = GUI_GetBitmapHasTrans();
				if(IMAGE_BITMAP_UNFOCUS_HAS_TRANS == (pObj->Status & IMAGE_BITMAP_UNFOCUS_HAS_TRANS)){
					GUI_SetDrawMode(GUI_DRAWMODE_TRANS);
					GUI_SetBitmapTransColor(pObj->UnFocusBitmapTransColor);
				}
				_CalculationDrawInfo(hObj, &Info, 1);
				GUI_DrawBitmap((GUI_BITMAP *)Info.ViewInfo.pExt, Info.OffestX, Info.OffestY);
				GUI_SetBitmapHasTrans(PreMode);
				return;
			}
			if(IMAGE_UNFOCUS_DECODE_SAVE != (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status)){
				DecodeFlag = 2;
				__ImageDecode(&pObj->UnFocusViewInfo);
			}
			tViewInfo = pObj->UnFocusViewInfo;
		}
		if(tViewInfo.pBuffer){
			Info.ViewInfo = tViewInfo;
			_CalculationDrawInfo(hObj, &Info, 0);
			_DrawImage(&Info);
		}else{
			GUI_Debug("buffer is null\n");
		}
		if(1 == DecodeFlag){
			GUI_ImageResRelease(&pObj->FocusViewInfo);
		}else if(2 == DecodeFlag){
			GUI_ImageResRelease(&pObj->UnFocusViewInfo);
		}
	}
}

static void _OnDelete(IMAGEBUTTON_Obj *pObj)
{
	if(IMAGE_FOCUS_DECODE_SAVE == (IMAGE_FOCUS_DECODE_SAVE & pObj->Status)){
		GUI_ImageResRelease(&pObj->FocusViewInfo);
	}
	if(IMAGE_UNFOCUS_DECODE_SAVE == (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status)){
		GUI_ImageResRelease(&pObj->UnFocusViewInfo);
	}
	if(pObj->hFocusText){
		GUI_ALLOC_FreePtr(&pObj->hFocusText);
	}
	if(pObj->hUnFocusText){
		GUI_ALLOC_FreePtr(&pObj->hUnFocusText);
	}
}
static void _OnImageButtonPressed(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Obj* pObj) 
{
	WIDGET_OrState(hObj, IMAGEBUTTON_STATE_PRESSED);
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}
static void _OnImageButtonReleased(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Obj* pObj, I32 Notification) 
{
	WIDGET_AndState(hObj, IMAGEBUTTON_STATE_PRESSED);
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, Notification);
	}
}
static void _OnTouch(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Obj* pObj, WM_MESSAGE*pMsg) 
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
		if (pState->Pressed) {
			if ((pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED) == 0){
				_OnImageButtonPressed(hObj, pObj);
			}
		} else {
			/* React only if button was pressed before ... avoid problems with moving / hiding windows above (such as dropdown) */
			if (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED) {
				_OnImageButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
			}
		}
	} else {
		_OnImageButtonReleased(hObj, pObj, WM_NOTIFICATION_MOVED_OUT);
	}
}
static void IMAGEBUTTON_Callback (WM_MESSAGE *pMsg) 
{
	IMAGEBUTTON_Handle hObj;
	IMAGEBUTTON_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
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
		case WM_DELETE:
			_OnDelete(pObj);
		break;
		case WM_KEY:
		break;
	}
	WM_DefaultProc(pMsg);
}
IMAGEBUTTON_Handle IMAGEBUTTON_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	IMAGEBUTTON_Handle hObj;
	/* Create the window */
	WinFlags |= WM_CF_HASTRANS;
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, IMAGEBUTTON_Callback, sizeof(IMAGEBUTTON_Obj) - sizeof(WM_Obj));
	if (hObj) {
		IMAGEBUTTON_Obj * pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		/* init member variables */
		IMAGEBUTTON_INIT_ID(pObj);

	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	return hObj;
}


void IMAGEBUTTON_SetFocusFile(IMAGEBUTTON_Handle hObj, void *pFile, U8 Flag)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		U8 Res = 0;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		if(GUI__SetText(&pObj->hFocusText, pFile)){
			char *pText = (char *)GUI_ALLOC_h2p(pObj->hFocusText);
			pObj->FocusViewInfo.pFile = pText;
			Res = 1;
		}else{
			return;
		}
		pObj->FocusViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_NONE;
		pObj->Status &= ~IMAGE_FOCUS_IS_MAPPING;
		if((1 == Flag) && (IMAGE_FOCUS_DECODE_SAVE != (IMAGE_FOCUS_DECODE_SAVE & pObj->Status))){
			pObj->Status |= IMAGE_FOCUS_DECODE_SAVE;
			__ImageDecode(&pObj->FocusViewInfo);
		}else if((1 == Flag) && (IMAGE_FOCUS_DECODE_SAVE == (IMAGE_FOCUS_DECODE_SAVE & pObj->Status))){
			GUI_ImageResRelease(&pObj->FocusViewInfo);
			__ImageDecode(&pObj->FocusViewInfo);
		}else if((0 == Flag) && (IMAGE_FOCUS_DECODE_SAVE == (IMAGE_FOCUS_DECODE_SAVE & pObj->Status))){
			pObj->Status &= ~IMAGE_FOCUS_DECODE_SAVE;
			GUI_ImageResRelease(&pObj->FocusViewInfo);
		}
		if(Res && (IMAGEBUTTON_STATE_PRESSED == (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED))){
			WM_InvalidateWindow(hObj);
		}
	}
}

void IMAGEBUTTON_SetUnFocusFile(IMAGEBUTTON_Handle hObj, void *pFile, U8 Flag)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		U8 Res = 0;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		if(GUI__SetText(&pObj->hUnFocusText, pFile)){
			char *pText = (char *)GUI_ALLOC_h2p(pObj->hUnFocusText);
			pObj->UnFocusViewInfo.pFile = pText;
			Res = 1;
		}else{
			return;
		}
		pObj->UnFocusViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_NONE;
		pObj->Status &= ~IMAGE_UNFOCUS_IS_MAPPING;
		if((1 == Flag) && (IMAGE_UNFOCUS_DECODE_SAVE != (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status))){
			pObj->Status |= IMAGE_UNFOCUS_DECODE_SAVE;
			__ImageDecode(&pObj->UnFocusViewInfo);
		}else if((1 == Flag) && (IMAGE_UNFOCUS_DECODE_SAVE == (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status))){
			GUI_Debug("Before iamge is decode save\n");
			GUI_ImageResRelease(&pObj->UnFocusViewInfo);
			__ImageDecode(&pObj->UnFocusViewInfo);
		}else if((0 == Flag) && (IMAGE_UNFOCUS_DECODE_SAVE == (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status))){
			pObj->Status &= ~IMAGE_UNFOCUS_DECODE_SAVE;
			GUI_ImageResRelease(&pObj->UnFocusViewInfo);
		}
		if(Res && (IMAGEBUTTON_STATE_PRESSED != (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED))){
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEBUTTON_SetBkColor(IMAGEBUTTON_Handle hObj, GUI_COLOR Color)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->BkColor = Color;
	}
}
void IMAGEBUTTON_SetState(IMAGEBUTTON_Handle hObj, U8 State)
{
	if(State > 1){
		return;
	}
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		U8 CurrentState = 0;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		CurrentState = (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED) ? 1 : 0;
		if(State != CurrentState){
			if(State){
				WIDGET_OrState(hObj, IMAGEBUTTON_STATE_PRESSED);
			}else{
				WIDGET_AndState(hObj, IMAGEBUTTON_STATE_PRESSED);
			}
		}
	}
}
/*
 * Only when hMap IMAGE_FOCUS_DECODE_SAVE is vaild to copy
 * */
void IMAGEBUTTON_SetFocusMapping(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Handle hMap)
{
	if(hObj && hMap){
		IMAGEBUTTON_Obj *pObj, *pMap;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pMap = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hMap);
		if(IMAGE_FOCUS_DECODE_SAVE != (pMap->Status & IMAGE_FOCUS_DECODE_SAVE)){
			return;
		}
		pObj->FocusViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_NONE;
		pObj->Status |= IMAGE_FOCUS_IS_MAPPING;
		if(IMAGE_FOCUS_DECODE_SAVE == (IMAGE_FOCUS_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->FocusViewInfo);
		}
		if(pObj->hFocusText){
			GUI_ALLOC_FreePtr(&pObj->hFocusText);
			pObj->hFocusText = WM_HWIN_NULL;
		}
		GUI_memcpy(&pObj->FocusViewInfo, &pMap->FocusViewInfo, sizeof(ImageViewInfo_t));
		if(IMAGEBUTTON_STATE_PRESSED == (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED)){
			WM_InvalidateWindow(hObj);
		}
	}
}
/*
 * Only when hMap IMAGE_UNFOCUS_IS_MAPPING is vaild to copy
 * */
void IMAGEBUTTON_SetUnFocusMapping(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Handle hMap)
{
	if(hObj && hMap){
		IMAGEBUTTON_Obj *pObj, *pMap;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pMap = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hMap);
		if(IMAGE_UNFOCUS_DECODE_SAVE != (pMap->Status & IMAGE_UNFOCUS_DECODE_SAVE)){
			return;
		}
		pObj->UnFocusViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_NONE;
		pObj->Status |= IMAGE_UNFOCUS_IS_MAPPING;
		if(IMAGE_UNFOCUS_DECODE_SAVE == (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->UnFocusViewInfo);
		}
		if(pObj->hUnFocusText){
			GUI_ALLOC_FreePtr(&pObj->hUnFocusText);
			pObj->hUnFocusText = WM_HWIN_NULL;
		}
		GUI_memcpy(&pObj->UnFocusViewInfo, &pMap->UnFocusViewInfo, sizeof(ImageViewInfo_t));
		if(IMAGEBUTTON_STATE_PRESSED != (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED)){
			WM_InvalidateWindow(hObj);
		}
	}
}

void IMAGEBUTTON_SetUnFocusBitmap(IMAGEBUTTON_Handle hObj, const GUI_BITMAP *pBitmap)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->hUnFocusText){
			GUI_ALLOC_FreePtr(&pObj->hUnFocusText);
		}
		if(IMAGE_UNFOCUS_DECODE_SAVE == (IMAGE_UNFOCUS_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->UnFocusViewInfo);
		}
		pObj->Status &= ~IMAGE_UNFOCUS_DECODE_SAVE;
		GUI_memset(&pObj->UnFocusViewInfo, 0, sizeof(ImageViewInfo_t));
		pObj->UnFocusViewInfo.pExt = (void *)pBitmap;
		pObj->UnFocusViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_BITMAP;
		pObj->UnFocusViewInfo.Width =  pBitmap->XSize;
		pObj->UnFocusViewInfo.Height = pBitmap->YSize;
		if(IMAGEBUTTON_STATE_PRESSED != (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED)){
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEBUTTON_SetUnFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj, GUI_COLOR TransColor)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->Status |= IMAGE_BITMAP_UNFOCUS_HAS_TRANS;
		pObj->UnFocusBitmapTransColor = TransColor;
	}
}
void IMAGEBUTTON_ClearUnFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->Status &= ~IMAGE_BITMAP_UNFOCUS_HAS_TRANS;
	}
}
void IMAGEBUTTON_SetFocusBitmap(IMAGEBUTTON_Handle hObj, const GUI_BITMAP *pBitmap)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->hFocusText){
			GUI_ALLOC_FreePtr(&pObj->hFocusText);
		}
		if(IMAGE_FOCUS_DECODE_SAVE == (IMAGE_FOCUS_DECODE_SAVE & pObj->Status)){
			GUI_ImageResRelease(&pObj->FocusViewInfo);
		}
		pObj->Status &= ~IMAGE_FOCUS_DECODE_SAVE;
		GUI_memset(&pObj->FocusViewInfo, 0, sizeof(ImageViewInfo_t));
		pObj->FocusViewInfo.pExt = (void *)pBitmap;
		pObj->FocusViewInfo.ColorType = IMAGEVIEW_COLOR_TYPE_BITMAP;
		pObj->FocusViewInfo.Width =  pBitmap->XSize;
		pObj->FocusViewInfo.Height = pBitmap->YSize;

		if(IMAGEBUTTON_STATE_PRESSED == (pObj->Widget.State & IMAGEBUTTON_STATE_PRESSED)){
			WM_InvalidateWindow(hObj);
		}
	}
}
void IMAGEBUTTON_SetFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj, GUI_COLOR TransColor)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->Status |= IMAGE_BITMAP_FOCUS_HAS_TRANS;
		pObj->FocusBitmapTransColor = TransColor;
	}
}
void IMAGEBUTTON_ClearFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj)
{
	if(hObj){
		IMAGEBUTTON_Obj* pObj;
		pObj = (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(hObj);
		pObj->Status &= ~IMAGE_BITMAP_FOCUS_HAS_TRANS;
	}
}
#endif 
