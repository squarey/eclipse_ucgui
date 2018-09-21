/*
 * LCDRLE16M.c
 *
 *  Created on: 2018年9月6日
 *      Author: Administrator
 */

#include "GUI_Private.h"
#include "LCD_Private.h"


static I32 _DisplayMode = 0;
static U8  _BitmapSwapRB = 0;
static U8  _BitmapWithAlpha = 0;

static U16 _Read16(const U8 GUI_UNI_PTR ** ppData)
{
	const U8 GUI_UNI_PTR * pData;
	U16  Value;
	pData = *ppData;
	Value = *pData;
	Value <<= 8;
	Value |= (U16)(*(pData + 1));
	pData += 2;
	*ppData = pData;
	return Value;
}

static LCD_PIXELINDEX _GetPixelIndex(const U8 GUI_UNI_PTR ** ppPixel)
{
	if(0 == GUI_Context.BitmapFlagChangeColor){
		U16 Data = _Read16(ppPixel);
		if (_DisplayMode == 565) {
			return (LCD_PIXELINDEX)Data;
		}
		if(1 == _BitmapSwapRB){
			return LCD_Color2Index(LCD_Index2Color_M565(Data));
		}
		return LCD_Color2Index(LCD_Index2Color_565(Data));
	}else{
		*ppPixel += 2;
		return LCD_Color2Index(GUI_Context.BitmapChangeColor);
	}
}

