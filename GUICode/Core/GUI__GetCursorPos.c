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
File        : GUI__GetCursorPos.c
Purpose     : Implementation of optional routine
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
*       GUI__GetCursorPosX
*
* Purpose:
*   Returns the cursor position in pixels by the given index
*
* Parameters:
*   s           : Pointer to the string
*   Index       : Index of cursor character
*   MaxNumChars : Number of charaters in the string
*/
I32 GUI__GetCursorPosX(const char GUI_UNI_PTR * s, I32 Index, I32 MaxNumChars) {
  #if GUI_SUPPORT_ARABIC
    return GUI__GetCursorPosXArabic(s, Index, MaxNumChars);
  #else
    I32 CursorPosX = 0;
    U16 Char;
    GUI_USE_PARA(MaxNumChars);
    while (Index--) {
      Char        = GUI_UC__GetCharCodeInc(&s);
      CursorPosX += GUI_GetCharDistX(Char);
    }
    return CursorPosX;
  #endif
}

/*********************************************************************
*
*       GUI__GetCursorPosChar
*
* Purpose:
*   Returns the cursor character index by the given pixel position
*
* Parameters:
*   s           : Pointer to the string
*   x           : X position of the cursor
*   MaxNumChars : Number of charaters in the string
*/
I32 GUI__GetCursorPosChar(const char GUI_UNI_PTR * s, I32 x, I32 MaxNumChars) {
  #if GUI_SUPPORT_ARABIC
    return GUI__GetCursorPosCharArabic(s, x, MaxNumChars);
  #else
    I32 SizeX = 0;
    const char GUI_UNI_PTR * p;
    p = s;
    while (--MaxNumChars> 0) {
      U16 Char;
      Char   = GUI_UC_GetCharCode(s);
      SizeX += GUI_GetCharDistX(Char);
      if (!Char || (SizeX > x)) {
        break;
      }
      s += GUI_UC_GetCharSize(s);
    }
    return GUI_UC__NumBytes2NumChars(p, s - p);
  #endif
}

/*********************************************************************
*
*       GUI__GetCursorCharacter
*/
U16 GUI__GetCursorCharacter(const char GUI_UNI_PTR * s, I32 Index, I32 MaxNumChars, I32 * pIsRTL) {
  #if GUI_SUPPORT_ARABIC
    return GUI__GetCursorCharacterArabic(s, Index, MaxNumChars, pIsRTL);
  #else
    GUI_USE_PARA(MaxNumChars);
    if (pIsRTL) {
      *pIsRTL = 0;
    }
    return GUI_UC_GetCharCode(s + Index);
  #endif
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
