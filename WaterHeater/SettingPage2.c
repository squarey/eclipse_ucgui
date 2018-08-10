/*
 * SettingPage2.c
 *
 *  Created on: 2018年8月3日
 *      Author: Administrator
 */


#include "SettingPage2.h"
#include "SettingInfo.h"


#define ID_WINDOW_SETTING2		(ID_SETTING_PAGE_BASE2 + 0)
#define ID_IMAGE_BG2			(ID_SETTING_PAGE_BASE2 + 1)
#define ID_TEXT_SERIAL_NUMBER	(ID_SETTING_PAGE_BASE2 + 2)
#define ID_TEXT_SERIAL_NUMBER2	(ID_SETTING_PAGE_BASE2 + 3)
#define ID_TEXT_PARA_CODE		(ID_SETTING_PAGE_BASE2 + 4)
#define ID_TEXT_PARA_CODE2		(ID_SETTING_PAGE_BASE2 + 5)
#define ID_TEXT_CUR_VALUE		(ID_SETTING_PAGE_BASE2 + 6)
#define ID_TEXT_CUR_VALUE2		(ID_SETTING_PAGE_BASE2 + 7)
#define ID_EDIT_SET_VALUE		(ID_SETTING_PAGE_BASE2 + 8)
#define ID_EDIT_SET_VALUE2		(ID_SETTING_PAGE_BASE2 + 9)
#define ID_BTN_SEND				(ID_SETTING_PAGE_BASE2 + 10)
#define ID_BTN_PRE				(ID_SETTING_PAGE_BASE2 + 11)
#define ID_BTN_NEXT				(ID_SETTING_PAGE_BASE2 + 12)
#define ID_BTN_BACK				(ID_SETTING_PAGE_BASE2 + 13)
#define ID_BTN_SAVE				(ID_SETTING_PAGE_BASE2 + 14)

//extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontYH48_S2;

static const GUI_WIDGET_CREATE_INFO _WindowSettingPage2Create[] =
{
	{WINDOW_CreateIndirect, "window", ID_WINDOW_SETTING2, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0, 0},
	{IMAGEVIEW_CreateIndirect, "view bg", ID_IMAGE_BG2, 0, 0, 787, 404, 0, 0x0, 0},
	{TEXT_CreateIndirect, "serial number", ID_TEXT_SERIAL_NUMBER, 0, 0, 250, 60, 0, 0, 0},
	{TEXT_CreateIndirect, "serial number", ID_TEXT_SERIAL_NUMBER2, 0, 0, 100, 50, 0, 0, 0},
	{TEXT_CreateIndirect, "param code", ID_TEXT_PARA_CODE, 0, 0, 250, 60, 0, 0, 0},
	{TEXT_CreateIndirect, "param code", ID_TEXT_PARA_CODE2, 0, 0, 100, 50, 0, 0, 0},
	{TEXT_CreateIndirect, "cur value", ID_TEXT_CUR_VALUE, 0, 0, 250, 60, 0, 0, 0},
	{TEXT_CreateIndirect, "cur value", ID_TEXT_CUR_VALUE2, 0, 0, 100, 50, 0, 0, 0},
	{TEXT_CreateIndirect, "set value", ID_EDIT_SET_VALUE, 0, 0, 250, 60, 0, 0, 0},
	{EDIT_CreateIndirect, "set value", ID_EDIT_SET_VALUE2, 0, 0, 100, 50, 0, 0, 0},
	{BUTTON_CreateIndirect, "btn send", ID_BTN_SEND, 0, 0, 150, 60, 0, 0, 0},
	{BUTTON_CreateIndirect, "btn pre", ID_BTN_PRE, 0, 0, 150, 60, 0, 0, 0},
	{BUTTON_CreateIndirect, "btn next", ID_BTN_NEXT, 0, 0, 150, 60, 0, 0, 0},
	{BUTTON_CreateIndirect, "btn back", ID_BTN_BACK, 0, 0, 150, 60, 0, 0, 0},
	{BUTTON_CreateIndirect, "btn save", ID_BTN_SAVE, 0, 0, 150, 60, 0, 0, 0},
};


static WM_HWIN	hSetting2 = WM_HWIN_NULL;

