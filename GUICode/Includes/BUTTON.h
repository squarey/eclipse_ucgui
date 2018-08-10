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
File        : BUTTON.h
Purpose     : BUTTON public header file (API)
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "GUI_StyleDraw.h"


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#if GUI_WINSUPPORT && BUTTON_SUPPORT

/************************************************************
*
*       Create flags
*/
/* For compatibility only ! */
#define BUTTON_CF_HIDE   WM_CF_HIDE
#define BUTTON_CF_SHOW   WM_CF_SHOW
#define BUTTON_CF_MEMDEV WM_CF_MEMDEV

/*********************************************************************
*
*       Color indices
*/
#define BUTTON_CI_UNPRESSED 0
#define BUTTON_CI_PRESSED   1
#define BUTTON_CI_DISABLED  2

/*********************************************************************
*
*       Bitmap indices
*/
#define BUTTON_BI_UNPRESSED 0
#define BUTTON_BI_PRESSED   1
#define BUTTON_BI_DISABLED  2

/************************************************************
*
*       Messages
*/

/************************************************************
*
*       States
*/

#define BUTTON_STATE_FOCUS      WIDGET_STATE_FOCUS
#define BUTTON_STATE_PRESSED    WIDGET_STATE_USER0

/************************************************************
*
*       Types
*
*************************************************************
*/
typedef WM_HMEM BUTTON_Handle;

/************************************************************
*
*       Create function(s)

  Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions
*/

BUTTON_Handle BUTTON_Create        (I32 x0, I32 y0, I32 xsize, I32 ysize, I32 ID, I32 Flags);
BUTTON_Handle BUTTON_CreateAsChild (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags);
BUTTON_Handle BUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
BUTTON_Handle BUTTON_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                    I32 WinFlags, I32 ExFlags, I32 Id);

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

GUI_COLOR                    	BUTTON_GetDefaultBkColor   (unsigned Index);
const GUI_FONT GUI_UNI_PTR* BUTTON_GetDefaultFont      (void);
I32                          	BUTTON_GetDefaultTextAlign (void);
GUI_COLOR                    	BUTTON_GetDefaultTextColor (unsigned Index);
void                         	BUTTON_SetDefaultBkColor   (GUI_COLOR Color, unsigned Index);
GUI_COLOR                    	BUTTON_SetDefaultFocusColor(GUI_COLOR Color);
void                         	BUTTON_SetDefaultFont      (const GUI_FONT GUI_UNI_PTR * pFont);
void                         	BUTTON_SetDefaultTextAlign (I32 Align);
void                         	BUTTON_SetDefaultTextColor (GUI_COLOR Color, unsigned Index);
void 							BUTTON_SetDefaultPressStyle(GUI_FullRectStyle *pStyle);
void 							BUTTON_SetDefaultRelStyle	 (GUI_FullRectStyle *pStyle);
#define BUTTON_EnableMemdev(hObj)  WM_EnableMemdev    (hObj)
#define BUTTON_DisableMemdev(hObj) WM_DisableMemdev   (hObj)
#define BUTTON_Delete(hObj)        WM_DeleteWindow    (hObj)
#define BUTTON_Paint(hObj)         WM_Paint           (hObj)
#define BUTTON_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void BUTTON_Callback(WM_MESSAGE *pMsg);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/

GUI_COLOR        				BUTTON_GetBkColor         (BUTTON_Handle hObj, U32 Index);
const GUI_FONT GUI_UNI_PTR* BUTTON_GetFont			(BUTTON_Handle hObj);
void             				BUTTON_GetText            (BUTTON_Handle hObj, char * pBuffer, I32 MaxLen);
GUI_COLOR        				BUTTON_GetTextColor       (BUTTON_Handle hObj, U32 Index);
unsigned         				BUTTON_IsPressed          (BUTTON_Handle hObj);
void             				BUTTON_SetBkColor         (BUTTON_Handle hObj, U32 Index, GUI_COLOR Color);
void             				BUTTON_SetFont            (BUTTON_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont);
void             				BUTTON_SetState           (BUTTON_Handle hObj, I32 State);                                    /* Not to be doc. */
void             				BUTTON_SetPressed         (BUTTON_Handle hObj, I32 State);
GUI_COLOR        				BUTTON_SetFocusColor      (BUTTON_Handle hObj, GUI_COLOR Color);
void             				BUTTON_SetFocussable      (BUTTON_Handle hObj, I32 State);
void            	 			BUTTON_SetText            (BUTTON_Handle hObj, const char* s);
void             				BUTTON_SetTextAlign       (BUTTON_Handle hObj, I32 Align);
void             				BUTTON_SetTextColor       (BUTTON_Handle hObj, U32 Index, GUI_COLOR Color);
void 							BUTTON_EnableNewStyle		(BUTTON_Handle hObj);
void 							BUTTON_DisableNewStyle	(BUTTON_Handle hObj);
void 							BUTTON_SetPressNewStyle	(BUTTON_Handle hObj, GUI_FullRectStyle *pStyle);
void 							BUTTON_SetRelNewStyle		(BUTTON_Handle hObj, GUI_FullRectStyle *pStyle);
/************************************************************
*
*       States
*/
#define BUTTON_STATE_HASFOCUS 0

#endif   /* BUTTON_H */

#if defined(__cplusplus)
  }
#endif

#endif   /* BUTTON_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
