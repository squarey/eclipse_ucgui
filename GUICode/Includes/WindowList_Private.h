/*
 * WindowList_Private.h
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */

#ifndef _WINDOWLIST_PRIVATE_H_
#define _WINDOWLIST_PRIVATE_H_

#include "WM.h"
#include "GUI_ARRAY.h"
#include "WindowList.h"

typedef void (*WinListShowChange)(WM_HWIN CurShowWin, const char *pWinName);

typedef struct _WindowListProps
{
	WM_HWIN		hWin;
//	struct _WindowListProps hNextWin;
	char WinName[1];
} WindowListItem;

typedef struct {
	WIDGET Widget;
	WM_HMEM hCurShowWin;
	WM_HMEM hNextShowWin;
	WM_HMEM hLastShowWin;
	I32 LastTouchXPos;
	U8 FirstTouch;
	U8 IsMove;
	WinListShowChange fWinShowChange;
//	WindowListProps Props;
	GUI_ARRAY WinArray;
} WindowList_Obj;

#endif /* _WINDOWLIST_PRIVATE_H_ */
