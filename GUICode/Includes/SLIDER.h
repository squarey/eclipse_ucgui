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
File        : SLIDER.h
Purpose     : SLIDER include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef SLIDER_H
#define SLIDER_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT && SLIDER_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/************************************************************
*
*       #defines
*
*************************************************************
*/

/************************************************************
*
*       States
*/
#define SLIDER_STATE_PRESSED    WIDGET_STATE_USER0

/************************************************************
*
*       Create / Status flags
*/
#define SLIDER_CF_VERTICAL WIDGET_CF_VERTICAL

/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef U8 (*SILDER_UserDraw)(WM_HWIN hWin, I32 CurValue, I32 MaxValue, I32 MinValue);

typedef WM_HMEM SLIDER_Handle;
/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

SLIDER_Handle SLIDER_Create        (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags);
SLIDER_Handle SLIDER_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
SLIDER_Handle SLIDER_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                    I32 WinFlags, I32 ExFlags, I32 Id);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void SLIDER_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

/* Methods changing properties */

/* Note: These are just examples. The actual methods available for the
   widget will depend on the type of widget. */
void      SLIDER_Dec          (SLIDER_Handle hObj);
void      SLIDER_Inc          (SLIDER_Handle hObj);
void      SLIDER_SetBkColor   (SLIDER_Handle hObj, GUI_COLOR Color);
GUI_COLOR SLIDER_SetFocusColor(SLIDER_Handle hObj, GUI_COLOR Color);
void      SLIDER_SetNumTicks  (SLIDER_Handle hObj, I32 NumTicks);
void      SLIDER_SetRange     (SLIDER_Handle hObj, I32 Min, I32 Max);
void      SLIDER_SetValue     (SLIDER_Handle hObj, I32 v);
void      SLIDER_SetWidth     (SLIDER_Handle hObj, I32 Width);
GUI_COLOR SLIDER_SetColor	  (SLIDER_Handle hObj, GUI_COLOR Color);
void SLIDER_SetUserDrawMethod(SLIDER_Handle hObj, void *pFunc);
/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

void      SLIDER_SetDefaultBkColor   (GUI_COLOR Color);
GUI_COLOR SLIDER_SetDefaultFocusColor(GUI_COLOR Color);

/*********************************************************************
*
*                 Query state
*
**********************************************************************
*/
I32 SLIDER_GetValue(SLIDER_Handle hObj);

#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* SLIDER_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
