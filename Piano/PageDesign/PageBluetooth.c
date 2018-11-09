/*
 * PageBluetooth.c
 *
 *  Created on: 2018年11月9日
 *      Author: Administrator
 */
#include "PageBluetooth.h"
#include "Wireless.h"

#define ID_WINDOW_BLUETOOTH 		(ID_PAGE_BLUETOOTH_BASE + 0)
#define ID_BLUETOOTH_TEXT_NOTICE	(ID_PAGE_BLUETOOTH_BASE + 1)
#define ID_BLUETOOTH_SWITCH			(ID_PAGE_BLUETOOTH_BASE + 2)
#define ID_BLUETOOTH_LIST			(ID_PAGE_BLUETOOTH_BASE + 3)
#define ID_BLUETOOTH_LINE_H			(ID_PAGE_BLUETOOTH_BASE + 4)
#define ID_BLUETOOTH_PROGBAR		(ID_PAGE_BLUETOOTH_BASE + 5)

typedef struct
{
	const GUI_BITMAP *bmConnectIcon;
	const GUI_BITMAP *bmBleIcon;
	WM_HMEM hName;
	WM_HMEM hMac;
} BleListItemInfo;

static WM_HWIN _hBluetooth = WM_HWIN_NULL;
static GUI_TIMER_HANDLE _hCheckTimer = WM_HMEM_NULL;
static I32 _SelectItemIndex = -1;
static U8 _BluetoothConnectSave = BLUETOOTH_DISCONNECTED;
static const GUI_WIDGET_CREATE_INFO _aDialogBluetoothCreate[] =
{
		{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_BLUETOOTH, 251, 0, 500, DEF_DIALOG_HEIGHT, 0, 0x0,0},
		{ TEXT_CreateIndirect,		"Text notice", 			ID_BLUETOOTH_TEXT_NOTICE, 0, 0, 150, 50, 0, 0, 0},
		{ CHECKBOX_CreateIndirect,	"switch", 				ID_BLUETOOTH_SWITCH, 0, 0, 100, 50, 0, 0, 0},
		{ LISTVIEW_CreateIndirect,  "list",					ID_BLUETOOTH_LIST, 0, 0, 500, 320, 0, 0, 0},
		{ IMAGEVIEW_CreateIndirect,  "view line",			ID_BLUETOOTH_LINE_H, 0, 0, 500, 1, 0, 0, 0},
		{ PROGBAR_CreateIndirect,	"progbar", 				ID_BLUETOOTH_PROGBAR, 0, 0, 30, 30, 0, 0, 0},
};
/*
 * Draw bluetooth item
 * */
static U8 _BleListItemDraw(const LISTVIEW_DrawItemInfo *pInfo)
{
	U16 BitmapHeight = 0, BitmapWidth = 0;
	U16 RectWidth, RectHeight;
	I32 DrawPosX = 0, DrawPosY = 0;
	BleListItemInfo *pItemInfo;
	pItemInfo = (BleListItemInfo *)pInfo->pItem;
	RectWidth = WM_GetRectSizeX(pInfo->Rect);
	RectHeight = WM_GetRectSizeY(pInfo->Rect);
	if(pItemInfo->bmConnectIcon){
		BitmapHeight = pItemInfo->bmConnectIcon->YSize;
		BitmapWidth = pItemInfo->bmConnectIcon->XSize;
		DrawPosY = (RectHeight - BitmapHeight)/2 + pInfo->Rect.y0;
		DrawPosX += pInfo->Rect.x0;
		GUI_DrawBitmap(pItemInfo->bmConnectIcon, DrawPosX, DrawPosY);
	}
	if(pItemInfo->hName){
		char *pText;
		GUI_RECT DrawRect;
		pText = (char *)GUI_ALLOC_h2p(pItemInfo->hName);
		DrawRect = pInfo->Rect;
		DrawRect.x0 = 32 + 10;
		GUI_DispStringInRect(pText, &DrawRect, GUI_TA_TOP);
	}
	if(pItemInfo->hMac){
		char *pText;
		GUI_RECT DrawRect;
		pText = (char *)GUI_ALLOC_h2p(pItemInfo->hMac);
		DrawRect = pInfo->Rect;
		DrawRect.x0 = 32 + 10;
		DrawRect.y0 += GUI_GetFontSizeY();
		GUI_DispStringInRect(pText, &DrawRect, GUI_TA_TOP);
	}
	if(pItemInfo->bmBleIcon){
		BitmapHeight = pItemInfo->bmBleIcon->YSize;
		BitmapWidth = pItemInfo->bmBleIcon->XSize;
		DrawPosY = (RectHeight - BitmapHeight)/2 + pInfo->Rect.y0;
		DrawPosX = RectWidth - BitmapWidth - 20 + pInfo->Rect.x0;
		GUI_DrawBitmap(pItemInfo->bmBleIcon, DrawPosX, DrawPosY);
	}
	GUI_SetColor(GUI_GRAY);
	GUI_DrawHLine(pInfo->Rect.y1 - 1, pInfo->Rect.x0, pInfo->Rect.x1);
	return 1;
}
static U8 _BleListItemDelete(void *pItem)
{
	BleListItemInfo *pItemInfo;
	pItemInfo = (BleListItemInfo *)pItem;
	GUI_ALLOC_Free(pItemInfo->hName);
	GUI_ALLOC_Free(pItemInfo->hMac);
	pItemInfo->hName = WM_HMEM_NULL;
	pItemInfo->hMac = WM_HMEM_NULL;
	return 1;
}
static U8 _BleScanResult_cb(const BleInfo *pInfo)
{
	WM_QUEUE_PARA Para;
	Para.QueueId = ID_MSG_QUEUE_ADD_ITEM;
	Para.hWin = WM_GetDialogItem(_hBluetooth, ID_BLUETOOTH_LIST);
	Para.pData = (void *)pInfo;
	Para.DataLen = sizeof(BleInfo);
	WM_PostMessageToQueue(&Para);
	return 1;
}

