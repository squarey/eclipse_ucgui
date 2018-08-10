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
File        : RADIO_Create.c
Purpose     : Implementation of radio widget
---------------------------END-OF-HEADER------------------------------
*/

#include "RADIO.h"

#if GUI_WINSUPPORT && RADIO_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_Create
*/
RADIO_Handle RADIO_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags, unsigned Para) {
  return RADIO_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id, Para & 0xFF, (Para >> 8) & 0xFF);
}

#else  /* avoid empty object files */
  void RADIO_Create_C(void) {}
#endif

/************************* end of file ******************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
