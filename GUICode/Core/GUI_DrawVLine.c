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
File        : GUI_DrawVLine.C
Purpose     : Implementation of GUI_DrawVLine
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
#define RETURN_IF_X_OUT() \
	if (x0 < GUI_Context.ClipRect.x0) return;             \
	if (x0 > GUI_Context.ClipRect.x1) return;

#define CLIP_Y() \
  if (y0 < GUI_Context.ClipRect.y0) { y0 = GUI_Context.ClipRect.y0; } \
  if (y1 > GUI_Context.ClipRect.y1) { y1 = GUI_Context.ClipRect.y1; }

#define _ADDORG_X()\
	x0 += GUI_Context.xOff;\

#define _ADDORG_Y()\
	y0 += GUI_Context.yOff;\
	y1 += GUI_Context.yOff;\

/*********************************************************************
*
*       GUI_DrawVLine
*/
void GUI_DrawVLine(I32 x0, I32 y0, I32 y1)
{
#if GUI_WINSUPPORT
	_ADDORG_X();
	_ADDORG_Y();
	RETURN_IF_X_OUT();
	CLIP_Y();
	if(y0 > y1){
		return;
	}
	LCD_DrawVLine(x0, y0, y1);
#endif
}
/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
