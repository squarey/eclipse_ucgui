/*
*********************************************************************************************************
*                                                uC/GUI
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
File        : LCDDummy.C
Purpose     : Empty driver for emWin GSC
              This driver does no perform any function, but it can be
              used for 2 purposes:
              a) Satisfy all externals so an application can be
                compiled and linked in target hardware even if the
                driver is not already available
              b) Template for a starting point for a new driver.
----------------------------------------------------------------------   
Adapting to a new system (creating a new driver):
  In this case, the first step is to fill the routines 
  LCD_L0_GetPixelIndex, LCD_L0_SetPixelIndex and LCD_L0_Init with
  functionality, which is sufficient to make the hardware work.
  A second (optional) step would be to optimize higher level routines. 
----------------------------------------------------------------------   
Version-Date---Author-Explanation                                        
----------------------------------------------------------------------   
1.00.00 020417 JE     a) Changed to have only to adapt _GetPixelIndex
                         and _SetPixelIndex
0.90.00 020214 JE     a) First release
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
//#include "LCD_0.h"            /* Defines for first display */


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#ifndef LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif

/*********************************************
*
*       Macros for MIRROR_, SWAP_ and LUT_
*
**********************************************
*/

#if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) y
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) y
    #define LOG2PHYS_Y(x, y) x
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) x
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) y
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) x
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    //#error This combination of mirroring/swapping not yet supported
  #endif
#else
  #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) y
  #elif ( defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #endif
#endif

static LCD_Driver_t 	tLCD_Driver;

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/*********************************************
*
*       Draw Bitmap 1 BPP
*
**********************************************
*/

static void  _DrawBitLine1BPP(I32 x, I32 y, U8 const*p, I32 Diff, I32 xsize, const LCD_PIXELINDEX*pTrans) {
	LCD_PIXELINDEX Index0 = *(pTrans+0);
	LCD_PIXELINDEX Index1 = *(pTrans+1);
	x += Diff;
	switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
		case 0:
			do {
				LCD_L0_SetPixelIndex(x++, y, (*p & (0x80 >> Diff)) ? Index1 : Index0, 0xff);
				if (++Diff == 8) {
					Diff = 0;
					p++;
				}
			} while (--xsize);
		break;
		case LCD_DRAWMODE_TRANS:
			do {
				if (*p & (0x80 >> Diff))
					LCD_L0_SetPixelIndex(x, y, Index1, 0xff);
				x++;
				if (++Diff == 8) {
					Diff = 0;
					p++;
				}
			} while (--xsize);
		break;
		case LCD_DRAWMODE_XOR:;
			do {
				if (*p & (0x80 >> Diff)) {
					I32 Pixel = LCD_L0_GetPixelIndex(x, y);
					LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel, 0xff);
				}
				x++;
				if (++Diff == 8) {
					Diff = 0;
					p++;
				}
			} while (--xsize);
		break;
	}
}

