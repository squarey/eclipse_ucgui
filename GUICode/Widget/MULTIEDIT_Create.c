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
File        : MULTIEDIT_Create.c
Purpose     : Implementation of multiedit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MULTIEDIT.h"

#if GUI_WINSUPPORT && MULTIEDIT_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIEDIT_Create
*/
MULTIEDIT_HANDLE MULTIEDIT_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags, I32 ExFlags, const char * pText, I32 MaxLen) {
  return MULTIEDIT_CreateEx(x0, y0, xsize, ysize, hParent, Flags, ExFlags, Id, MaxLen, pText);
}

#else  /* avoid empty object files */
  void MULTIEDIT_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
