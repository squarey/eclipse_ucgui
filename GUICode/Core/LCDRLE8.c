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
File        : LCDRLE8.c
Purpose     : Drawing routines for run length encoded bitmaps
              with 8 bpp
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "LCD_Private.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static struct {
  I32 x,y;
  const U8 GUI_UNI_PTR * pPixel;
  const U8 GUI_UNI_PTR * pPixelStart;
} Cache;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawBitmap_RLE8
*/
static void _DrawBitmap_RLE8(I32 x0,I32 y0,I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag)
{
	LCD_PIXELINDEX aColorIndex[2];
	LCD_PIXELINDEX PixelIndex;
	LCD_PIXELINDEX TransColorIndex;
	I32 xi,y;
	I32 xL, yL;
	I32 DrawX0, DrawX1;
	U8 BitmapHasTrans;
	const U8 GUI_UNI_PTR * pPixelOrg = pPixel;
	char NoTrans = !(GUI_Context.DrawMode & LCD_DRAWMODE_TRANS);
	const LCD_PIXELINDEX* pTrans =NULL;
	char IsMagnified = ((yMag | xMag) != 1);
	aColorIndex[0] = LCD_ACOLORINDEX[0];
	aColorIndex[1] = LCD_ACOLORINDEX[1];
	BitmapHasTrans = GUI_Context.BitmapHasTrans;
	TransColorIndex = GUI_Color2Index(GUI_Context.BitmapTransColor);
	/* Handle color translation */
	if ((pLogPal) && (pLogPal->pPalEntries)) {
		if ((pTrans = LCD_GetpPalConvTable(pLogPal)) == NULL) {
			return;
		}
	}
	/* Check if we can limit the number of lines due to clipping) */
	if (yMag == 1) {
		if (ysize > GUI_Context.ClipRect.y1 - y0 + 1){
			ysize = GUI_Context.ClipRect.y1 - y0 + 1;
		}
	}
	/* Init variables for looping */
	xi=0;
	y =0;
	/* Check if we can use the cache to save some unnecessary iterations */
	if (!IsMagnified) {
		I32 yDiff = GUI_Context.ClipRect.y0 - y0;
		if ((Cache.pPixelStart == pPixel) && (yDiff > Cache.y)) {
			/* Accept cache values */
			y = Cache.y;
			xi = Cache.x;
			pPixel = Cache.pPixel;
		}
	}
	/* Init values for caching */
	Cache.pPixel = Cache.pPixelStart = pPixelOrg;
	Cache.x = Cache.y = 0;
	/* Repeat until we have reached bottom */
	for (; y < ysize; ) {
		U8 Cmd  = *pPixel++;
		U8 Data = *pPixel++;
		if (Cmd) {
			/* Save cache info */
			Cache.pPixel = pPixel-2;
			Cache.x = xi;
			Cache.y = y;
			LCD_ACOLORINDEX[1] = pTrans ? *(pTrans+Data) : Data;
			while (Cmd) {
				I32 xi1 = xi+Cmd;
				if (xi1>=xsize){
					xi1 = xsize;
				}
				Cmd -= (xi1-xi);
				if(1 == BitmapHasTrans){
					if(TransColorIndex != PixelIndex){
						goto DRAW1;
					}
				}else{
DRAW1:
					if (Data || NoTrans) {  /* Skip transparent pixels */
						if (IsMagnified) {
							xL = xMag * xi + x0;
							yL = yMag * y + y0;
							LCD_FillRect(xL, yL, xL + xMag * (xi1 - xi) -1 , yL + yMag - 1);
						} else {
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
								LCD_DrawHLine(DrawX0, y + y0, DrawX1);
							}
						}
					}
				}
				xi =xi1;
				if (xi1==xsize) {
					y++;
					xi=0;
				}
			}
		} else {

			do {
				U8 Index = *pPixel++;
				if(1 == BitmapHasTrans){
					if(TransColorIndex != PixelIndex){
						goto DRAW2;
					}
				}else{
DRAW2:
					if (Index || NoTrans) {  /* Skip transparent pixels */
						I32 x = 0;
						x = x0+xi;
						PixelIndex = pTrans ? *(pTrans+Index) : Index;
						if (IsMagnified) {
							LCD_SetColorIndex(PixelIndex);
							xL = xMag * xi + x0;
							yL = yMag * y + y0;
							LCD_FillRect(xL, yL, xL + xMag -1 , yL + yMag - 1);
						} else {
	#if 1 /* High speed variant */
							if (y + y0>= GUI_Context.ClipRect.y0){
								if (x >= GUI_Context.ClipRect.x0){
									if (x <= GUI_Context.ClipRect.x1){
										LCDDEV_L0_SetPixelIndex(x, y + y0, PixelIndex, 0xff);
									}
								}
							}
	#else
							LCD_SetPixelIndex(x, y + y0, PixelIndex);
	#endif
						}
					}
				}
				if (++xi >= xsize) {
					xi=0; y++;
					if (y >= ysize){
						break;
					}

				}
			} while (--Data);
		}
	}
	LCD_ACOLORINDEX[0] = aColorIndex[0];
	LCD_ACOLORINDEX[1] = aColorIndex[1];
}

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_BitmapMethodsRLE8
*/
const GUI_BITMAP_METHODS GUI_BitmapMethodsRLE8 = {
  _DrawBitmap_RLE8,
  NULL
};

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