/*********************************************
*
*       Draw Bitmap 2 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)
static void  _DrawBitLine2BPP(I32 x, I32 y, U8 const * p, I32 Diff, I32 xsize, const LCD_PIXELINDEX * pTrans)
{
	LCD_PIXELINDEX Pixels = *p;
	I32 CurrentPixel = Diff;
	x += Diff;
	switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
		case 0:
			do {
				I32 Shift = (3 - CurrentPixel) << 1;
				I32 Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
				LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
				LCD_L0_SetPixelIndex(x++, y, PixelIndex, 0xff);
				if (++CurrentPixel == 4) {
					CurrentPixel = 0;
					Pixels = *(++p);
				}
			} while (--xsize);
		break;
		case LCD_DRAWMODE_TRANS:
			do {
				I32 Shift = (3 - CurrentPixel) << 1;
				I32 Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
				if (Index) {
					LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
					LCD_L0_SetPixelIndex(x, y, PixelIndex, 0xff);
				}
				x++;
				if (++CurrentPixel == 4) {
					CurrentPixel = 0;
					Pixels = *(++p);
				}
			} while (--xsize);
		break;
	}
}
#endif

/*********************************************
*
*       Draw Bitmap 4 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 4)
static void  _DrawBitLine4BPP(I32 x, I32 y, U8 const * p, I32 Diff, I32 xsize, const LCD_PIXELINDEX * pTrans)
{
	LCD_PIXELINDEX Pixels = *p;
	I32 CurrentPixel = Diff;
	switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
		case 0:
			do {
				I32 Shift = (1 - CurrentPixel) << 2;
				I32 Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
				LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
				LCD_L0_SetPixelIndex(x++, y, PixelIndex, 0xff);
				if (++CurrentPixel == 2) {
					CurrentPixel = 0;
					Pixels = *(++p);
				}
			} while (--xsize);
		break;
		case LCD_DRAWMODE_TRANS:
			do {
				I32 Shift = (1 - CurrentPixel) << 2;
				I32 Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
				if (Index) {
					LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
					LCD_L0_SetPixelIndex(x, y, PixelIndex, 0xff);
				}
				x++;
				if (++CurrentPixel == 2) {
					CurrentPixel = 0;
					Pixels = *(++p);
				}
			} while (--xsize);
		break;
	}
}
#endif

/*********************************************
*
*       Draw Bitmap 8 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)
static void  _DrawBitLine8BPP(I32 x, I32 y, U8 const * p, I32 xsize, const LCD_PIXELINDEX * pTrans) {
	LCD_PIXELINDEX Pixel;
	switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
		case 0:
			if (pTrans) {
				for (; xsize > 0; xsize--, x++, p++) {
					Pixel = *p;
					LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel), 0xff);
				}
			} else {
				for (; xsize > 0; xsize--, x++, p++) {
					LCD_L0_SetPixelIndex(x, y, *p, 0xff);
				}
			}
			break;
		case LCD_DRAWMODE_TRANS:
			if (pTrans) {
				for (; xsize > 0; xsize--, x++, p++) {
					Pixel = *p;
					if (Pixel) {
						LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel), 0xff);
					}
				}
			} else {
				for (; xsize > 0; xsize--, x++, p++) {
					Pixel = *p;
					if (Pixel) {
						LCD_L0_SetPixelIndex(x, y, Pixel, 0xff);
					}
				}
			}
		break;
	}
}
#endif

/*********************************************
*
*       Draw Bitmap 16 BPP
*
**********************************************
*/

#if (LCD_BITSPERPIXEL > 8)
static void  DrawBitLine16BPP(I32 x, I32 y, U16 const * p, I32 xsize, const LCD_PIXELINDEX * pTrans)
{
	LCD_PIXELINDEX pixel;
	if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
		if (pTrans) {
			for (; xsize > 0; xsize--, x++, p++) {
				pixel = *p;
				LCD_L0_SetPixelIndex(x, y, *(pTrans + pixel), 0xff);
			}
		} else {
			for (;xsize > 0; xsize--, x++, p++) {
				LCD_L0_SetPixelIndex(x, y, *p, 0xff);
			}
		}
	} else {
		if (pTrans) {
			for (; xsize > 0; xsize--, x++, p++) {
				pixel = *p;
				if (pixel) {
					LCD_L0_SetPixelIndex(x, y, *(pTrans + pixel), 0xff);
				}
			}
		} else {
			for (; xsize > 0; xsize--, x++, p++) {
				pixel = *p;
				if (pixel) {
					LCD_L0_SetPixelIndex(x, y, pixel, 0xff);
				}
			}
		}
	}
}
#endif
static void  DrawBitLine32BPP(I32 x, I32 y, U32 const * p, I32 xsize, const LCD_PIXELINDEX * pTrans)
{
	LCD_PIXELINDEX pixel;
	for (; xsize > 0; xsize--, x++, p++) {
		pixel = *p;
		//if (pixel) {
		LCD_L0_SetPixelIndex(x, y, pixel, 0xff);
	//}
	}
}
/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/

/*********************************************
*
*       LCD_L0_SetPixelIndex
*
**********************************************
Purpose:
  Sets the index of the given pixel. The upper layers of emWin
  calling this routine make sure that the coordinates are in range, so
  that no check on the parameters needs to be performed.
*/

void LCD_L0_SetPixelIndex(I32 x, I32 y, I32 PixelIndex, unsigned char Alpha)
{
	/* Convert logical into physical coordinates (Dep. on LCDConf.h) */
#if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
	I32 xPhys = LOG2PHYS_X(x, y);
	I32 yPhys = LOG2PHYS_Y(x, y);
#else
	#define xPhys x
	#define yPhys y
#endif
	if(NULL == tLCD_Driver.LCD_PutPixel){
		return;
	}
	if(0xff == Alpha){
		tLCD_Driver.LCD_PutPixel(xPhys, yPhys, PixelIndex);
	}else{
		U32 BkColorIndex;
		U32 ColorIndex;
		BkColorIndex = LCD_L0_GetPixelIndex(x, y);
#if (24 == LCD_BITSPERPIXEL)
		ColorIndex = LCD_MixColors256(PixelIndex, BkColorIndex, Alpha);
		ColorIndex |= 0xff000000;
#elif (16 == LCD_BITSPERPIXEL)
		ColorIndex = LCD_MixColors565(PixelIndex, BkColorIndex, Alpha);
#else
		Color = ColorIndex;
#endif
		tLCD_Driver.LCD_PutPixel(x, y, ColorIndex);
	}
}

