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
File        : LCD_RotateCW.c
Purpose     : Implementation of GUI_SetRotation
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"
#include "LCD.h"
#if GUI_WINSUPPORT
  #include "WM.h"
#endif

#if GUI_SUPPORT_ROTATION

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void  _DrawBitLine1BPP(I32 x, I32 y, U8 const GUI_UNI_PTR *p, I32 Diff, I32 xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  y -= Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      LCDDEV_L0_SetPixelIndex(x, y, (*p & (0x80 >> Diff)) ? Index1 : Index0, 0xff);
      y++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
  		if (*p & (0x80 >> Diff))
        LCDDEV_L0_SetPixelIndex(x, y, Index1, 0xff);
      y++;
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
        LCDDEV_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel, 0xff);
      }
      y++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    break;
	}
}

/*********************************************************************
*
*       _DrawBitmap
*
* Purpose:
*   Draws a bitmap (1bpp) clockwise.
*/
static void _DrawBitmap(I32 x0, I32 y0,
                       I32 xsize, I32 ysize,
                       I32 BitsPerPixel, 
                       I32 BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, I32 Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  I32 i;
  /* Use _DrawBitLineXBPP */
  for (i = 0; i < ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0 - i, y0, pData, Diff, xsize, pTrans);
      break;
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       _Rect2TextRect
*
* Purpose:
*   This function transforms a given rectangle (window coordinates)
*   to the rectangle used to clip the text.
*/
static void _Rect2TextRect(GUI_RECT * pRect) {
  I32 x1, y1;
  x1 = pRect->x1;
  y1 = pRect->y1;
  pRect->x1 = pRect->x0 + (y1 - pRect->y0);
  pRect->y1 = pRect->y0 + (x1 - pRect->x0);
}

/*********************************************************************
*
*       _TransformPointCW
*
* Purpose:
*   This function transforms an unrotated point (window
*   coordinates) into a rotated point in desktop coordinates
*   and handles the rotation of the current text rectangle.
*/
static void _TransformPointCW(I32 * pXPos, I32 * pYPos) {
  GUI_RECT ClientRect = {0};
  I32 xPos, yPos, xNumPixel, yNumPixel;
  /* Get the client rectangle */
  #if GUI_WINSUPPORT
    WM_GetWindowRect(&ClientRect);
  #else
    GUI_GetClientRect(&ClientRect);
  #endif
  xNumPixel = LCD_GetXSize() - 1;
  yNumPixel = LCD_GetYSize() - 1;
  if (ClientRect.x1 > xNumPixel) {
    ClientRect.x1 = xNumPixel;
  }
  if (ClientRect.y1 > yNumPixel) {
    ClientRect.y1 = yNumPixel;
  }
  /* Save old positions */
  xPos = *pXPos;
  yPos = *pYPos;
  /* Rotate and add window origin */
  *pXPos = ClientRect.x0 - yPos;
  *pYPos = ClientRect.y0 + xPos;
  /* Handle rotation of text rectangle */
  *pXPos = *pXPos + GUI_RectDispString.x1 + GUI_RectDispString.y0;
  *pYPos = *pYPos + GUI_RectDispString.y0 - GUI_RectDispString.x0;
}

/*********************************************************************
*
*       _DrawBitmapCW
*/
static void _DrawBitmapCW(I32 x0, I32 y0, I32 xsize, I32 ysize, I32 xMul, I32 yMul,
                           I32 BitsPerPixel, I32 BytesPerLine,
                           const U8 GUI_UNI_PTR * pPixel, const LCD_PIXELINDEX* pTrans)
{
  U8  Data = 0;
  I32 x1, y1;
  /* Handle the optional Y-magnification */
  y1 = y0 + ysize - 1;
  x1 = x0 + xsize - 1;
  /* Rotate positions */
  _TransformPointCW(&x0, &y0);
  _TransformPointCW(&x1, &y1);
  /*  Handle BITMAP without magnification */
  if ((xMul == 1) && (yMul == 1)) {
    I32 Diff = 0;
    /* Clip top */
    if (y1 > GUI_Context.ClipRect.y1) {
      I32 Diff = y1 - GUI_Context.ClipRect.y1; 
      xsize -= Diff;
    }
    /* Clip bottom */
    if (y0 < GUI_Context.ClipRect.y0) {
      Diff = GUI_Context.ClipRect.y1 - y0;
			xsize -= Diff;
			switch (BitsPerPixel) {
			case 1:
  			pPixel += (Diff >> 3); y0 -= (Diff >> 3) << 3; Diff &= 7;
				break;
			}
    }
    if (ysize <=0) {
		  return;
    }
    /* Clip right side */
    if (x0 > GUI_Context.ClipRect.x1) {
      I32 Diff = x0 - GUI_Context.ClipRect.x1;
      ysize -= Diff;
      x0 -= Diff;
      pPixel += Diff * BytesPerLine;
    }
    /* Clip left side */
    if (x1 < GUI_Context.ClipRect.x0) {
      I32 Diff = GUI_Context.ClipRect.x0 - x1;
      x1 += Diff;
      ysize -= Diff;
    }
    if (xsize <= 0) {
		  return;
    }
    _DrawBitmap(x0, y0, xsize, ysize, BitsPerPixel, BytesPerLine, pPixel, Diff, pTrans);
  } else {
    /* Handle BITMAP with magnification */
    I32 x, y, xi, yi;
    I32 Shift = 8 - BitsPerPixel;
    for (x = x0, xi = 0; xi < ysize; xi++, x -= yMul, pPixel += BytesPerLine) {
      I32 xMax = x - yMul + 1;
      if ((xMax >= GUI_Context.ClipRect.x0) && (x <= GUI_Context.ClipRect.x1)) {
        I32 BitsLeft = 0;
        const U8 GUI_UNI_PTR * pDataLine = pPixel;
        for (y = y0, yi = 0; yi < xsize; yi++, y += xMul) {
          U8  Index;
          if (!BitsLeft) {
            Data = *pDataLine++;
            BitsLeft =8;
          }
          Index = Data >> Shift;
          Data    <<= BitsPerPixel;
          BitsLeft -= BitsPerPixel;
          if (Index || ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0)) {
            LCD_PIXELINDEX OldColor = LCD_COLORINDEX;
            if (pTrans) {
              LCD_COLORINDEX = *(pTrans + Index);
            } else {
              LCD_COLORINDEX = Index;
            }
            LCD_FillRect(xMax, y, x, y + xMul - 1);
            LCD_COLORINDEX = OldColor;
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*       Global data
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_APIListCW
*
* Purpose:
*   Function pointer table for rotating text CW
*/
tLCD_APIList LCD_APIListCW = {
  (tLCD_DrawBitmap*)&_DrawBitmapCW,
  &_Rect2TextRect
};

#else
void LCD_RotateCW_C(void);
void LCD_RotateCW_C(void){}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
