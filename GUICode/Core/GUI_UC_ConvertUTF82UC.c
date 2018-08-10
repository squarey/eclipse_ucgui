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
File        : GUI_UC_ConvertUTF82UC.c
Purpose     : Converts a UTF8 string to UNICODE
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
*       GUI_UC_ConvertUTF82UC
*/
I32 GUI_UC_ConvertUTF82UC(const char GUI_UNI_PTR * s, I32 Len, U16 * pBuffer, I32 BufferSize)
{
	I32 LenDest;
	LenDest = 0;
	while (Len) {
		I32 NumBytes;
		NumBytes = GUI_UC_GetCharSize(s);
		*(pBuffer++) = GUI_UC_GetCharCode(s);
		s += NumBytes;
		LenDest++;
		if (LenDest >= BufferSize) {
			break;
		}
		Len -= NumBytes;
	}
	return LenDest;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
