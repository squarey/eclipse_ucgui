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
File        : WM_BringToTop.c
Purpose     : Windows manager routine
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */


/*********************************************************************
*
*         Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _BringToTop
*/
static void _BringToTop(WM_HWIN hWin)
{
	WM_HWIN hNext, hParent;
	WM_Obj * pWin, * pNext, *pParent;
	if (hWin) {
		pWin = WM_H2P(hWin);
		hParent = pWin->hParent;
		pParent = WM_H2P(hParent);
		hNext = pParent->hFirstChild;
		WM__RemoveWindowFromList(hWin);
		pWin->hNext = 0;
		while(hNext){
			pNext = WM_H2P(hNext);
			if(0 == pNext->hNext){
				pNext->hNext = hWin;
				break;
			}else{
				hNext = pNext->hNext;
			}
		}
		WM_InvalidateWindow(hWin);
	}
}

/*********************************************************************
*
*         Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_BringToTop
*/
void WM_BringToTop(WM_HWIN hWin)
{
	_BringToTop(hWin);
}

#else
  void WM_BringToTop_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
