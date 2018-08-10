/*
*********************************************************************************************************
*                                                uC/GUI
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
File        : GUIArcAA.C
Purpose     : Draw Arc routines with Antialiasing
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <math.h>

#include "GUI_Protected.h"

#if GUI_SUPPORT_AA

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawArcAA
*/
static void _DrawArcAA(I32 x0, I32 y0, I32 rx, I32 ry, I32 a0, I32 a1)
{
	I32 PenSizePrev = GUI_GetPenSize();
	I32 PenSize_AA;
	I32 Factor;

	Factor = GUI_Context.AA_HiResEnable ? 1 : GUI_Context.AA_Factor;
	/* Convert into Hires coordinates (if not already done) */
	x0 *= Factor;
	y0 *= Factor;
	rx *= Factor;
	ry *= Factor;
	PenSize_AA = PenSizePrev * GUI_Context.AA_Factor;
	GUI_AA_Init_HiRes(x0 - rx - PenSize_AA, x0 + rx + PenSize_AA);
	GUI_SetPenSize(PenSize_AA);
	GL_DrawArc(x0, y0, rx, ry,a0,a1);
	GUI_SetPenSize(PenSizePrev);          /* restore former pen size */
	/* Cleanup */
	GUI_AA_Exit();
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_AA_DrawArc
*/
void GUI_AA_DrawArc(I32 x0, I32 y0, I32 rx, I32 ry, I32 a0, I32 a1)
{
#if (GUI_WINSUPPORT)
	WM_ADDORG_AA(x0,y0);
#endif
	_DrawArcAA( x0, y0, rx, ry, a0, a1);
}

#else                            /* Avoid problems with empty object modules */
  void GUIAAArc_C(void);
  void GUIAAArc_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
