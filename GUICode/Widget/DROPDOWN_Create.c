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
File        : DROPDOWN_Create.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include "DROPDOWN.h"

#if GUI_WINSUPPORT && DROPDOWN_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       DROPDOWN_Create
*/
DROPDOWN_Handle DROPDOWN_Create(WM_HWIN hWinParent, I32 x0, I32 y0, I32 xsize, I32 ysize, I32 Flags) {
  return DROPDOWN_CreateEx(x0, y0, xsize, ysize, hWinParent, Flags, 0, 0);
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
