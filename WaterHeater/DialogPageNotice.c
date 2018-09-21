/*
 * DialogPage.c
 *
 *  Created on: 2018年6月19日
 *      Author: Administrator
 */

#include <GUI_main.h>
#include "ImageResource.h"
#include "DialogPageNotice.h"



#define ID_WINDOW_DIALOG				(ID_DIALOG_PAGE_BASE + 0)
#define ID_DIALOG_BG					(ID_DIALOG_PAGE_BASE + 1)
#define ID_DIALOG_BACK					(ID_DIALOG_PAGE_BASE + 2)

extern GUI_CONST_STORAGE GUI_BITMAP bmerror_canhuo;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_chaowen;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_dianhuo;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_dingshi;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_duanlu;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_fengya;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_paishui;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_passowrd;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_tongxin;
extern GUI_CONST_STORAGE GUI_BITMAP bmerror_xihuo;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_close;

static const GUI_WIDGET_CREATE_INFO _aWindowsDialgNoticeCreate[] =
{
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_DIALOG, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "notice view",		ID_DIALOG_BG, 0, 0, 586, 302, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "btn back",			ID_DIALOG_BACK, 0, 0, 134, 134, 0, 0x0,0},
};


static WM_HWIN hDialogPage = WM_HMEM_NULL;
static U8 NoticeViewIndex = 0;

static void _NoticeViewIndexToFullName(WM_HWIN hImage, U8 Index)
{
	switch(Index){
		case ERROR_FIRE://残火
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_FIRE, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_canhuo);
		break;
		case ERROR_TEMP_CONTROL_OPEN://超温或温控器开路故障
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_TEMP_CONTROL_OPEN, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_chaowen);
		break;
		case ERROR_FIRE_ON://点火失败
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_FIRE_ON, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_dianhuo);
		break;
		case ERROR_TEMP_CONTROL_SHORT://温度传感器开路或短路
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_TEMP_CONTROL_SHORT, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_duanlu);
		break;
		case ERROR_TIMER_END://定时到
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_TIMER_END, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_dingshi);
		break;
		case ERROR_PASSWORD://密码错误
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_PASSWORD, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_passowrd);
		break;
		case ERROR_FAN_SWITCH://风压开关故障
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_FAN_SWITCH, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_fengya);
		break;
		case ERROR_WATER://排水异常
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_WATER, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_paishui);
		break;
		case ERROR_COMMUNICATION://通信故障
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_COMMUNICATION, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_tongxin);
		break;
		case ERROR_FIRE_ACCIDENT://意外熄火
			//IMAGEVIEW_SetFile(hImage, IMAGE_DIALOG_FIRE_ACCIDENT, 0);
			IMAGEVIEW_SetBitmap(hImage, &bmerror_xihuo);
		break;
		default:
		break;
	}
	NoticeViewIndex = Index;
}
static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem;
	/* notice view */
	hItem = WM_GetDialogItem(hParent, ID_DIALOG_BG);
	_NoticeViewIndexToFullName(hItem, NoticeViewIndex);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	/* btn back */
	hItem = WM_GetDialogItem(hParent, ID_DIALOG_BACK);
	IMAGEVIEW_SetFile(hItem, IMAGE_DIALOG_BACK, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, -20, -20);
}

static void _cbWindowsDialgNotice(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;
	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			_DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hDialogPage = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				if(ID_DIALOG_BACK == Id){
					WM_DeleteWindow(pMsg->hWin);
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}
void DialgPageNoticeCreate(U8 ViewIndex)
{
	if(WM_HMEM_NULL == hDialogPage){
		NoticeViewIndex = ViewIndex;
		hDialogPage = GUI_CreateDialogBox(_aWindowsDialgNoticeCreate, GUI_COUNTOF(_aWindowsDialgNoticeCreate), _cbWindowsDialgNotice, WM_HBKWIN, 0, 0);
		GUI_Debug("dialog page %d create\n", hDialogPage);
	}else{
		_NoticeViewIndexToFullName(WM_GetDialogItem(hDialogPage, ID_DIALOG_BG), ViewIndex);
	}
}


