/*
 * PageWifi.c
 *
 *  Created on: 2018年9月28日
 *      Author: Administrator
 */


#include "PageWifi.h"
#include "DialogWifiPassword.h"
#include <Wireless.h>

#define ID_WINDOW_WIFI 				(ID_PAGE_WIFI_BASE + 0)
#define ID_WIFI_TEXT_NOTICE			(ID_PAGE_WIFI_BASE + 1)
#define ID_WIFI_SWITCH				(ID_PAGE_WIFI_BASE + 2)
#define ID_WIFI_LIST				(ID_PAGE_WIFI_BASE + 3)
#define ID_WIFI_LINE_H				(ID_PAGE_WIFI_BASE + 4)
#define ID_WIFI_PROGBAR				(ID_PAGE_WIFI_BASE + 5)

typedef struct
{
	const GUI_BITMAP *bmConnectIcon;
	const GUI_BITMAP *bmEncrySignal;
	WM_HMEM hSSID;
	U8 FlagEncry;
	I32 SignalLevel;
} WifiListItemInfo;

static const GUI_WIDGET_CREATE_INFO _aDialogWifiCreate[] =
{
		{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_WIFI, 251, 0, 500, DEF_DIALOG_HEIGHT, 0, 0x0,0},
		{ TEXT_CreateIndirect,		"Text notice", 			ID_WIFI_TEXT_NOTICE, 0, 0, 150, 50, 0, 0, 0},
		{ CHECKBOX_CreateIndirect,	"switch", 				ID_WIFI_SWITCH, 0, 0, 100, 50, 0, 0, 0},
		{ LISTVIEW_CreateIndirect,  "list",					ID_WIFI_LIST, 0, 0, 500, 320, 0, 0, 0},
		{ IMAGEVIEW_CreateIndirect,  "view line",			ID_WIFI_LINE_H, 0, 0, 500, 1, 0, 0, 0},
		{ PROGBAR_CreateIndirect,	"progbar", 				ID_WIFI_PROGBAR, 0, 0, 30, 30, 0, 0, 0},
};

static WM_HWIN _hWifi = WM_HWIN_NULL;
static U8 _FlagNewScan = 0;
static U8 _WifiConnectSave = 0;
static GUI_TIMER_HANDLE _hCheckTimer = WM_HMEM_NULL;


