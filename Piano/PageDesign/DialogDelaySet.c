/*
 * DialogSetting.c
 *
 *  Created on: 2018年9月20日
 *      Author: Administrator
 */

#include "DialogDelaySet.h"


#define ID_WINDOW_DELAY_SET 			(ID_PAGE_DELAY_SET_BASE + 0)
#define ID_DELAY_TEXT					(ID_PAGE_DELAY_SET_BASE + 1)
#define ID_DELAY_SWITCH					(ID_PAGE_DELAY_SET_BASE + 2)
#define ID_DELAY_LINE_H1				(ID_PAGE_DELAY_SET_BASE + 3)
#define ID_DELAY_LINE_H2				(ID_PAGE_DELAY_SET_BASE + 4)
#define ID_DELAY_LINE_V					(ID_PAGE_DELAY_SET_BASE + 5)
#define ID_DELAY_PICKER					(ID_PAGE_DELAY_SET_BASE + 6)
#define ID_DELAY_BTN_CANLE				(ID_PAGE_DELAY_SET_BASE + 7)
#define ID_DELAY_BTN_CONFIRM			(ID_PAGE_DELAY_SET_BASE + 8)

static const GUI_WIDGET_CREATE_INFO _aDialogDelaySetCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_DELAY_SET, 0, 0, DEF_DIALOG_WIDTH, DEF_DIALOG_HEIGHT, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"delay text",			ID_DELAY_TEXT, 0, 0, 140, 50, 0, 0x0, 0},
	{ CHECKBOX_CreateIndirect, 	"delay switch",			ID_DELAY_SWITCH, 0, 0, 100, 50, WM_SF_HASTRANS, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "delay line h1",		ID_DELAY_LINE_H1, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "delay line h2",		ID_DELAY_LINE_H2, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "delay line v",			ID_DELAY_LINE_V, 0, 0, 2, 40, 0, 0x0, 0},
	{ Picker_CreateIndirect, 	"delay picker",			ID_DELAY_PICKER, 0, 0, 150, 240, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"delay cancle",			ID_DELAY_BTN_CANLE, 0, 0, 198, 50, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"delay confirm",		ID_DELAY_BTN_CONFIRM, 0, 0, 198, 50, 0, 0x0, 0},
};

static WM_HWIN _hDelaySet = WM_HMEM_NULL;
static void _DelayDialogInit(WM_HWIN hParent)
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
	//延时关机text
	hItem = WM_GetDialogItem(hParent, ID_DELAY_TEXT);
	TEXT_SetText(hItem, "延时关机");
	TEXT_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	TEXT_SetTextColor(hItem,GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_TOP, 20, 0);
	hBase = hItem;
	//开关按钮
	hItem = WM_GetDialogItem(hParent, ID_DELAY_SWITCH);
	/*if(DELAY_OPEN == Setting_GetDelayCloseStatus()){
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_open);
	}else{
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_close);
	}*/
	CHECKBOX_SetImage(hItem, &bmbtn_close, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmbtn_open, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	if(DELAY_OPEN == Setting_GetDelayCloseStatus()){
		CHECKBOX_SetState(hItem, 1);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, 0, 0);
	//上方分割线
	hItem = WM_GetDialogItem(hParent, ID_DELAY_LINE_H1);
	IMAGEVIEW_SetBkColor(hItem, 0xfff4f4f4);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	//picker
	hItem = WM_GetDialogItem(hParent, ID_DELAY_PICKER);
	WM_SetHasTrans(hItem);
	Picker_SetMaxValue(hItem, 99);
	Picker_SetMinValue(hItem, 0);
	Picker_SetFontColor(hItem, GUI_BLACK, GUI_GRAY, GUI_GRAY);
	if(DELAY_CLOSE == Setting_GetDelayCloseStatus()){
		WM_DisableWindow(hItem);
	}else{
		Picker_SetValue(hItem, Setting_GetDelayCloseCnt()/60);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	//取消按钮
	hItem = WM_GetDialogItem(hParent, ID_DELAY_BTN_CANLE);
	BUTTON_SetText(hItem, "取消");
	BUTTON_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	BUTTON_SetTextColor(hItem, 0, GUI_BLACK);
	BUTTON_SetTextColor(hItem, 1, GUI_BLUE);
	BUTTON_EnableNewStyle(hItem);
	BUTTON_SetPressNewStyle(hItem, &BtnStyle);
	BUTTON_SetRelNewStyle(hItem, &BtnStyle);
	WM_SetHasTrans(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_BOTTOM, 0, 0);
	hBase = hItem;
	//确定按钮
	hItem = WM_GetDialogItem(hParent, ID_DELAY_BTN_CONFIRM);
	BUTTON_SetText(hItem, "确定");
	BUTTON_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	BUTTON_SetTextColor(hItem, 0, GUI_BLACK);
	BUTTON_SetTextColor(hItem, 1, GUI_BLUE);
	BUTTON_EnableNewStyle(hItem);
	BUTTON_SetPressNewStyle(hItem, &BtnStyle);
	BUTTON_SetRelNewStyle(hItem, &BtnStyle);
	WM_SetHasTrans(hItem);
	if(DELAY_CLOSE == Setting_GetDelayCloseStatus()){
		WM_DisableWindow(hItem);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, 0, 0);

	//下方分割线
	hItem = WM_GetDialogItem(hParent, ID_DELAY_LINE_H2);
	IMAGEVIEW_SetBkColor(hItem, 0xffafafaf); //0xfff4f4f4
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_ABOVE_TOP, 0, 0);
	//中间竖线分割线
	hItem = WM_GetDialogItem(hParent, ID_DELAY_LINE_V);
	IMAGEVIEW_SetBkColor(hItem, 0xff8f8f8f); //0xfff4f4f4
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_V_CENTER, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, -5);
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);

	WM_ShowWindowAndChild(hParent);
}

static void _cbDelaySetDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_DelayDialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hDelaySet = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_DELAY_SWITCH:
						if(CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_DELAY_SWITCH))){
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_DELAY_PICKER));
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_DELAY_BTN_CONFIRM));
							Setting_SetDelayCloseStatus(DELAY_OPEN);
						}else{
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_DELAY_PICKER));
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_DELAY_BTN_CONFIRM));
							Setting_SetDelayCloseStatus(DELAY_CLOSE);
						}
					break;
					case ID_DELAY_BTN_CANLE:
						WM_DeleteWindow(pMsg->hWin);
					break;
					case ID_DELAY_BTN_CONFIRM:
					{
						I32 Value = Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_DELAY_PICKER));
						if(0 != Value){
							Setting_SetDelayCloseCnt(Value * 60);
							Setting_SetDelayCloseStatus(DELAY_START);
						}else{
							Setting_SetDelayCloseStatus(DELAY_CLOSE);
						}
					}
						WM_DeleteWindow(pMsg->hWin);
					break;
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN DialogDelaySetCreate(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hDelaySet){
		_hDelaySet = GUI_CreateDialogBox(_aDialogDelaySetCreate, GUI_COUNTOF(_aDialogDelaySetCreate), _cbDelaySetDialog, hParent, 0, 0);
		GUI_Debug("_hDelaySet:%d\n", _hDelaySet);
	}
	return _hDelaySet;
}
