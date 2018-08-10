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
File        : FRAMEWIN_SetTitleHeight.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>
#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT && FRAMEWIN_SUPPORT


/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_SetTitleHeight
*/
I32 FRAMEWIN_SetTitleHeight(FRAMEWIN_Handle hObj, I32 Height) {
  I32 r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    I32 OldHeight;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    r = pObj->Props.TitleHeight;
    if (Height != r) {
      OldHeight = FRAMEWIN__CalcTitleHeight(pObj);
      pObj->Props.TitleHeight = Height;
      FRAMEWIN__UpdatePositions(pObj);
      FRAMEWIN__UpdateButtons(pObj, OldHeight);
      FRAMEWIN_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
  return r;
}


#else
  void FRAMEWIN_SetTitleHeight_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
