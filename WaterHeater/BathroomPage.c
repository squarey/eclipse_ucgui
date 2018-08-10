/*
 * BathroomPage.c
 *
 *  Created on: 2018年5月15日
 *      Author: Administrator
 */

#include "GUI_main.h"
#include "ImageResource.h"
#include "BathroomPage.h"
#include "SettingInfo.h"

#define ID_WINDOW_BATHROOM			(ID_BATHROOM_PAGE_BASE + 0)
#define ID_BATHROOM_ICON			(ID_BATHROOM_PAGE_BASE + 1)
#define ID_BATHROOM_LINE_H			(ID_BATHROOM_PAGE_BASE + 2)
#define ID_BATHROOM_INC				(ID_BATHROOM_PAGE_BASE + 3)
#define ID_BATHROOM_DEC				(ID_BATHROOM_PAGE_BASE + 4)
#define ID_BATHROOM_UNIT			(ID_BATHROOM_PAGE_BASE + 5)
#define ID_BATHROOM_BACK			(ID_BATHROOM_PAGE_BASE + 6)
#define ID_BATHROOM_TEMP_VALUE		(ID_BATHROOM_PAGE_BASE + 7)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH75;

static const GUI_WIDGET_CREATE_INFO _aWindowsBathroomCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_BATHROOM, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "icon",					ID_BATHROOM_ICON, 0, 0, 156, 156, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "line h", 				ID_BATHROOM_LINE_H, 0, 0, 635, 12, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn inc", 			ID_BATHROOM_INC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn dec", 			ID_BATHROOM_DEC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "unit", 				ID_BATHROOM_UNIT, 0, 0, 38, 33, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn back", 			ID_BATHROOM_BACK, 0, 0, 117, 74, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"temp value", 				ID_BATHROOM_TEMP_VALUE, 0, 0, 100, 50, 0, 0x0,0},
};

static WM_HWIN hBathroom = WM_HWIN_NULL;

static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;
	char Buffer[3] = "";
	/* icon */
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_ICON);
	IMAGEVIEW_SetFile(hItem, IMAGE_BATHROOM_ICON, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 40);
	/* horizontal line */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_LINE_H);
	IMAGEVIEW_SetFile(hItem, IMAGE_LINE_H1, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 50);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 0);
	/* btn inc */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_INC);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_INC_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_INC_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -150, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 60);
	/* btn dec */
	BaseWin = WM_GetDialogItem(hParent, ID_BATHROOM_LINE_H);
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_DEC);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_DEC_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_DEC_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 200, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 60);
	/* unit */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_UNIT);
	IMAGEVIEW_SetFile(hItem, IMAGE_TEMP_UNIT, 0);
	//WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, -5);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 80, 0);
	/* btn back */
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_BACK);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_BACK_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_BACK_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, -20, -20);

	/* temperature value */
	GUI_sprintf(Buffer, "%d", GetBathroomTempValue());
	hItem = WM_GetDialogItem(hParent, ID_BATHROOM_TEMP_VALUE);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, Buffer);
	TEXT_SetFont(hItem, &GUI_FontNUM_YH75);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER | GUI_TA_HCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_BATHROOM_DEC), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_BATHROOM_UNIT), hItem, OBJ_ALIGN_BROTHER_OUT_LEFT, -10, 0);
}
static U8 __BathroomTempValueProcess(U8 IsInc)
{
	U8 Value = GetBathroomTempValue();
	if(IsInc){
		if(Value < MAX_WATER_TEMPERATURE){
			Value++;
			SetBathroomTempValue(Value);
		}
	}else{
		if(Value > MIN_WATER_TEMPERATURE){
			Value--;
			SetBathroomTempValue(Value);
		}
	}
	return Value;
}
static void _cbWindowsBathroomDialog(WM_MESSAGE * pMsg) {
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
			hBathroom = WM_HWIN_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_BATHROOM_INC:
						TempValue = __BathroomTempValueProcess(1);
						GUI_sprintf(Buffer, "%d", TempValue);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_BATHROOM_TEMP_VALUE), Buffer);
					break;
					case ID_BATHROOM_DEC:
						TempValue = __BathroomTempValueProcess(0);
						GUI_sprintf(Buffer, "%d", TempValue);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_BATHROOM_TEMP_VALUE), Buffer);
					break;
					case ID_BATHROOM_BACK:
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

void BathroomPageCreate(void)
{
	if(WM_HWIN_NULL == hBathroom){
		hBathroom = GUI_CreateDialogBox(_aWindowsBathroomCreate, GUI_COUNTOF(_aWindowsBathroomCreate), _cbWindowsBathroomDialog, WM_HBKWIN, 0, 0);
		//GUI_SetPageSwitchAnimation(hBathroom);
		GUI_Debug("kitchen page %d create\n", hBathroom);
	}
}
