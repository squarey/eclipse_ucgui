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
File        : LCD_DrawVLine.c
Purpose     : Implementation of optional routines
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Private.h"
#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_DrawVLine
*/
void LCD_DrawVLine(I32 x, I32 y0,  I32 y1)
{
	if (y1 < y0) {
		return;
	}
	/* Call driver to draw */
	LCDDEV_L0_DrawVLine(x, y0, y1);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
