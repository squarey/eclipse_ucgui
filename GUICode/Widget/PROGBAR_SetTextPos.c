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
File        : PROGBAR_SetTextPos.c
Purpose     : Implementation of progbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "PROGBAR_Private.h"

#if GUI_WINSUPPORT && PROGBAR_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_SetTextPos
*/
void PROGBAR_SetTextPos(PROGBAR_Handle hObj, I32 XOff, I32 YOff) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    pObj = PROGBAR_H2P(hObj);
    pObj->XOff = XOff;
    pObj->YOff = YOff;
    WM_InvalidateWindow(hObj);
  }
}

#else  /* avoid empty object files */
  void PROGBAR_SetTextPos_C(void);
  void PROGBAR_SetTextPos_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
