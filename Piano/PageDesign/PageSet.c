/*
 * PageSet.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#include "PageSet.h"
#include "PageBrightnessSet.h"
#include "PageWifi.h"

#define ID_WINDOW_SET				(ID_PAGE_SET_BASE + 0)
#define ID_SET_H_LINE				(ID_PAGE_SET_BASE + 1)
#define ID_SET_V_LINE				(ID_PAGE_SET_BASE + 2)
#define ID_SET_LIGHT_VIEW			(ID_PAGE_SET_BASE + 3)
#define ID_SET_LIGHT_ICON			(ID_PAGE_SET_BASE + 4)
#define ID_SET_LIGHT_TEXT			(ID_PAGE_SET_BASE + 5)
#define ID_SET_WIFI_VIEW			(ID_PAGE_SET_BASE + 6)
#define ID_SET_WIFI_ICON			(ID_PAGE_SET_BASE + 7)
#define ID_SET_WIFI_TEXT			(ID_PAGE_SET_BASE + 8)
#define ID_SET_BLUETOOTH_VIEW		(ID_PAGE_SET_BASE + 9)
#define ID_SET_BLUETOOTH_ICON		(ID_PAGE_SET_BASE + 10)
#define ID_SET_BLUETOOTH_TEXT		(ID_PAGE_SET_BASE + 11)
#define ID_SET_BTN_CLOSE			(ID_PAGE_SET_BASE + 12)

#define DEF_PART_PIXEL				-30
#define DEF_SELECT_COLOR			0xffdf9b00
#define DEF_UNSELECT_COLOR			GUI_BLACK

static const GUI_WIDGET_CREATE_INFO _aWindowsPageSetCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_SET, 0, DEF_TITLE_BAR_HEIGHT, DEF_PAGE_WIDTH, DEF_MAIN_PAGE_HEIGH, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "h line",				ID_SET_H_LINE, 0, 11, DEF_PAGE_WIDTH, 1, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "v line",				ID_SET_V_LINE, 0, 11, 1, DEF_MAIN_PAGE_HEIGH, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "light view",			ID_SET_LIGHT_VIEW, 0, 0, 160, 90, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "light icon",			ID_SET_LIGHT_ICON, 0, 0, 40, 28, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"light text",			ID_SET_LIGHT_TEXT, 0, 0, 60, 40, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "wifi view",			ID_SET_WIFI_VIEW, 0, 0, 160, 90, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "wifi icon",			ID_SET_WIFI_ICON, 0, 0, 40, 28, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"wifi text",			ID_SET_WIFI_TEXT, 0, 0, 60, 40, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "bluetooth view",		ID_SET_BLUETOOTH_VIEW, 0, 0, 160, 90, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "bluetooth icon",		ID_SET_BLUETOOTH_ICON, 0, 0, 40, 28, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"bluetooth text",		ID_SET_BLUETOOTH_TEXT, 0, 0, 60, 40, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "close",				ID_SET_BTN_CLOSE, 887, 298, 70, 64, WM_CF_HASTRANS, 0x0,0},
};

static WM_HWIN _hPageSet = WM_HMEM_NULL;
static WM_HWIN _hPageShow = WM_HWIN_NULL;
static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;

	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_H_CENTRE, 0, 0);
	//WINDOW_SetBkColor(hParent, GUI_GREEN);
	//h line
	hItem = WM_GetDialogItem(hParent, ID_SET_H_LINE);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	//v line
	hItem = WM_GetDialogItem(hParent, ID_SET_V_LINE);
	hBase =  WM_GetDialogItem(hParent, ID_SET_LIGHT_VIEW);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);

	//亮度区域
	hItem = WM_GetDialogItem(hParent, ID_SET_LIGHT_VIEW);
	IMAGEVIEW_SetBkColor(hItem, DEF_SELECT_COLOR);
	WM_SetAlignWindow( WM_GetDialogItem(hParent, ID_SET_H_LINE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	hBase = hItem;
	//亮度icon
	hItem = WM_GetDialogItem(hParent, ID_SET_LIGHT_ICON);
	IMAGEVIEW_SetBitmap(hItem, &bmlight_icon_focus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, DEF_PART_PIXEL, 0);
	//亮度text
	hItem = WM_GetDialogItem(hParent, ID_SET_LIGHT_TEXT);
	TEXT_SetText(hItem, "亮度");
	TEXT_SetFont(hItem, &GUI_FontSetCHN_YH32);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_SET_LIGHT_ICON), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 5, 0);

	//wifi区域
	hItem = WM_GetDialogItem(hParent, ID_SET_WIFI_VIEW);
	//IMAGEVIEW_SetBkColor(hItem, GUI_BLUE);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	hBase = hItem;
	//wifi icon
	hItem = WM_GetDialogItem(hParent, ID_SET_WIFI_ICON);
	IMAGEVIEW_SetBitmap(hItem, &bmwifi_icon_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, DEF_PART_PIXEL, 0);
	//wifi text
	hItem = WM_GetDialogItem(hParent, ID_SET_WIFI_TEXT);
	TEXT_SetText(hItem, "Wifi");
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	TEXT_SetTextColor(hItem, GUI_GRAY);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_SET_WIFI_ICON), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 5, 0);
	//蓝牙区域
	hItem = WM_GetDialogItem(hParent, ID_SET_BLUETOOTH_VIEW);
	//IMAGEVIEW_SetBkColor(hItem, GUI_BLUE);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	hBase = hItem;
	//蓝牙 icon
	hItem = WM_GetDialogItem(hParent, ID_SET_BLUETOOTH_ICON);
	IMAGEVIEW_SetBitmap(hItem, &bmbluetooth_icon_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, DEF_PART_PIXEL, 0);
	//蓝牙 text
	hItem = WM_GetDialogItem(hParent, ID_SET_BLUETOOTH_TEXT);
	TEXT_SetText(hItem, "蓝牙");
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	TEXT_SetTextColor(hItem, GUI_GRAY);
	TEXT_SetFont(hItem, &GUI_FontSetCHN_YH32);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_CENTER, 5, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_SET_BLUETOOTH_ICON), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 5, 0);
	//关机按钮
	hItem = WM_GetDialogItem(hParent, ID_SET_BTN_CLOSE);
	IMAGEVIEW_SetBitmap(hItem, &bmbtn_power_unfocus);
	//WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, -30, -20);

	_hPageShow = PageBrightnessSetCreate(hParent);

	WM_ShowWindowAndChild(hParent);

}

static void _cbWindowsPageSetDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			_DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hPageSet = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_SET_LIGHT_VIEW:
					case ID_SET_LIGHT_ICON:
					case ID_SET_LIGHT_TEXT:
						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_VIEW), DEF_SELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_ICON), &bmlight_icon_focus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_TEXT), GUI_WHITE);

						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_VIEW), DEF_UNSELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_ICON), &bmwifi_icon_unfocus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_TEXT), GUI_GRAY);

						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_VIEW), DEF_UNSELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_ICON), &bmbluetooth_icon_unfocus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_TEXT), GUI_GRAY);
						if(PageBrightnessGetHander() != _hPageShow){
							WM_DeleteWindow(_hPageShow);
							_hPageShow = PageBrightnessSetCreate(pMsg->hWin);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_SET_WIFI_VIEW:
					case ID_SET_WIFI_ICON:
					case ID_SET_WIFI_TEXT:
						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_VIEW), DEF_UNSELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_ICON), &bmlight_icon_unfocus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_TEXT), GUI_GRAY);

						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_VIEW), DEF_SELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_ICON), &bmwifi_icon_focus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_TEXT), GUI_WHITE);

						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_VIEW), DEF_UNSELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_ICON), &bmbluetooth_icon_unfocus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_TEXT), GUI_GRAY);
						if(PageWifiGetHander() == _hPageShow){
							WM_SendMessageNoPara(_hPageShow, ID_MSG_TO_SCAN_AP);
						}else{
							if(_hPageShow){
								WM_DeleteWindow(_hPageShow);
							}
							_hPageShow = PageWifiCreate(pMsg->hWin);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_SET_BLUETOOTH_VIEW:
					case ID_SET_BLUETOOTH_ICON:
					case ID_SET_BLUETOOTH_TEXT:
						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_VIEW), DEF_UNSELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_ICON), &bmlight_icon_unfocus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_LIGHT_TEXT), GUI_GRAY);

						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_VIEW), DEF_UNSELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_ICON), &bmwifi_icon_unfocus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_WIFI_TEXT), GUI_GRAY);

						IMAGEVIEW_SetBkColor(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_VIEW), DEF_SELECT_COLOR);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_ICON), &bmbluetooth_icon_focus);
						TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_SET_BLUETOOTH_TEXT), GUI_WHITE);
						HoodCom_SendTouchVoice();
					break;
					case ID_SET_BTN_CLOSE:
						Setting_SetCloseAllFunc();
					break;
				}
			}
		break;
		case WM_TOUCH_PRESSING:
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN PageSetCreate(void)
{
	if(WM_HMEM_NULL == _hPageSet){
		_hPageSet = GUI_CreateDialogBox(_aWindowsPageSetCreate, GUI_COUNTOF(_aWindowsPageSetCreate), _cbWindowsPageSetDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("page set %d create end\n", _hPageSet);
	}
	return _hPageSet;
}
