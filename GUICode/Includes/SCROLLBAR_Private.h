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
File        : SCROLLBAR_Private.h
Purpose     : SCROLLBAR internal header file
---------------------------END-OF-HEADER------------------------------
*/

#ifndef UC_SCROLLBAR_PRIVATE_H
#define UC_SCROLLBAR_PRIVATE_H

#include "SCROLLBAR.h"
#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI_StyleDraw.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Module internal data
*
**********************************************************************
*/
extern GUI_COLOR  SCROLLBAR__aDefaultBkColor[2];
extern GUI_COLOR  SCROLLBAR__aDefaultColor[2];
extern I16        SCROLLBAR__DefaultWidth;

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct
{
	GUI_COLOR aColor[3];
} SCROLLBAR_PROPS;

typedef struct
{
	WIDGET Widget;
	GUI_FullRectStyle RectStyle;
	I32 ActualLength;
	I32 Offest;
	U8 Align;
#if GUI_DEBUG_LEVEL >1
	I32 DebugId;
#endif
} SCROLLBAR_Obj;


/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  SCROLLBAR_Obj * SCROLLBAR_h2p(SCROLLBAR_Handle h);
  #define SCROLLBAR_H2P(h) SCROLLBAR_h2p(h)
  #define SCROLLBAR_INIT_ID(p) p->DebugId = SCROLLBAR_ID
#else
  #define SCROLLBAR_H2P(h) (SCROLLBAR_Obj *)GUI_ALLOC_h2p(h)
  #define SCROLLBAR_INIT_ID(p)
#endif

void SCROLLBAR__InvalidatePartner(SCROLLBAR_Handle hObj);

extern SCROLLBAR_PROPS SCROLLBAR__DefaultProps;

#endif        /* GUI_WINSUPPORT */
#endif        /* Avoid multiple inclusion */


	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
