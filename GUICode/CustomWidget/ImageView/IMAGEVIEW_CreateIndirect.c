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
File        : IMAGEVIEW_CreateIndirect.c
Purpose     : Implementation of slider widget
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
*       IMAGEVIEW_CreateIndirect
*/
IMAGEVIEW_Handle IMAGEVIEW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb) {
  IMAGEVIEW_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = IMAGEVIEW_CreateEx(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                          hWinParent, pCreateInfo->Flags, 0 , pCreateInfo->Id);
  return hThis;
}

#else  /* avoid empty object files */
  void IMAGEVIEW_CreateIndirect_C(void) {}
#endif
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
