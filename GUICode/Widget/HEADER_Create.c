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
File        : HEADER_Create.c
Purpose     : Implementation of header widget
---------------------------END-OF-HEADER------------------------------
*/

#include "HEADER.h"

#if GUI_WINSUPPORT && HEADER_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_CreateAttached
*/
HEADER_Handle HEADER_CreateAttached(WM_HWIN hParent, I32 Id, I32 SpecialFlags) {
  return HEADER_CreateEx(0, 0, 0, 0, hParent, WM_CF_SHOW, SpecialFlags, Id);
}

#else  /* avoid empty object files */
  void HEADER_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
