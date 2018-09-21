/*
 * PageMainList.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#include "PageMainList.h"
#include "PageMain.h"
#include "PageSet.h"
static WM_HWIN _hWinList = WM_HWIN_NULL;

WM_HWIN PageListCreate(void)
{
	if(WM_HWIN_NULL == _hWinList){
		_hWinList = WindowList_Create(0, DEF_TITLE_BAR_HEIGHT, DEF_PAGE_WIDTH, DEF_MAIN_PAGE_HEIGH, WM_HBKWIN, 0x500, WM_CF_SHOW, 0);
	}
	WM_SetAlignParent(_hWinList, OBJ_ALIGN_PARENT_H_CENTRE, 0, 0);
	GUI_Debug("_hWinList parent %d\n", WM_GetParent(_hWinList));
	GUI_Debug("_hWinList:%d, x pos %d, y pos %d\n", _hWinList, WM_GetWindowOrgX(_hWinList), WM_GetWindowOrgY(_hWinList));

	WindowList_AddWin(_hWinList, PageMainCreate(), PAGE_MAIN);
	WindowList_AddWin(_hWinList, PageSetCreate(), PAGE_SET);
	return _hWinList;
}

void PageListShowWinByName(const char *pWinName)
{
	WindowList_SetShowByNameWin(_hWinList, pWinName, 0);
}
