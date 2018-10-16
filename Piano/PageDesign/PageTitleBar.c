/*
 * PageTitleBar.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */


#include "PageTitleBar.h"
#include "PageMainList.h"
#include "DialogTimeSet.h"
#include "Wireless.h"
#if COMPILE_ON_C600
#include <SystemTime.h>
#else
#include <time.h>
#endif

#define ID_WINDOW_TITLE_BAR			(ID_PAGE_TITLE_BAR_BASE + 0)
#define ID_TITLE_LOGO				(ID_PAGE_TITLE_BAR_BASE + 1)
#define ID_TITLE_HOME_TEXT			(ID_PAGE_TITLE_BAR_BASE + 2)
#define ID_TITLE_SET_TEXT			(ID_PAGE_TITLE_BAR_BASE + 3)
#define ID_TITLE_HOME_LINE			(ID_PAGE_TITLE_BAR_BASE + 4)
#define ID_TITLE_SET_LINE			(ID_PAGE_TITLE_BAR_BASE + 5)
#define ID_TITLE_TIME_HOUR			(ID_PAGE_TITLE_BAR_BASE + 6)
#define ID_TITLE_TIME_COLON			(ID_PAGE_TITLE_BAR_BASE + 7)
#define ID_TITLE_TIME_MINUTE		(ID_PAGE_TITLE_BAR_BASE + 8)
#define ID_TITLE_ICON_WIFI			(ID_PAGE_TITLE_BAR_BASE + 9)


static const GUI_WIDGET_CREATE_INFO _aWindowsTitleBarCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_TITLE_BAR, 0, 0, DEF_PAGE_WIDTH, DEF_TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "logo",					ID_TITLE_LOGO, 0, 0, 153, 30, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"home text",			ID_TITLE_HOME_TEXT, 0, 0, 80, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"set text",				ID_TITLE_SET_TEXT, 0, 0, 80, 50, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "home line",			ID_TITLE_HOME_LINE, 0, 0, 60, 4, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "set line",				ID_TITLE_SET_LINE, 0, 0, 60, 4, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"time hours",			ID_TITLE_TIME_HOUR, 0, 0, 50, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"time colon",			ID_TITLE_TIME_COLON, 0, 0, 12, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"time minute",			ID_TITLE_TIME_MINUTE, 0, 0, 50, 50, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "icon wifi",			ID_TITLE_ICON_WIFI, 0, 0, 48, 34, 0, 0x0,0},
};

static void _SelectItem(WM_HWIN hParent, U8 Flag);

static U8 _FlagColon = 0;
static WM_HWIN _hTitleBar = WM_HMEM_NULL;
static GUI_TIMER_HANDLE hPageTitleBarTimer = WM_HMEM_NULL;

static void _RefreshTimeText(WM_HWIN hParent, U8 ShowColon)
{
	char Buffer[10];
	U8 Hours, Minutes;
#if COMPILE_ON_C600
	SystemTimeInfo TimeInfo;
	GetSystemTime(&TimeInfo);
	Hours = TimeInfo.Hours;
	Minutes = TimeInfo.Minutes;
#else
	time_t Rawtime;
	struct tm *pInfo;
	time(&Rawtime);
	pInfo = localtime(&Rawtime);
	Hours = pInfo->tm_hour;
	Minutes = pInfo->tm_min;
#endif
	if(0 == ShowColon){
		WM_HideWindow(WM_GetDialogItem(hParent, ID_TITLE_TIME_COLON));

	}else{
		WM_ShowWindow(WM_GetDialogItem(hParent, ID_TITLE_TIME_COLON));
	}
	GUI_sprintf(Buffer, "%d", Hours);
	TEXT_SetText(WM_GetDialogItem(hParent, ID_TITLE_TIME_HOUR), Buffer);
	GUI_sprintf(Buffer, "%02d", Minutes);
	TEXT_SetText(WM_GetDialogItem(hParent, ID_TITLE_TIME_MINUTE), Buffer);
}

static void _RefreshWifiIconStatus(WM_HWIN hParent)
{
	if(WIFI_DISCONNECTED == GetWifiConnectStatus()){
		WM_HideWindow(WM_GetDialogItem(hParent, ID_TITLE_ICON_WIFI));
	}else{
		WM_ShowWindow(WM_GetDialogItem(hParent, ID_TITLE_ICON_WIFI));
	}
}
static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;

	_FlagColon = 1;

	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_TOP_CENTRE, 0, 0);

	hItem = WM_GetDialogItem(hParent, ID_TITLE_LOGO);
	IMAGEVIEW_SetBitmap(hItem, &bmlogo);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_CENTER, 25, 0);

	hItem = WM_GetDialogItem(hParent, ID_TITLE_HOME_TEXT);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, -50, 0);
	TEXT_SetFont(hItem, &GUI_FontTitleCHN_YH28);
	TEXT_SetText(hItem, "主页");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	hBase = hItem;

	hItem = WM_GetDialogItem(hParent, ID_TITLE_HOME_LINE);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 2, 0);
	IMAGEVIEW_SetBkColor(hItem, GUI_BLUE);

	hItem = WM_GetDialogItem(hParent, ID_TITLE_SET_TEXT);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 50, 0);
	TEXT_SetFont(hItem, &GUI_FontTitleCHN_YH28);
	TEXT_SetText(hItem, "设置");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	hBase = hItem;

	hItem = WM_GetDialogItem(hParent, ID_TITLE_SET_LINE);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 2, 0);
	IMAGEVIEW_SetBkColor(hItem, GUI_BLUE);

	//time hours
	hItem = WM_GetDialogItem(hParent, ID_TITLE_TIME_HOUR);
	TEXT_SetFont(hItem, &GUI_FontNumberYH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_RIGHT);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_CENTER, -100, 0);
	hBase = hItem;
	//time colon
	hItem = WM_GetDialogItem(hParent, ID_TITLE_TIME_COLON);
	TEXT_SetFont(hItem, &GUI_FontNumberYH48);
	TEXT_SetText(hItem, ":");
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	hBase = hItem;
	//time minute
	hItem = WM_GetDialogItem(hParent, ID_TITLE_TIME_MINUTE);
	TEXT_SetFont(hItem, &GUI_FontNumberYH48);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);

	_RefreshTimeText(hParent, _FlagColon);
	//icon wifi
	hItem = WM_GetDialogItem(hParent, ID_TITLE_ICON_WIFI);
	IMAGEVIEW_SetBitmap(hItem, &bmwifi_enable);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TITLE_TIME_HOUR), hItem, OBJ_ALIGN_BROTHER_OUT_LEFT, -10, 0);
	WM_ShowWindowAndChild(hParent);
	_SelectItem(hParent, 1);
	_RefreshWifiIconStatus(hParent);
}

