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
File        : GUI_Exec.c
Purpose     : Implementation of GUI_Exec
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#if GUI_WINSUPPORT
#include "WM.h"
#include "GUI_Animation.h"
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_Exec1
*/
I32 GUI_Exec1(void)
{
	I32 r = 0;
	/* Execute background jobs */
	if (GUI_pfTimerExec) {
		if ((*GUI_pfTimerExec)()) {
			r = 1;                  /* We have done something */
		}
	}
	GUI_Animation_Exec();
	GUI_TOUCH_Exec();
#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
	if (WM_Exec()){
		r = 1;
	}
#endif
	return r;
}

/*********************************************************************
*
*       GUI_Exec
*/
I32 GUI_Exec(void)
{
	I32 r = 0;
	while (GUI_Exec1()) {
		r = 1;                  /* We have done something */
	}
	return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
