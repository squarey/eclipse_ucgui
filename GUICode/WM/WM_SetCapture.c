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
File        : WM_SetCapture.c
Purpose     : Implementation of WM_SetCapture
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Public data
*
**********************************************************************
*/


/*********************************************************************
*
*        Static code
*
**********************************************************************
*/
static WM_HWIN _hCaptureHWin = WM_HWIN_NULL;
static WM_HWIN _hCaptureVWin = WM_HWIN_NULL;
static WM_HWIN _LockCapture = 0;
/*********************************************************************
*
*       WM__ReleaseCapture
*/
static void WM__ReleaseCapture(void) {
  if (WM__hCapture) {
    WM_MESSAGE Msg;
    Msg.MsgId  = WM_CAPTURE_RELEASED;
    WM__SendMessage(WM__hCapture, &Msg);
    WM__hCapture = 0;
  }
}

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetCapture
*/
void WM_SetCapture(WM_HWIN hObj, I32 AutoRelease)
{
	if(2 != _LockCapture){
		if (WM__hCapture != hObj) {
			WM__ReleaseCapture();
		}
		WM__hCapture = hObj;
		WM__CaptureReleaseAuto = AutoRelease;
		_LockCapture = AutoRelease;
	}
}

/*********************************************************************
*
*       WM_ReleaseCapture
*/
void WM_ReleaseCapture(void)
{
	WM__ReleaseCapture();
	_hCaptureHWin = WM_HWIN_NULL;
	_hCaptureVWin = WM_HWIN_NULL;
	_LockCapture = 0;
}

void WM_SetCaptureHWin(WM_HWIN hWin)
{
	_hCaptureHWin = hWin;
}
void WM_SetCaptureVWin(WM_HWIN hWin)
{
	_hCaptureVWin = hWin;
}
WM_HWIN WM_GetCaptureHWin(void)
{
	return _hCaptureHWin;
}
WM_HWIN WM_GetCaptureVWin(void)
{
	return _hCaptureVWin;
}
#else
  void WM_SetCapture_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
