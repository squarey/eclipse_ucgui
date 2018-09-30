/*
 * DialogTimingAir.c
 *
 *  Created on: 2018年9月21日
 *      Author: Administrator
 */


/*
 * DialogSetting.c
 *
 *  Created on: 2018年9月20日
 *      Author: Administrator
 */

#include "DialogTimingAir.h"

#define ID_WINDOW_TIMING_AIR_SET 				(ID_PAGE_TIMING_AIR_BASE + 0)
#define ID_TIMING_AIR_TEXT						(ID_PAGE_TIMING_AIR_BASE + 1)
#define ID_TIMING_AIR_SWITCH					(ID_PAGE_TIMING_AIR_BASE + 2)
#define ID_TIMING_AIR_LINE_H1					(ID_PAGE_TIMING_AIR_BASE + 3)
#define ID_TIMING_AIR_LINE_H2					(ID_PAGE_TIMING_AIR_BASE + 4)
#define ID_TIMING_AIR_LINE_V					(ID_PAGE_TIMING_AIR_BASE + 5)
#define ID_TIMING_AIR_PICKER1					(ID_PAGE_TIMING_AIR_BASE + 6)
#define ID_TIMING_AIR_PICKER2					(ID_PAGE_TIMING_AIR_BASE + 7)
#define ID_TIMING_AIR_BTN_CANLE					(ID_PAGE_TIMING_AIR_BASE + 8)
#define ID_TIMING_AIR_BTN_CONFIRM				(ID_PAGE_TIMING_AIR_BASE + 9)
#define ID_TIMING_AIR_DPOINT					(ID_PAGE_TIMING_AIR_BASE + 10)

static const GUI_WIDGET_CREATE_INFO _aDialogTimingAirCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_TIMING_AIR_SET, 0, 0, DEF_DIALOG_WIDTH, DEF_DIALOG_HEIGHT, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"timing text",			ID_TIMING_AIR_TEXT, 0, 0, 140, 50, 0, 0x0, 0},
	{ CHECKBOX_CreateIndirect, 	"timing switch",			ID_TIMING_AIR_SWITCH, 0, 0, 100, 50, WM_SF_HASTRANS, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "timing line h1",		ID_TIMING_AIR_LINE_H1, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "timing line h2",		ID_TIMING_AIR_LINE_H2, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "timing line v",			ID_TIMING_AIR_LINE_V, 0, 0, 2, 40, 0, 0x0, 0},
	{ Picker_CreateIndirect, 	"timing picker",			ID_TIMING_AIR_PICKER1, 0, 0, 130, 240, 0, 0x0, 0},
	{ Picker_CreateIndirect, 	"timing picker",			ID_TIMING_AIR_PICKER2, 0, 0, 130, 240, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"timing cancle",			ID_TIMING_AIR_BTN_CANLE, 0, 0, 198, 50, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"timing confirm",		ID_TIMING_AIR_BTN_CONFIRM, 0, 0, 198, 50, 0, 0x0, 0},
	{ TEXT_CreateIndirect, 		"timing d point",			ID_TIMING_AIR_DPOINT, 0, 0, 50, 80, 0, 0x0, 0},
};

