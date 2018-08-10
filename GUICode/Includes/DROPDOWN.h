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
File        : DROPDOWN.h
Purpose     : Multiple choice object include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef DROPDOWN_H
#define DROPDOWN_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT && DROPDOWN_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM DROPDOWN_Handle;

/************************************************************
*
*       Create flags
*/
#define DROPDOWN_CF_AUTOSCROLLBAR   (1 << 0)
#define DROPDOWN_CF_UP              (1 << 1)

/*********************************************************************
*
*       Color indices
*/
#define DROPDOWN_CI_UNSEL    0
#define DROPDOWN_CI_SEL      1
#define DROPDOWN_CI_SELFOCUS 2

#define DROPDOWN_CI_ARROW    0
#define DROPDOWN_CI_BUTTON   1

/*********************************************************************
*
*                 Standard member functions
*
**********************************************************************
*/

#define DROPDOWN_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define DROPDOWN_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define DROPDOWN_Delete(hObj)        WM_DeleteWindow(hObj)
#define DROPDOWN_Paint(hObj)         WM_Paint(hObj)
#define DROPDOWN_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

DROPDOWN_Handle DROPDOWN_Create        (WM_HWIN hWinParent, I32 x0, I32 y0, I32 xsize, I32 ysize, I32 Flags);
DROPDOWN_Handle DROPDOWN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
DROPDOWN_Handle DROPDOWN_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                        I32 WinFlags, I32 ExFlags, I32 Id);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void DROPDOWN_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

void     DROPDOWN_AddKey          (DROPDOWN_Handle hObj, I32 Key);
void     DROPDOWN_AddString       (DROPDOWN_Handle hObj, const char* s);
void     DROPDOWN_Collapse        (DROPDOWN_Handle hObj);
void     DROPDOWN_DecSel          (DROPDOWN_Handle hObj);
void     DROPDOWN_DeleteItem      (DROPDOWN_Handle hObj, U32 Index);
void     DROPDOWN_Expand          (DROPDOWN_Handle hObj);
unsigned DROPDOWN_GetItemSpacing  (DROPDOWN_Handle hObj);
I32      DROPDOWN_GetNumItems     (DROPDOWN_Handle hObj);
I32      DROPDOWN_GetSel          (DROPDOWN_Handle hObj);
void     DROPDOWN_IncSel          (DROPDOWN_Handle hObj);
void     DROPDOWN_InsertString    (DROPDOWN_Handle hObj, const char* s, U32 Index);
void     DROPDOWN_SetAutoScroll   (DROPDOWN_Handle hObj, I32 OnOff);
void     DROPDOWN_SetBkColor      (DROPDOWN_Handle hObj, U32 Index, GUI_COLOR color);
void     DROPDOWN_SetColor        (DROPDOWN_Handle hObj, U32 Index, GUI_COLOR Color);
void     DROPDOWN_SetFont         (DROPDOWN_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont);
void     DROPDOWN_SetItemSpacing  (DROPDOWN_Handle hObj, unsigned Value);
void     DROPDOWN_SetSel          (DROPDOWN_Handle hObj, I32 Sel);
void     DROPDOWN_SetScrollbarColor(DROPDOWN_Handle hObj, unsigned Index, GUI_COLOR Color);
void     DROPDOWN_SetScrollbarWidth(DROPDOWN_Handle hObj, unsigned Width);
void     DROPDOWN_SetTextAlign    (DROPDOWN_Handle hObj, I32 Align);
void     DROPDOWN_SetTextColor    (DROPDOWN_Handle hObj, U32 index, GUI_COLOR color);
void     DROPDOWN_SetTextHeight   (DROPDOWN_Handle hObj, unsigned TextHeight);


/*********************************************************************
*
*                 Global functions
*
**********************************************************************
*/
const GUI_FONT GUI_UNI_PTR * DROPDOWN_GetDefaultFont          (void);
void                         DROPDOWN_SetDefaultFont          (const GUI_FONT GUI_UNI_PTR * pFont);
GUI_COLOR                    DROPDOWN_SetDefaultColor         (I32 Index, GUI_COLOR Color);
GUI_COLOR                    DROPDOWN_SetDefaultScrollbarColor(I32 Index, GUI_COLOR Color);

#if defined(__cplusplus)
  }
#endif

#endif   /* GUI_WINSUPPORT */
#endif   /* DROPDOWN_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
