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
File        : BUTTON_SetTextAlign.c
Purpose     : Implementation of BUTTON_SetTextAlign
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON_Private.h"

#if GUI_WINSUPPORT && BUTTON_SUPPORT

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_SetTextAlign
*/
void BUTTON_SetTextAlign(BUTTON_Handle hObj, I32 Align)
{
	if (hObj) {
		BUTTON_Obj* pObj;
		pObj = BUTTON_H2P(hObj);
		pObj->Props.Align = Align;
		BUTTON_Invalidate(hObj);
	}
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_SetTextAlign_C(void);
  void BUTTON_SetTextAlign_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
