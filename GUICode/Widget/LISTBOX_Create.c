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
File        : LISTBOX_Create.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX.h"

#if GUI_WINSUPPORT && LISTBOX_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_Create
*/
LISTBOX_Handle LISTBOX_Create(const GUI_ConstString* ppText, I32 x0, I32 y0, I32 xsize, I32 ysize, I32 Flags) {
  return LISTBOX_CreateEx(x0, y0, xsize, ysize, WM_HWIN_NULL, Flags, 0, 0, ppText);
}

/*********************************************************************
*
*       LISTBOX_CreateAsChild
*/
LISTBOX_Handle LISTBOX_CreateAsChild(const GUI_ConstString* ppText, WM_HWIN hWinParent,
                                     I32 x0, I32 y0, I32 xsize, I32 ysize, I32 Flags)
{
  return LISTBOX_CreateEx(x0, y0, xsize, ysize, hWinParent, Flags, 0, 0, ppText);
}

#else  /* avoid empty object files */
  void LISTBOX_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