static void __DrawBitmap_RLE16M(I32 x0, I32 y0, I32 xsize, I32 ysize,
						const U8 GUI_UNI_PTR * pPixel, I32 xMag, I32 yMag)
{
	I32 y = 0;
	I32 xi = 0, xi1 = 0, DrawX0 = 0, DrawX1 = 0;
	I32 DrawSizeY = 0;
	U8 tPiexl = 0;
	U8 Flag = 0;
	U8 PreAlpha = 0;
	U32 Alpha = 0;
	U8 LeftNoDrawPixels = 0;
	U8 NumCompressedPixels = 0;
	I32 TotalPixels = 0, CurPixels = 0;
	LCD_PIXELINDEX PixelIndex = 0, OldColorIndex = 0;
	const U8 GUI_UNI_PTR * pPixeStart;
	//exp:
	//y0 = 20  ysize = 100  ClipRect.y1 = 110
	//
	_DisplayMode   = LCD_GetFixedPaletteEx(GUI_Context.SelLayer);
	OldColorIndex = LCD_ACOLORINDEX[1];
	if((y0 + ysize) > GUI_Context.ClipRect.y1 + 1){
		DrawSizeY = GUI_Context.ClipRect.y1 - y0 + 1;
	}else{
		DrawSizeY = ysize;
	}
	TotalPixels = xsize * ysize;
	pPixeStart = pPixel;
	PreAlpha = GUI_Context.Alpha;
	if(0 == _BitmapWithAlpha){
		GUI_Context.Alpha = GUI_Context.BitmapChangeAlpha;
	}
	while(CurPixels < TotalPixels){
		tPiexl = *pPixeStart++;
		NumCompressedPixels = (tPiexl & 0x7f);
		CurPixels += NumCompressedPixels;
		if(tPiexl & 0x80){
			xi1 += NumCompressedPixels;
			if(1 == _BitmapWithAlpha){
				GUI_Context.Alpha = *pPixeStart++;
				Alpha = (GUI_Context.Alpha * GUI_Context.BitmapChangeAlpha) >> 8;
				GUI_Context.Alpha = Alpha & 0xff;
			}
			PixelIndex = _GetPixelIndex(&pPixeStart);
			LCD_ACOLORINDEX[1] = PixelIndex;
			//绘制连续的点     xsize: 77  xi1 = 113 - 72 = 41
			//xi1 - NumCompressedPixels + k = xsize
			//k = xsize + NumCompressedPixels - xi1 +  = 77 + 72 - 113 = 36
			//LeftNoDrawPixels = NumCompressedPixels - k;
DRAW_NEXT_LINE:
			if(xi1 >= xsize){
				LeftNoDrawPixels = xi1 - xsize;
				//LeftNoDrawPixels = xi1 + xsize - NumCompressedPixels;
				xi1 = xsize;
				Flag = 1;
			}
			if(((y + y0) >= GUI_Context.ClipRect.y0) && ((y + y0) <= GUI_Context.ClipRect.y1)){
				if((x0 + xi) > GUI_Context.ClipRect.x0){
					DrawX0 = x0 + xi;
				}else{
					DrawX0 = GUI_Context.ClipRect.x0;
				}
				if((xi1 + x0 - 1) > GUI_Context.ClipRect.x1){
					DrawX1 = GUI_Context.ClipRect.x1;
				}else{
					DrawX1 = xi1 + x0 - 1;
				}
				//GUI_Debug("draw L x0:%d, y:%d, x1:%d, Alpha:0x%02x\n", DrawX0, y + y0, DrawX1, GUI_Context.Alpha);
				LCD_DrawHLine(DrawX0, y + y0, DrawX1);
			}
			xi = xi1;
			if(1 == Flag){
				y++;
				Flag = 0;
				xi = 0;
				xi1 = LeftNoDrawPixels;
				goto DRAW_NEXT_LINE;
			}
			//pPixeStart += 2;
			if(y >= DrawSizeY){
				break;
			}
		}else{
			//绘制不连续的点
			while(NumCompressedPixels > 0){
				if(1 == _BitmapWithAlpha){
					Alpha = *pPixeStart++;
					Alpha = (Alpha * GUI_Context.BitmapChangeAlpha) >> 8;
				}else{
					Alpha = GUI_Context.BitmapChangeAlpha;
				}
				PixelIndex = _GetPixelIndex(&pPixeStart);
				//GUI_Debug("draw x:%d, y:%d\n", x0 + xi, y + y0);
				if ((y + y0) >= GUI_Context.ClipRect.y0) {
					if (x0 + xi >= GUI_Context.ClipRect.x0) {
						if (x0 + xi <= GUI_Context.ClipRect.x1) {
							//GUI_Debug("draw x:%d, y:%d, Alpha:0x%02x\n", x0 + xi, y + y0, Alpha);
							//LCDDEV_L0_SetPixelIndex(x0 + xi, y + y0, PixelIndex, Alpha);
							LCD_SetPixelIndex(x0 + xi, y + y0, PixelIndex, Alpha);
						}
					}
				}
				xi++;
				if(xi >= xsize){
					xi = 0;
					y++;
				}
				xi1= xi;
				NumCompressedPixels--;
				//pPixeStart += 2;
				if(y >= DrawSizeY){
					break;
				}
			}
		}
	}
	GUI_Context.BitmapFlagChangeColor = 0;
	GUI_Context.Alpha = PreAlpha;
	LCD_ACOLORINDEX[1] = OldColorIndex;
	GUI_Context.BitmapChangeAlpha = 0xff;
}
static void _DrawBitmap_RLEM16M(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	_BitmapWithAlpha = 0;
	_BitmapSwapRB = 1;
	__DrawBitmap_RLE16M(x0, y0, xsize, ysize, pPixel, xMag, yMag);
}
static void _DrawBitmap_AlphaRLEM16M(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	_BitmapWithAlpha = 1;
	_BitmapSwapRB = 1;
	__DrawBitmap_RLE16M(x0, y0, xsize, ysize, pPixel, xMag, yMag);
}
static void _DrawBitmap_RLE16M(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	_BitmapWithAlpha = 0;
	_BitmapSwapRB = 0;
	__DrawBitmap_RLE16M(x0, y0, xsize, ysize, pPixel, xMag, yMag);
}
static void _DrawBitmap_AlphaRLE16M(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	_BitmapWithAlpha = 1;
	_BitmapSwapRB = 0;
	__DrawBitmap_RLE16M(x0, y0, xsize, ysize, pPixel, xMag, yMag);
}
const GUI_BITMAP_METHODS GUI_BitmapMethodsRLEM16M =
{
	_DrawBitmap_RLEM16M,
	NULL
};
const GUI_BITMAP_METHODS GUI_BitmapMethodAlphaRLEM16M =
{
	_DrawBitmap_AlphaRLEM16M,
	NULL
};
const GUI_BITMAP_METHODS GUI_BitmapMethodsRLE16M =
{
	_DrawBitmap_RLE16M,
	NULL
};
const GUI_BITMAP_METHODS GUI_BitmapMethodAlphaRLE16M =
{
	_DrawBitmap_AlphaRLE16M,
	NULL
};


void GUI_SetBitmapAlpha(U8 Alpha)
{
	GUI_Context.BitmapChangeAlpha = Alpha;
}

void GUI_SetBitmapChangeColor(GUI_COLOR Color)
{
	GUI_Context.BitmapFlagChangeColor = 1;
	GUI_Context.BitmapChangeColor = Color;
}