/*********************************************
*
*       LCD_L0_GetPixelIndex
*
**********************************************
Purpose:
  Returns the index of the given pixel. The upper layers of emWin
  calling this routine make sure that the coordinates are in range, so
  that no check on the parameters needs to be performed.
*/

U32 LCD_L0_GetPixelIndex(I32 x, I32 y)
{
	/* Convert logical into physical coordinates (Dep. on LCDConf.h) */
#if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
	I32 xPhys = LOG2PHYS_X(x, y);
	I32 yPhys = LOG2PHYS_Y(x, y);
#else
	#define xPhys x
	#define yPhys y
#endif
	if(tLCD_Driver.LCD_GetPixel){
		return tLCD_Driver.LCD_GetPixel(xPhys, yPhys);
	}else{
		return LCD_BKCOLORINDEX;
	}
}

/*********************************************
*
*       LCD_L0_XorPixel
*
**********************************************
*/

void LCD_L0_XorPixel(I32 x, I32 y)
{
	LCD_PIXELINDEX PixelIndex = LCD_L0_GetPixelIndex(x, y);
	PixelIndex &= 0xffffff;
	LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - PixelIndex - 1, 0xff);
}

/*********************************************
*
*       LCD_L0_DrawHLine
*
**********************************************
*/


void LCD_L0_DrawHLine  (I32 x0, I32 y,  I32 x1)
{
	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
		for (; x0 <= x1; x0++) {
			LCD_L0_XorPixel(x0, y);
		}
	} else {
		if(0xff == GUI_Context.Alpha){
			if(tLCD_Driver.LCD_HLineAcce){
				tLCD_Driver.LCD_HLineAcce(x0, y, x1, LCD_COLORINDEX);
			}else{
				for (; x0 <= x1; x0++) {
					LCD_L0_SetPixelIndex(x0, y, LCD_COLORINDEX, 0xff);
				}
			}
		}else{
			for (; x0 <= x1; x0++) {
				LCD_L0_SetPixelIndex(x0, y, LCD_COLORINDEX, GUI_Context.Alpha);
			}
		}
	}
}

/*********************************************
*
*       LCD_L0_DrawVLine
*
**********************************************
*/

void LCD_L0_DrawVLine  (I32 x, I32 y0,  I32 y1)
{
	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
		for (; y0 <= y1; y0++) {
			LCD_L0_XorPixel(x, y0);
		}
	} else {
		if(0xff == GUI_Context.Alpha){
			if(tLCD_Driver.LCD_VLineAcce){
				tLCD_Driver.LCD_VLineAcce(x, y0, y1, LCD_COLORINDEX);
			}else{
				for (; y0 <= y1; y0++) {
					LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX, 0xff);
				}
			}
		}else{
			for (; y0 <= y1; y0++) {
				LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX, GUI_Context.Alpha);
			}
		}
	}
}

/*********************************************
*
*       LCD_L0_FillRect
*
**********************************************
*/

void LCD_L0_FillRect(I32 x0, I32 y0, I32 x1, I32 y1)
{
	I32 x = 0;
	if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
		for (; y0 <= y1; y0++) {
			for(x = x0; x <= x1; x++){
				LCD_L0_XorPixel(x, y0);
			}
		}
	}else if(0xff == GUI_Context.Alpha){
		if(tLCD_Driver.LCD_PutRect){
			tLCD_Driver.LCD_PutRect(x0, y0, x1, y1, LCD_COLORINDEX);
		}else{
			for(; y0 <= y1; y0++){
				for(x = x0; x <= x1; x++){
					LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX, 0xff);
				}
			}
		}
	}else{
		for(; y0 <= y1; y0++){
			for(x = x0; x <= x1; x++){
				LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX, GUI_Context.Alpha);
			}
		}
	}
}

/*********************************************
*
*       LCD_L0_DrawBitmap
*
**********************************************
*/

