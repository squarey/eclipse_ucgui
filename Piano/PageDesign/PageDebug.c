/*
 * PageDebug.c
 *
 *  Created on: 2018年11月6日
 *      Author: Administrator
 */


#include "PageDebug.h"


#define ID_WINDOW_DEBUG				(ID_PAGE_DEBUG_BASE + 0)
#define ID_DEBUG_TEXT_RX1			(ID_PAGE_DEBUG_BASE + 1)
#define ID_DEBUG_TEXT_RX2			(ID_PAGE_DEBUG_BASE + 2)
#define ID_DEBUG_TEXT_TX1			(ID_PAGE_DEBUG_BASE + 3)
#define ID_DEBUG_TEXT_TX2			(ID_PAGE_DEBUG_BASE + 4)

#define ID_DEBUG_BTN_CLOSE			(ID_PAGE_DEBUG_BASE + 5)



static const GUI_WIDGET_CREATE_INFO _aWindowsDebugCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_DEBUG, 0, 0, DEF_DIALOG_WIDTH, DEF_DIALOG_HEIGHT, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"rx1",					ID_DEBUG_TEXT_RX1, 0, 0, 48, 32, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"rx2",					ID_DEBUG_TEXT_RX2, 0, 0, DEF_DIALOG_WIDTH - 48, 70, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"tx1",					ID_DEBUG_TEXT_TX1, 0, 0, 48, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"tx2",					ID_DEBUG_TEXT_TX2, 0, 0, DEF_DIALOG_WIDTH - 48, 70, 0, 0x0,0},
	{ BUTTON_CreateIndirect, 	"close",				ID_DEBUG_BTN_CLOSE, 0, 0, 80, 50, 0, 0x0,0},
};


static WM_HWIN _hDebugSet = WM_HMEM_NULL;
static GUI_TIMER_HANDLE _hTimer = WM_HMEM_NULL;
static void _DebugDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	GUI_FullRectStyle BtnStyle = {
			.MainColor = GUI_WHITE,
			.GradColor = GUI_GRAY,
			.Radius = 3,
			.Opacity = 0xff,
	};
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	WINDOW_SetBkColor(hParent, &BtnStyle);
	//rx1
	hItem = WM_GetDialogItem(hParent, ID_DEBUG_TEXT_RX1);
	TEXT_SetText(hItem, "RX:");
	TEXT_SetTextColor(hItem,GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_TOP);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_TOP, 20, 10);
	hBase = hItem;
	//rx2
	hItem = WM_GetDialogItem(hParent, ID_DEBUG_TEXT_RX2);
	TEXT_SetText(hItem, "---");
	TEXT_SetTextColor(hItem,GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_TOP);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 10);
	//tx1
	hItem = WM_GetDialogItem(hParent, ID_DEBUG_TEXT_TX1);
	TEXT_SetText(hItem, "TX:");
	TEXT_SetTextColor(hItem,GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_TOP);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 20, 50);
	//tx2
	hItem = WM_GetDialogItem(hParent, ID_DEBUG_TEXT_TX2);
	TEXT_SetText(hItem, "TX data");
	TEXT_SetTextColor(hItem,GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_TOP);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_DEBUG_TEXT_TX1), hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 50);

	//btn close
	hItem = WM_GetDialogItem(hParent, ID_DEBUG_BTN_CLOSE);
	BUTTON_SetText(hItem, "Close");
	BUTTON_SetTextColor(hItem, 0, GUI_BLACK);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, 0);

	WM_ShowWindowAndChild(hParent);
}
static void _RefreshTimer_cb(GUI_TIMER_MESSAGE *pContext)
{
	char StringBuffer[128] = "";
	char DataBuffer[32] = "";
	U32 Len = 0;
	U32 i = 0;
	Len = GetSerialPortReceivedData(DataBuffer, 32);
	for(i = 0; i < Len; i++){
		GUI_sprintf(StringBuffer, "%s%02x ", StringBuffer, DataBuffer[i]);
		if((i > 0) && (0 == i % 7)){
			GUI_sprintf(StringBuffer, "%s\n", StringBuffer);
		}
	}
	TEXT_SetText(WM_GetDialogItem(pContext->Context, ID_DEBUG_TEXT_RX2), StringBuffer);
}
static void _RefreshTimeInit(WM_HWIN hWin)
{
	if(WM_HMEM_NULL == _hTimer){
		_hTimer = GUI_TIMER_Create(_RefreshTimer_cb, WM_TIMER + 1, hWin, 0);
		GUI_TIMER_SetPeriod(_hTimer, 300);
		GUI_TIMER_Restart(_hTimer);
	}
}
static void _cbDebugDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_DebugDialogInit(pMsg->hWin);
			_RefreshTimeInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hDebugSet = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_DEBUG_BTN_CLOSE:
						WM_DeleteWindow(pMsg->hWin);
					break;
					default:
					break;
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN DialogDebugSetCreate(void)
{
	if(WM_HMEM_NULL == _hDebugSet){
		_hDebugSet = GUI_CreateDialogBox(_aWindowsDebugCreate, GUI_COUNTOF(_aWindowsDebugCreate), _cbDebugDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("_hDebugSet:%d\n", _hDebugSet);
	}
	return _hDebugSet;
}
