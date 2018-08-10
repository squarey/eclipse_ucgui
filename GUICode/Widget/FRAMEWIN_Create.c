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
File        : FRAMEWIN_Create.c
Purpose     : Implementation of framewin widget
---------------------------END-OF-HEADER------------------------------
*/

#include "FRAMEWIN.h"

#if GUI_WINSUPPORT && FRAMEWIN_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_Create
*/
FRAMEWIN_Handle FRAMEWIN_Create(const char* pText, WM_CALLBACK* cb, I32 Flags,
                                I32 x0, I32 y0, I32 xsize, I32 ysize) {
  return FRAMEWIN_CreateEx(x0, y0, xsize, ysize, WM_HWIN_NULL, Flags, 0, 0, pText, cb);
}

/*********************************************************************
*
*       FRAMEWIN_CreateAsChild
*/
FRAMEWIN_Handle FRAMEWIN_CreateAsChild(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                       const char* pText, WM_CALLBACK* cb, I32 Flags) {
  return FRAMEWIN_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, 0, pText, cb);
}

#else  /* avoid empty object files */
  void FRAMEWIN_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