static WM_HWIN _hTimingAir = WM_HMEM_NULL;
static void _TimingAirDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	GUI_FullRectStyle BtnStyle = {
			.MainColor = GUI_WHITE,
			.GradColor = GUI_WHITE,
			.Radius = 3,
			.Opacity = 0xff,
	};
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	BtnStyle.GradColor = GUI_GRAY;
	WINDOW_SetBkColor(hParent, &BtnStyle);
	//BtnStyle.GradColor = GUI_WHITE;
	//延时关机text
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_TEXT);
	TEXT_SetText(hItem, "定时换气");
	TEXT_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	TEXT_SetTextColor(hItem, GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_TOP, 20, 0);
	hBase = hItem;
	//开关按钮
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_SWITCH);
	/*if(TIMING_AIR_OPEN == Setting_GetDelayCloseStatus()){
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_open);
	}else{
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_close);
	}*/
	CHECKBOX_SetImage(hItem, &bmbtn_close, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmbtn_open, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	if(TIMING_AIR_CLOSE != Setting_GetTimingAirStatus()){
		CHECKBOX_SetState(hItem, 1);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, 0, 0);
	//上方分割线
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_LINE_H1);
	IMAGEVIEW_SetBkColor(hItem, 0xfff4f4f4);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	//picker1
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_PICKER1);
	WM_SetHasTrans(hItem);
	Picker_SetMaxValue(hItem, 23);
	Picker_SetMinValue(hItem, 0);
	Picker_SetFontColor(hItem, GUI_BLACK, GUI_GRAY, GUI_GRAY);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, -65, 0);
	hBase = hItem;
	//picker2
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_PICKER2);
	WM_SetHasTrans(hItem);
	Picker_SetMaxValue(hItem, 59);
	Picker_SetMinValue(hItem, 0);
	Picker_SetFontColor(hItem, GUI_BLACK, GUI_GRAY, GUI_GRAY);
	if(TIMING_AIR_CLOSE == Setting_GetTimingAirStatus()){
		WM_DisableWindow(hBase);
		WM_DisableWindow(hItem);
	}else{
		U8 Hours, Minutes;
		Setting_GetTimingAirTime(&Hours, &Minutes);
		Picker_SetValue(hBase, Hours);
		Picker_SetValue(hItem, Minutes);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	//取消按钮
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_BTN_CANLE);
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
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_BTN_CONFIRM);
	BUTTON_SetText(hItem, "确定");
	BUTTON_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	BUTTON_SetTextColor(hItem, 0, GUI_BLACK);
	BUTTON_SetTextColor(hItem, 1, GUI_BLUE);
	BUTTON_EnableNewStyle(hItem);
	BUTTON_SetPressNewStyle(hItem, &BtnStyle);
	BUTTON_SetRelNewStyle(hItem, &BtnStyle);
	WM_SetHasTrans(hItem);
	if(TIMING_AIR_CLOSE == Setting_GetTimingAirStatus()){
		WM_DisableWindow(hItem);
	}
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, 0, 0);

	//下方分割线
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_LINE_H2);
	IMAGEVIEW_SetBkColor(hItem, 0xffafafaf); //0xfff4f4f4
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_ABOVE_TOP, 0, 0);
	//中间竖线分割线
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_LINE_V);
	IMAGEVIEW_SetBkColor(hItem, 0xff8f8f8f); //0xfff4f4f4
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_V_CENTER, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, -5);
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	//两个点
	hItem = WM_GetDialogItem(hParent, ID_TIMING_AIR_DPOINT);
	if(TIMING_AIR_CLOSE == Setting_GetTimingAirStatus()){
		TEXT_SetTextColor(hItem, GUI_GRAY);
	}else{
		TEXT_SetTextColor(hItem, GUI_BLACK);
	}
	TEXT_SetFont(hItem, &GUI_FontNumberYH72);
	TEXT_SetText(hItem, ":");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER);
	WM_DisableWindow(hItem);
	hBase = WM_GetDialogItem(hParent, ID_TIMING_AIR_PICKER1);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_V_CENTER, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, -20, 0);
	WM_ShowWindowAndChild(hParent);
}

static void _cbTimingAirDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_TimingAirDialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hTimingAir = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_TIMING_AIR_SWITCH:
						if(CHECKBOX_IsChecked(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_SWITCH))){
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_PICKER1));
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_PICKER2));
							WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_BTN_CONFIRM));
							TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_DPOINT), GUI_BLACK);
							Setting_SetTimingAirStatus(TIMING_AIR_OPEN);
						}else{
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_PICKER1));
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_PICKER2));
							WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_BTN_CONFIRM));
							TEXT_SetTextColor(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_DPOINT), GUI_GRAY);
							Setting_SetTimingAirStatus(TIMING_AIR_CLOSE);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_TIMING_AIR_BTN_CANLE:
						WM_DeleteWindow(pMsg->hWin);
						HoodCom_SendTouchVoice();
					break;
					case ID_TIMING_AIR_BTN_CONFIRM:
						Setting_SetTimingAirTime(Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_PICKER1)),
								Picker_GetCurValue(WM_GetDialogItem(pMsg->hWin, ID_TIMING_AIR_PICKER2)));
						Setting_SetTimingAirStatus(TIMING_AIR_START);
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

WM_HWIN DialogTimingAirCreate(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hTimingAir){
		_hTimingAir = GUI_CreateDialogBox(_aDialogTimingAirCreate, GUI_COUNTOF(_aDialogTimingAirCreate), _cbTimingAirDialog, hParent, 0, 0);
		GUI_Debug("_hTimingAir:%d\n", _hTimingAir);
	}
	return _hTimingAir;
}
