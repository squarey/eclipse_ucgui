/*
 * DialogSetting.c
 *
 *  Created on: 2018年9月20日
 *      Author: Administrator
 */

#include "DialogCookerTime.h"


#define ID_WINDOW_COOKER_TIME 			(ID_PAGE_COOKER_TIME_BASE + 0)
#define ID_COOKER_TEXT					(ID_PAGE_COOKER_TIME_BASE + 1)
#define ID_COOKER_SWITCH					(ID_PAGE_COOKER_TIME_BASE + 2)
#define ID_COOKER_LINE_H1				(ID_PAGE_COOKER_TIME_BASE + 3)
#define ID_COOKER_LINE_H2				(ID_PAGE_COOKER_TIME_BASE + 4)
#define ID_COOKER_LINE_V					(ID_PAGE_COOKER_TIME_BASE + 5)
#define ID_COOKER_PICKER					(ID_PAGE_COOKER_TIME_BASE + 6)
#define ID_COOKER_BTN_CANLE				(ID_PAGE_COOKER_TIME_BASE + 7)
#define ID_COOKER_BTN_CONFIRM			(ID_PAGE_COOKER_TIME_BASE + 8)
#define ID_COOKER_SELECT			(ID_PAGE_COOKER_TIME_BASE + 9)
#define ID_COOKER_TIMER_UNIT			(ID_PAGE_COOKER_TIME_BASE + 10)

static const GUI_WIDGET_CREATE_INFO _aDialogCookerTimeCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_COOKER_TIME, 0, 0, DEF_DIALOG_WIDTH, DEF_DIALOG_HEIGHT, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"cooker text",			ID_COOKER_TEXT, 0, 0, 130, 50, 0, 0x0, 0},
	{ CHECKBOX_CreateIndirect, 	"cooker switch",		ID_COOKER_SWITCH, 0, 0, 100, 50, WM_SF_HASTRANS, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "cooker line h1",		ID_COOKER_LINE_H1, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ CHECKBOX_CreateIndirect, 	"cooker select",		ID_COOKER_SELECT, 0, 0, 115, 50, WM_SF_HASTRANS, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "cooker line h2",		ID_COOKER_LINE_H2, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "cooker line v",		ID_COOKER_LINE_V, 0, 0, 2, 40, 0, 0x0, 0},
	{ Picker_CreateIndirect, 	"cooker picker",		ID_COOKER_PICKER, 0, 0, 150, 240, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"cooker cancle",		ID_COOKER_BTN_CANLE, 0, 0, 198, 50, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"cooker confirm",		ID_COOKER_BTN_CONFIRM, 0, 0, 198, 50, 0, 0x0, 0},
	{ TEXT_CreateIndirect, 		"timer unit",			ID_COOKER_TIMER_UNIT, 0, 0, 50, 30, 0, 0x0, 0},
};

