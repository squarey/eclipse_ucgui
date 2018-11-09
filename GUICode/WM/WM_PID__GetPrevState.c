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
File        : WM_PID__GetPrevState.c
Purpose     : Touch support
----------------------------------------------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"

#if (GUI_WINSUPPORT)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static GUI_PID_STATE _PrevState;
static GUI_PID_STATE _CurState;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_PID__GetPrevState
*/
void WM_PID__GetPrevState(GUI_PID_STATE* pPrevState)
{
	*pPrevState = _PrevState;
}

/*********************************************************************
*
*       WM_PID__SetPrevState
*/
void WM_PID__SetPrevState(GUI_PID_STATE* pPrevState)
{
	_PrevState = *pPrevState;
}
/*********************************************************************
*
*       WM_PID__GetCurState
*/
void WM_PID__GetCurState(GUI_PID_STATE* pCurState)
{
	*pCurState = _CurState;
}

/*********************************************************************
*
*       WM_PID__SetPrevState
*/
void WM_PID__SetCurState(GUI_PID_STATE* pCurState)
{
	_CurState = *pCurState;
}
#else
  void WM_PID__GetPrevState_c(void) {} /* avoid empty object files */
#endif  /* (GUI_WINSUPPORT) */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