static void _AddOneItemToListview(WM_HWIN hWin, const BleInfo *pInfo, U8 Flag)
{
	char *pText;

	BleListItemInfo ItemInfo = {0};
	WM_ShowWindow(hWin);

	ItemInfo.hName = GUI_ALLOC_AllocZero(GUI_strlen(pInfo->Name) + 1);
	pText = (char *)GUI_ALLOC_h2p(ItemInfo.hName);
	GUI_strcpy(pText, pInfo->Name);
	ItemInfo.hMac = GUI_ALLOC_AllocZero(GUI_strlen(pInfo->MacAddress) + 1);
	pText = (char *)GUI_ALLOC_h2p(ItemInfo.hMac);
	GUI_strcpy(pText, pInfo->MacAddress);
	if(1 == Flag){
		ItemInfo.bmConnectIcon = &bmselect_icon;
	}else{
		ItemInfo.bmConnectIcon = NULL;
	}
	LISTVIEW_AddExternItem(hWin, (void *)&ItemInfo, sizeof(BleListItemInfo));
}
static void _BluetoothDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	GUI_FullRectStyle BgStyle = {
			.MainColor = GUI_CYAN,
			.GradColor = GUI_CYAN,
			.Radius = 0,
			.Opacity = 0xff,
	};
	_BluetoothConnectSave = BluetoothGetConnectStauts();
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_V_CENTRE, 0, 6);
	WINDOW_SetBkColor(hParent, &BgStyle);
	//text
	hItem = WM_GetDialogItem(hParent, ID_BLUETOOTH_TEXT_NOTICE);
	TEXT_SetText(hItem, "选择网络:");
	TEXT_SetFont(hItem, &GUI_FontWifiPageNotice);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	//WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	hBase = hItem;

	//switch
	hItem = WM_GetDialogItem(hParent, ID_BLUETOOTH_SWITCH);
	CHECKBOX_SetImage(hItem, &bmbtn_close, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmbtn_open, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	if(BLUETOOTH_FUNC_OPEN == GetBluetoothFunctionStatus()){
		CHECKBOX_SetState(hItem, 1);
	}
	WM_SetHasTrans(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, 0, 0);
	hBase = hItem;
	//line h
	hItem = WM_GetDialogItem(hParent, ID_BLUETOOTH_LINE_H);
	IMAGEVIEW_SetBkColor(hItem, GUI_GRAY);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	//progbar
	hItem = WM_GetDialogItem(hParent, ID_BLUETOOTH_PROGBAR);
	PROGBAR_SetStyle(hItem, PROGBAR_STYLE_CIRCLE);
	WM_SetHasTrans(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 15);
	//listview
	hItem = WM_GetDialogItem(hParent, ID_BLUETOOTH_LIST);
	LISTVIEW_SetItemYSize(hItem, 64);
	LISTVIEW_SetDrawItemMethod(hItem, _BleListItemDraw, _BleListItemDelete);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 1);
	GUI_Debug("hListView %d\n", hItem);

	WM_ShowWindowAndChild(hParent);
	LISTVIEW_HideScrollbar(hItem);
	if(WIFI_FUNC_CLOSE == GetWifiFunctionStatus()){
		WM_HideWindow(WM_GetDialogItem(hParent, ID_BLUETOOTH_PROGBAR));
	}

	if(0 == CHECKBOX_IsChecked(WM_GetDialogItem(hParent, ID_BLUETOOTH_SWITCH))){
		WM_HideWindow(WM_GetDialogItem(hParent, ID_BLUETOOTH_LIST));
	}else{
		if(BLUETOOTH_CONNECTED == BluetoothGetConnectStauts()){
			BleInfo ConnectedInfo;
			BluetoothGetConnectInfo(ConnectedInfo.Name, ConnectedInfo.MacAddress);
			_AddOneItemToListview(WM_GetDialogItem(hParent, ID_BLUETOOTH_LIST), &ConnectedInfo, 1);
		}else{
			WM_ShowWindow(WM_GetDialogItem(hParent, ID_BLUETOOTH_PROGBAR));
			SetBleStartScan();
		}
	}
}

