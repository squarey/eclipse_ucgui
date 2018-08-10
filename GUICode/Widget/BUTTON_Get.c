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
File        : BUTTON_Get.c
Purpose     : Button widget, various (optional) Get routines
---------------------------END-OF-HEADER------------------------------
*/

//#include <string.h>
#include "BUTTON.h"
#include "BUTTON_Private.h"
#include "GUI_Protected.h"
#include "GUI_ReDefine.h"

#if GUI_WINSUPPORT && BUTTON_SUPPORT

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_GetBkColor  
*/
GUI_COLOR BUTTON_GetBkColor(BUTTON_Handle hObj,U32 Index)
{
	GUI_COLOR Color = 0;
	if (hObj && (Index < 2)) {
		BUTTON_Obj * pObj;
		pObj = BUTTON_H2P(hObj);
		Color = pObj->Props.aBkColor[Index];
	}
	return Color;
}

/*********************************************************************
*
*       BUTTON_GetFont     
*/
const GUI_FONT GUI_UNI_PTR * BUTTON_GetFont(BUTTON_Handle hObj)
{
	const GUI_FONT GUI_UNI_PTR * pFont = 0;
	if (hObj) {
		BUTTON_Obj * pObj;
		pObj = BUTTON_H2P(hObj);
		pFont = pObj->Props.pFont;
	}
	return pFont;
}

/*********************************************************************
*
*       BUTTON_GetText  
*/
void BUTTON_GetText(BUTTON_Handle hObj, char * pBuffer, I32 MaxLen)
{
	if (hObj) {
	BUTTON_Obj * pObj;
	pObj = BUTTON_H2P(hObj);
	if (pObj->hpText) {
		const char * pText = (const char*) GUI_ALLOC_h2p(pObj->hpText);
		I32 Len = GUI_strlen(pText);
		if (Len > (MaxLen - 1))
			Len = MaxLen - 1;
		GUI_memcpy((void *)pBuffer, (const void *)pText, Len);
		*(pBuffer + Len) = 0;
		} else {
			*pBuffer = 0;     /* Empty string */
		}
	}
}

/*********************************************************************
*
*       BUTTON_GetTextColor  
*/
GUI_COLOR BUTTON_GetTextColor(BUTTON_Handle hObj,U32 Index)
{
	GUI_COLOR Color = 0;
	if (hObj && (Index < 2)) {
		BUTTON_Obj * pObj;
		pObj = BUTTON_H2P(hObj);
		Color = pObj->Props.aTextColor[Index];
	}
	return Color;
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_Get_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
