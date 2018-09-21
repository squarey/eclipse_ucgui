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
File        : GUIChar.C
Purpose     : Implementation of character and string services
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include "GUI_Protected.h"
 
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DispNextLine
*/
void GUI_DispNextLine(void)
{
	GUI_Context.DispPosY += GUI_GetFontDistY();
	GUI_Context.DispPosX  = GUI_Context.LBorder;
}

/*********************************************************************
*
*       GL_DispChar
*/
void GL_DispChar(U16 c)
{
	/* check for control characters */
	if (c == '\n') {
		GUI_DispNextLine();
	} else {
		if (c != '\r') {
			GUI_Context.pAFont->pfDispChar(c);
			if (GUI_pfDispCharStyle) {
				GUI_pfDispCharStyle(c);
			}
		}
	}
}

/*********************************************************************
*
*       GUI_GetYAdjust
*
* Returns adjustment in vertical (Y) direction
*
* Note: The return value needs to be subtracted from
*       the y-position of the character.
*/
I32 GUI_GetYAdjust(void)
{
	I32 r = 0;
	switch (GUI_Context.TextAlign & GUI_TA_VERTICAL) {
		case GUI_TA_BOTTOM:
			r = ((GUI_Context.FontScale * GUI_Context.pAFont->YSize) >> GUI_FIX_DIV_BIT) - 1;
			break;
		case GUI_TA_VCENTER:
			r = ((GUI_Context.FontScale * GUI_Context.pAFont->YSize) >> GUI_FIX_DIV_BIT) / 2;
			break;
		case GUI_TA_BASELINE:
			r = ((GUI_Context.FontScale * GUI_Context.pAFont->YSize) >> GUI_FIX_DIV_BIT) / 2;
			break;
	}
	return r;
}

/*********************************************************************
*
*       GUI_GetFontDistY
*/
I32 GUI_GetFontDistY(void)
{
	I32 r;
	r = (GUI_Context.FontScale * GUI_Context.pAFont->YDist) >> GUI_FIX_DIV_BIT;
	return r;
}

/*********************************************************************
*
*       GUI_GetCharDistX
*/
I32 GUI_GetCharDistX(U16 c)
{
	I32 r;
	r = (GUI_Context.FontScale * GUI_Context.pAFont->pfGetCharDistX(c)) >> GUI_FIX_DIV_BIT;
	return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
