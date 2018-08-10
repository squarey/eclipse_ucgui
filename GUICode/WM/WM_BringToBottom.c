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
File        : WM_BringToBottom.c
Purpose     : Window manager routine
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_BringToBottom
*/
void WM_BringToBottom(WM_HWIN hWin)
{
	WM_HWIN hParent;
	WM_HWIN hFirst;
	WM_Obj* pWin;
	WM_Obj* pParent;
	if (hWin) {
		WM__RemoveWindowFromList(hWin);
		pWin = WM_H2P(hWin);
		hParent = pWin->hParent;
		if(hParent){
			pParent = WM_H2P(hParent);
			hFirst = pParent->hFirstChild;
			pParent->hFirstChild = hWin;
			pWin->hNext = hFirst;
		}
	}
}

#else
  void WM_BringToBottom_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
