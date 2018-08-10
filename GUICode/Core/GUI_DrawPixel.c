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
File        : GUI_DrawPixel.c
Purpose     : Implementation of GUI_DrawPixel
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
#define RETURN_IF_Y_OUT() \
	if (y < GUI_Context.ClipRect.y0) return;             \
	if (y > GUI_Context.ClipRect.y1) return;

#define RETURN_IF_X_OUT() \
	if (x < GUI_Context.ClipRect.x0) return;             \
	if (x > GUI_Context.ClipRect.x1) return;
/*********************************************************************
*
*       GUI_DrawPixel
*/
void GUI_DrawPixel(I32 x, I32 y)
{
	WM_ADDORGX(x);
	WM_ADDORGY(y);
	RETURN_IF_X_OUT();
	RETURN_IF_Y_OUT();
	LCD_HL_DrawPixel(x,y);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