static U8 _WifiListItemDraw(const LISTVIEW_DrawItemInfo *pInfo)
{
	U16 BitmapHeight = 0, BitmapWidth = 0;
	U16 RectWidth, RectHeight;
	I32 DrawPosX = 0, DrawPosY = 0;
	WifiListItemInfo *pItemInfo;
	pItemInfo = (WifiListItemInfo *)pInfo->pItem;
	RectWidth = WM_GetRectSizeX(pInfo->Rect);
	RectHeight = WM_GetRectSizeY(pInfo->Rect);
	if(pItemInfo->bmConnectIcon){
		BitmapHeight = pItemInfo->bmConnectIcon->YSize;
		BitmapWidth = pItemInfo->bmConnectIcon->XSize;
		DrawPosY = (RectHeight - BitmapHeight)/2 + pInfo->Rect.y0;
		DrawPosX += pInfo->Rect.x0;
		GUI_DrawBitmap(pItemInfo->bmConnectIcon, DrawPosX, DrawPosY);
	}
	if(pItemInfo->hSSID){
		char *pText;
		GUI_RECT DrawRect;
		pText = (char *)GUI_ALLOC_h2p(pItemInfo->hSSID);
		DrawRect = pInfo->Rect;
		DrawRect.x0 = 32 + 10;
		GUI_DispStringInRect(pText, &DrawRect, GUI_TA_VCENTER);
	}
	if(pItemInfo->bmEncrySignal){
		BitmapHeight = pItemInfo->bmEncrySignal->YSize;
		BitmapWidth = pItemInfo->bmEncrySignal->XSize;
		DrawPosY = (RectHeight - BitmapHeight)/2 + pInfo->Rect.y0;
		DrawPosX = RectWidth - BitmapWidth - 20 + pInfo->Rect.x0;
		GUI_DrawBitmap(pItemInfo->bmEncrySignal, DrawPosX, DrawPosY);
	}
	GUI_SetColor(GUI_GRAY);
	GUI_DrawHLine(pInfo->Rect.y1 - 1, pInfo->Rect.x0, pInfo->Rect.x1);
	return 1;
}
static U8 _WifiListItemDelete(void *pItem)
{
	WifiListItemInfo *pItemInfo;
	pItemInfo = (WifiListItemInfo *)pItem;
	GUI_ALLOC_Free(pItemInfo->hSSID);
	pItemInfo->hSSID = WM_HMEM_NULL;
	return 1;
}
static U8 _WifiScanResult_cb(const APInfo *pInfo)
{
	WM_QUEUE_PARA Para;
	Para.QueueId = ID_MSG_QUEUE_ADD_ITEM;
	Para.hWin = WM_GetDialogItem(_hWifi, ID_WIFI_LIST);
	Para.pData = (void *)pInfo;
	Para.DataLen = sizeof(APInfo);
	WM_PostMessageToQueue(&Para);
	return 1;
}
static void _AddOneItemToListview(WM_HWIN hWin, const APInfo *pInfo)
{
	char *pSSID;
	U8 Flag = 0;
	WifiListItemInfo ItemInfo;
	WM_ShowWindow(hWin);
	ItemInfo.FlagEncry = pInfo->Encry;
	ItemInfo.SignalLevel = pInfo->SignalLevel;
	ItemInfo.hSSID = GUI_ALLOC_AllocZero(GUI_strlen(pInfo->SSID) + 1);
	pSSID = (char *)GUI_ALLOC_h2p(ItemInfo.hSSID);
	GUI_strcpy(pSSID, pInfo->SSID);
	if(_FlagNewScan){
		LISTVIEW_ClearItem(hWin);
		_FlagNewScan = 0;
	}
	if(ItemInfo.SignalLevel < -75){
		Flag = 0x01;
	}else if(ItemInfo.SignalLevel < -70){
		Flag = 0x02;
	}else if(ItemInfo.SignalLevel < -50){
		Flag = 0x04;
	}else{
		Flag = 0x08;
	}
	if(ENCRYPTION_OPEN != (ItemInfo.FlagEncry & ENCRYPTION_OPEN)){
		Flag |= 0x10;
		ItemInfo.bmEncrySignal = &bmic_wifi_lock_signal_4_dark;
	}else{
		Flag |= 0x20;
	}
	switch(Flag){
		case 0x11://加密 信号非常差
			ItemInfo.bmEncrySignal = &bmwifi_level4_lock_w;
		break;
		case 0x12://加密 信号差
			ItemInfo.bmEncrySignal = &bmwifi_level3_lock_w;
		break;
		case 0x14://加密 信号一般
			ItemInfo.bmEncrySignal = &bmwifi_level2_lock_w;
		break;
		case 0x18://加密 信号好
			ItemInfo.bmEncrySignal = &bmwifi_level1_lock_w;
		break;
		case 0x21://开放 信号非常差
			ItemInfo.bmEncrySignal = &bmwifi_level4_open_w;
		break;
		case 0x22://开放 信号差
			ItemInfo.bmEncrySignal = &bmwifi_level3_open_w;
		break;
		case 0x24://开放 信号一般
			ItemInfo.bmEncrySignal = &bmwifi_level2_open_w;
		break;
		case 0x28://开放 信号好
			ItemInfo.bmEncrySignal = &bmwifi_level1_open_w;
		break;
		default:
			ItemInfo.bmEncrySignal = &bmwifi_level4_lock_w;
		break;
	}
	if(WIFI_CONNECTED == GetWifiConnectStatus()){
		const char *pConnectedSSID;
		pConnectedSSID = GetWifiConnectedSSID();
		if(0 == GUI_strcmp(pConnectedSSID, pSSID)){
			ItemInfo.bmConnectIcon = &bmselect_icon;
			ListView_InsertExternItem(hWin, 0, (void *)&ItemInfo, sizeof(WifiListItemInfo));
		}else{
			ItemInfo.bmConnectIcon = NULL;
			LISTVIEW_AddExternItem(hWin, (void *)&ItemInfo, sizeof(WifiListItemInfo));
		}
	}else{
		ItemInfo.bmConnectIcon = NULL;
		LISTVIEW_AddExternItem(hWin, (void *)&ItemInfo, sizeof(WifiListItemInfo));
	}
}
static void _WifiDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	/*GUI_FullRectStyle BgStyle = {
			.MainColor = GUI_CYAN,
			.GradColor = GUI_CYAN,
			.Radius = 0,
			.Opacity = 0xff,
	};*/
	_WifiConnectSave = GetWifiConnectStatus();
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_V_CENTRE, 0, 6);
	//WINDOW_SetBkColor(hParent, &BgStyle);
	//text
	hItem = WM_GetDialogItem(hParent, ID_WIFI_TEXT_NOTICE);
	TEXT_SetText(hItem, "Network Set");
	TEXT_SetFont(hItem, &GUI_FontASSIC_YH32);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	//WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	hBase = hItem;

	//switch
	hItem = WM_GetDialogItem(hParent, ID_WIFI_SWITCH);
	CHECKBOX_SetImage(hItem, &bmbtn_close, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmbtn_open, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	WM_SetHasTrans(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, 0, 0);
	hBase = hItem;
	//line h
	hItem = WM_GetDialogItem(hParent, ID_WIFI_LINE_H);
	IMAGEVIEW_SetBkColor(hItem, GUI_GRAY);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	//progbar
	hItem = WM_GetDialogItem(hParent, ID_WIFI_PROGBAR);
	PROGBAR_SetStyle(hItem, PROGBAR_STYLE_CIRCLE);
	WM_SetHasTrans(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 15);
	//listview
	hItem = WM_GetDialogItem(hParent, ID_WIFI_LIST);
	LISTVIEW_SetItemYSize(hItem, 50);
	LISTVIEW_SetDrawItemMethod(hItem, _WifiListItemDraw, _WifiListItemDelete);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 1);
	GUI_Debug("hListView %d\n", hItem);

	WM_ShowWindowAndChild(hParent);
	LISTVIEW_HideScrollbar(hItem);
	WM_HideWindow(WM_GetDialogItem(hParent, ID_WIFI_PROGBAR));

	if(0 == CHECKBOX_IsChecked(WM_GetDialogItem(hParent, ID_WIFI_SWITCH))){
		WM_HideWindow(hItem);
	}
}

