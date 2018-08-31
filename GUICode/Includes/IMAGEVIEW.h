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
File        : IMAGEVIEW.h
Purpose     : IMAGEVIEW include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"      /* Req. for Create indirect data structure */


#define VISIABLE		1
#define INVISIABLE		0


#if GUI_WINSUPPORT  && IMAGEVIEW_SUPPORT

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
#define IMAGEVIEW_STATE_PRESSED    WIDGET_STATE_USER0

/************************************************************
*
*       Create / Status flags
*/
#define IMAGEVIEW_CF_VERTICAL WIDGET_CF_VERTICAL

/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef WM_HMEM IMAGEVIEW_Handle;

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

IMAGEVIEW_Handle IMAGEVIEW_Create        (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags);
IMAGEVIEW_Handle IMAGEVIEW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
IMAGEVIEW_Handle IMAGEVIEW_CreateEx      (I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                    I32 WinFlags, I32 ExFlags, I32 Id);

void IMAGEVIEW_SetFile						(IMAGEVIEW_Handle hObj, const char *pFile, U8 Flag);
void IMAGEVIEW_SetBkColor					(IMAGEVIEW_Handle hObj,GUI_COLOR color);
void IMAGEVIEW_SetChangeColor				(IMAGEVIEW_Handle hObj, GUI_COLOR Color);
void IMAGEVIEW_SetRotateAngle				(IMAGEVIEW_Handle hObj, I16 Angle);
void IMAGEVIEW_SetAlpha						(IMAGEVIEW_Handle hObj, U8 Alpha);
void IMAGEVIEW_SetMapping					(IMAGEVIEW_Handle hObj, IMAGEVIEW_Handle hMap);
void IMAGEVIEW_SetBitmap					(IMAGEVIEW_Handle hObj, const GUI_BITMAP *pBitmap);
void IMAGEVIEW_SetBitmapHasTrans			(IMAGEVIEW_Handle hObj, GUI_COLOR TransColor);
void IMAGEVIEW_ClearBitmapHasTrans			(IMAGEVIEW_Handle hObj);

#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* IMAGEVIEW_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
