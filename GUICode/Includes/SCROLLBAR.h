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
File        : SCROLLBAR.h
Purpose     : SCROLLBAR include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef _SCROLLBAR_H
#define _SCROLLBAR_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*********************************************************************
*
*       Public Types
*
**********************************************************************
*/
typedef WM_HMEM SCROLLBAR_Handle;

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/
SCROLLBAR_Handle SCROLLBAR_Create        (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags);
SCROLLBAR_Handle SCROLLBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
SCROLLBAR_Handle SCROLLBAR_CreateAttached(WM_HWIN hParent, I32 SpecialFlags);
SCROLLBAR_Handle SCROLLBAR_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                          I32 WinFlags, I32 ExFlags, I32 Id);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
//void SCROLLBAR_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/

/* Methods changing properties */
void SCROLLBAR_SetActualLength(SCROLLBAR_Handle hObj, I32 Length);
void SCROLLBAR_SetOffest(SCROLLBAR_Handle hObj, I16 Offest);
void SCROLLBAR_CreateAlphaAnim(SCROLLBAR_Handle hObj);
void SCROLLBAR_DeleteAlphaAnim(SCROLLBAR_Handle hObj);
void      SCROLLBAR_AddValue   (SCROLLBAR_Handle hObj, I32 Add);
void      SCROLLBAR_Dec        (SCROLLBAR_Handle hObj);
void      SCROLLBAR_Inc        (SCROLLBAR_Handle hObj);
GUI_COLOR SCROLLBAR_SetColor   (SCROLLBAR_Handle hObj, I32 Index, GUI_COLOR Color);
void      SCROLLBAR_SetNumItems(SCROLLBAR_Handle hObj, I32 NumItems);
void      SCROLLBAR_SetPageSize(SCROLLBAR_Handle hObj, I32 PageSize);
void      SCROLLBAR_SetValue   (SCROLLBAR_Handle hObj, I32 v);
I32       SCROLLBAR_SetWidth   (SCROLLBAR_Handle hObj, I32 Width);
//void      SCROLLBAR_SetState   (SCROLLBAR_Handle hObj, const WM_SCROLL_STATE* pState);

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
I32       SCROLLBAR_GetDefaultWidth  (void);
GUI_COLOR SCROLLBAR_SetDefaultColor  (GUI_COLOR Color, U32 Index); /* Not yet documented */
I32       SCROLLBAR_SetDefaultWidth  (I32 DefaultWidth);

/*********************************************************************
*
*       Query state
*
**********************************************************************
*/
I32 SCROLLBAR_GetValue(SCROLLBAR_Handle hObj);


#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* SCROLLBAR_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
