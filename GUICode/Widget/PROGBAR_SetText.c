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
File        : PROGBAR_SetText.c
Purpose     : Implementation of progbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "PROGBAR_Private.h"

#if GUI_WINSUPPORT && PROGBAR_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_SetText
*/
void PROGBAR_SetText(PROGBAR_Handle hObj, const char* s) {
  if (hObj) {
    PROGBAR_Obj* pObj;
    const GUI_FONT GUI_UNI_PTR * pOldFont;
    GUI_RECT r1;
    char acBuffer[5];
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pOldFont = GUI_SetFont(pObj->Props.pFont);
    PROGBAR_GetTextRect(pObj, &r1, PROGBAR_GetText(pObj, acBuffer));
    if (!s) {
      PROGBAR_FreeText(hObj);
      WM_InvalidateRect(hObj, &r1);
    } else {
      if (GUI__SetText(&pObj->hpText, s)) {
        GUI_RECT r2;
        PROGBAR_GetTextRect(pObj, &r2, PROGBAR_GetText(pObj, acBuffer));
        GUI_MergeRect(&r1, &r1, &r2);
        WM_InvalidateRect(hObj, &r1);
      }
    }
    GUI_SetFont(pOldFont);
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void PROGBAR_SetText_C(void);
  void PROGBAR_SetText_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
