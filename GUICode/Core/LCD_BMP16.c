/*
 * LCD_BMP16.c
 *
 *  Created on: 2018年9月11日
 *      Author: Administrator
 */

#include "GUI_Private.h"
#include "LCD_Private.h"

static I32 _DisplayMode = 0;
static U8  _BMPSwapRB = 0;
static U8  _BMPWithAlpha = 0;

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
		if(0 == _BMPSwapRB){
			return LCD_Color2Index(LCD_Index2Color_M565(Data));
		}
		return LCD_Color2Index(LCD_Index2Color_565(Data));
	}else{
		*ppPixel += 2;
		return LCD_Color2Index(GUI_Context.BitmapChangeColor);
	}
}

static void _DrawAlphaBMP16(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, I32 xMag, I32 yMag)
{
	LCD_PIXELINDEX PixelIndex;
	_DisplayMode   = LCD_GetFixedPaletteEx(GUI_Context.SelLayer);
	const U8 GUI_UNI_PTR * tpPixel, *pPixelStart;
	U32 Alpha = 0;
	I32 DrawSizeX = 0, DrawSizeY = 0;
	I32 x = 0, y = 0;
	I32 StartX = 0, StartY = 0;
	I32 BytesPerLine = 0;
	tpPixel = pPixel;
	pPixelStart = pPixel;
	DrawSizeX = xsize;
	_DisplayMode   = LCD_GetFixedPaletteEx(GUI_Context.SelLayer);
	if(x0 < GUI_Context.ClipRect.x0){
		StartX = GUI_Context.ClipRect.x0;
	}else{
		StartX = x0;
	}
	if((x0 + xsize) > (GUI_Context.ClipRect.x1 - GUI_Context.ClipRect.x0 + 1)){
		DrawSizeX = GUI_Context.ClipRect.x1 - GUI_Context.ClipRect.x0 + 1;
	}else{
		DrawSizeX = xsize;
	}
	if(y0 < GUI_Context.ClipRect.y0){
		StartY = GUI_Context.ClipRect.y0;
	}else{
		StartY = y0;
	}
	if((y0 + ysize) > (GUI_Context.ClipRect.y1 - GUI_Context.ClipRect.y0 + 1)){
		DrawSizeY = GUI_Context.ClipRect.y1 - GUI_Context.ClipRect.y0 + 1;
	}else{
		DrawSizeY = ysize;
	}
	if(1 == _BMPWithAlpha){
		BytesPerLine = xsize * 3;
	}else{
		BytesPerLine = xsize * 2;
	}

	pPixelStart += (StartY - y0)* BytesPerLine + StartX - x0;
	tpPixel = pPixelStart;
	for(y = 0; y < DrawSizeY; y++){
		for(x = 0; x < DrawSizeX; x++){
			if(1 == _BMPWithAlpha){
				Alpha = *tpPixel++;
			}else{
				Alpha = 0xff;
			}
			Alpha = (Alpha * GUI_Context.BitmapChangeAlpha) >> 8;
			PixelIndex = _GetPixelIndex(&tpPixel);
			LCD_SetPixelIndex(StartX + x, StartY + y, PixelIndex, Alpha);
		}
		pPixelStart += BytesPerLine;
		tpPixel = pPixelStart;
	}
}



static void _DrawBMPAlpha16M(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel,
									const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	_BMPSwapRB = 0;
	_BMPWithAlpha = 1;
	_DrawAlphaBMP16(x0, y0, xsize, ysize, pPixel, xMag, yMag);
}

static void _DrawBMPAlphaM16M(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel,
									const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	_BMPSwapRB = 1;
	_BMPWithAlpha = 1;
	_DrawAlphaBMP16(x0, y0, xsize, ysize, pPixel, xMag, yMag);
}

const GUI_BITMAP_METHODS GUI_BMPAlphaM16M =
{
	_DrawBMPAlphaM16M,
	NULL
};
const GUI_BITMAP_METHODS GUI_BMPAlpha16M =
{
	_DrawBMPAlpha16M,
	NULL
};
