/*
 * TimerPage.c
 *
 *  Created on: 2018年5月14日
 *      Author: Administrator
 */

#include <GUI_main.h>
#include "ImageResource.h"
#include "TimerPage.h"
#include "SettingInfo.h"

#define ID_WINDOW_TIMER				(ID_TIMER_PAGE_BASE + 0)
#define ID_TIMER_ICON				(ID_TIMER_PAGE_BASE + 1)
#define ID_TIMER_LINE				(ID_TIMER_PAGE_BASE + 2)
#define ID_TIMER_BTN_INC			(ID_TIMER_PAGE_BASE + 3)
#define ID_TIMER_BTN_DEC			(ID_TIMER_PAGE_BASE + 4)
#define ID_TIMER_UNIT				(ID_TIMER_PAGE_BASE + 5)
#define ID_TIMER_BTN_BACK			(ID_TIMER_PAGE_BASE + 6)
#define ID_TIMER_TIME_VALUE			(ID_TIMER_PAGE_BASE + 7)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH75;
extern GUI_CONST_STORAGE GUI_BITMAP bmicon_timer;
extern GUI_CONST_STORAGE GUI_BITMAP bmline_fgx;
extern GUI_CONST_STORAGE GUI_BITMAP bmiocn_tarrow_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmiocn_tarrow_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmiocn_darrow_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmiocn_darrow_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_back1_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_back1_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmunit_minute;

static const GUI_WIDGET_CREATE_INFO _aWindowsTimerCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_TIMER, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "icon",				ID_TIMER_ICON, 0, 0, 156, 156, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "line", 				ID_TIMER_LINE, 0, 0, 635, 12, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn inc",			ID_TIMER_BTN_INC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn dec",			ID_TIMER_BTN_DEC, 0, 0, 77, 47, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "unit",				ID_TIMER_UNIT, 0, 0, 63, 32, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "btn back",			ID_TIMER_BTN_BACK, 0, 0, 117, 74, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"temp value", 			ID_TIMER_TIME_VALUE, 0, 0, 100, 50, 0, 0x0,0},
};

static WM_HWIN hTimerPage = WM_HMEM_NULL;

static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;
	char TmpBuffer[3];
	/* ICON */
	GUI_Debug("timer page init start\n");
	hItem = WM_GetDialogItem(hParent, ID_TIMER_ICON);
	//IMAGEVIEW_SetFile(hItem, IMAGE_TIMER_ICON, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmicon_timer);
	IMAGEVIEW_SetBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 20);
	GUI_Debug("timer icon win:%d\n", hItem);
	/* line */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_TIMER_LINE);
	GUI_Debug("To start timer line hItem:%d\n", hItem);
	//IMAGEVIEW_SetFile(hItem, IMAGE_LINE_H1, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmline_fgx);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 0, 30);
	/* btn inc */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_TIMER_BTN_INC);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_INC_REALEASE, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_INC_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmiocn_tarrow_focus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmiocn_tarrow_unfocus);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 50);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -250, 0);
	/* btn dec */
	BaseWin = WM_GetDialogItem(hParent, ID_TIMER_LINE);
	hItem = WM_GetDialogItem(hParent, ID_TIMER_BTN_DEC);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_DEC_REALEASE, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_DEC_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmiocn_darrow_focus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmiocn_darrow_unfocus);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 50);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 250, 0);
	/* unit */
	BaseWin = WM_GetDialogItem(hParent, ID_TIMER_LINE);
	hItem = WM_GetDialogItem(hParent, ID_TIMER_UNIT);
	//IMAGEVIEW_SetFile(hItem, IMAGE_TIMER_UNIT, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmunit_minute);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 50);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, 80, 10);
	/* btn back */
	hItem = WM_GetDialogItem(hParent, ID_TIMER_BTN_BACK);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_BTN_BACK_REALEASE, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_BTN_BACK_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_back1_focus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_back1_unfocus);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_RIGHT_BOTTOM, -20, -20);
	/* timer value */
	GUI_sprintf(TmpBuffer, "%d", GetTimerTimeValue());
	hItem = WM_GetDialogItem(hParent, ID_TIMER_TIME_VALUE);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	TEXT_SetText(hItem, TmpBuffer);
	TEXT_SetFont(hItem, &GUI_FontNUM_YH75);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER | GUI_TA_HCENTER);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TIMER_BTN_DEC), hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_TIMER_UNIT), hItem, OBJ_ALIGN_BROTHER_OUT_LEFT, -10, 0);
}

static U8 __TimerTimeProcess(U8 Value, U8 IsInc)
{
	U8 ValueResult = 0;
	if(1 == IsInc){
		switch(Value){
			case 0:
				ValueResult = 20;
			break;
			case 20:
				ValueResult = 30;
			break;
			case 30:
				ValueResult = 40;
			break;
			case 40:
				ValueResult = 50;
			break;
			case 50:
				ValueResult = 60;
			break;
			case 60:
				ValueResult = 60;
			break;
			default:
				ValueResult = Value;
			break;
		}
	}else{
		switch(Value){
			case 0:
				ValueResult = 0;
			break;
			case 20:
				ValueResult = 0;
			break;
			case 30:
				ValueResult = 20;
			break;
			case 40:
				ValueResult = 30;
			break;
			case 50:
				ValueResult = 40;
			break;
			case 60:
				ValueResult = 50;
			break;
			default:
				ValueResult = Value;
			break;
		}
	}
	return ValueResult;
}
static void _WindowDeleteAnimEnd(WM_HWIN hWin)
{
	WM_DeleteWindow(hWin);
}
static void _StartWindowDeleteAnim(WM_HWIN hWin)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = 0;
	Anim.End = 1024;
	Anim.Time = 200;
	Anim.pFunc = WM_SetWindowPosX;
	Anim.pEnd = _WindowDeleteAnimEnd;
	GUI_AnimationCreate(hWin, &Anim);
}
static void _cbWindowsTimerDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;
	U8		Value = 0;
	char 	Buffer[3];
	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hTimerPage = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_TIMER_BTN_INC:
						Value = __TimerTimeProcess(GetTimerTimeValue(), 1);
						GUI_sprintf(Buffer, "%d", Value);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TIMER_TIME_VALUE), Buffer);
						SetTimerTimeValue(Value);
					break;
					case ID_TIMER_BTN_DEC:
						Value = __TimerTimeProcess(GetTimerTimeValue(), 0);
						GUI_sprintf(Buffer, "%d", Value);
						TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TIMER_TIME_VALUE), Buffer);
						SetTimerTimeValue(Value);
					break;
					case ID_TIMER_BTN_BACK:
						//WM_DeleteWindow(hTimerPage);
						_StartWindowDeleteAnim(hTimerPage);
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

void TimerPageCreate(void)
{
	if(WM_HMEM_NULL == hTimerPage){
		hTimerPage = GUI_CreateDialogBox(_aWindowsTimerCreate, GUI_COUNTOF(_aWindowsTimerCreate), _cbWindowsTimerDialog, WM_HBKWIN, 0, 0);
		//GUI_SetPageSwitchAnimation(hTimerPage);
		GUI_Debug("timer page %d create\n", hTimerPage);
	}
}