static void _cbCheckStatusTimer(GUI_TIMER_MESSAGE *pContext)
{
	if(_BluetoothConnectSave != BluetoothGetConnectStauts()){
		if(BLUETOOTH_CONNECTED == _BluetoothConnectSave){
			GUI_Debug("Before bluetooth is connected, now is disconnected\n");
		}else{
			BleInfo ConnectedInfo;
			ListView_DeleteItemByIndex(WM_GetDialogItem(pContext->Context, ID_BLUETOOTH_LIST), _SelectItemIndex);
			BluetoothGetConnectInfo(ConnectedInfo.Name, ConnectedInfo.MacAddress);
			_AddOneItemToListview(WM_GetDialogItem(pContext->Context, ID_BLUETOOTH_LIST), &ConnectedInfo, 1);
			GUI_Debug("Before bluetooth is disconnected, now is connected\n");
			WM_HideWindow(WM_GetDialogItem(pContext->Context, ID_BLUETOOTH_PROGBAR));
		}
		_BluetoothConnectSave = BluetoothGetConnectStauts();
	}
	GUI_TIMER_Restart(_hCheckTimer);
}
static void _CheckBleConnectStatusTimer(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hCheckTimer){
		_hCheckTimer = GUI_TIMER_Create(_cbCheckStatusTimer, 0, hParent, 0);
		GUI_TIMER_SetPeriod(_hCheckTimer, 500);
		GUI_TIMER_Restart(_hCheckTimer);
	}
}

static void _cbBluetoothDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_BluetoothDialogInit(pMsg->hWin);
			_CheckBleConnectStatusTimer(pMsg->hWin);
			SetBleScanResultCallback(_BleScanResult_cb);
		return;
		case WM_DELETE:
			_hBluetooth = WM_HWIN_NULL;
			SetBleScanResultCallback(NULL);
			GUI_Debug("To delete page bluetooth\n");
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_BLUETOOTH_SWITCH:
						if(0 == CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_SWITCH))){
							WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_LIST));
							WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_PROGBAR));
							SetBluetoothFunctionStatus(BLUETOOTH_FUNC_CLOSE);
						}else{
							SetBluetoothFunctionStatus(BLUETOOTH_FUNC_OPEN);
							WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_PROGBAR));
							SetBleStartScan();
						}
					break;
					case ID_BLUETOOTH_LIST:
					{
						const char *pSelectName;
						const char *pSelectMac;
						BleListItemInfo ItemInfo;
						_SelectItemIndex = LISTVIEW_GetSel(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_LIST));
						GUI_Debug("_SelectItemIndex:%d\n", _SelectItemIndex);
						LISTVIEW_GetSelItemInfo(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_LIST), &ItemInfo);
						pSelectName = (const char *)GUI_ALLOC_h2p(ItemInfo.hName);
						pSelectMac = (const char *)GUI_ALLOC_h2p(ItemInfo.hMac);
						if(BLUETOOTH_CONNECTED == BluetoothGetConnectStauts()){
							BleInfo ConnectedInfo;
							BluetoothGetConnectInfo(ConnectedInfo.Name, ConnectedInfo.MacAddress);
							if(0 == GUI_strcmp(pSelectMac, ConnectedInfo.MacAddress)){
								GUI_Debug("Is same with before\n");
								return;
							}
						}
						GUI_Debug("Select Name:%s, Mac:%s\n", pSelectName, pSelectMac);
						BluetoothStartToConnect(pSelectName, pSelectMac);
						TOTAST_StaticShow("正在连接...", &GUI_FontWifiPageNotice);
						WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_PROGBAR));
					}
					break;
				}
			}
		break;
		case ID_MSG_QUEUE_ADD_ITEM:
			if(pMsg->Data.p){
				BleInfo *pInfo;
				pInfo = (BleInfo *)pMsg->Data.p;
				WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_PROGBAR));
				_AddOneItemToListview(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_LIST), pInfo, 0);
			}
		break;
		case ID_MSG_TO_SCAN_AP:
			/*if(_PageWifiToRescanList()){
				WM_ShowWindow(WM_GetDialogItem(pMsg->hWin, ID_BLUETOOTH_PROGBAR));
			}*/
			break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN PageBluetoothCreate(WM_HWIN hParent)
{
	if(WM_HWIN_NULL == _hBluetooth){
		_hBluetooth = GUI_CreateDialogBox(_aDialogBluetoothCreate, GUI_COUNTOF(_aDialogBluetoothCreate), _cbBluetoothDialog, hParent, 0, 0);
	}
	return _hBluetooth;
}

WM_HWIN PageBluetoothGetHander(void)
{
	return _hBluetooth;
}
