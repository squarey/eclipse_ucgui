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
	WM_HWIN hCurShowWin;
	WM_HWIN hNextShowWin;
	WM_HWIN hDestShowWin;
	WM_HMEM	hAnim;
	I32 LastTouchXPos;
	U8 FirstTouch;
	U8 IsMove;
	U8 UseAnim;
	U8 FlagSwitchPage;
	WinListShowChange fWinShowChange;
//	WindowListProps Props;
	GUI_ARRAY WinArray;
} WindowList_Obj;

#endif /* _WINDOWLIST_PRIVATE_H_ */
