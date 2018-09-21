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
File        : CHECKBOX.h
Purpose     : CHECKBOX include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT && CHECKBOX_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Color indices
*/
#define CHECKBOX_CI_DISABLED 0
#define CHECKBOX_CI_ENABLED  1

/*********************************************************************
*
*       Bitmap indices
*/
#define CHECKBOX_BI_INACTIV_UNCHECKED 0
#define CHECKBOX_BI_ACTIV_UNCHECKED   1
#define CHECKBOX_BI_INACTIV_CHECKED   2
#define CHECKBOX_BI_ACTIV_CHECKED     3
#define CHECKBOX_BI_INACTIV_3STATE    4
#define CHECKBOX_BI_ACTIV_3STATE      5

/*********************************************************************
*
*       Public Types
*
**********************************************************************

*/
typedef WM_HMEM CHECKBOX_Handle;

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/

CHECKBOX_Handle CHECKBOX_Create        (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags);
CHECKBOX_Handle CHECKBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
CHECKBOX_Handle CHECKBOX_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                        I32 WinFlags, I32 ExFlags, I32 Id);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void CHECKBOX_Callback(WM_MESSAGE *pMsg);

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

I32                          CHECKBOX_GetDefaultAlign     (void);
GUI_COLOR                    CHECKBOX_GetDefaultBkColor   (void);
const GUI_FONT GUI_UNI_PTR * CHECKBOX_GetDefaultFont      (void);
I32                          CHECKBOX_GetDefaultSpacing   (void);
I32                          CHECKBOX_GetDefaultTextAlign (void);
GUI_COLOR                    CHECKBOX_GetDefaultTextColor (void);
void                         CHECKBOX_SetDefaultAlign     (I32 Align);
void                         CHECKBOX_SetDefaultBkColor   (GUI_COLOR Color);
GUI_COLOR                    CHECKBOX_SetDefaultFocusColor(GUI_COLOR Color);
void                         CHECKBOX_SetDefaultFont      (const GUI_FONT GUI_UNI_PTR * pFont);
void                         CHECKBOX_SetDefaultImage     (const GUI_BITMAP * pBitmap, U32 Index);
void                         CHECKBOX_SetDefaultSpacing   (I32 Spacing);
void                         CHECKBOX_SetDefaultTextAlign (I32 Align);
void                         CHECKBOX_SetDefaultTextColor (GUI_COLOR Color);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/

I32       CHECKBOX_GetState     (CHECKBOX_Handle hObj);
I32       CHECKBOX_GetText      (CHECKBOX_Handle hObj, char * pBuffer, I32 MaxLen);
I32       CHECKBOX_IsChecked    (CHECKBOX_Handle hObj);
void      CHECKBOX_SetBkColor   (CHECKBOX_Handle hObj, GUI_COLOR Color);
GUI_COLOR CHECKBOX_SetBoxBkColor(CHECKBOX_Handle hObj, GUI_COLOR Color, I32 Index);
GUI_COLOR CHECKBOX_SetFocusColor(CHECKBOX_Handle hObj, GUI_COLOR Color);
void      CHECKBOX_SetFont      (CHECKBOX_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont);
void      CHECKBOX_SetImage     (CHECKBOX_Handle hObj, const GUI_BITMAP * pBitmap, U32 Index);
void      CHECKBOX_SetNumStates (CHECKBOX_Handle hObj, unsigned NumStates);
void      CHECKBOX_SetSpacing   (CHECKBOX_Handle hObj, unsigned Spacing);
void      CHECKBOX_SetState     (CHECKBOX_Handle hObj, unsigned State);
void      CHECKBOX_SetText      (CHECKBOX_Handle hObj, const char * pText);
void      CHECKBOX_SetTextAlign (CHECKBOX_Handle hObj, I32 Align);
void      CHECKBOX_SetTextColor (CHECKBOX_Handle hObj, GUI_COLOR Color);
void 	  CHECKBOX_SetNoDrawDownRect(CHECKBOX_Handle hCheckbox, U8 IsDraw);

void CHECKBOX_SetStyleCircleRadius(CHECKBOX_Handle hObj, I16 RadiusExt, I16 RadiusIn);
void CHECKBOX_SetStyleCircleColor(CHECKBOX_Handle hObj, GUI_COLOR ColorExt, GUI_COLOR ColorIn);
void CHECKBOX_EnableStyleCircle(CHECKBOX_Handle hObj);
void CHECKBOX_DisableStyleCircle(CHECKBOX_Handle hObj);

/*********************************************************************
*
*       Macros for compatibility
*
**********************************************************************
*/

#define CHECKBOX_Check(hObj)   CHECKBOX_SetState(hObj, 1)
#define CHECKBOX_Uncheck(hObj) CHECKBOX_SetState(hObj, 0)

#define CHECKBOX_BI_INACTIV    CHECKBOX_BI_INACTIV_CHECKED
#define CHECKBOX_BI_ACTIV      CHECKBOX_BI_ACTIV_CHECKED

#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* CHECKBOX_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
