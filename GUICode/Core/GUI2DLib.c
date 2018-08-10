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
File        : GUI2DLib.C
Purpose     : Main part of the 2D graphics library
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
#define RETURN_IF_OUT() \
  if (x0 > x1) return; \
  if (y0 > y1) return;

#define CLIP_X() \
  if (x0 < GUI_Context.ClipRect.x0) { x0 = GUI_Context.ClipRect.x0; } \
  if (x1 > GUI_Context.ClipRect.x1) { x1 = GUI_Context.ClipRect.x1; }

#define CLIP_Y() \
  if (y0 < GUI_Context.ClipRect.y0) { y0 = GUI_Context.ClipRect.y0; } \
  if (y1 > GUI_Context.ClipRect.y1) { y1 = GUI_Context.ClipRect.y1; }

/*********************************************************************
*
*       GUI_MoveRel
*/
/*tbd: GL_LinePos. */
void GUI_MoveRel(I32 dx, I32 dy)
{
	GUI_Context.DrawPosX += dx;
	GUI_Context.DrawPosY += dy;
}

/*********************************************************************
*
*       GL_MoveTo
*/
void GL_MoveTo(I32 x, I32 y)
{
	GUI_Context.DrawPosX = x;
	GUI_Context.DrawPosY = y;
}

/*********************************************************************
*
*       GUI_MoveTo
*/
void GUI_MoveTo(I32 x, I32 y)
{
#if (GUI_WINSUPPORT)
	WM_ADDORG(x,y);
#endif
	GL_MoveTo(x,y);
}

/*********************************************************************
*
*       Rectangle filling / inverting
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawRect
*/
static void _DrawRect(I32 x0, I32 y0, I32 x1, I32 y1)
{
	LCD_DrawHLine(x0, y0, x1);
	LCD_DrawHLine(x0, y1, x1);
	LCD_DrawVLine(x0, y0 + 1, y1 - 1);
	LCD_DrawVLine(x1, y0 + 1, y1 - 1);
}

/*********************************************************************
*
*       GUI_DrawRect
*/
void GUI_DrawRect(I32 x0, I32 y0, I32 x1, I32 y1)
{
#if GUI_WINSUPPORT
	/* Perform clipping and check if there is something to do */
	WM_ADDORG(x0, y0);
	WM_ADDORG(x1, y1);
	CLIP_X();
	CLIP_Y();
	RETURN_IF_OUT();
#endif
	_DrawRect(x0, y0, x1, y1);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
