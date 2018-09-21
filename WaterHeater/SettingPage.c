/*
 * SettingPage.c
 *
 *  Created on: 2018年6月20日
 *      Author: Administrator
 */

#include <GUI_main.h>
#include <stdlib.h>
#include "ImageResource.h"
#include "SettingPage.h"
#include "SettingInfo.h"
#include "TOTAST.h"
#include "SimpleKeyboard.h"


#define ID_WINDOW_SETTING		(ID_SETTING_PAGE_BASE + 0)
#define ID_IMAGE_BG				(ID_SETTING_PAGE_BASE + 1)
#define ID_TEXT_MODEL			(ID_SETTING_PAGE_BASE + 2)
#define ID_TEXT_MAX_VALUE		(ID_SETTING_PAGE_BASE + 3)
#define ID_TEXT_MIN_VALUE		(ID_SETTING_PAGE_BASE + 4)
#define ID_TEXT_FIRE_VALUE		(ID_SETTING_PAGE_BASE + 5)
#define ID_EDIT_MODEL			(ID_SETTING_PAGE_BASE + 6)
#define ID_EDIT_MAX_VALUE		(ID_SETTING_PAGE_BASE + 7)
#define ID_EDIT_MIN_VALUE		(ID_SETTING_PAGE_BASE + 8)
#define ID_EDIT_FIRE_VALUE		(ID_SETTING_PAGE_BASE + 9)
#define ID_BTN_SAVE				(ID_SETTING_PAGE_BASE + 10)
#define ID_BTN_BACK				(ID_SETTING_PAGE_BASE + 11)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontYH48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH48;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_save_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_save_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_back3_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_back3_unfocus;

static const GUI_WIDGET_CREATE_INFO _WindowSettingPageCreate[] =
{
		{WINDOW_CreateIndirect, "window", ID_WINDOW_SETTING, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0, 0},
		{IMAGEVIEW_CreateIndirect, "view bg", ID_IMAGE_BG, 0, 0, 787, 404, 0, 0x0, 0},
		{TEXT_CreateIndirect, "model", ID_TEXT_MODEL, 0, 0, 250, 60, 0, 0, 0},
		{EDIT_CreateIndirect, "model", ID_EDIT_MODEL, 0, 0, 100, 50, 0, 0, 0},
		{TEXT_CreateIndirect, "max", ID_TEXT_MAX_VALUE, 0, 0, 250, 60, 0, 0, 0},
		{EDIT_CreateIndirect, "max", ID_EDIT_MAX_VALUE, 0, 0, 100, 50, 0, 0, 0},
		{TEXT_CreateIndirect, "min", ID_TEXT_MIN_VALUE, 0, 0, 250, 60, 0, 0, 0},
		{EDIT_CreateIndirect, "min", ID_EDIT_MIN_VALUE, 0, 0, 100, 50, 0, 0, 0},
		{TEXT_CreateIndirect, "frie", ID_TEXT_FIRE_VALUE, 0, 0, 250, 60, 0, 0, 0},
		{EDIT_CreateIndirect, "fire", ID_EDIT_FIRE_VALUE, 0, 0, 100, 50, 0, 0, 0},
		{IMAGEBUTTON_CreateIndirect, "save", ID_BTN_SAVE, 0, 0, 178, 82, 0, 0, 0},
		{IMAGEBUTTON_CreateIndirect, "back", ID_BTN_BACK, 0, 0, 178, 82, 0, 0, 0},
};

