/*
 * PageMain.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#include "DialogDelaySet.h"
#include "DialogTimingAir.h"
#include "DialogCookerTime.h"
#include "PageMain.h"

#define ID_WINDOW_PAGE_MAIN			(ID_PAGE_MAIN_BASE + 0)
#define ID_MAIN_BTN_DELAY_SET		(ID_PAGE_MAIN_BASE + 1)
#define ID_MAIN_BTN_TIMING_AIR		(ID_PAGE_MAIN_BASE + 2)
#define ID_MAIN_BTN_BLUETOOTH		(ID_PAGE_MAIN_BASE + 3)
#define ID_MAIN_BTN_COOKER_TIMER	(ID_PAGE_MAIN_BASE + 4)
#define ID_MAIN_WEATHER_BG			(ID_PAGE_MAIN_BASE + 5)
#define ID_MAIN_BTN_RECIPE			(ID_PAGE_MAIN_BASE + 6)
#define ID_MAIN_BTN_MUSIC			(ID_PAGE_MAIN_BASE + 7)
#define ID_MAIN_BTN_MOVIE			(ID_PAGE_MAIN_BASE + 8)
#define ID_MAIN_BTN_CLOSE			(ID_PAGE_MAIN_BASE + 9)
#define ID_MAIN_DELAY_REMAIN_TEXT	(ID_PAGE_MAIN_BASE + 10)
#define ID_MAIN_TIMING_REMAIN_TEXT	(ID_PAGE_MAIN_BASE + 11)
#define ID_MAIN_COOKER_REMAIN_LEFT_TEXT	(ID_PAGE_MAIN_BASE + 12)
#define ID_MAIN_COOKER_REMAIN_RIGHT_TEXT	(ID_PAGE_MAIN_BASE + 13)

#define DEF_PART_PIXEL_H				10
#define DEF_PART_PIXEL_V				11


static const GUI_WIDGET_CREATE_INFO _aWindowsPageMainCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_PAGE_MAIN_BASE, 0, DEF_TITLE_BAR_HEIGHT, DEF_PAGE_WIDTH, DEF_MAIN_PAGE_HEIGH, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "delay set",			ID_MAIN_BTN_DELAY_SET, 0, 0, 225, 130, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "timing air",			ID_MAIN_BTN_TIMING_AIR, 0, 0, 225, 130, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "bluetooth",			ID_MAIN_BTN_BLUETOOTH, 0, 0, 237, 252, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "cooker timer",			ID_MAIN_BTN_COOKER_TIMER, 0, 0, 229, 114, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect,   "weather bg",			ID_MAIN_WEATHER_BG, 0, 0, 229, 130, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "recipe",				ID_MAIN_BTN_RECIPE, 0, 0, 460, 238, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "music",				ID_MAIN_BTN_MUSIC, 0, 0, 181, 115, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "movie",				ID_MAIN_BTN_MOVIE, 0, 0, 181, 115, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "close",				ID_MAIN_BTN_CLOSE, 0, 0, 70, 64, 0, 0x0,0},
	{ TEXT_CreateIndirect, "delay remain",				ID_MAIN_DELAY_REMAIN_TEXT, 0, 0, 200, 30, 0, 0x0,0},
	{ TEXT_CreateIndirect, "timing remain",				ID_MAIN_TIMING_REMAIN_TEXT, 0, 0, 200, 30, 0, 0x0,0},
	{ TEXT_CreateIndirect, "delay remain",				ID_MAIN_COOKER_REMAIN_LEFT_TEXT, 0, 0, 200, 30, 0, 0x0,0},
	{ TEXT_CreateIndirect, "timing remain",				ID_MAIN_COOKER_REMAIN_RIGHT_TEXT, 0, 0, 200, 30, 0, 0x0,0},
};


static WM_HWIN _hPageMain = WM_HMEM_NULL;
static GUI_TIMER_HANDLE _hPageMainTimer = WM_HMEM_NULL;
static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;

	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_H_CENTRE, 0, 0);
	//WINDOW_SetBkColor(hParent, GUI_RED);

	//延时关机按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_DELAY_SET);
	IMAGEVIEW_SetBitmap(hItem, &bmysgj_unfocus);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT, 25, DEF_PART_PIXEL_V);
	hBase = hItem;
	//菜谱按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_RECIPE);
	IMAGEVIEW_SetBitmap(hItem, &bmrecipe_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, DEF_PART_PIXEL_H);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT, 25, 0);
	//定时换气按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_TIMING_AIR);
	IMAGEVIEW_SetBitmap(hItem, &bmzdhq_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H, DEF_PART_PIXEL_V);

	//烟灶联动按钮
	hBase = WM_GetDialogItem(hParent, ID_MAIN_BTN_RECIPE);
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_BLUETOOTH);
	IMAGEVIEW_SetBitmap(hItem, &bmyzld_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H, DEF_PART_PIXEL_V);
	hBase = hItem;
	//天气背景
	hItem = WM_GetDialogItem(hParent, ID_MAIN_WEATHER_BG);
	IMAGEVIEW_SetBitmap(hItem, &bmweather_bg);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H, DEF_PART_PIXEL_V);
	//烹饪计时按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_COOKER_TIMER);
	IMAGEVIEW_SetBitmap(hItem, &bmcooker_timer_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_WEATHER_BG), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, DEF_PART_PIXEL_H);
	GUI_Debug("Cooker time bg %d\n", hItem);
	//音乐按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_MUSIC);
	IMAGEVIEW_SetBitmap(hItem, &bmqqmusic_unfocus);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_RECIPE), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_BLUETOOTH), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, DEF_PART_PIXEL_H);
	//视频按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_MOVIE);
	IMAGEVIEW_SetBitmap(hItem, &bmqqmovie_unfocus);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_MUSIC), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_BLUETOOTH), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, DEF_PART_PIXEL_H);
	//关闭按钮
	hItem = WM_GetDialogItem(hParent, ID_MAIN_BTN_CLOSE);
	IMAGEVIEW_SetBitmap(hItem, &bmbtn_power_unfocus);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_MOVIE), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL_H + 10, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_BLUETOOTH), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, DEF_PART_PIXEL_H + 25);
	//GUI_Debug("button close x %d, y %d\n", WM_GetWindowOrgX(hItem) - WM_GetWindowOrgX(hParent), WM_GetWindowOrgY(hItem) - WM_GetWindowOrgY(hParent));
	//延时关机倒计时
	hItem = WM_GetDialogItem(hParent, ID_MAIN_DELAY_REMAIN_TEXT);
	TEXT_SetText(hItem, "距关机还剩99分");
	TEXT_SetFont(hItem, &GUI_FontYH24);
	TEXT_SetTextColor(hItem, GUI_YELLOW);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_DELAY_SET), hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_DELAY_SET), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, -5);
	//定时换气倒计时
	hItem = WM_GetDialogItem(hParent, ID_MAIN_TIMING_REMAIN_TEXT);
	TEXT_SetText(hItem, "距换气还剩12时13分");
	TEXT_SetFont(hItem, &GUI_FontYH24);
	TEXT_SetTextColor(hItem, GUI_YELLOW);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_TIMING_AIR), hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_TIMING_AIR), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, -5);
	//左灶剩余时间
	hItem = WM_GetDialogItem(hParent, ID_MAIN_COOKER_REMAIN_LEFT_TEXT);
	TEXT_SetText(hItem, "左灶剩余30分");
	TEXT_SetFont(hItem, &GUI_FontYH24);
	TEXT_SetTextColor(hItem, GUI_YELLOW);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_COOKER_TIMER), hItem, OBJ_ALIGN_BROTHER_CENTER, 20, -10);
	//右灶剩余时间
	hItem = WM_GetDialogItem(hParent, ID_MAIN_COOKER_REMAIN_RIGHT_TEXT);
	TEXT_SetText(hItem, "右灶剩余30分");
	TEXT_SetFont(hItem, &GUI_FontYH24);
	TEXT_SetTextColor(hItem, GUI_YELLOW);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_MAIN_BTN_COOKER_TIMER), hItem, OBJ_ALIGN_BROTHER_CENTER, 20, 15);
	WM_ShowWindowAndChild(hParent);
}
static void __PageMainTimer_cb(GUI_TIMER_MESSAGE *pContext)
{
	IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MAIN_BTN_COOKER_TIMER), &bmcooker_timer_pic);
	GUI_TIMER_Restart(_hPageMainTimer);
}

static void _PageMainTimerInit(WM_HWIN hWin)
{
	if(WM_HMEM_NULL == _hPageMainTimer){
		_hPageMainTimer = GUI_TIMER_Create(__PageMainTimer_cb, WM_TIMER + 1, hWin, 0);
		GUI_TIMER_SetPeriod(_hPageMainTimer, 500);
		GUI_TIMER_Restart(_hPageMainTimer);
	}
}
static void _cbWindowsPageMainDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			_DialogInit(pMsg->hWin);
			_PageMainTimerInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hPageMain = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_MAIN_BTN_DELAY_SET:
						GUI_Debug("DialogDelaySetCreate\n");
						DialogDelaySetCreate(pMsg->hWin);
					break;
					case ID_MAIN_BTN_TIMING_AIR:
						DialogTimingAirCreate(pMsg->hWin);
					break;
					case ID_MAIN_BTN_COOKER_TIMER:
						DialogCookerTimeCreate(pMsg->hWin);
					break;
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}
WM_HWIN PageMainCreate(void)
{
	if(WM_HMEM_NULL == _hPageMain){
		_hPageMain = GUI_CreateDialogBox(_aWindowsPageMainCreate, GUI_COUNTOF(_aWindowsPageMainCreate), _cbWindowsPageMainDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("page main %d create end\n", _hPageMain);
	}
	return _hPageMain;
}
