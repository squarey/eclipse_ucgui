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
File        : CHECKBOX_SetBkColor.c
Purpose     : Implementation of CHECKBOX_SetBkColor
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT && CHECKBOX_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_SetBkColor
*/
void CHECKBOX_SetBkColor(CHECKBOX_Handle hObj, GUI_COLOR Color)
{
	if (hObj) {
		CHECKBOX_Obj* pObj;
		pObj = CHECKBOX_H2P(hObj);
		if (Color != pObj->Props.BkColor) {
			pObj->Props.BkColor = Color;
			WM_InvalidateWindow(hObj);
		}
	}
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_SetBkColor_C(void);
  void CHECKBOX_SetBkColor_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
