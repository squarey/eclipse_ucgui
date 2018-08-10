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
File        : GUI_Goto.c
Purpose     : Implementation of GUI_Goto... routines
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
//#include <string.h>
#include "GUI_Protected.h"
 
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GotoY
*/
static char _GotoY(I32 y)
{
	GUI_Context.DispPosY = y;
	return 0;
}

/*********************************************************************
*
*       _GotoX
*/
static char _GotoX(I32 x)
{
	GUI_Context.DispPosX = x;
	return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GotoY
*/
char GUI_GotoY(I32 y)
{
	char r;
	r = _GotoY(y);
	return r;
}

/*********************************************************************
*
*       GUI_GotoX
*/
char GUI_GotoX(I32 x)
{
	char r;
	r = _GotoX(x);
	return r;
}

/*********************************************************************
*
*       GUI_GotoXY
*/
char GUI_GotoXY(I32 x, I32 y)
{
	char r;
	r  = _GotoX(x);
	r |= _GotoY(y);
	return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