static WM_HWIN	hSetting = WM_HWIN_NULL;
static void _DialogInit(WM_HWIN hParent)
{
	char TempBuffer[5] = "";
	WM_HWIN hItem, hBaseWin;
	hItem = WM_GetDialogItem(hParent, ID_IMAGE_BG);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_MODEL);
	TEXT_SetFont(hItem, &GUI_FontYH48);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "机              型:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -110, 120);

	hBaseWin = hItem;
	GUI_sprintf(TempBuffer, "%d", GetWaterHeaterModel());
	hItem = WM_GetDialogItem(hParent, ID_EDIT_MODEL);
	EDIT_SetTextAlign(hItem, GUI_TA_CENTER);
	EDIT_SetFont(hItem, &GUI_FontNUM_YH48);
	EDIT_SetMaxLen(hItem, 2);
	//EDIT_SetDecMode(hItem, GetWaterHeaterModel(), 0, 16, 0, 1);
	EDIT_SetValue(hItem, GetWaterHeaterModel());
	EDIT_SetText(hItem, TempBuffer);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_MAX_VALUE);
	TEXT_SetFont(hItem, &GUI_FontYH48);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "比例阀最大值:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MODEL), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MODEL), hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	hBaseWin = hItem;
	GUI_sprintf(TempBuffer, "%d", GetWaterHeaterValveMaxValue());
	hItem = WM_GetDialogItem(hParent, ID_EDIT_MAX_VALUE);
	EDIT_SetTextAlign(hItem, GUI_TA_CENTER);
	EDIT_SetFont(hItem, &GUI_FontNUM_YH48);
	EDIT_SetMaxLen(hItem, 3);
	EDIT_SetText(hItem, TempBuffer);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MODEL), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_MIN_VALUE);
	TEXT_SetFont(hItem, &GUI_FontYH48);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "比例阀最小值:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MAX_VALUE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MODEL), hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	hBaseWin = hItem;
	GUI_sprintf(TempBuffer, "%d", GetWaterHeaterValveMinValue());
	hItem = WM_GetDialogItem(hParent, ID_EDIT_MIN_VALUE);
	EDIT_SetTextAlign(hItem, GUI_TA_CENTER);
	EDIT_SetFont(hItem, &GUI_FontNUM_YH48);
	EDIT_SetMaxLen(hItem, 3);
	EDIT_SetText(hItem, TempBuffer);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MAX_VALUE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_FIRE_VALUE);
	TEXT_SetFont(hItem, &GUI_FontYH48);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "比例阀点火值:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MIN_VALUE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MODEL), hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	hBaseWin = hItem;
	GUI_sprintf(TempBuffer, "%d", GetWaterHeaterFireOnValue());
	hItem = WM_GetDialogItem(hParent, ID_EDIT_FIRE_VALUE);
	EDIT_SetTextAlign(hItem, GUI_TA_CENTER);
	EDIT_SetFont(hItem, &GUI_FontNUM_YH48);
	EDIT_SetMaxLen(hItem, 3);
	EDIT_SetText(hItem, TempBuffer);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_MIN_VALUE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_BTN_SAVE);
	//IMAGEBUTTON_SetFocusFile(hItem, IAMGE_SETTING_FOCUS_SAVE, 0);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IAMGE_SETTING_UNFOCUS_SAVE, 0);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_save_focus);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_save_unfocus);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, -90, -70);
	WM_EnableFocuss(hItem);

	hItem = WM_GetDialogItem(hParent, ID_BTN_BACK);
	//IMAGEBUTTON_SetFocusFile(hItem, IAMGE_SETTING_FOCUS_BACK, 0);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IAMGE_SETTING_UNFOCUS_BACK, 0);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_back3_focus);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_back3_unfocus);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 90, -70);
	WM_EnableFocuss(hItem);
	WM_SetFocus(hItem);
}
static I8 _CheckEditValue(void)
{
	I16 Value = 0;
	char pText[5] = "";
	EDIT_GetText(WM_GetDialogItem(hSetting, ID_EDIT_MODEL), pText, 5);
	Value = atoi(pText);
	if(Value > 16){
		TOTAST_StaticShow("机型错误");
		return -1;
	}
	SetWaterHeaterModel(Value);
	EDIT_GetText(WM_GetDialogItem(hSetting, ID_EDIT_MAX_VALUE), pText, 5);
	Value = atoi(pText);
	if(Value > 255){
		TOTAST_StaticShow("最大值错误");
		return -1;
	}
	SetWaterHeaterValveMaxValue(Value);
	EDIT_GetText(WM_GetDialogItem(hSetting, ID_EDIT_MIN_VALUE), pText, 5);
	Value = atoi(pText);
	if(Value > 255){
		TOTAST_StaticShow("最小值错误");
		return -1;
	}
	SetWaterHeaterValveMinValue(Value);
	EDIT_GetText(WM_GetDialogItem(hSetting, ID_EDIT_FIRE_VALUE), pText, 5);
	Value = atoi(pText);
	if(Value > 255){
		TOTAST_StaticShow("点火值错误");
		return -1;
	}
	SetWaterHeaterFireOnValue(Value);
	return 0;
}
static void _cbKeyboardKeyEnter(void)
{
	_CheckEditValue();
}
static void _cbWindowSettingDialog(WM_MESSAGE *pMsg)
{
	int     NCode;
	int     Id;
	switch(pMsg->MsgId){
		case WM_INIT_DIALOG:
			_DialogInit(pMsg->hWin);
		break;
		case WM_DELETE:
			hSetting = WM_HWIN_NULL;
		break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_EDIT_MODEL:
					case ID_EDIT_MAX_VALUE:
					case ID_EDIT_MIN_VALUE:
					case ID_EDIT_FIRE_VALUE:
						SimpleKeyboardCreate(1024 - 350, 200);
						SimpleKeyboardSetStyle(KEYBOARD_STYLE_NUMBER);
						SimpleKeyboardLockStyle();
						SimpleKeyboardReportNumberOnly();
						SimpleKeyboardSetEnterCb(_cbKeyboardKeyEnter);
					break;
					case ID_BTN_SAVE:
						if(-1 == _CheckEditValue()){
							return;
						}
					case ID_BTN_BACK:
						SimpleKeyboardDelete();
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


void SettingPageCreate(void)
{
	if(WM_HWIN_NULL == hSetting){
		hSetting = GUI_CreateDialogBox(_WindowSettingPageCreate, GUI_COUNTOF(_WindowSettingPageCreate),
					_cbWindowSettingDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("setting page:%d\n", hSetting);
	}
}

