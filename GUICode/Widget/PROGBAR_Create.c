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
File        : PROGBAR_Create.c
Purpose     : Implementation of progbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "PROGBAR.h"

#if GUI_WINSUPPORT && PROGBAR_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_Create
*/
PROGBAR_Handle PROGBAR_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, I32 Flags) {
  return PROGBAR_CreateEx(x0, y0, xsize, ysize, 0, Flags, 0, 0);
}

/*********************************************************************
*
*       PROGBAR_CreateAsChild
*/
PROGBAR_Handle PROGBAR_CreateAsChild(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags) {
  return PROGBAR_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id);
}

#else  /* avoid empty object files */
  void PROGBAR_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
