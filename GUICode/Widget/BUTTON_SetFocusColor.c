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
File        : BUTTON_SetFocusColor.c
Purpose     : Implementation of BUTTON_SetFocusColor
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON_Private.h"

#if GUI_WINSUPPORT && BUTTON_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_SetFocusColor
*/
GUI_COLOR BUTTON_SetFocusColor(BUTTON_Handle hObj, GUI_COLOR Color)
{
	GUI_COLOR OldColor = 0;
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		if (Color != pObj->Props.FocusColor) {
			OldColor = pObj->Props.FocusColor;
			pObj->Props.FocusColor = Color;
			WM_InvalidateWindow(hObj);
		}
	}
	return OldColor;
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_SetFocusColor_C(void);
  void BUTTON_SetFocusColor_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
