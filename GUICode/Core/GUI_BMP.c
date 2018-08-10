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
File        : GUI_BMP.c
Purpose     : Implementation of GUI_BMP... functions
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI_Private.h"

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetStep
*/
static I32 _GetStep(I32 * pYSize, I32 * pY)
{
	if (*pYSize > 0) {
		*pY = *pYSize - 1;
		return -1;
	} else if (*pYSize < 0) {
		*pYSize = -*pYSize;
		*pY = 0;
		return 1;
	} else {
		return 0;
	}
}

/*********************************************************************
*
*       _DrawBitmap_Pal
*/
static I32 _DrawBitmap_Pal(const U8 * pData, I32 x0, I32 y0, I32 XSize, I32 YSize, I32 Bpp, I32 NumColors)
{
	I32 i, y, Step;
	I32 BytesPerLine = 0;
	Step = _GetStep(&YSize, &y);
	if (!Step) {
		return 1;
	}
	for (i = 0; i < NumColors; i++) {
		U8 r, g, b;
		b = *(pData);
		g = *(pData + 1);
		r = *(pData + 2);
		pData += 4;
		LCD__aConvTable[i] = LCD_Color2Index(((U32)b << 16) | (g << 8) | r);
	}
	switch (Bpp) {
		case 1:
			BytesPerLine = ((XSize + 31) >> 5) << 2;
		break;
		case 4:
			BytesPerLine = (((XSize << 2) + 31) >> 5) << 2;
		break;
		case 8:
			BytesPerLine = ((XSize +  3) >> 2) << 2;
		break;
	}
	for (; (y < YSize) && (y >= 0); y += Step) {
		LCD_DrawBitmap(x0, y0 + y, XSize, 1, 1, 1, Bpp, XSize, pData, LCD__aConvTable);
		pData += BytesPerLine;
	}
	return 0;
}

/*********************************************************************
*
*       _DrawBitmap_24bpp
*/
static I32 _DrawBitmap_24bpp(const U8 * pData, I32 x0, I32 y0, I32 XSize, I32 YSize) 
{
	I32 x, y, BytesPerLine, Step;
	Step = _GetStep(&YSize, &y);
	if (!Step) {
	return 1;
	}
	BytesPerLine = ((24 * XSize + 31) >> 5) << 2;
	for (; (y < YSize) && (y >= 0); y += Step) {
		for (x = 0; x < XSize; x++) {
			const U8 * pColor = pData + 3 * x;
			U8 r, g, b;
			U32 color;
			b = *(pColor);
			g = *(pColor + 1);
			r = *(pColor + 2);
			color = LCD_Color2Index(((U32)b << 16) | (g << 8) | r);
			LCD_SetPixelIndex(x0 + x, y0 + y, color, 0xff);
		}
		pData += BytesPerLine;
	}
	return 0;
}
static I32 _DrawBitmap_32bpp(const U8 * pData, I32 x0, I32 y0, I32 XSize, I32 YSize)
{
  I32 x, y, BytesPerLine, Step;
  Step = _GetStep(&YSize, &y);
  if (!Step) {
    return 1;
  }
  BytesPerLine = ((32 * XSize + 31) >> 5) << 2;
  for (; (y < YSize) && (y >= 0); y += Step) {
    for (x = 0; x < XSize; x++) {
      const U8 * pColor = pData + 4 * x;
      U8 a, r, g, b;
      b = *(pColor);
      g = *(pColor + 1);
      r = *(pColor + 2);
	  a = *(pColor + 3);
	  //if(0 != a){
		LCD_SetPixelIndex(x0 + x, y0 + y, LCD_Color2Index((((U32)a << 24) | (U32)b << 16) | (g << 8) | r), a);
	 // }
    }
    pData += BytesPerLine;
  }
  return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_BMP_GetXSize
*/
I32 GUI_BMP_GetXSize(const void * pBMP)
{
	const U8 * pSrc = (const U8 *)pBMP;
	if (!pBMP) {
		return 0;
	}
	pSrc += 18;                   /* skip rest of BITMAPFILEHEADER */
	return GUI__Read32(&pSrc);
}

/*********************************************************************
*
*       GUI_BMP_GetYSize
*/
I32 GUI_BMP_GetYSize(const void * pBMP)
{
	const U8 * pSrc = (const U8 *)pBMP;
	if (!pBMP) {
		return 0;
	}
	pSrc += 22;
	return labs((I32)GUI__Read32(&pSrc));
}

/*********************************************************************
*
*       GUI_BMP_Draw
*/
I32 GUI_BMP_Draw(const void * pBMP, I32 x0, I32 y0)
{
	I32 Ret = 0;
	I32 Width, Height;
	U16 BitCount, Type;
	U32 ClrUsed, Compression;
	I32 NumColors;
	const U8 * pSrc = (const U8 *)pBMP;
	Type        = GUI__Read16(&pSrc); /* get type from BITMAPFILEHEADER */
	pSrc += 12;                   /* skip rest of BITMAPFILEHEADER */
	/* get values from BITMAPINFOHEADER */
	pSrc += 4;
	Width       = GUI__Read32(&pSrc);
	Height      = GUI__Read32(&pSrc);
	pSrc += 2;
	BitCount    = GUI__Read16(&pSrc);
	Compression = GUI__Read32(&pSrc);
	pSrc += 12;
	ClrUsed     = GUI__Read32(&pSrc);
	pSrc += 4;
	/* calculate number of colors */
	switch (BitCount) {
		case 0:   return 1; /* biBitCount = 0 (JPEG format) not supported. Please convert image ! */
		case 1:   NumColors = 2;   break;
		case 4:   NumColors = 16;  break;
		case 8:   NumColors = 256; break;
		case 24:  NumColors = 0;   break;
		case 32:  NumColors = 0;   break;
		default:
			return 1; /* biBitCount should be 1, 4, 8 or 24 */
	}
	if (NumColors && ClrUsed) {
		NumColors = ClrUsed;
	}
	/* check validity of bmp */
	if ((NumColors > LCD_MAX_LOG_COLORS) ||
			(Type != 0x4d42)                 || /* 'BM' */
			(Compression)                    || /* only uncompressed bitmaps */
			(Width  > 1024)                  ||
			(Height > 1024)) {
		return 1;
	}
	/* start output */
#if (GUI_WINSUPPORT)
	WM_ADDORG(x0,y0);
#endif
	/* Show bitmap */
	switch (BitCount) {
		case 1:
		case 4:
		case 8:
			Ret = _DrawBitmap_Pal(pSrc, x0, y0, Width, Height, BitCount, NumColors);
		break;
		case 24:
			Ret = _DrawBitmap_24bpp(pSrc, x0, y0, Width, Height);
		break;
		case 32:
		Ret = _DrawBitmap_32bpp(pSrc, x0, y0, Width, Height);
		break;
	}
	return Ret;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
