/*
 * DialogTimeSet.c
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

#include "DialogTimeSet.h"

#define ID_WINDOW_TIME_SET_SET 				(ID_PAGE_TIME_SET_BASE + 0)
#define ID_TIME_SET_TEXT						(ID_PAGE_TIME_SET_BASE + 1)
#define ID_TIME_SET_SWITCH					(ID_PAGE_TIME_SET_BASE + 2)
#define ID_TIME_SET_LINE_H1					(ID_PAGE_TIME_SET_BASE + 3)
#define ID_TIME_SET_LINE_H2					(ID_PAGE_TIME_SET_BASE + 4)
#define ID_TIME_SET_LINE_V					(ID_PAGE_TIME_SET_BASE + 5)
#define ID_TIME_SET_PICKER1					(ID_PAGE_TIME_SET_BASE + 6)
#define ID_TIME_SET_PICKER2					(ID_PAGE_TIME_SET_BASE + 7)
#define ID_TIME_SET_BTN_CANLE					(ID_PAGE_TIME_SET_BASE + 8)
#define ID_TIME_SET_BTN_CONFIRM				(ID_PAGE_TIME_SET_BASE + 9)

static const GUI_WIDGET_CREATE_INFO _aDialogTimeSetCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_TIME_SET_SET, 0, 0, DEF_DIALOG_WIDTH, DEF_DIALOG_HEIGHT, 0, 0x0,0},
	{ TEXT_CreateIndirect, 		"timing text",			ID_TIME_SET_TEXT, 0, 0, 140, 50, 0, 0x0, 0},
	//{ CHECKBOX_CreateIndirect, 	"timing switch",			ID_TIME_SET_SWITCH, 0, 0, 100, 50, WM_SF_HASTRANS, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "timing line h1",		ID_TIME_SET_LINE_H1, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "timing line h2",		ID_TIME_SET_LINE_H2, 0, 0, DEF_DIALOG_WIDTH, 2, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "timing line v",			ID_TIME_SET_LINE_V, 0, 0, 2, 40, 0, 0x0, 0},
	{ Picker_CreateIndirect, 	"timing picker",			ID_TIME_SET_PICKER1, 0, 0, 130, 240, 0, 0x0, 0},
	{ Picker_CreateIndirect, 	"timing picker",			ID_TIME_SET_PICKER2, 0, 0, 130, 240, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"timing cancle",			ID_TIME_SET_BTN_CANLE, 0, 0, 198, 50, 0, 0x0, 0},
	{ BUTTON_CreateIndirect, 	"timing confirm",		ID_TIME_SET_BTN_CONFIRM, 0, 0, 198, 50, 0, 0x0, 0},
};

static WM_HWIN _hTimeSet = WM_HMEM_NULL;
static void _TimeSetDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	GUI_FullRectStyle BtnStyle = {
			.MainColor = GUI_WHITE,
			.GradColor = GUI_WHITE,
			.Radius = 3,
			.Opacity = 0xff,
	};
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_CENTRE, 0, -20);
	BtnStyle.GradColor = GUI_GRAY;
	WINDOW_SetBkColor(hParent, &BtnStyle);
	//BtnStyle.GradColor = GUI_WHITE;
	//延时关机text
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_TEXT);
	TEXT_SetText(hItem, "时间设置");
	TEXT_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	TEXT_SetTextColor(hItem, GUI_BLACK);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_LEFT_TOP, 20, 0);
	hBase = hItem;
	//开关按钮
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_SWITCH);
	/*if(TIME_SET_OPEN == Setting_GetDelayCloseStatus()){
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_open);
	}else{
		IMAGEVIEW_SetBitmap(hItem, &bmbtn_close);
	}*/
	/*CHECKBOX_SetImage(hItem, &bmbtn_close, CHECKBOX_BI_ACTIV_UNCHECKED);
	CHECKBOX_SetImage(hItem, &bmbtn_open, CHECKBOX_BI_ACTIV_CHECKED);
	CHECKBOX_SetNoDrawDownRect(hItem, 1);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT, 0, 0);*/
	//上方分割线
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_LINE_H1);
	IMAGEVIEW_SetBkColor(hItem, 0xfff4f4f4);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	//picker1
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_PICKER1);
	WM_SetHasTrans(hItem);
	Picker_SetMaxValue(hItem, 23);
	Picker_SetMinValue(hItem, 0);
	Picker_SetFontColor(hItem, GUI_BLACK, GUI_GRAY, GUI_GRAY);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, -65, 0);
	hBase = hItem;
	//picker2
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_PICKER2);
	WM_SetHasTrans(hItem);
	Picker_SetMaxValue(hItem, 59);
	Picker_SetMinValue(hItem, 0);
	Picker_SetFontColor(hItem, GUI_BLACK, GUI_GRAY, GUI_GRAY);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	//取消按钮
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_BTN_CANLE);
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
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_BTN_CONFIRM);
	BUTTON_SetText(hItem, "确定");
	BUTTON_SetFont(hItem, &GUI_FontDialogCHN_YH36);
	BUTTON_SetTextColor(hItem, 0, GUI_BLACK);
	BUTTON_SetTextColor(hItem, 1, GUI_BLUE);
	BUTTON_EnableNewStyle(hItem);
	BUTTON_SetPressNewStyle(hItem, &BtnStyle);
	BUTTON_SetRelNewStyle(hItem, &BtnStyle);
	WM_SetHasTrans(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, 0, 0);

	//下方分割线
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_LINE_H2);
	IMAGEVIEW_SetBkColor(hItem, 0xffafafaf); //0xfff4f4f4
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_ABOVE_TOP, 0, 0);
	//中间竖线分割线
	hItem = WM_GetDialogItem(hParent, ID_TIME_SET_LINE_V);
	IMAGEVIEW_SetBkColor(hItem, 0xff8f8f8f); //0xfff4f4f4
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_V_CENTER, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, -5);
	//WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);

	WM_ShowWindowAndChild(hParent);
}

static void _cbTimeSetDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_TimeSetDialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hTimeSet = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_TIME_SET_SWITCH:

					break;
					case ID_TIME_SET_BTN_CANLE:
						WM_DeleteWindow(pMsg->hWin);
					break;
					case ID_TIME_SET_BTN_CONFIRM:
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

WM_HWIN DialogTimeSetCreate(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hTimeSet){
		_hTimeSet = GUI_CreateDialogBox(_aDialogTimeSetCreate, GUI_COUNTOF(_aDialogTimeSetCreate), _cbTimeSetDialog, hParent, 0, 0);
		GUI_Debug("_hTimeSet:%d\n", _hTimeSet);
	}
	return _hTimeSet;
}