static void _SelectItem(WM_HWIN hParent, U8 Flag)
{
	//选择的是主页
	if(Flag){
		TEXT_SetTextColor(WM_GetDialogItem(hParent, ID_TITLE_HOME_TEXT), GUI_WHITE);
		WM_ShowWindow(WM_GetDialogItem(hParent, ID_TITLE_HOME_LINE));
		TEXT_SetTextColor(WM_GetDialogItem(hParent, ID_TITLE_SET_TEXT), GUI_GRAY);
		WM_HideWindow(WM_GetDialogItem(hParent, ID_TITLE_SET_LINE));
	}else{
		TEXT_SetTextColor(WM_GetDialogItem(hParent, ID_TITLE_HOME_TEXT), GUI_GRAY);
		//WM_HideWindow(WM_GetDialogItem(hParent, ID_TITLE_HOME_TEXT));
		WM_HideWindow(WM_GetDialogItem(hParent, ID_TITLE_HOME_LINE));
		TEXT_SetTextColor(WM_GetDialogItem(hParent, ID_TITLE_SET_TEXT), GUI_WHITE);
		WM_ShowWindow(WM_GetDialogItem(hParent, ID_TITLE_SET_LINE));
	}
}
static void __PageTitleBarTimer_cb(GUI_TIMER_MESSAGE *pContext)
{
	if(_FlagColon){
		_FlagColon = 0;
	}else{
		_FlagColon = 1;
	}
	_RefreshTimeText(pContext->Context, _FlagColon);
	_RefreshWifiIconStatus(pContext->Context);
	GUI_TIMER_Restart(hPageTitleBarTimer);
}
static void _hTitleTimerInit(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == hPageTitleBarTimer){
		hPageTitleBarTimer = GUI_TIMER_Create(__PageTitleBarTimer_cb, WM_TIMER + 1, hParent, 0);
		GUI_TIMER_SetPeriod(hPageTitleBarTimer, 500);
		GUI_TIMER_Restart(hPageTitleBarTimer);
	}
}

static void _cbWindowsTitleBarDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			_DialogInit(pMsg->hWin);
			//_hTitleTimerInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hTitleBar = WM_HMEM_NULL;
			hPageTitleBarTimer = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_TITLE_LOGO:
#if !COMPILE_ON_C600
						ReverseWifiConnectStatus();
#endif
					break;
					case ID_TITLE_HOME_TEXT:
						_SelectItem(pMsg->hWin, 1);
						PageListShowWinByName(PAGE_MAIN);
						HoodCom_SendTouchVoice();
					break;
					case ID_TITLE_SET_TEXT:
						_SelectItem(pMsg->hWin, 0);
						PageListShowWinByName(PAGE_SET);
						HoodCom_SendTouchVoice();
					break;
					case ID_TITLE_TIME_HOUR:
					case ID_TITLE_TIME_COLON:
					case ID_TITLE_TIME_MINUTE:
						DialogTimeSetCreate(WM_HBKWIN);
						HoodCom_SendTouchVoice();
					break;
				}
			}
		break;
		case ID_MSG_WIN_LIST_CHANGE:
		{
			const char *pWinName;
			pWinName = (const char *)pMsg->Data.p;
			if(0 == GUI_strcmp(pWinName, PAGE_MAIN)){
				_SelectItem(pMsg->hWin, 1);
			}else if(0 == GUI_strcmp(pWinName, PAGE_SET)){
				_SelectItem(pMsg->hWin, 0);
			}
		}
		break;
		case WM_TOUCH_PRESSING:
			if(ID_TITLE_LOGO == WM_GetId(pMsg->hWinSrc)){
				//GUI_Debug("Press logo icon\n");
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN PageTitleBarCreate(void)
{
	if(WM_HMEM_NULL == _hTitleBar){
		GUI_Debug("title bar create\n");
		_hTitleBar = GUI_CreateDialogBox(_aWindowsTitleBarCreate, GUI_COUNTOF(_aWindowsTitleBarCreate), _cbWindowsTitleBarDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("title bar %d create end\n", _hTitleBar);
	}
	return _hTitleBar;
}

WM_HWIN PageTitleBarGetHander(void)
{
	return _hTitleBar;
}


