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
File        : GUI__memset.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
//#include <string.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__memset
*
* Purpose:
*  Replacement for the memset function. The advantage is high speed
*  on all systems (sometime up to 10 times as fast as the one
*  in the library)
*  Main idea is to write I32-wise.
*/
void GUI__memset(U8* p, U8 Fill, I32 NumBytes) {
  I32 NumInts;
  /* Write bytes until we are done or have reached an I32 boundary */
  while ((U32)NumBytes && (U32)((sizeof(I32) - 1) & (U32)p)) {
    *p++ = Fill;
    NumBytes--;
  }
  /* Write Ints */
  NumInts = (unsigned)NumBytes / sizeof(I32);
  if (NumInts) {
    I32 FillInt;
    I32 *pInt;
    NumBytes &= (sizeof(I32) - 1);
    if (sizeof(I32) == 2) {        /* May some compilers generate a warning at this line: Condition is alwaws true/false */
      FillInt = Fill * 0x101;      /* May some compilers generate a warning at this line: Unreachable code */
    } else if (sizeof(I32) == 4) { /* May some compilers generate a warning at this line: Condition is alwaws true/false */
      FillInt = Fill * 0x1010101;  /* May some compilers generate a warning at this line: Unreachable code */
    }
    pInt = (I32*)p;
    /* Fill large amount of data at a time */
    while (NumInts >= 4) { 
      *pInt++ = FillInt;
      *pInt++ = FillInt;
      *pInt++ = FillInt;
      *pInt++ = FillInt;
      NumInts -= 4;
    }
    /* Fill one I32 at a time */
    while (NumInts) {
      *pInt++ = FillInt;
      NumInts--;
    }
    p = (U8*)pInt;
  }
  /* Fill the remainder byte wise */
  while (NumBytes) {
    *p++ = Fill;
    NumBytes--;
  }
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
