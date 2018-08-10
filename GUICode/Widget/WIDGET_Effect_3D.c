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
File        : WIDGET_Effect_3D.c
Purpose     : Effect routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
//#include <string.h>

#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define WIDGET_H2P(hWin)        ((WIDGET*)GUI_ALLOC_h2p(hWin))

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
static GUI_BorderStyle _UpStyle =
{
	4,					//.Radius
	2,					//.Width
	GUI_BORDER_FULL,	//.Part
	0xffd0d0d0,			//.Color
};
static GUI_BorderStyle _DownStyle =
{
	4,					//.Radius
	2,					//.Width
	GUI_BORDER_FULL,	//.Part
	0xfffbd846,			//.Color
};
/*********************************************************************
*
*       _WIDGET_EFFECT_3D_DrawUpRect
*
* Add. info:
*   This routine does not preserve the drawing colors for speed
*   reasons. If this is required, it should be done in the calling
*   routine.
*/
static void _WIDGET_EFFECT_3D_DrawUpRect(const GUI_RECT* pRect) {

	GUI_RECT r;
	/* Saving of context no longer required ... Speeds up the system
	GUI_CONTEXT Context;
	GUI_SaveContext(&Context);
	*/

	r = *pRect;
#if 0
	LCD_SetColor(0xff000000);
	GUI_DrawRect(r.x0, r.y0, r.x1, r.y1);          /* Draw rectangle around it */
	/* Draw the bright sides */
	LCD_SetColor(0xffffffff);
	GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 2);    /* Draw top line */
	GUI_DrawVLine(r.x0 + 1, r.y0 + 1, r.y1 - 2);
	/* Draw the dark sides */
	LCD_SetColor(0xff555555);
	GUI_DrawHLine(r.y1-1, r.x0 + 1, r.x1 - 1);
	GUI_DrawVLine(r.x1-1, r.y0 + 1, r.y1 - 2);
	/*  GUI_RestoreContext(&Context); */
#else
	GUI_DrawRectBorderStraight(&r, &_UpStyle);
	GUI_DrawRectBorderCorner(&r, &_UpStyle);
#endif
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D_DrawDownRect
*/
static void _WIDGET_EFFECT_3D_DrawDownRect(const GUI_RECT* pRect)
{
	GUI_RECT r;
	r = *pRect;
#if 0
	LCD_SetColor(0xff000000);  /* TBD: Use halftone */
	/*  GUI_DrawRect(0, 0, r.x1, r.y1);*/
	/* Draw the upper left sides */
	LCD_SetColor(0xff808080);
	GUI_DrawHLine(r.y0, r.x0, r.x1);
	GUI_DrawVLine(r.x0, r.y0 + 1, r.y1);
	LCD_SetColor(0xff000000);
	GUI_DrawHLine(r.y0 + 1, r.x0 + 1, r.x1 - 1);
	GUI_DrawVLine(r.x0 + 1, r.y0 + 2, r.y1 - 1);
	/* Draw the lower right sides */
	LCD_SetColor(0xffffffff);
	GUI_DrawHLine(r.y1, r.x0 + 1, r.x1);
	GUI_DrawVLine(r.x1, r.y0 + 1, r.y1);
	LCD_SetColor(0xffc0c0c0);
	GUI_DrawHLine(r.y1 - 1, r. x0 + 2, r.x1-1);
	GUI_DrawVLine(r.x1 - 1, r. y0 + 2, r.y1-1);
#else
	GUI_DrawRectBorderStraight(&r, &_DownStyle);
	GUI_DrawRectBorderCorner(&r, &_DownStyle);
#endif
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D_DrawDown
*/
static void _WIDGET_EFFECT_3D_DrawDown(void)
{
	GUI_RECT r;
	WM_GetClientRect(&r);
	_WIDGET_EFFECT_3D_DrawDownRect(&r);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D_GetRect
*/
static void _WIDGET_EFFECT_3D_GetRect(GUI_RECT* pRect)
{
	WM_GetClientRect(pRect);
	GUI__ReduceRect(pRect, pRect, 2);
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET_EFFECT_3D_DrawUp
*/
void WIDGET_EFFECT_3D_DrawUp(void)
{
	GUI_RECT r;
	WM_GetClientRect(&r);
	_WIDGET_EFFECT_3D_DrawUpRect(&r);
}

/*********************************************************************
*
*       WIDGET_SetDefaultEffect_3D
*/
void WIDGET_SetDefaultEffect_3D(void)
{
	WIDGET_SetDefaultEffect(&WIDGET_Effect_3D);
}

/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/

const WIDGET_EFFECT WIDGET_Effect_3D =
{
	WIDGET_EFFECT_3D_DrawUp,			//.pfDrawUp
	_WIDGET_EFFECT_3D_DrawDown,			//.pfDrawDown
	_WIDGET_EFFECT_3D_DrawUpRect,		//.pfDrawUpRect
	_WIDGET_EFFECT_3D_DrawDownRect,		//.pfDrawDownRect
	_WIDGET_EFFECT_3D_GetRect,			//.pfGetRect
	2									//.EffectSize
};
#else                            /* Avoid problems with empty object modules */
  void WIDGET_Effect_3D_C(void) {}
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
