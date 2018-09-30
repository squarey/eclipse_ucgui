/*
 * PageMainList.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#include "PageMainList.h"
#include "PageMain.h"
#include "PageSet.h"
#include "PageTitleBar.h"
#include "HoodCom.h"
static WM_HWIN _hWinList = WM_HWIN_NULL;

static void _NotifyWinShowChageToChild(WM_HWIN hParent, WM_HWIN ShowWin)
{
	WM_HWIN hChild;
	WM_Obj *pChild, *pParent;
	WM_MESSAGE Msg;
	pParent = WM_H2P(hParent);
	for(hChild = pParent->hFirstChild; hChild; hChild = pChild->hNext){
		pChild = WM_H2P(hChild);
		Msg.hWin = hChild;
		Msg.MsgId = ID_MSG_WIN_LIST_CHANGE;
		Msg.Data.v = ShowWin;
		WM_SendMessage(hChild, &Msg);
	}
}

static void _WinListShowChange(WM_HWIN CurShowWin, const char *pWinName)
{
	//_NotifyWinShowChageToChild(_hWinList, CurShowWin);
	WM_MESSAGE Msg;
	Msg.hWin = PageTitleBarGetHander();
	Msg.MsgId = ID_MSG_WIN_LIST_CHANGE;
	Msg.Data.p = (void *)pWinName;
	WM_SendMessage(Msg.hWin, &Msg);
}

WM_HWIN PageListCreate(void)
{
	if(WM_HWIN_NULL == _hWinList){
		_hWinList = WindowList_Create(0, DEF_TITLE_BAR_HEIGHT, DEF_PAGE_WIDTH, DEF_MAIN_PAGE_HEIGH, WM_HBKWIN, 0x500, WM_CF_SHOW, 0);
	}
	WM_SetAlignParent(_hWinList, OBJ_ALIGN_PARENT_H_CENTRE, 0, 0);
	GUI_Debug("_hWinList parent %d\n", WM_GetParent(_hWinList));
	GUI_Debug("_hWinList:%d, x pos %d, y pos %d\n", _hWinList, WM_GetWindowOrgX(_hWinList), WM_GetWindowOrgY(_hWinList));
	HoodComInit();
	HoodCom_SendOpenVoice();
	WindowList_AddWin(_hWinList, PageMainCreate(), PAGE_MAIN);
	WindowList_AddWin(_hWinList, PageSetCreate(), PAGE_SET);
	WindowList_SetShowWinChangeCallback(_hWinList, (void *)_WinListShowChange);
	return _hWinList;
}

void PageListShowWinByName(const char *pWinName)
{
	WindowList_SetShowByNameWin(_hWinList, pWinName, 0);
}
