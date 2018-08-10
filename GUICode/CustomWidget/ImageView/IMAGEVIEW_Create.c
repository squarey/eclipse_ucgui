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
File        : SLIDER_Create.c
Purpose     : Implementation of imageview widget
---------------------------END-OF-HEADER------------------------------
*/

#include "IMAGEVIEW.h"

#if GUI_WINSUPPORT && IMAGEVIEW_SUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       SLIDER_Create
*/
IMAGEVIEW_Handle IMAGEVIEW_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags) {
  return IMAGEVIEW_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}

#else  /* avoid empty object files */
  void ImageView_Create_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
