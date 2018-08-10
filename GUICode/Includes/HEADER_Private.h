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
File        : HEADER_Private.h
Purpose     : Private HEADER include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef HEADER_PRIVATE_H
#define HEADER_PRIVATE_H


#include "WIDGET.h"
#include "HEADER.h"
#include "WM.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT && HEADER_SUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  I32 Width;
  I16 Align;
  WM_HMEM hDrawObj;
  char acText[1];
} HEADER_COLUMN;

typedef struct {
  WIDGET Widget;
  GUI_COLOR BkColor;
  GUI_COLOR TextColor;
  GUI_ARRAY Columns;
  I32 CapturePosX;
  I32 CaptureItem;
  I32 ScrollPos;
  I32 Sel;
  I32 DirIndicatorColumn;
  I32 DirIndicatorReverse;
  const GUI_FONT GUI_UNI_PTR * pFont;
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    I32 DebugId;
  #endif
  U8 DragLimit;
} HEADER_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  HEADER_Obj * HEADER_h2p(HEADER_Handle h);
  #define HEADER_H2P(h) HEADER_h2p(h)
  #define HEADER_INIT_ID(p) p->DebugId = HEADER_ID
#else
  #define HEADER_H2P(h) (HEADER_Obj *)GUI_ALLOC_h2p(h)
  #define HEADER_INIT_ID(p)
#endif

void HEADER__SetDrawObj(HEADER_Handle hObj, unsigned Index, GUI_DRAW_HANDLE hDrawObj);


#endif /* GUI_WINSUPPORT */
#endif /* Avoid multiple inclusion */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
