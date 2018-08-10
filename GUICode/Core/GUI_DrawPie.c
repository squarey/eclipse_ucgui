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
File        : GUIARCFloat.C
Purpose     : Draw Arc routines based on floating point
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
*       _DrawPie
*/
static void _DrawPie(I32 x0, I32 y0, U32 r, I32 Angle0, I32 Angle1, I32 Type) {
  I32 PenSizeOld;
  PenSizeOld = GUI_GetPenSize();
  GUI_SetPenSize(r);
  r /= 2;
  GL_DrawArc(x0,y0,r,r,Angle0, Angle1);
  GUI_SetPenSize(PenSizeOld);
  GUI_USE_PARA(Type);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawPie
*/
void GUI_DrawPie(I32 x0, I32 y0, I32 r, I32 a0, I32 a1, I32 Type)
{
#if GUI_WINSUPPORT
	WM_ADDORG(x0,y0);
#endif
	_DrawPie( x0, y0, r, a0, a1, Type);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
