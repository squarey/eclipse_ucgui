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
File        : GUI_FillRect.C
Purpose     : Implementation of GUI_FillRect
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
#define CLIP_X() \
	if (x0 < GUI_Context.ClipRect.x0) { x0 = GUI_Context.ClipRect.x0; } \
	if (x1 > GUI_Context.ClipRect.x1) { x1 = GUI_Context.ClipRect.x1; }

#define CLIP_Y() \
	if (y0 < GUI_Context.ClipRect.y0) { y0 = GUI_Context.ClipRect.y0; } \
	if (y1 > GUI_Context.ClipRect.y1) { y1 = GUI_Context.ClipRect.y1; }

/*********************************************************************
*
*       GUI_FillRect
*/
void GUI_FillRect(I32 x0, I32 y0, I32 x1, I32 y1)
{
#if GUI_WINSUPPORT
	WM_ADDORG(x0, y0);
	WM_ADDORG(x1, y1);
	CLIP_X();
	CLIP_Y();
#endif
	LCD_FillRect(x0 ,y0, x1, y1);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
