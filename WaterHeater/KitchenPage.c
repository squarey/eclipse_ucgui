/*
 * KitchenPage.c
 *
 *  Created on: 2018年5月14日
 *      Author: Administrator
 */

#include <GUI_main.h>
#include "ImageResource.h"
#include "KitchenPage.h"
#include "SettingInfo.h"

#define ID_WINDOW_KITCHEN		(ID_KITCHEN_PAGE_BASE + 0)
#define ID_KITCHEN_ICON			(ID_KITCHEN_PAGE_BASE + 1)
#define ID_KITCHEN_LINE_V		(ID_KITCHEN_PAGE_BASE + 2)
#define ID_KITCHEN_INC			(ID_KITCHEN_PAGE_BASE + 3)
#define ID_KITCHEN_DEC			(ID_KITCHEN_PAGE_BASE + 4)
#define ID_KITCHEN_UNIT			(ID_KITCHEN_PAGE_BASE + 5)
#define ID_KITCHEN_LINE_H		(ID_KITCHEN_PAGE_BASE + 6)
#define ID_KITCHEN_CHECK_5L		(ID_KITCHEN_PAGE_BASE + 7)
#define ID_KITCHEN_CHECK_6L		(ID_KITCHEN_PAGE_BASE + 8)
#define ID_KITCHEN_CHECK_7L		(ID_KITCHEN_PAGE_BASE + 9)
#define ID_KITCHEN_CHECK_8L		(ID_KITCHEN_PAGE_BASE + 10)
#define ID_KITCHEN_BACK			(ID_KITCHEN_PAGE_BASE + 11)
#define ID_KITCHEN_TEMP_VALUE	(ID_KITCHEN_PAGE_BASE + 12)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH40;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH75;

static const GUI_WIDGET_CREATE_INFO _aWindowsKitchenCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_KITCHEN, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "icon",				ID_KITCHEN_ICON, 0, 0, 156, 156, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "line v", 			ID_KITCHEN_LINE_V, 0, 0, 8, 442, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn inc", 			ID_KITCHEN_INC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn dec", 			ID_KITCHEN_DEC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "unit", 				ID_KITCHEN_UNIT, 0, 0, 38, 33, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "line h", 			ID_KITCHEN_LINE_H, 0, 0, 760, 7, 0, 0x0,0},
	{ CHECKBOX_CreateIndirect, "5L", 					ID_KITCHEN_CHECK_5L, 0, 0, 70, 50, 0, 0x0,0},
	{ CHECKBOX_CreateIndirect, "6L", 					ID_KITCHEN_CHECK_6L, 0, 0, 70, 50, 0, 0x0,0},
	{ CHECKBOX_CreateIndirect, "7L", 					ID_KITCHEN_CHECK_7L, 0, 0, 70, 50, 0, 0x0,0},
	{ CHECKBOX_CreateIndirect, "8L", 					ID_KITCHEN_CHECK_8L, 0, 0, 70, 50, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn back", 		ID_KITCHEN_BACK, 0, 0, 117, 74, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"temp value", 			ID_KITCHEN_TEMP_VALUE, 0, 0, 100, 50, 0, 0x0,0},
};

