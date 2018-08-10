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
File        : CHECKBOX_SetState.c
Purpose     : Implementation of CHECKBOX_SetState
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
*       CHECKBOX_SetState
*/
void CHECKBOX_SetState(CHECKBOX_Handle hObj, unsigned State)
{
	CHECKBOX_Obj * pObj;
	if (hObj) {
		pObj = CHECKBOX_H2P(hObj);
		if (State != pObj->CurrentState) {
			//GUI_Debug("State:%d, pObj->NumStates:%d\n", State, pObj->NumStates);
			pObj->CurrentState = State;
			WM_Invalidate(hObj);
			WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
		}
	}
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_SetState_C(void);
  void CHECKBOX_SetState_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
