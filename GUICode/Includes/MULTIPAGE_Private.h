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
File        : ucMULTIPAGE_Private.h
Purpose     : Private MULTIPAGE include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef UC_MULTIPAGE_PRIVATE_H
#define UC_MULTIPAGE_PRIVATE_H

#include "GUIDebug.h"
#include "GUI_ARRAY.h"
#include "MULTIPAGE.h"

#if GUI_WINSUPPORT && MULTIPAGE_SUPPORT

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define MULTIPAGE_STATE_ENABLED     (1<<0)
#define MULTIPAGE_STATE_SCROLLMODE  WIDGET_STATE_USER0

/* Define colors */
#define MULTIPAGE_NUMCOLORS 2

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WM_HWIN hWin;
  U8      Status;
  char    acText;
} MULTIPAGE_PAGE;

typedef struct {
  WIDGET          Widget;
  WM_HWIN         hClient;
  GUI_ARRAY       Handles;
  unsigned        Selection;
  I32             ScrollState;
  unsigned        Align;
  const GUI_FONT GUI_UNI_PTR * Font;
  GUI_COLOR       aBkColor[MULTIPAGE_NUMCOLORS];
  GUI_COLOR       aTextColor[MULTIPAGE_NUMCOLORS];
  #if GUI_DEBUG_LEVEL >1
    I32 DebugId;
  #endif  
} MULTIPAGE_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  MULTIPAGE_Obj * MULTIPAGE_h2p(MULTIPAGE_Handle h);
  #define MULTIPAGE_H2P(h) MULTIPAGE_h2p(h)
  #define MULTIPAGE_INIT_ID(p) p->DebugId = MULTIPAGE_ID
#else
  #define MULTIPAGE_H2P(h) (MULTIPAGE_Obj *)GUI_ALLOC_h2p(h)
  #define MULTIPAGE_INIT_ID(p)
#endif

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

extern const GUI_FONT GUI_UNI_PTR * MULTIPAGE__pDefaultFont;
extern unsigned                     MULTIPAGE__DefaultAlign;
extern GUI_COLOR                    MULTIPAGE__DefaultBkColor[2];
extern GUI_COLOR                    MULTIPAGE__DefaultTextColor[2];

#endif /* GUI_WINSUPPORT */

#endif /* MULTIPAGE_PRIVATE_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