static WM_HWIN _hCookerTime = WM_HMEM_NULL;
static void _CookerSetDialogInit(WM_HWIN hParent)
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
	hItem = WM_GetDialogItem(hParent, ID_COOKER_TEXT);
	TEXT_SetText(hItem, "计时器");
	TEXT_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	TEXT_SetTextColor(hItem, GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_TOP, 20, 0);
	hBase = hItem;
	//开关按钮
	hItem = WM_GetDialogItem(hParent, ID_COOKER_SWITCH);
	/*if(COOKER_OPEN == Setting_GetDelayCloseStatus()){
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_open);
	}else{
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_close);
	}*/
	CHECKBOX_SetImage(hItem, &bmbtn_close, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmbtn_open, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	if(COOKER_TIMER_CLOSE != Setting_GetCookerTimerStatus()){
		CHECKBOX_SetState(hItem, 1);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, 0, 0);
	//上方分割线
	hItem = WM_GetDialogItem(hParent, ID_COOKER_LINE_H1);
	IMAGEVIEW_SetBkColor(hItem, 0xfff4f4f4);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	hBase = hItem;
	//灶台选择按钮
	hItem = WM_GetDialogItem(hParent, ID_COOKER_SELECT);
	CHECKBOX_SetImage(hItem, &bmcooker_left, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmcooker_right, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetImage(hItem, &bmcooker_left, CHECKBOX_BI_INACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmcooker_left, CHECKBOX_BI_INACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	if(COOKER_TIMER_CLOSE == Setting_GetCookerTimerStatus()){
		WM_DisableWindow(hItem);
	}
	if(COOKER_TIMER_START == Setting_GetCookerTimerLeftStatus()){
		CHECKBOX_SetState(hItem, 0);
	}else if(COOKER_TIMER_START == Setting_GetCookerTimerRightStatus()){
		CHECKBOX_SetState(hItem, 1);
	}
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 10, 10);
	//picker
	hItem = WM_GetDialogItem(hParent, ID_COOKER_PICKER);
	WM_SetHasTrans(hItem);
	Picker_SetMaxValue(hItem, 99);
	Picker_SetMinValue(hItem, 0);
	Picker_SetFontColor(hItem, GUI_BLACK, GUI_GRAY, GUI_GRAY);

	Picker_SetValue(hItem, Setting_GetCookerTimerLeftCnt()/60);
	if(COOKER_TIMER_CLOSE == Setting_GetCookerTimerStatus()){
		WM_DisableWindow(hItem);
	}else{
		if(COOKER_TIMER_START == Setting_GetCookerTimerLeftStatus()){
			Picker_SetValue(hItem, Setting_GetCookerTimerLeftCnt()/60);
		}else if(COOKER_TIMER_START == Setting_GetCookerTimerRightStatus()){
			Picker_SetValue(hItem, Setting_GetCookerTimerRightCnt()/60);
		}
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	//取消按钮
	hItem = WM_GetDialogItem(hParent, ID_COOKER_BTN_CANLE);
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
	hItem = WM_GetDialogItem(hParent, ID_COOKER_BTN_CONFIRM);
	BUTTON_SetText(hItem, "确定");
	BUTTON_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	BUTTON_SetTextColor(hItem, 0, GUI_BLACK);
	BUTTON_SetTextColor(hItem, 1, GUI_BLUE);
	BUTTON_EnableNewStyle(hItem);
	BUTTON_SetPressNewStyle(hItem, &BtnStyle);
	BUTTON_SetRelNewStyle(hItem, &BtnStyle);
	WM_SetHasTrans(hItem);
	if(COOKER_TIMER_CLOSE == Setting_GetCookerTimerStatus()){
		WM_DisableWindow(hItem);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, 0, 0);

	//下方分割线
	hItem = WM_GetDialogItem(hParent, ID_COOKER_LINE_H2);
	IMAGEVIEW_SetBkColor(hItem, 0xffafafaf); //0xfff4f4f4
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_ABOVE_TOP, 0, 0);
	//中间竖线分割线
	hItem = WM_GetDialogItem(hParent, ID_COOKER_LINE_V);
	IMAGEVIEW_SetBkColor(hItem, 0xff8f8f8f); //0xfff4f4f4
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_V_CENTER, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, -5);
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	//picker单位
	hItem = WM_GetDialogItem(hParent, ID_COOKER_TIMER_UNIT);
	if(COOKER_TIMER_CLOSE == Setting_GetCookerTimerStatus()){
		TEXT_SetTextColor(hItem, GUI_GRAY);
	}else{
		TEXT_SetTextColor(hItem, GUI_BLACK);
	}
	TEXT_SetFont(hItem, &GUI_FontDialogYH24);
	TEXT_SetText(hItem, "分钟");
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_COOKER_PICKER), hItem, OBJ_ALIGN_BROTHER_CENTER, 70, 20);

	WM_ShowWindowAndChild(hParent);
}

static void _cbCookerTimeDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_CookerSetDialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hCookerTime = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_COOKER_SWITCH:
						if(CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_COOKER_SWITCH))){
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_COOKER_SELECT));
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER));
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_COOKER_BTN_CONFIRM));
							TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_COOKER_TIMER_UNIT), GUI_BLACK);
							Setting_SetCookerTimerStatus(COOKER_TIMER_OPEN);
						}else{
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_COOKER_SELECT));
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER));
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_COOKER_BTN_CONFIRM));
							TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_COOKER_TIMER_UNIT), GUI_GRAY);
							Setting_SetCookerTimerStatus(COOKER_TIMER_CLOSE);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_COOKER_SELECT:
						if(CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_COOKER_SELECT))){
							Setting_SetCookerTimerLeftCnt(Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER))*60);
							Picker_SetValue(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER),
									Setting_GetCookerTimerRightCnt()/60);
						}else{
							Setting_SetCookerTimerRightCnt(Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER))*60);
							Picker_SetValue(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER),
							Setting_GetCookerTimerLeftCnt()/60);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_COOKER_BTN_CANLE:
						WM_DeleteWindow(pMsg->hWin);
						HoodCom_SendTouchVoice();
					break;
					case ID_COOKER_BTN_CONFIRM:
						if(!CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_COOKER_SELECT))){
							Setting_SetCookerTimerLeftCnt(Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER))*60);
						}else{
							Setting_SetCookerTimerRightCnt(Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_COOKER_PICKER))*60);
						}
						if(0 != Setting_GetCookerTimerLeftCnt()){
							Setting_SetCookerTimerLeftStatus(COOKER_TIMER_START);
						}else{
							Setting_SetCookerTimerRightStatus(COOKER_TIMER_CLOSE);
						}
						if(0 != Setting_GetCookerTimerRightCnt()){
							Setting_SetCookerTimerRightStatus(COOKER_TIMER_START);
						}else{
							Setting_SetCookerTimerRightStatus(COOKER_TIMER_CLOSE);
						}
						WM_DeleteWindow(pMsg->hWin);
						HoodCom_SendTouchVoice();
					break;
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN DialogCookerTimeCreate(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hCookerTime){
		_hCookerTime = GUI_CreateDialogBox(_aDialogCookerTimeCreate, GUI_COUNTOF(_aDialogCookerTimeCreate), _cbCookerTimeDialog, hParent, 0, 0);
		GUI_Debug("_hCookerTime:%d\n", _hCookerTime);
	}
	return _hCookerTime;
}