void LCD_L0_DrawBitmap(I32 x0, I32 y0,
                       I32 xsize, I32 ysize,
                       I32 BitsPerPixel, 
                       I32 BytesPerLine,
                       const U8* pData, I32 Diff,
                       const LCD_PIXELINDEX* pTrans)
{
	I32 i;
	/* Use _DrawBitLineXBPP */
	for (i = 0; i < ysize; i++) {
		switch (BitsPerPixel) {
			case 1:
				_DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
			break;
#if (LCD_MAX_LOG_COLORS > 2)
			case 2:
				_DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
			break;
#endif
#if (LCD_MAX_LOG_COLORS > 4)
			case 4:
				_DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
			break;
#endif
#if (LCD_MAX_LOG_COLORS > 16)
			case 8:
				_DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
			break;
#endif
#if (LCD_BITSPERPIXEL > 8)
			case 16:
				DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize, pTrans);
			break;
#endif
#if (LCD_BITSPERPIXEL > 16)
			case 24:
			case 32:
				DrawBitLine32BPP(x0, i + y0, (const U32 *)pData, xsize, NULL);
			break;
#endif
		}
		pData += BytesPerLine;
	}
}

/*********************************************
*
*       LCD_L0_SetOrg
*
**********************************************
*/

void LCD_L0_SetOrg(I32 x, I32 y)
{
	GUI_USE_PARA(x);
	GUI_USE_PARA(y);
}

/*********************************************
*
*       LCD_On / LCD_Off
*
**********************************************
*/
void LCD_On (void) 
{
	if(tLCD_Driver.LCD_ScreenOn){
		tLCD_Driver.LCD_ScreenOn();
	}
}

void LCD_Off (void) 
{
	if(tLCD_Driver.LCD_ScreenOff){
		tLCD_Driver.LCD_ScreenOff();
	}
}
/*********************************************************************
*
*       LCD_L0_GetDevFunc
*/
void * LCD_L0_GetDevFunc(I32 Index)
{
	GUI_USE_PARA(Index);
	return NULL;
}


/*********************************************
*
*       LCD_L0_Init
*
**********************************************
Purpose:
  Initialises the LCD-controller.
*/

I32  LCD_L0_Init(void)
{
	if(tLCD_Driver.LCD_Init){
		tLCD_Driver.LCD_Init();
	}
	return 0;
}

/*********************************************
*
*       LCD_L0_SetLUTEntry
*
**********************************************
*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color)
{
	GUI_USE_PARA(Pos);
	GUI_USE_PARA(Color);
}
/* *
 *  LCD Driver Register
 * */
void LCD_UpdateRectEnd(I32 x0, I32 y0, I32 x1, I32 y1)
{
	if(tLCD_Driver.LCD_UpdateRectEnd){
		tLCD_Driver.LCD_UpdateRectEnd(x0, y0, x1, y1);
	}
}
void LCD_UpdateAllEnd(void)
{
	if(tLCD_Driver.LCD_UpdateAllEnd){
		tLCD_Driver.LCD_UpdateAllEnd();
	}
}
void LCD_DriverInit(LCD_Driver_t *pDriver)
{
	pDriver->LCD_Init = NULL;
	pDriver->LCD_ScreenOn = NULL;
	pDriver->LCD_ScreenOff = NULL;
	pDriver->LCD_PutPixel = NULL;
	pDriver->LCD_GetPixel = NULL;
	pDriver->LCD_PutRect = NULL;
	pDriver->LCD_HLineAcce = NULL;
	pDriver->LCD_VLineAcce = NULL;
	pDriver->LCD_UpdateRectEnd = NULL;
	pDriver->LCD_UpdateAllEnd = NULL;
}
void LCD_DriverRegister(LCD_Driver_t *pDriver)
{
	tLCD_Driver.LCD_Init = pDriver->LCD_Init;
	tLCD_Driver.LCD_ScreenOn = pDriver->LCD_ScreenOn;
	tLCD_Driver.LCD_ScreenOff = pDriver->LCD_ScreenOff;
	tLCD_Driver.LCD_GetPixel = pDriver->LCD_GetPixel;
	tLCD_Driver.LCD_HLineAcce = pDriver->LCD_HLineAcce;
	tLCD_Driver.LCD_PutPixel = pDriver->LCD_PutPixel;
	tLCD_Driver.LCD_PutRect = pDriver->LCD_PutRect;
	tLCD_Driver.LCD_VLineAcce = pDriver->LCD_VLineAcce;
	tLCD_Driver.LCD_UpdateRectEnd = pDriver->LCD_UpdateRectEnd;
	tLCD_Driver.LCD_UpdateAllEnd = pDriver->LCD_UpdateAllEnd;
}



