/*
 * WindowList.h
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */

#ifndef _WINDOWLIST_H_
#define _WINDOWLIST_H_

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"




WM_HWIN WindowList_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags);
WM_HWIN WindowList_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
void WindowList_AddWin(WM_HWIN hWinList, WM_HWIN hAddWin, const char *pWinName);
void WindowList_RemoveWinByName(WM_HWIN hWinList, const char *pWinName);
void WindowList_RemoveWin(WM_HWIN hWinList, WM_HWIN hRemoveWin);
void WindowList_SetShowByNameWin(WM_HWIN hWinList, const char *pShowWinName, U8 UseAnim);
void WindowList_SetShowWin(WM_HWIN hWinList, WM_HWIN hShowWin);
void WindowList_ShowNextWin(WM_HWIN hWinList, U8 UseAnim);
void WindowList_ShowPrevWin(WM_HWIN hWinList, U8 UseAnim);
void WindowList_SetShowWinChangeCallback(WM_HWIN hWinList, void *pFunc);


#endif /* _WINDOWLIST_H_ */
