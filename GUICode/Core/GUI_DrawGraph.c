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
File        : GUI_DrawPolyline.c
Purpose     : Implementation of GUI_DrawPolyline
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawGraph
*/
static void _DrawGraph(I16 *pay, I32 NumPoints, I32 xOff, I32 yOff)
{
	I32 i;
	I32 y0, y1;
	I32 yClip0, yClip1;
	/* Perform high level clipping in x */
	yClip0 = GUI_Context.pClipRect_HL->y0;
	yClip1 = GUI_Context.pClipRect_HL->y1;
	i=0;
	if (GUI_Context.pClipRect_HL) {
		if (xOff < GUI_Context.pClipRect_HL->x0)
			i = GUI_Context.pClipRect_HL->x0 - xOff;
		if (xOff+NumPoints-1 > GUI_Context.pClipRect_HL->x1)
			NumPoints = GUI_Context.pClipRect_HL->x1 - xOff + 1;
	}
	/* Start drawing if there is something left to do after x-clipping */
	if (i < NumPoints) {
		y0 = *(pay + i++) + yOff;
		/* Iterate */
		for (; i < NumPoints; i++) {
			/* Perform high level clipping in y */
			y1 = *(pay + i) + yOff;
			if ((y0 >= yClip0) || (y1 >= yClip0)) {
				if ((y0 <= yClip1) || (y1 <= yClip1)) {
					I32 y01;
					y01 = (y1 + y0) / 2;
					if (y0 <= y1) {
						LCD_DrawVLine(i + xOff - 1, y0, y01);
						LCD_DrawVLine(i + xOff, y01, y1);
					} else {
						LCD_DrawVLine(i + xOff - 1, y01, y0);
						LCD_DrawVLine(i + xOff, y1, y01);
					}
				}
			}
			y0 = y1;
		}
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawGraph
*/  
void GUI_DrawGraph(I16 *pay, I32 NumPoints, I32 x0, I32 y0)
{
#if (GUI_WINSUPPORT)
	WM_ADDORG(x0,y0);
#endif
	_DrawGraph(pay, NumPoints, x0, y0);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
