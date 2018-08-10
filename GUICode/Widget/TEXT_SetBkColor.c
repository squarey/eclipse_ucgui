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
File        : TEXT_SetBkColor.c
Purpose     : Implementation of TEXT_SetBkColor
---------------------------END-OF-HEADER------------------------------
*/

#include "TEXT_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT && TEXT_SUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       TEXT_SetBkColor
*/
void TEXT_SetBkColor(TEXT_Handle hObj, GUI_COLOR Color)
{
	if (hObj) {
		TEXT_Obj* pObj;
		pObj = TEXT_H2P(hObj);
		if (pObj->Props.BkColor != Color) {
			pObj->Props.BkColor = Color;
#if TEXT_SUPPORT_TRANSPARENCY
			if (Color & 0xFF000000) {
				WM_ClrHasTrans(hObj);
			} else {
				WM_SetHasTrans(hObj);
			}
#endif
			WM_Invalidate(hObj);
		}
	}
}


#else  /* avoid empty object files */

void TEXT_SetBkColor_c(void);
void TEXT_SetBkColor_c(void){}

#endif  /* #if GUI_WINSUPPORT */

	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
