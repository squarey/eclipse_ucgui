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
File        : GUI_GetColor.C
Purpose     : Implementation of different GUI_GetColor routines
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetBkColorIndex
*/
I32 GUI_GetBkColorIndex(void)
{
	I32 r;
	r = LCD_GetBkColorIndex();
	return r;
}

/*********************************************************************
*
*       GUI_GetBkColor
*/
GUI_COLOR GUI_GetBkColor(void)
{
	GUI_COLOR r;
	r = LCD_Index2Color(LCD_GetBkColorIndex());
	return r;
}

/*********************************************************************
*
*       GUI_GetColorIndex
*/
I32 GUI_GetColorIndex(void)
{
	I32 r;
	r = LCD_GetColorIndex();
	return r;
}

/*********************************************************************
*
*       GUI_GetColor
*/
GUI_COLOR GUI_GetColor(void)
{
	GUI_COLOR r;
	r = LCD_Index2Color(LCD_GetColorIndex());
	return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
