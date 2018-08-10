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
File        : WM_SetTrans.C
Purpose     : Windows manager, optional routines
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetHasTrans
*/
void WM_SetHasTrans(WM_HWIN hWin) 
{
	WM_Obj *pWin;
	if (hWin) {
		pWin = WM_H2P(hWin);  
		/* First check if this is necessary at all */
		if ((pWin->Status & WM_SF_HASTRANS) == 0) {
			pWin->Status |= WM_SF_HASTRANS; /* Set Transparency flag */
	  		WM_InvalidateWindow(hWin);      /* Mark content as invalid */
		}
	}
}

/*********************************************************************
*
*       WM_ClrHasTrans
*/
void WM_ClrHasTrans(WM_HWIN hWin)
{
	WM_Obj *pWin;
	if (hWin) {
		pWin = WM_H2P(hWin);  
		/* First check if this is necessary at all */
		if (pWin->Status & WM_SF_HASTRANS) {
			pWin->Status &= ~WM_SF_HASTRANS;
			WM_InvalidateWindow(hWin);        /* Mark content as invalid */
		}
	}
}

/*********************************************************************
*
*       WM_GetHasTrans
*/
I32 WM_GetHasTrans(WM_HWIN hWin) 
{
	I32 r = 0;
	WM_Obj *pWin;
	if (hWin) {
		pWin = WM_H2P(hWin);  
		r = pWin->Status & WM_SF_HASTRANS;
	}
	return r;
}

#else
  void WM_SetTrans_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
