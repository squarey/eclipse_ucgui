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
File        : WM_SetWindowPos.c
Purpose     : Implementation of WM_SetWindowPos
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetWindowPos
*/
void WM_SetWindowPos(WM_HWIN hWin, I32 xPos, I32 yPos)
{
	WM_MoveTo(hWin, xPos, yPos);
}
void WM_SetWindowPosAndSize(WM_HWIN hWin, I32 xPos, I32 yPos, I32 xSize, I32 ySize)
{
	WM_SetSize(hWin, xSize, ySize);
	WM_MoveTo(hWin, xPos, yPos);
}
void WM_SetWindowPosX(WM_HWIN hWin, I32 xPos)
{
	I32 PosY = WM_GetWindowOrgY(hWin);
	WM_MoveTo(hWin, xPos, PosY);
}
void WM_SetWindowPosY(WM_HWIN hWin, I32 yPos)
{
	I32 PosX = WM_GetWindowOrgX(hWin);
	WM_MoveTo(hWin, PosX, yPos);
}
void WM_SetWindowRect(WM_HWIN hWin, GUI_RECT Rect)
{
	if(hWin){
		WM_Obj *pObj;
		pObj = WM_H2P(hWin);
		if(GUI_memcmp(&pObj->Rect, &Rect, sizeof(GUI_RECT))){
			pObj->Rect = Rect;
			WM_InvalidateWindow(hWin);
		}
	}
}
#else
  void WM_SetWindowPos_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