static WM_HWIN hKitchen = WM_HMEM_NULL;
static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;;
	char Buffer[3] = "";
	/* icon */
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_ICON);
	IMAGEVIEW_SetFile(hItem, IMAGE_KITCHEN_ICON, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 40, 0);
	/* vertical line */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_LINE_V);
	IMAGEVIEW_SetFile(hItem, IMAGE_LINE_V, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 40, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	/* btn inc */
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_INC);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_INC_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_INC_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -100, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, -100);
	/* btn dec */
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_DEC);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_DEC_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_DEC_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 300, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, -100);
	/* unit */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_UNIT);
	IMAGEVIEW_SetFile(hItem, IMAGE_TEMP_UNIT, 0);
	//WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 10);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 150, 0);
	/* horizontal line */
	BaseWin = WM_GetDialogItem(hParent, ID_KITCHEN_LINE_V);
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_LINE_H);
	IMAGEVIEW_SetFile(hItem, IMAGE_LINE_H2, 0);
	IMAGEVIEW_SetChangeColor(hItem, GUI_GRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	/* checkbox 5L */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_CHECK_5L);
	CHECKBOX_SetFont(hItem, &GUI_FontNUM_YH48);
	CHECKBOX_SetBkColor(hItem, GUI_BLACK);
	CHECKBOX_SetText(hItem, "5L");
	CHECKBOX_EnableStyleCircle(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 40);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -80, 0);
	if(5 == GetKitchenWaterValue()){
		CHECKBOX_Check(hItem);
	}
	/* checkbox 6L */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_CHECK_6L);
	CHECKBOX_SetFont(hItem, &GUI_FontNUM_YH48);
	CHECKBOX_SetBkColor(hItem, GUI_BLACK);
	CHECKBOX_SetText(hItem, "6L");
	CHECKBOX_EnableStyleCircle(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 30);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);
	if(6 == GetKitchenWaterValue()){
		CHECKBOX_Check(hItem);
	}
	/* checkbox 7L */
	BaseWin = WM_GetDialogItem(hParent, ID_KITCHEN_LINE_H);
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_CHECK_7L);
	CHECKBOX_SetFont(hItem, &GUI_FontNUM_YH48);
	CHECKBOX_SetBkColor(hItem, GUI_BLACK);
	CHECKBOX_SetText(hItem, "7L");
	CHECKBOX_EnableStyleCircle(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 40);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 200, 0);
	if(7 == GetKitchenWaterValue()){
		CHECKBOX_Check(hItem);
	}
	/* checkbox 8L */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_CHECK_8L);
	CHECKBOX_SetFont(hItem, &GUI_FontNUM_YH48);
	CHECKBOX_SetBkColor(hItem, GUI_BLACK);
	CHECKBOX_SetText(hItem, "8L");
	CHECKBOX_EnableStyleCircle(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 30);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);
	if(8 == GetKitchenWaterValue()){
		CHECKBOX_Check(hItem);
	}
	/* btn back */
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_BACK);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_BACK_REALEASE, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_BACK_PRESS, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, -20, -20);
	/* temperature value */
	GUI_sprintf(Buffer, "%d", GetKitchenTempValue());
	hItem = WM_GetDialogItem(hParent, ID_KITCHEN_TEMP_VALUE);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, Buffer);
	TEXT_SetFont(hItem, &GUI_FontNUM_YH75);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER | GUI_TA_HCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_KITCHEN_DEC), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_KITCHEN_UNIT), hItem, OBJ_ALIGN_BROTHER_OUT_LEFT, -10, 0);
}

static U8 __KitchenTempValueProcess(U8 IsInc)
{
	U8 Value = GetKitchenTempValue();
	if(IsInc){
		if(Value < MAX_WATER_TEMPERATURE){
			Value++;
			SetKitchenTempValue(Value);
		}
	}else{
		if(Value > MIN_WATER_TEMPERATURE){
			Value--;
			SetKitchenTempValue(Value);
		}
	}
	return Value;
}
static void _cbWindowsKitchenDialog(WM_MESSAGE * pMsg) {
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
			hKitchen = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_KITCHEN_INC:
						TempValue = __KitchenTempValueProcess(1);
						GUI_sprintf(Buffer, "%d", TempValue);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_TEMP_VALUE), Buffer);
					break;
					case ID_KITCHEN_DEC:
						TempValue = __KitchenTempValueProcess(0);
						GUI_sprintf(Buffer, "%d", TempValue);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_TEMP_VALUE), Buffer);
					break;
					case ID_KITCHEN_CHECK_5L:
						CHECKBOX_Check(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_5L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_6L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_7L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_8L));
						SetKitchenWaterValue(5);
					break;
					case ID_KITCHEN_CHECK_6L:
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_5L));
						CHECKBOX_Check(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_6L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_7L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_8L));
						SetKitchenWaterValue(6);
					break;
					case ID_KITCHEN_CHECK_7L:
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_5L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_6L));
						CHECKBOX_Check(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_7L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_8L));
						SetKitchenWaterValue(7);
					break;
					case ID_KITCHEN_CHECK_8L:
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_5L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_6L));
						CHECKBOX_Uncheck(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_7L));
						CHECKBOX_Check(WM_GetDialogItem(pMsg->hWin, ID_KITCHEN_CHECK_8L));
						SetKitchenWaterValue(8);
					break;
					case ID_KITCHEN_BACK:
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

void KitchenPageCreate(void)
{
	if(WM_HMEM_NULL == hKitchen){
		hKitchen = GUI_CreateDialogBox(_aWindowsKitchenCreate, GUI_COUNTOF(_aWindowsKitchenCreate), _cbWindowsKitchenDialog, WM_HBKWIN, 0, 0);
		//GUI_SetPageSwitchAnimation(hKitchen);
		GUI_Debug("kitchen page %d create\n", hKitchen);
	}
}
