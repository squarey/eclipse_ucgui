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
File        : EDIT_Create.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "EDIT.h"

#if GUI_WINSUPPORT && EDIT_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_Create
*/
EDIT_Handle EDIT_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, I32 Id, I32 MaxLen, I32 Flags) {
  return EDIT_CreateEx(x0, y0, xsize, ysize, WM_HMEM_NULL, Flags, 0, Id, MaxLen);
}

/*********************************************************************
*
*       EDIT_CreateAsChild
*/
EDIT_Handle EDIT_CreateAsChild(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags, I32 MaxLen) {
  return EDIT_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id, MaxLen);
}

#else  /* avoid empty object files */
  void EDIT_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
