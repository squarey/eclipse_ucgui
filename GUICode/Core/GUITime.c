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
File        : GUITime.C
Purpose     : Time related routines
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

static U32 SystemTime = 0;
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*
 * 	GUI_TimeIncrease
 * 	TickPeriod: unit ms
 * */
void GUI_TimeIncrease(U32 TickPeriod)
{
	SystemTime += TickPeriod;
}
U32 GUI_GetTimeElapsed(U32 PrevTime)
{
	if(SystemTime >= PrevTime) {
			PrevTime = SystemTime - PrevTime;
	} else {
		PrevTime = 0xffffffff - PrevTime + 1;
		PrevTime += SystemTime;
	}
	return PrevTime;
}
/*********************************************************************
*
*       GUI_GetTime
*/
U32 GUI_GetTime(void)
{
	return SystemTime;
}
/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