static void _DialogInit(WM_HWIN hParent)
{
	char TempBuffer[5] = "";
	WM_HWIN hItem, hBaseWin;
	hItem = WM_GetDialogItem(hParent, ID_IMAGE_BG2);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	GUI_Debug("Setting page2 background win:%d\n", hItem);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER);
	TEXT_SetFont(hItem, &GUI_FontYH48_S2);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "序  列 号:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -110, 120);

	hBaseWin = hItem;
	GUI_sprintf(TempBuffer, "%d", GetWaterHeaterPowerDebugSerialNumber());
	hItem = WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER2);
	TEXT_SetFont(hItem, &GUI_FontASSIC_YH32);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, TempBuffer);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_PARA_CODE);
	TEXT_SetFont(hItem, &GUI_FontYH48_S2);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "参数代码:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER2), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER), hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	hBaseWin = hItem;
	//GUI_sprintf(TempBuffer, "%d", GetWaterHeaterValveMaxValue());
	GetWaterHeaterPowerParameterCodeString((U8 *)TempBuffer);
	hItem = WM_GetDialogItem(hParent, ID_TEXT_PARA_CODE2);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetFont(hItem, &GUI_FontASSIC_YH32);
	TEXT_SetText(hItem, TempBuffer);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER2), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_TEXT_CUR_VALUE);
	TEXT_SetFont(hItem, &GUI_FontYH48_S2);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "当  前 值:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_PARA_CODE2), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER), hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	hBaseWin = hItem;
	//GUI_sprintf(TempBuffer, "%d", GetWaterHeaterValveMinValue());
	GetWaterHeaterPowerParameterValueString((U8 *)TempBuffer);
	hItem = WM_GetDialogItem(hParent, ID_TEXT_CUR_VALUE2);
	TEXT_SetFont(hItem, &GUI_FontASSIC_YH32);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, TempBuffer);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_PARA_CODE2), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 5);

	hItem = WM_GetDialogItem(hParent, ID_EDIT_SET_VALUE);
	TEXT_SetFont(hItem, &GUI_FontYH48_S2);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "设  置 值:");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_CUR_VALUE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_SERIAL_NUMBER), hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	hBaseWin = hItem;
	GUI_sprintf(TempBuffer, "%d", GetWaterHeaterFireOnValue());
	hItem = WM_GetDialogItem(hParent, ID_EDIT_SET_VALUE2);
	EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(hItem, &GUI_FontASSIC_YH32);
	EDIT_SetMaxLen(hItem, 3);
	EDIT_SetText(hItem, TempBuffer);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TEXT_CUR_VALUE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 5);


	hItem = WM_GetDialogItem(hParent, ID_BTN_SEND);
	BUTTON_SetFont(hItem, &GUI_FontYH48_S2);
	BUTTON_SetText(hItem, "发送");
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_IMAGE_BG2), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, -20);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 0);
	hBaseWin = hItem;

	hBaseWin = WM_GetDialogItem(hParent, ID_IMAGE_BG2);
	hItem = WM_GetDialogItem(hParent, ID_BTN_PRE);
	BUTTON_SetFont(hItem, &GUI_FontYH48_S2);
	BUTTON_SetText(hItem, "前一项");
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 20, 0);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 40);
	hBaseWin = hItem;

	hItem = WM_GetDialogItem(hParent, ID_BTN_NEXT);
	BUTTON_SetFont(hItem, &GUI_FontYH48_S2);
	BUTTON_SetText(hItem, "后一项");
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 30);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);
	hBaseWin = hItem;

	hItem = WM_GetDialogItem(hParent, ID_BTN_SAVE);
	BUTTON_SetFont(hItem, &GUI_FontYH48_S2);
	BUTTON_SetText(hItem, "保存");
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 30);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);
	hBaseWin = hItem;

	hItem = WM_GetDialogItem(hParent, ID_BTN_BACK);
	BUTTON_SetFont(hItem, &GUI_FontYH48_S2);
	BUTTON_SetText(hItem, "返回");
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 30);
	WM_SetAlignWindow(hBaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);

	WM_SetFocus(hItem);
}
static void _cbWindowSettingDialog2(WM_MESSAGE *pMsg)
{
	int     NCode;
	int     Id;
	switch(pMsg->MsgId){
		case WM_INIT_DIALOG:
			_DialogInit(pMsg->hWin);
		break;
		case WM_DELETE:
			hSetting2 = WM_HWIN_NULL;
		break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_EDIT_SET_VALUE2:
						SimpleKeyboardCreate(1024 - 350, 200);
						SimpleKeyboardSetStyle(KEYBOARD_STYLE_NUMBER);
						SimpleKeyboardLockStyle();
						SimpleKeyboardReportNumberOnly();
					break;
					case ID_BTN_SEND:
					break;
					case ID_BTN_PRE:
					break;
					case ID_BTN_NEXT:
					break;
					case ID_BTN_SAVE:
					break;
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


void SettingPage2Create(void)
{
	if(WM_HWIN_NULL == hSetting2){
		hSetting2 = GUI_CreateDialogBox(_WindowSettingPage2Create, GUI_COUNTOF(_WindowSettingPage2Create),
				_cbWindowSettingDialog2, WM_HBKWIN, 0, 0);
		GUI_Debug("setting page2:%d\n", hSetting2);
	}
}

