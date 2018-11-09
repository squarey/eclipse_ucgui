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
File        : GUIPolyR.c
Purpose     : Polygon rotation
----------------------------------------------------------------------
*/

#include <math.h>
#include "GUI.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_RotatePolygon
*/
void GUI_RotatePolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, I32 NumPoints, float Angle) {
  I32 j;
  float fcos = cos(Angle);
  float fsin = sin(Angle);
  for (j = 0; j < NumPoints; j++) {
    I32 x = (pSrc+j)->x;
    I32 y = (pSrc+j)->y;
    (pDest+j)->x =  x * fcos + y * fsin + 0.3;
    (pDest+j)->y = -x * fsin + y * fcos + 0.3;
  }
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
