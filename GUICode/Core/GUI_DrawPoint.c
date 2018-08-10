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
File        : GUI_DrawPoint.c
Purpose     : Implementation of point drawing routines
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"
#include "GUIDebug.h"

#define RETURN_IF_Y_OUT() \
	if (y < GUI_Context.ClipRect.y0) return;             \
	if (y > GUI_Context.ClipRect.y1) return;

#define RETURN_IF_X_OUT() \
	if (x < GUI_Context.ClipRect.x0) return;             \
	if (x > GUI_Context.ClipRect.x1) return;

/*********************************************************************
*
*       GL_DrawPoint
*/
void GL_DrawPoint(I32 x, I32 y) {
	if (GUI_Context.PenSize == 1) {
		LCD_HL_DrawPixel(x, y);
	} else {
		GL_FillCircle(x, y, (GUI_Context.PenSize - 1) / 2);
	}
}

/*********************************************************************
*
*       GUI_DrawPoint
*/
void GUI_DrawPoint(I32 x, I32 y)
{
	WM_ADDORGX(x);
	WM_ADDORGY(y);
	RETURN_IF_X_OUT();
	RETURN_IF_Y_OUT();
	GL_DrawPoint(x, y);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
