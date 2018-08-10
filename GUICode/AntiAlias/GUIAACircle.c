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
File        : GUICirleAA.C
Purpose     : Draw Circle routines with Antialiasing

TBD: Circle needs to be calculated from top to bottom in order
to avoid AA problems at certain positions.  
    
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

#include <stdio.h>
//#include <string.h>
#include <math.h>

#if GUI_SUPPORT_AA


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       FillCircle
*/
static void FillCircle(I32 x0, I32 y0, I32 r)
{
	I32 i, x;
	I32 sqmax = r * r + r/2;
	I32 yMin, yMax;
	/* First step : find uppermost and lowermost coordinates */
	yMin = y0 - r;
	yMax = y0 + r;

	/* Use Clipping rect to reduce calculation (if possible) */
	/* if (GUI_Context.pClipRect_HL) {
	if (yMax > GUI_Context.pClipRect_HL->y1)
	yMax = GUI_Context.pClipRect_HL->y1;
	if (yMin < GUI_Context.pClipRect_HL->y0)
	yMin = GUI_Context.pClipRect_HL->y0;
	}*/
	/* Draw top half */
	for (i = 0, x = r; i < r; i++) {
		I32 y = y0 - i;
		if ((y >= yMin) && (y <= yMax)) {
			/* calc proper x-value */
			while ((i * i + x * x) > sqmax){
				--x;
			}
			LCD_HL_DrawHLine (x0 - x, y, x0 + x);
		}
	}
	/* Draw bottom half */
	for (i = 0, x = r; i < r; i++) {
		I32 y = y0 + i;
		if ((y >= yMin) && (y <= yMax)) {
			/* calc proper x-value */
			while ((i * i + x * x) >sqmax){
				--x;
			}
			LCD_HL_DrawHLine (x0 - x, y, x0 + x);
		}
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GL_FillCircleAA_HiRes
*/
void GL_FillCircleAA_HiRes(I32 x0, I32 y0, I32 r)
{
	I32 Factor = 0;

	Factor = GUI_Context.AA_HiResEnable ? 1 : GUI_Context.AA_Factor;
	/* Convert into Hires coordinates (if not already done) */
	x0 *= Factor;
	y0 *= Factor;
	r  *= Factor;
	/* Init AA Subsystem, pass horizontal limits */
	GUI_AA_Init_HiRes(x0 - r, x0 + r);
	/* Do the actual drawing */
	FillCircle(x0, y0, r);
	/* Cleanup */
	GUI_AA_Exit();
}

/*********************************************************************
*
*       GUI_AA_FillCircle
*/
void GUI_AA_FillCircle(I32 x0, I32 y0, I32 r)
{
#if (GUI_WINSUPPORT)
	WM_ADDORG_AA(x0,y0);
#endif
	GL_FillCircleAA_HiRes(x0, y0, r);
}

#else                            /* Avoid problems with empty object modules */
  void GUIAACircle_C(void);
  void GUIAACircle_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
