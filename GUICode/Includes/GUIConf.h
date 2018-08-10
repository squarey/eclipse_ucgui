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
File        : GUIConf.h
Purpose     : Configures abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

#include "stdio.h"

#define LCD_BITSPERPIXEL  		(24)

#define LCD_XSIZE         		(1024)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE         		(600)   /* Y-resolution of LCD, Logical coor. */

#define LCD_GET_PIXEL_SUPPORT		1

#define LCD_SWAP_XY    			(0)
#define LCD_SWAP_RB    			(1)		/* 1: RGB  0:BGR */

#define GUI_SUPPORT_TOUCH         (1)  /* Support a touch screen (req. win-manager) */
#define GUI_SUPPORT_UNICODE       (1)  /* Support mixed ASCII/UNICODE strings */

#define GUI_DEFAULT_FONT          &GUI_FontASSIC_YH32
#define GUI_ALLOC_SIZE            854 * 480 * 1  /* Size of dynamic memory ... For WM and memory devices*/

#define GUI_LOG_OUT				printf


/*********************************************************************
*
*         Configuration of available packages
*/

#define GUI_WINSUPPORT            1  /* Window manager package available */
#define GUI_SUPPORT_MEMDEV        1  /* Memory devices available */
#define GUI_SUPPORT_AA            1  /* Anti aliasing available */

#define IMAGEBUTTON_SUPPORT			1
#define IMAGEVIEW_SUPPORT			1
#define LISTVIEW_SUPPORT			1
#define PICKER_SUPPORT				1
#define PICTURENUMBER_SUPPORT		0
#define TIMERPICKER_SUPPORT			1
#define BUTTON_SUPPORT				1
#define CHECKBOX_SUPPORT			1
#define DROPDOWN_SUPPORT			0
#define EDIT_SUPPORT				1
#define FRAMEWIN_SUPPORT			0
#define HEADER_SUPPORT				0
#define LISTBOX_SUPPORT				0
#define MENU_SUPPORT				0
#define MESSAGEBOX_SUPPORT			0
#define MULTIEDIT_SUPPORT			0
#define MULTIPAGE_SUPPORT			0
#define PROGBAR_SUPPORT				0
#define RADIO_SUPPORT				0
#define SCROLLBAR_SUPPORT			0
#define GRAPH_SUPPORT				0
#define SLIDER_SUPPORT				0
#define TEXT_SUPPORT				1

#endif  /* Avoid multiple inclusion */



