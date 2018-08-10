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
File        : LISTBOX_SetString.c
Purpose     : Implementation of LISTBOX_SetString
---------------------------END-OF-HEADER------------------------------
*/

//#include <string.h>
#include "LISTBOX_Private.h"
#include "GUI_ReDefine.h"

#if GUI_WINSUPPORT && LISTBOX_SUPPORT


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_SetString
*/
void LISTBOX_SetString(LISTBOX_Handle hObj, const char* s, U32 Index) {
  if (hObj) {
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    if (Index < (U32)LISTBOX__GetNumItems(pObj)) {
      LISTBOX_ITEM* pItem;
      pItem = (LISTBOX_ITEM*)GUI_ARRAY_ResizeItem(&pObj->ItemArray, Index, sizeof(LISTBOX_ITEM) + GUI_strlen(s));
      if (pItem) {
        GUI_strcpy(pItem->acText, s);
        LISTBOX__InvalidateItemSize(pObj, Index);
        LISTBOX_UpdateScrollers(hObj);
        LISTBOX__InvalidateItem(hObj, pObj, Index);
      }
    }
    WM_UNLOCK();
  }
}


#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetString_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
