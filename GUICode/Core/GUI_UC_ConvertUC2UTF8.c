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
File        : GUI_UC_ConvertUC2UTF8.c
Purpose     : Converts a UNICODE string to UTF8
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_UC_ConvertUC2UTF8
*/
I32 GUI_UC_ConvertUC2UTF8(const U16 GUI_UNI_PTR * s, I32 Len, char * pBuffer, I32 BufferSize)
{
	I32 LenDest;
	LenDest = 0;
	while (Len--) {
		I32 NumBytes;
		NumBytes = GUI_UC_Encode(pBuffer, *s++);
		if ((LenDest + NumBytes) > BufferSize) {
			break;
		}
		pBuffer += NumBytes;
		LenDest += NumBytes;
	}
	return LenDest;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
