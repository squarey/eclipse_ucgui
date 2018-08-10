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
File        : BUTTON_Private.h
Purpose     : BUTTON private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef BUTTON_PRIVATE_H
#define BUTTON_PRIVATE_H

#include "WM.h"
#include "BUTTON.h"
#include "GUI_StyleDraw.h"

#if GUI_WINSUPPORT && BUTTON_SUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef GUI_FullRectStyle BUTTON_STYLE;

typedef struct {
	GUI_COLOR aBkColor[3];
	GUI_COLOR aTextColor[3];
	GUI_COLOR FocusColor;
	const GUI_FONT GUI_UNI_PTR * pFont;
	I16 Align;
} BUTTON_PROPS;

typedef struct {
	WIDGET Widget;
	BUTTON_PROPS Props;
	BUTTON_STYLE Style[2];
	WM_HMEM hpText;
	U8	NewStyle;
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
	I32 DebugId;
#endif
} BUTTON_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  BUTTON_Obj * BUTTON_h2p(BUTTON_Handle h);
  #define BUTTON_H2P(h) BUTTON_h2p(h)
  #define BUTTON_INIT_ID(p) p->DebugId = BUTTON_ID
#else
  #define BUTTON_H2P(h) (BUTTON_Obj *)GUI_ALLOC_h2p(h)
  #define BUTTON_INIT_ID(p)
#endif

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern BUTTON_PROPS BUTTON__DefaultProps;
extern BUTTON_STYLE BUTTON_DefaultPressStyle;
extern BUTTON_STYLE BUTTON_DefaultRelStyle;



/*********************************************************************
*
*       Private functions
*
**********************************************************************
*/
void BUTTON__SetDrawObj(BUTTON_Handle hObj, I32 Index, GUI_DRAW_HANDLE hDrawObj);


#endif   /* GUI_WINSUPPORT */
#endif   /* BUTTON_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
