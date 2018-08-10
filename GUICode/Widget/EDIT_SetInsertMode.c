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
File        : EDIT_SetInsertMode.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "EDIT.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT && EDIT_SUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_SetInsertMode
*/
I32 EDIT_SetInsertMode(EDIT_Handle hObj, I32 OnOff)
{
	I32 PrevMode = 0;
	if (hObj) {
		EDIT_Obj* pObj;
		pObj = EDIT_H2P(hObj);
		PrevMode = pObj->EditMode;
		pObj->EditMode = OnOff ? GUI_EDIT_MODE_INSERT : GUI_EDIT_MODE_OVERWRITE;
	}
  return PrevMode;
}

#else  /* avoid empty object files */

void EDIT_SetInsertMode_C(void);
void EDIT_SetInsertMode_C(void) {}

#endif /* GUI_WINSUPPORT */

	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
