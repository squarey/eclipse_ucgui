/*
 * TOTAST_Private.h
 *
 *  Created on: 2018年6月19日
 *      Author: Administrator
 */

#ifndef TOTAST_PRIVATE_H_
#define TOTAST_PRIVATE_H_

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"      /* Req. for Create indirect data structure */
#include "GUIDebug.h" /* Req. for GUI_DEBUG_LEVEL */

typedef struct
{
	const GUI_FONT GUI_UNI_PTR * pFont;
	GUI_COLOR TextColor;
	GUI_COLOR BkColor;
} TOTAST_PROPS;

typedef struct
{
	WIDGET Widget;
	TOTAST_PROPS Props;
	WM_HMEM hpText;
	GUI_TIMER_HANDLE hTimer;
} TOTAST_Obj;

#endif /* TOTAST_PRIVATE_H_ */
