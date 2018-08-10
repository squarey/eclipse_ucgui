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
File        : GUI_PID.C
Purpose     : PID (Pointer input device) management
----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Protected.h"
#include "GUI_ReDefine.h"


#if GUI_WINSUPPORT
  #include "WM.h"
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//static U8	StoreCnt = 0;
static GUI_PID_STATE _State;
//static GUI_PID_STATE _UpState;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_PID_GetState
*/
I32 GUI_PID_GetState(GUI_PID_STATE *pState)
{
	*pState = _State;
	return (pState->Pressed != 0) ? 1 : 0;
}

/*********************************************************************
*
*       GUI_PID_StoreState
*/
void GUI_PID_StoreState(const GUI_PID_STATE *pState)
{
	if (GUI_memcmp(&_State, pState, sizeof(_State))){
		_State = *pState;
		GUI_X_SIGNAL_EVENT();
	}
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
