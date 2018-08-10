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
File        : LCDInfo1.C
Purpose     : Routines returning info at runtime
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.h"		          /* interface definitions */
#include "LCD_Private.h"      /* private modul definitions & config */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

I32 LCD_GetXSize(void)        { return LCD_XSIZE; }
I32 LCD_GetYSize(void)        { return LCD_YSIZE; }
I32 LCD_GetVXSize(void)       { return LCD_VXSIZE; }
I32 LCD_GetVYSize(void)       { return LCD_VYSIZE; }
I32 LCD_GetBitsPerPixel(void) { return LCD_BITSPERPIXEL; }
U32 LCD_GetNumColors(void)    { return LCD_NUM_COLORS; }
I32 LCD_GetYMag(void)         { return LCD_YMAG; }
I32 LCD_GetXMag(void)         { return LCD_XMAG; }
I32 LCD_GetFixedPalette(void) { return LCD_FIXEDPALETTE; }

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
