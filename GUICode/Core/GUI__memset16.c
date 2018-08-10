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
File        : GUI__memset16.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
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
*  Equivalent to the memset function, for 16 bit Data.
*/
void GUI__memset16(U16 * p, U16 Fill, I32 NumWords) {
  /* Code for 16 bit CPUs */
  if (sizeof(I32) == 2) { /* May some compilers generate a warning at this line: Condition is alwaws true/false */
    if (NumWords >= 8) {  /* May some compilers generate a warning at this line: Unreachable code */
      *p++ = Fill;
      *p++ = Fill;
      *p++ = Fill;
      *p++ = Fill;
      *p++ = Fill;
      *p++ = Fill;
      *p++ = Fill;
      *p++ = Fill;
      NumWords -= 8;
    }
    while (NumWords) {
      *p++ = Fill;
      NumWords--;
    }
  } else {
    I32 NumInts;
    /* May some compilers generate a warning at this line: Unreachable code */
    /* Write 16 bit until we are done or have reached an I32 boundary */
    if ((U32)2 & (U32)p) {
      *p++ = Fill;
      NumWords--;
    }
    /* Write Ints */
    NumInts = (unsigned)NumWords / (sizeof(I32) / 2);
    if (NumInts) {
      I32 FillInt;
      I32 *pInt;
      FillInt = Fill * 0x10001;

      pInt = (I32*)p;
      /* Fill large amount of data at a time */
      if (NumInts >= 4) {
        do {
          *pInt       = FillInt;
          *(pInt + 1) = FillInt;
          *(pInt + 2) = FillInt;
          *(pInt + 3) = FillInt;
          pInt += 4;
        } while ((NumInts -= 4) >= 4);
      }
      /* Fill one I32 at a time */
      while (NumInts) {
        *pInt++ = FillInt;
        NumInts--;
      }
      p = (U16*)pInt;
    }
    /* Fill the remainder */
    if (NumWords & 1) {
      *p = Fill;
    }
  }
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
