/*
 * PageLightSet.c
 *
 *  Created on: 2018年9月27日
 *      Author: Administrator
 */


#include "DialogWifiPassword.h"
#include "Wireless.h"

#define ID_WINDOW_WIFI_PASSWORD_SET 				(ID_PAGE_WIFI_PASSWORD_BASSE + 0)
#define ID_WIFI_PASSWORD_TEXT_NAME					(ID_PAGE_WIFI_PASSWORD_BASSE + 1)
#define ID_WIFI_PASSWORD_TEXT_SSID					(ID_PAGE_WIFI_PASSWORD_BASSE + 2)
#define ID_WIFI_PASSWORD_TEXT_PASS					(ID_PAGE_WIFI_PASSWORD_BASSE + 3)
#define ID_WIFI_PASSWORD_EDIT						(ID_PAGE_WIFI_PASSWORD_BASSE + 4)
#define ID_WIFI_PASSWORD_CANCLE						(ID_PAGE_WIFI_PASSWORD_BASSE + 5)
#define ID_WIFI_PASSWORD_CONFIRM					(ID_PAGE_WIFI_PASSWORD_BASSE + 6)

static const GUI_WIDGET_CREATE_INFO _aDialogWifiPasswordCreate[] =
{
		{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_WIFI_PASSWORD_SET, 0, 0, 400, 230, 0, 0x0,0},
		{ TEXT_CreateIndirect,		"name", 				ID_WIFI_PASSWORD_TEXT_NAME, 0, 0, 80, 50, 0, 0, 0},
		{ TEXT_CreateIndirect,		"ssid", 				ID_WIFI_PASSWORD_TEXT_SSID, 0, 0, 240, 50, 0, 0, 0},
		{ TEXT_CreateIndirect,		"pass", 				ID_WIFI_PASSWORD_TEXT_PASS, 0, 0, 80, 50, 0, 0, 0},
		{ EDIT_CreateIndirect,		"password", 			ID_WIFI_PASSWORD_EDIT, 0, 0, 240, 50, 0, 0, 0},
		{ BUTTON_CreateIndirect,	"cancle", 				ID_WIFI_PASSWORD_CANCLE, 0, 0, 100, 60, 0, 0, 0},
		{ BUTTON_CreateIndirect,	"confirm", 				ID_WIFI_PASSWORD_CONFIRM, 0, 0, 100, 60, 0, 0, 0},
};
static WM_HWIN _hWifiPassword = WM_HMEM_NULL;
static U8 _SaveEncry = 0;
static void _WifiPasswordDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	GUI_FullRectStyle BgStyle = {
			.MainColor = GUI_RED,
			.GradColor = GUI_GREEN,
			.Radius = 3,
			.Opacity = 0xff,
	};
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	WINDOW_SetBkColor(hParent, &BgStyle);
	//名称
	hItem = WM_GetDialogItem(hParent, ID_WIFI_PASSWORD_TEXT_NAME);
	TEXT_SetText(hItem, "SSID:");
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_TOP, 10, 10);
	hBase = hItem;
	//所选的名称
	hItem = WM_GetDialogItem(hParent, ID_WIFI_PASSWORD_TEXT_SSID);
	TEXT_SetText(hItem, "secomid");
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 10);
	//密码
	hItem = WM_GetDialogItem(hParent, ID_WIFI_PASSWORD_TEXT_PASS);
	TEXT_SetText(hItem, "PASS:");
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 10, 0);
	hBase = hItem;
	//密码edit
	hItem = WM_GetDialogItem(hParent, ID_WIFI_PASSWORD_EDIT);
	EDIT_SetMaxLen(hItem, 64);
	EDIT_SetTextAlign(hItem, EDIT_CF_VCENTER);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);

	hItem = WM_GetDialogItem(hParent, ID_WIFI_PASSWORD_CANCLE);
	BUTTON_SetText(hItem, "Cancle");
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, -80, 0);

	hItem = WM_GetDialogItem(hParent, ID_WIFI_PASSWORD_CONFIRM);
	BUTTON_SetText(hItem, "Confirm");
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 80, 0);

	WM_ShowWindowAndChild(hParent);
}

static void _cbWifiPasswordDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_WifiPasswordDialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hWifiPassword = WM_HMEM_NULL;
			SimpleKeyboardDelete();
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_WIFI_PASSWORD_EDIT:
						SimpleKeyboardShow();
						WM_SetAlignParent(pMsg->hWin, OBJ_ALIGN_PARENT_TOP_CENTRE, 0, 0);
					break;
					case ID_WIFI_PASSWORD_CANCLE:
						WM_DeleteWindow(pMsg->hWin);
					break;
					case ID_WIFI_PASSWORD_CONFIRM:
					{
						char pPassword[64];
						const char *pSSID;
						EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_WIFI_PASSWORD_EDIT), pPassword, 64);
						if(GUI_strlen(pPassword) < 8){
							TOTAST_StaticShow("Password length less than 8");
							return;
						}
						pSSID = TEXT_GetText(WM_GetDialogItem(pMsg->hWin, ID_WIFI_PASSWORD_TEXT_SSID));
						StartConnectToAp(pSSID, pPassword, _SaveEncry);
						WM_SendMessageNoPara(WM_GetParent(pMsg->hWin), ID_MSG_TO_CONNECT_NEW_AP);
						WM_DeleteWindow(pMsg->hWin);
					}
					break;
				}
			}
		break;
		case ID_MSG_NOTIFY_SET_SSID:
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_WIFI_PASSWORD_TEXT_SSID), (const char *)pMsg->Data.p);
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN PageWifiPasswordCreate(WM_HWIN hParent, const char *pSelectSSID, U8 Encry)
{
	WM_MESSAGE Msg;
	if(WM_HMEM_NULL == _hWifiPassword){
		_hWifiPassword = GUI_CreateDialogBox(_aDialogWifiPasswordCreate, GUI_COUNTOF(_aDialogWifiPasswordCreate), _cbWifiPasswordDialog, hParent, 0, 0);
		GUI_Debug("_hWifiPassword:%d\n", _hWifiPassword);
	}
	if(pSelectSSID){
		Msg.hWin = _hWifiPassword;
		Msg.MsgId = ID_MSG_NOTIFY_SET_SSID;
		Msg.Data.p = (void *)pSelectSSID;
		WM_SendMessage(_hWifiPassword, &Msg);
	}
	_SaveEncry = Encry;
	return _hWifiPassword;
}

WM_HWIN PageWifiPasswordGetHander(void)
{
	return _hWifiPassword;
}
