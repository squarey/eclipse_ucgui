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
File        : GUI_SetFont.C
Purpose     : Optional routines
----------------------------------------------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetFont
*/
const GUI_FONT GUI_UNI_PTR* GUI_SetFont(const GUI_FONT GUI_UNI_PTR * pNewFont)
{
	const GUI_FONT GUI_UNI_PTR* pOldFont = GUI_Context.pAFont;
	if (pNewFont)
		GUI_Context.pAFont = pNewFont;
	return pOldFont;
}

float GUI_SetFontScale(float Scale)
{
	U32 r = 0;
	r = GUI_Context.FontScale;
	GUI_Context.FontScale = (U32)(Scale * GUI_FIX_DIV);
	return (float)r/GUI_FIX_DIV;
}
float GUI_GetFontScale(void)
{
	return (float)GUI_Context.FontScale/GUI_FIX_DIV;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
