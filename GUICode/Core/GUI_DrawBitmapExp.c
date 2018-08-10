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
File        : GUI_DrawBitmapExp.C
Purpose     : Implementation of GUI_DrawBitmapExp
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawBitmapExp
*/
void GUI_DrawBitmapExp(I32 x0, I32 y0, I32 XSize, I32 YSize, I32 XMul, I32 YMul,
                       I32 BitsPerPixel, I32 BytesPerLine, const U8 GUI_UNI_PTR * pData,
                       const GUI_LOGPALETTE GUI_UNI_PTR * pPal)
{
	GUI_DRAWMODE PrevDraw;
	const LCD_PIXELINDEX* pTrans;
	pTrans = LCD_GetpPalConvTable(pPal);
	PrevDraw = GUI_SetDrawMode((pPal && pPal->HasTrans) ? GUI_DRAWMODE_TRANS : 0);
	LCD_DrawBitmap( x0, y0 ,XSize ,YSize, XMul, YMul
		 ,BitsPerPixel, BytesPerLine, pData, pTrans);
	GUI_SetDrawMode(PrevDraw);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
