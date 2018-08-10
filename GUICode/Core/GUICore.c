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
File        : GUICore.C
Purpose     : Core routines
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */

#define  GL_CORE_C

#include "GUI_Private.h"
#include "GUIDebug.h"

#if GUI_WINSUPPORT
  #include "WM_GUI.h"
  #include "WM.h"
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#if GUI_SUPPORT_AA
static const tLCD_HL_APIList _HL_APIList =
{
	LCD_DrawHLine,
	LCD_DrawPixel
};
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
#define CLIP_X() \
  if (x0 < GUI_Context.ClipRect.x0) { x0 = GUI_Context.ClipRect.x0; } \
  if (x1 > GUI_Context.ClipRect.x1) { x1 = GUI_Context.ClipRect.x1; }


#define CLIP_Y() \
  if (y0 < GUI_Context.ClipRect.y0) { y0 = GUI_Context.ClipRect.y0; } \
  if (y1 > GUI_Context.ClipRect.y1) { y1 = GUI_Context.ClipRect.y1; }

U8 LOG_OPEN = 0;
/*********************************************************************
*
*       _InitContext
*
* Purpose
*   Initializes the given context.
*
* Special considerations
*   Make sure that no GUI functions are called, because locking is
*   not allowed here (GUITASK_INIT not yet called).
*/
static void _InitContext(GUI_CONTEXT* pContext)
{
	/* GUI_memset(..,0,..) is not required, as this function is called only at startup of the GUI when data is 0 */
#if GUI_SUPPORT_DEVICES
	pContext->pDeviceAPI   = LCD_aAPI[0]; /* &LCD_L0_APIList; */
#endif
	pContext->pClipRect_HL = &GUI_Context.ClipRect;
	LCD_L0_GetRect(&pContext->ClipRect);
#if GUI_SUPPORT_AA
	pContext->pLCD_HL      = &_HL_APIList;
#endif
	pContext->pAFont       = GUI_DEFAULT_FONT;
	pContext->pClipRect_HL = &GUI_Context.ClipRect;
	pContext->PenSize      = 1;
	/* Variables in WM module */
#if GUI_WINSUPPORT
	pContext->hAWin    = WM_GetDesktopWindow();
#endif
	/* Variables in GUI_AA module */
#if GUI_SUPPORT_AA
	pContext->AA_Factor = 3;
#endif
	pContext->Color   = GUI_INVALID_COLOR;
	pContext->BkColor = GUI_INVALID_COLOR;
	LCD_SetBkColor(GUI_DEFAULT_BKCOLOR);
	LCD_SetColor(GUI_DEFAULT_COLOR);
#if GUI_SUPPORT_UNICODE
	pContext->pUC_API = &GUI_UC_None;
#endif
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ClearRect
*/
void GUI_ClearRect(I32 x0, I32 y0, I32 x1, I32 y1)
{
	GUI_DRAWMODE PrevDraw;
#if GUI_WINSUPPORT
	WM_ADDORG(x0, y0);
	WM_ADDORG(x1, y1);
	CLIP_X();
	CLIP_Y();
#endif
	PrevDraw = LCD_SetDrawMode(GUI_DRAWMODE_REV);
	LCD_FillRect(x0,y0,x1,y1);
	LCD_SetDrawMode(PrevDraw);
}

/*********************************************************************
*
*       GUI_Clear
*/
void GUI_Clear(void)
{
	GUI_GotoXY(0,0);     /* Reset text cursor to upper left */
	GUI_ClearRect(GUI_XMIN, GUI_YMIN, GUI_XMAX, GUI_YMAX);
}

/*********************************************************************
*
*       GUI_Init
*
* Purpose:
*   Init of GUI internal data structures & variables
*/
void GUI_EnableLogOut(void)
{
	LOG_OPEN = 1;
}
void GUI_DisableLogOut(void)
{
	LOG_OPEN = 0;
}
I32 GUI_Init(void)
{
	I32 r;
	GUI_DEBUG_LOG("\nGUI_Init()");
	/* Init system wide globals first */
	GUI_DecChar = '.';
	/* Init context */
	WM_pfHandlePID = WM_HandlePID;
	_InitContext(&GUI_Context);
	r = LCD_Init();
#if GUI_WINSUPPORT
	WM_Init();
#endif
	WM_InitScreenTimeout();
#if defined(GUI_TRIAL_VERSION)
	#if GUI_TRIAL_VERSION
	GUI_DispString(  "This software\n"
	                 "contains an eval-\n"
	                 "uC/GUI build.\n"
	                 "\n"
	                 "A license is\n"
	                 "required to use\n"
	                 "it in a product.\n\n"
	                 "www.segger.com\n");
	GUI_GotoXY(0, 0);
    GUI_X_Delay(1000);
    GUI_Clear();
    #endif
#endif
  return r;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
