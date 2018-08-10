/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDPM888.C
Purpose     : Color conversion routines for 888 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

#define B_BITS 8
#define G_BITS 8
#define R_BITS 8
#define A_BITS 8

#define R_MASK ((1 << R_BITS) -1)
#define G_MASK ((1 << G_BITS) -1)
#define B_MASK ((1 << B_BITS) -1)
#define A_MASK ((1 << A_BITS) -1)
/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 8888, 16777216 colors, RRRRRRRRGGGGGGGGBBBBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_8888
*/
unsigned LCD_Color2Index_8888(LCD_COLOR Color) {
  I32 a, r,g,b;
  r = (Color>> (8  - R_BITS)) & R_MASK;
  g = (Color>> (16 - G_BITS)) & G_MASK;
  b = (Color>> (24 - B_BITS)) & B_MASK;
  a = (Color>> (32 - A_BITS)) & A_MASK;
  return b + (g << B_BITS) + (r << (G_BITS + B_BITS))+(a<<(G_BITS + B_BITS + R_BITS));
}


/*********************************************************************
*
*       LCD_Index2Color_8888
*/
LCD_COLOR LCD_Index2Color_8888(I32 Index) {
  U32 a, r,g,b;
  /* Seperate the color masks */
  b = Index                                            & B_MASK;
  g = (Index >> B_BITS)                                & G_MASK;
  r = ((unsigned)Index >> (B_BITS + G_BITS))           & R_MASK;
  a = ((unsigned)Index >> (B_BITS + G_BITS + R_BITS))  & A_MASK;
  /* Convert the color masks */
  r = r * 255 / R_MASK;
  g = g * 255 / G_MASK;
  b = b * 255 / B_MASK;
  a = a * 255 / A_MASK;
  return r + (g<<8) + (((U32)b)<<16)+(((U32)a)<<24);
}
/*********************************************************************
*
*       LCD_GetIndexMask_M565
*/
unsigned LCD_GetIndexMask_8888(void) {
  return 0xffffffff;
}


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
