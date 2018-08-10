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
File        : GUI_DrawHLine.C
Purpose     : Implementation of GUI_DrawHLine
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
#define RETURN_IF_Y_OUT() \
	if (y0 < GUI_Context.ClipRect.y0) return;             \
	if (y0 > GUI_Context.ClipRect.y1) return;

#define CLIP_X() \
	if (x0 < GUI_Context.ClipRect.x0) { x0 = GUI_Context.ClipRect.x0; } \
	if (x1 > GUI_Context.ClipRect.x1) { x1 = GUI_Context.ClipRect.x1; }

#define _ADDORG_X()\
	x0 += GUI_Context.xOff;\
	x1 += GUI_Context.xOff;

#define _ADDORG_Y()\
	y0 += GUI_Context.yOff;

/*********************************************************************
*
*       GUI_DrawHLine
*/
void GUI_DrawHLine(I32 y0, I32 x0, I32 x1)
{
#if GUI_WINSUPPORT
	_ADDORG_X();
	_ADDORG_Y();
	RETURN_IF_Y_OUT();
	CLIP_X();
	if(x0 > x1){
		return;
	}
	LCD_HL_DrawHLine(x0, y0, x1);
#endif
}
/*************************** End of file ****************************/
