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
File        : DROPDOWN_SetColor.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX.h"
#include "DROPDOWN_Private.h"

#if GUI_WINSUPPORT && DROPDOWN_SUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       DROPDOWN_SetColor
*/
void DROPDOWN_SetColor(DROPDOWN_Handle hObj, U32 Index, GUI_COLOR Color) {
  DROPDOWN_Obj * pObj;
  if (hObj) {
    if (Index < GUI_COUNTOF(pObj->Props.aColor)) {
      WM_LOCK();
      pObj = DROPDOWN_H2P(hObj);
      if (pObj->Props.aColor[Index] != Color) {
        pObj->Props.aColor[Index] = Color;
        DROPDOWN_Invalidate(hObj);
      }
      WM_UNLOCK();
    }
  }
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_SetColor_C(void);
  void DROPDOWN_SetColor_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 