/*
 * BathtubPage.c
 *
 *  Created on: 2018年5月15日
 *      Author: Administrator
 */

#include <GUI_main.h>
#include "ImageResource.h"
#include "BathtubPage.h"
#include "SettingInfo.h"
#include "SimpleKeyboard.h"

#define ID_WINDOW_BATHTUB			(ID_BATHTUB_PAGE_BASE + 0)
#define ID_BATHTUB_ICON				(ID_BATHTUB_PAGE_BASE + 1)
#define ID_BATHTUB_LINE_V			(ID_BATHTUB_PAGE_BASE + 2)
#define ID_BATHTUB_TEXT_WATER		(ID_BATHTUB_PAGE_BASE + 3)
#define ID_BATHTUB_TEXT_WATER_UNIT	(ID_BATHTUB_PAGE_BASE + 4)
#define ID_BATHTUB_EDIT				(ID_BATHTUB_PAGE_BASE + 5)
#define ID_BATHTUB_LINE_H			(ID_BATHTUB_PAGE_BASE + 6)
#define ID_BATHTUB_INC				(ID_BATHTUB_PAGE_BASE + 7)
#define ID_BATHTUB_DEC				(ID_BATHTUB_PAGE_BASE + 8)
#define ID_BATHTUB_UNIT				(ID_BATHTUB_PAGE_BASE + 9)
#define ID_BATHTUB_BACK				(ID_BATHTUB_PAGE_BASE + 10)
#define ID_BATHTUB_TEMP_VALUE		(ID_BATHTUB_PAGE_BASE + 11)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontCHN_YH40;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH40;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH75;

static const GUI_WIDGET_CREATE_INFO _aWindowsBathtubCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_BATHTUB, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "icon",				ID_BATHTUB_ICON, 0, 0, 156, 156, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "line v", 			ID_BATHTUB_LINE_V, 0, 0, 8, 442, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"water txt", 			ID_BATHTUB_TEXT_WATER, 0, 0, 80, 50, 0, 0x0,0},
	{ EDIT_CreateIndirect, 	"edit", 				ID_BATHTUB_EDIT, 0, 0, 100, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"water unit", 			ID_BATHTUB_TEXT_WATER_UNIT, 0, 0, 40, 50, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "line h", 			ID_BATHTUB_LINE_H, 0, 0, 760, 7, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn inc", 			ID_BATHTUB_INC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn dec", 			ID_BATHTUB_DEC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "unit", 				ID_BATHTUB_UNIT, 0, 0, 38, 33, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn back", 		ID_BATHTUB_BACK, 0, 0, 117, 74, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"temp value", 			ID_BATHTUB_TEMP_VALUE, 0, 0, 100, 50, 0, 0x0,0},
};

static WM_HWIN hBathtub = WM_HMEM_NULL;

static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;
	char Buffer[3] = "";
	/* icon */
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_ICON);
	IMAGEVIEW_SetFile(hItem, IMAGE_BATHTUB_ICON, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 40, 0);
	/* vertical line */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_LINE_V);
	IMAGEVIEW_SetFile(hItem, IMAGE_LINE_V, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 40, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	/* water text */
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_TEXT_WATER);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, "水量:");
	TEXT_SetFont(hItem, &GUI_FontCHN_YH40);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 100);
	/* edit */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_EDIT);
	EDIT_SetText(hItem, "");
	EDIT_SetTextAlign(hItem, EDIT_CF_VCENTER | EDIT_CF_HCENTER);
	EDIT_SetMaxLen(hItem, 2);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 100);
	/* water unit */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_TEXT_WATER_UNIT);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 10, 100);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetText(hItem, "L");
	/* horizontal line */
	BaseWin = WM_GetDialogItem(hParent, ID_BATHTUB_LINE_V);
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_LINE_H);
	IMAGEVIEW_SetFile(hItem, IMAGE_LINE_H2, 0);
	IMAGEVIEW_SetChangeColor(hItem, GUI_GRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	/* btn inc */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_INC);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_INC_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_INC_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -80, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 60);
	/* btn dec */
	BaseWin = WM_GetDialogItem(hParent, ID_BATHTUB_LINE_H);
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_DEC);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_DEC_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_DEC_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 250, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 60);
	/* unit */
	BaseWin = WM_GetDialogItem(hParent, ID_BATHTUB_LINE_H);
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_UNIT);
	IMAGEVIEW_SetFile(hItem, IMAGE_TEMP_UNIT, 0);
	//WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 70);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 150, 0);
	/* btn back */
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_BACK);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_BACK_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_BACK_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, -20, -20);
	/* temperature value */
	GUI_sprintf(Buffer, "%d", GetBathtubTempValue());
	hItem = WM_GetDialogItem(hParent, ID_BATHTUB_TEMP_VALUE);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, Buffer);
	TEXT_SetFont(hItem, &GUI_FontNUM_YH75);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER | GUI_TA_HCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_BATHTUB_DEC), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_BATHTUB_UNIT), hItem, OBJ_ALIGN_BROTHER_OUT_LEFT, -10, 0);
}
static U8 __BathtubTempValueProcess(U8 IsInc)
{
	U8 Value = GetBathtubTempValue();
	if(IsInc){
		if(Value < MAX_WATER_TEMPERATURE){
			Value++;
			SetBathtubTempValue(Value);
		}
	}else{
		if(Value > MIN_WATER_TEMPERATURE){
			Value--;
			SetBathtubTempValue(Value);
		}
	}
	return Value;
}
static void _cbWindowsBathtubDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;
	U8		TempValue = 0;
	char	Buffer[3];
	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hBathtub = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_BATHTUB_INC:
						TempValue = __BathtubTempValueProcess(1);
						GUI_sprintf(Buffer, "%d", TempValue);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_BATHTUB_TEMP_VALUE), Buffer);
					break;
					case ID_BATHTUB_DEC:
						TempValue = __BathtubTempValueProcess(0);
						GUI_sprintf(Buffer, "%d", TempValue);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_BATHTUB_TEMP_VALUE), Buffer);
					break;
					case ID_BATHTUB_BACK:
						WM_DeleteWindow(pMsg->hWin);
					break;
					case ID_BATHTUB_EDIT:
						GUI_Debug("edit click\n");
						SimpleKeyboardCreate(300, 300);
						SimpleKeyboardSetStyle(KEYBOARD_STYLE_NUMBER);
						SimpleKeyboardLockStyle();
						SimpleKeyboardReportNumberOnly();
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

void BathtubPageCreate(void)
{
	if(WM_HMEM_NULL == hBathtub){
		hBathtub = GUI_CreateDialogBox(_aWindowsBathtubCreate, GUI_COUNTOF(_aWindowsBathtubCreate), _cbWindowsBathtubDialog, WM_HBKWIN, 0, 0);
		//GUI_SetPageSwitchAnimation(hBathtub);
		GUI_Debug("kitchen page %d create\n", hBathtub);
	}
}
