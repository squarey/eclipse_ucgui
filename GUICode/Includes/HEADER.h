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
File        : HEADER.h
Purpose     : HEADER include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef HEADER_H
#define HEADER_H

#include "GUI.h"
#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT && HEADER_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Public Types
*
**********************************************************************
*/

typedef WM_HMEM HEADER_Handle;

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/

HEADER_Handle HEADER_Create        (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 Flags, I32 SpecialFlags);
HEADER_Handle HEADER_CreateIndirect(const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK * cb);
HEADER_Handle HEADER_CreateAttached(WM_HWIN hParent, I32 Id, I32 SpecialFlags);
HEADER_Handle HEADER_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                    I32 WinFlags, I32 ExFlags, I32 Id);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void HEADER_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

#define HEADER_EnableMemdev(hObj)  WM_EnableMemdev    (hObj)
#define HEADER_DisableMemdev(hObj) WM_DisableMemdev   (hObj)
#define HEADER_Delete(hObj)        WM_DeleteWindow    (hObj)
#define HEADER_Paint(hObj)         WM_Paint           (hObj)
#define HEADER_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/* Set defaults */
GUI_COLOR          HEADER_SetDefaultBkColor  (GUI_COLOR Color);
const GUI_CURSOR GUI_UNI_PTR * HEADER_SetDefaultCursor   (const GUI_CURSOR * pCursor);
const GUI_FONT GUI_UNI_PTR *   HEADER_SetDefaultFont     (const GUI_FONT GUI_UNI_PTR * pFont);
I32                HEADER_SetDefaultBorderH (I32 Spacing);
I32                HEADER_SetDefaultBorderV (I32 Spacing);
GUI_COLOR          HEADER_SetDefaultTextColor(GUI_COLOR Color);

/* Get defaults */
GUI_COLOR          HEADER_GetDefaultBkColor  (void);
const GUI_CURSOR GUI_UNI_PTR * HEADER_GetDefaultCursor   (void);
const GUI_FONT GUI_UNI_PTR *   HEADER_GetDefaultFont     (void);
I32                HEADER_GetDefaultBorderH  (void);
I32                HEADER_GetDefaultBorderV  (void);
GUI_COLOR          HEADER_GetDefaultTextColor(void);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/

void HEADER_AddItem            (HEADER_Handle hObj, I32 Width, const char * s, I32 Align);
void HEADER_DeleteItem         (HEADER_Handle hObj, unsigned Index);
I32  HEADER_GetHeight          (HEADER_Handle hObj);
I32  HEADER_GetItemWidth       (HEADER_Handle hObj, U32 Index);
I32  HEADER_GetNumItems        (HEADER_Handle hObj);
I32  HEADER_GetSel             (HEADER_Handle hObj);
void HEADER_SetBitmap          (HEADER_Handle hObj, U32 Index, const GUI_BITMAP * pBitmap);
void HEADER_SetBitmapEx        (HEADER_Handle hObj, U32 Index, const GUI_BITMAP * pBitmap, I32 x, I32 y);
void HEADER_SetBkColor         (HEADER_Handle hObj, GUI_COLOR Color);
void HEADER_SetBMP             (HEADER_Handle hObj, U32 Index, const void * pBitmap);
void HEADER_SetBMPEx           (HEADER_Handle hObj, U32 Index, const void * pBitmap, I32 x, I32 y);
void HEADER_SetDirIndicator    (HEADER_Handle hObj, I32 Column, I32 Reverse); /* !!!Not to be documented!!! */
void HEADER_SetDragLimit       (HEADER_Handle hObj, unsigned DragLimit);
void HEADER_SetFont            (HEADER_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont);
void HEADER_SetHeight          (HEADER_Handle hObj, I32 Height);
void HEADER_SetTextAlign       (HEADER_Handle hObj, U32 Index, I32 Align);
void HEADER_SetItemText        (HEADER_Handle hObj, U32 Index, const char * s);
void HEADER_SetItemWidth       (HEADER_Handle hObj, U32 Index, I32 Width);
void HEADER_SetScrollPos       (HEADER_Handle hObj, I32 ScrollPos);
void HEADER_SetStreamedBitmap  (HEADER_Handle hObj, U32 Index, const GUI_BITMAP_STREAM * pBitmap);
void HEADER_SetStreamedBitmapEx(HEADER_Handle hObj, U32 Index, const GUI_BITMAP_STREAM * pBitmap, I32 x, I32 y);
void HEADER_SetTextColor       (HEADER_Handle hObj, GUI_COLOR Color);

/*********************************************************************
*
*       Macros for compatibility with older versions
*
**********************************************************************
*/

#ifdef HEADER_SPACING_H
  #define HEADER_BORDER_H_DEFAULT HEADER_SPACING_H
#endif
#ifdef HEADER_SPACING_V
  #define HEADER_BORDER_V_DEFAULT HEADER_SPACING_V
#endif
#define HEADER_SetDefaultSpacingH(Value) HEADER_SetDefaultBorderH(Value)
#define HEADER_SetDefaultSpacingV(Value) HEADER_SetDefaultBorderV(Value)
#define HEADER_GetDefaultSpacingH()      HEADER_GetDefaultBorderH()
#define HEADER_GetDefaultSpacingV()      HEADER_GetDefaultBorderV()

#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* HEADER_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
