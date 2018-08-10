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
File        : TEXT_SetTextAlign.c
Purpose     : Implementation of TEXT_SetTextAlign
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>
#include "TEXT_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT && TEXT_SUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       TEXT_SetTextAlign
*/
void TEXT_SetTextAlign(TEXT_Handle hObj, I32 Align)
{
	if (hObj) {
		TEXT_Obj* pObj;
		pObj = TEXT_H2P(hObj);
		pObj->Align = Align;
		WM_Invalidate(hObj);
	}
}

#else  /* avoid empty object files */

void TEXT_SetTextAlign_c(void);
void TEXT_SetTextAlign_c(void){}

#endif  /* #if GUI_WINSUPPORT */

	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
