/*
 * TitleBar.c
 *
 *  Created on: 2018年5月14日
 *      Author: Administrator
 */
#include <GUI_main.h>
#include "ImageResource.h"
#include "PasswordPage.h"
#include "TitleBar.h"

#define ID_WINDOW_TITLE_BAR		(ID_TITLE_BAR_BASE + 0)
#define ID_TITLE_LOGO			(ID_TITLE_BAR_BASE + 1)
#define ID_TITLE_SETTING		(ID_TITLE_BAR_BASE + 2)

static const GUI_WIDGET_CREATE_INFO _aWindowsTitleBarCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_TITLE_BAR, 0, 0, 1024, TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "logo",				ID_TITLE_LOGO, 0, 0, 264, 42, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "setting", 			ID_TITLE_SETTING, 0, 0, 50, 50, 0, 0x0,0},
};

static WM_HWIN hTitleBar = WM_HMEM_NULL;
static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem;

	WINDOW_SetBkColor(hParent, GUI_GRAY);

	hItem = WM_GetDialogItem(hParent, ID_TITLE_LOGO);
	IMAGEVIEW_SetFile(hItem, IMAGE_TITLE_LOGO, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 10, 0);

	hItem = WM_GetDialogItem(hParent, ID_TITLE_SETTING);
	IMAGEVIEW_SetFile(hItem, IMAGE_TITLE_SETTING, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, -40, 0);
}

static void _cbWindowsTitleBarDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hTitleBar = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				if(ID_TITLE_SETTING == Id){
					GUI_Debug("Click Setting\n");
					PasswordPageCreate();
				}
			}
		break;
		case WM_TOUCH_PRESSING:
			if(ID_TITLE_LOGO == WM_GetId(pMsg->hWinSrc)){
				GUI_Debug("Press logo icon\n");
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

void TitleBarCreate(void)
{
	if(WM_HMEM_NULL == hTitleBar){
		GUI_Debug("title bar create\n");
		hTitleBar = GUI_CreateDialogBox(_aWindowsTitleBarCreate, GUI_COUNTOF(_aWindowsTitleBarCreate), _cbWindowsTitleBarDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("title bar %d create end\n", hTitleBar);
	}
}