static void _cbCheckStatusTimer(GUI_TIMER_MESSAGE *pContext)
{
	if(_WifiConnectSave != GetWifiConnectStatus()){
		PageWifiToRescanList();
		_WifiConnectSave = GetWifiConnectStatus();
		WM_ShowWindow(WM_GetDialogItem(WM_GetParent(pContext->Context), ID_WIFI_PROGBAR));
	}
	GUI_TIMER_Restart(_hCheckTimer);
}
static void _CheckWifiConnectStatusTimer(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hCheckTimer){
		_hCheckTimer = GUI_TIMER_Create(_cbCheckStatusTimer, 0, hParent, 0);
		GUI_TIMER_SetPeriod(_hCheckTimer, 500);
		GUI_TIMER_Restart(_hCheckTimer);
	}
}
static void _cbWifiDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_WifiDialogInit(pMsg->hWin);
			WirelessInit();
			_CheckWifiConnectStatusTimer(pMsg->hWin);
			SetScanResultCallback(_WifiScanResult_cb);
		return;
		case WM_DELETE:
			_hWifi = WM_HWIN_NULL;
			_hCheckTimer = WM_HMEM_NULL;
			SetScanResultCallback(NULL);
			GUI_Debug("To delete page wifi\n");
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_WIFI_SWITCH:
						if(0 == CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_WIFI_SWITCH))){
							WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_WIFI_LIST));
							SetWifiFunctionStatus(WIFI_FUNC_CLOSE);
						}else{
							PageWifiToRescanList();
							SetWifiFunctionStatus(WIFI_FUNC_OPEN);
							WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_WIFI_PROGBAR));
							//WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_WIFI_LIST));
						}
					break;
					case ID_WIFI_LIST:
					{
						const char *pSelectSSID;
						WifiListItemInfo ItemInfo;
						LISTVIEW_GetSelItemInfo(WM_GetDialogItem(pMsg->hWin, ID_WIFI_LIST), &ItemInfo);
						pSelectSSID = (const char *)GUI_ALLOC_h2p(ItemInfo.hSSID);
						if(WIFI_CONNECTED == GetWifiConnectStatus()){
							if(0 == GUI_strcmp(pSelectSSID, GetWifiConnectedSSID())){
								return;
							}
						}
						GUI_Debug("Sel ssid %s\n", pSelectSSID);
						PageWifiPasswordCreate(pMsg->hWin, pSelectSSID, ItemInfo.FlagEncry);
					}
					break;
				}
			}
		break;
		case ID_MSG_QUEUE_ADD_ITEM:
			if(pMsg->Data.p){
				APInfo *pInfo;
				pInfo = (APInfo *)pMsg->Data.p;
				WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_WIFI_PROGBAR));
				_AddOneItemToListview(WM_GetDialogItem(pMsg->hWin, ID_WIFI_LIST), pInfo);
			}
		break;
		case ID_MSG_TO_CONNECT_NEW_AP:
			GUI_Debug("To connect new ap\n");
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}
WM_HWIN PageWifiCreate(WM_HWIN hParent)
{
	if(WM_HWIN_NULL == _hWifi){
		_hWifi = GUI_CreateDialogBox(_aDialogWifiCreate, GUI_COUNTOF(_aDialogWifiCreate), _cbWifiDialog, hParent, 0, 0);
		GUI_Debug("_hWifi:%d\n", _hWifi);
	}
	return _hWifi;
}
WM_HWIN PageWifiGetHander(void)
{
	return _hWifi;
}
void PageWifiToRescanList(void)
{
	if(WIFI_FUNC_OPEN == GetWifiFunctionStatus()){
		_FlagNewScan = 1;
		if(WM_HWIN_NULL != PageWifiPasswordGetHander()){
			WM_DeleteWindow(PageWifiPasswordGetHander());
		}
		StartScanWifiList();
	}
}
