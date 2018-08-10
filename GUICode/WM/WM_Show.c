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
File        : WM_Show.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM_ShowWindow
*/
void WM_ShowWindow(WM_HWIN hWin)
{
	if (hWin) {
		WM_Obj *pWin;
		pWin = WM_H2P(hWin);
		if ((pWin->Status & WM_SF_ISVIS) == 0) {  /* First check if this is necessary at all */
			pWin->Status |= WM_SF_ISVIS;  /* Set Visibility flag */
			WM_AddToInvalidateRectLink(pWin->Rect);
#if WM_SUPPORT_NOTIFY_VIS_CHANGED
			WM__NotifyVisChanged(hWin, &pWin->Rect);
#endif
		}
	}
}

#else
  void WM_Show_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
