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
File        : GUI_UC_EncodeUTF8.c
Purpose     : Encoding routines
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_UC_GetCharSize
*/
I32 GUI_UC_GetCharSize(const char GUI_UNI_PTR * s)
{
#if GUI_SUPPORT_UNICODE
	I32 r;
	r =  GUI_Context.pUC_API->pfGetCharSize(s);
	return r;
#else
	return 1;
#endif
}

/*********************************************************************
*
*       GUI_UC_GetCharCode
*/
U16 GUI_UC_GetCharCode(const char GUI_UNI_PTR * s)
{
#if GUI_SUPPORT_UNICODE
	U16 r;
	r =  GUI_Context.pUC_API->pfGetCharCode(s);
	return r;
#else
	return *(const U8 GUI_UNI_PTR *)s;
#endif
}

/*********************************************************************
*
*       GUI_UC_Encode
*/
I32 GUI_UC_Encode(char* s, U16 Char)
{
#if GUI_COMPILER_SUPPORTS_FP
#if GUI_SUPPORT_UNICODE
	I32 r;
	r = GUI_Context.pUC_API->pfEncode(s, Char);
	return r;
#else
	*s = (U8)(Char);
	return Char;
#endif
#else
	GUI_USE_PARA(s);
	GUI_USE_PARA(Char);
	return 0;
#endif
}

/*********************************************************************
*
*       GUI_UC__CalcSizeOfChar
*/
I32 GUI_UC__CalcSizeOfChar(U16 Char)
{
#if GUI_SUPPORT_UNICODE
    return GUI_Context.pUC_API->pfCalcSizeOfChar(Char);
#else
    return 1;
#endif
}

/*********************************************************************
*
*       GUI_UC__GetCharCodeInc
*/
U16 GUI_UC__GetCharCodeInc(const char GUI_UNI_PTR ** ps)
{
	const char GUI_UNI_PTR * s;
	U16 r;
	s   = *ps;
#if GUI_SUPPORT_UNICODE
	r   = GUI_UC__GetCharCode(s);
	s  += GUI_UC__GetCharSize(s);
#else
	r   = *s;
	s  += 1;
#endif
	*ps = s;
	return r;
}

/*********************************************************************
*
*       GUI_UC__NumChars2NumBytes
*/
I32 GUI_UC__NumChars2NumBytes(const char GUI_UNI_PTR * s, I32 NumChars)
{
	I32 CharSize, NumBytes = 0;
	while (NumChars--) {
#if GUI_SUPPORT_UNICODE
		CharSize = GUI_UC__GetCharSize(s);
#else
		CharSize = 1;
#endif
		s += CharSize;
		NumBytes += CharSize;
	}
	return NumBytes;
}

/*********************************************************************
*
*       GUI_UC__NumBytes2NumChars
*/
I32 GUI_UC__NumBytes2NumChars(const char GUI_UNI_PTR * s, I32 NumBytes)
{
	I32 CharSize, Chars = 0, Bytes = 0;
	while (NumBytes > Bytes) {
#if GUI_SUPPORT_UNICODE
		CharSize = GUI_UC__GetCharSize(s + Bytes);
#else
		CharSize = 1;
#endif
		Bytes += CharSize;
		Chars++;
	}
	return Chars;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
