/*
 * PageMenuBar.c
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#include "PageMenuBar.h"

#define ID_WINDOW_MENU_BAR			(ID_PAGE_MENU_BAR_BASE + 0)
#define ID_MENU_LIGHT				(ID_PAGE_MENU_BAR_BASE + 1)
#define ID_MENU_WIND_SMALL			(ID_PAGE_MENU_BAR_BASE + 2)
#define ID_MENU_WIND_MIDDLE			(ID_PAGE_MENU_BAR_BASE + 3)
#define ID_MENU_WIND_LARGE			(ID_PAGE_MENU_BAR_BASE + 4)
#define ID_MENU_SMART				(ID_PAGE_MENU_BAR_BASE + 5)
#define ID_MENU_V_LINE1				(ID_PAGE_MENU_BAR_BASE + 6)
#define ID_MENU_V_LINE2				(ID_PAGE_MENU_BAR_BASE + 7)
#define ID_MENU_V_LINE3				(ID_PAGE_MENU_BAR_BASE + 8)
#define ID_MENU_V_LINE4				(ID_PAGE_MENU_BAR_BASE + 9)

#define DEF_PART_PIXEL				2
#define DEF_WIND_ANIM_NUM		24

static const GUI_WIDGET_CREATE_INFO _aWindowsMenuBarCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_MENU_BAR, 0, 470, DEF_PAGE_WIDTH, DEF_MENU_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "light",				ID_MENU_LIGHT, 0, 0, 140, 118, WM_CF_HASTRANS, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "wind small",			ID_MENU_WIND_SMALL, 0, 0, 171, 118, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "wind middle",			ID_MENU_WIND_MIDDLE, 0, 0, 171, 118, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "wind large",			ID_MENU_WIND_LARGE, 0, 0, 171, 118, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "smart",				ID_MENU_SMART, 0, 0, 264, 82, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "v line1",				ID_MENU_V_LINE1, 0, 0, 2, 60, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "v line2",				ID_MENU_V_LINE2, 0, 0, 2, 60, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "v line3",				ID_MENU_V_LINE3, 0, 0, 2, 60, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "v line4",				ID_MENU_V_LINE4, 0, 0, 2, 60, 0, 0x0,0},
};

static GUI_CONST_STORAGE GUI_BITMAP *WindLargeAnimArray[DEF_WIND_ANIM_NUM] = {
		&bmwind_large01, &bmwind_large02, &bmwind_large03, &bmwind_large04,
		&bmwind_large05, &bmwind_large06, &bmwind_large07, &bmwind_large08,
		&bmwind_large09, &bmwind_large10, &bmwind_large11, &bmwind_large12,
		&bmwind_large13, &bmwind_large14, &bmwind_large15, &bmwind_large16,
		&bmwind_large17, &bmwind_large18, &bmwind_large19, &bmwind_large20,
		&bmwind_large21, &bmwind_large22, &bmwind_large23, &bmwind_large24,
};
static GUI_CONST_STORAGE GUI_BITMAP *WindMiddleAnimArray[DEF_WIND_ANIM_NUM] = {
		&bmwind_middle01, &bmwind_middle02, &bmwind_middle03, &bmwind_middle04,
		&bmwind_middle05, &bmwind_middle06, &bmwind_middle07, &bmwind_middle08,
		&bmwind_middle09, &bmwind_middle10, &bmwind_middle11, &bmwind_middle12,
		&bmwind_middle13, &bmwind_middle14, &bmwind_middle15, &bmwind_middle16,
		&bmwind_middle17, &bmwind_middle18, &bmwind_middle19, &bmwind_middle20,
		&bmwind_middle21, &bmwind_middle22, &bmwind_middle23, &bmwind_middle24,
};
static GUI_CONST_STORAGE GUI_BITMAP *WindSmallAnimArray[DEF_WIND_ANIM_NUM] = {
		&bmwind_small01, &bmwind_small02, &bmwind_small03, &bmwind_small04,
		&bmwind_small05, &bmwind_small06, &bmwind_small07, &bmwind_small08,
		&bmwind_small09, &bmwind_small10, &bmwind_small11, &bmwind_small12,
		&bmwind_small13, &bmwind_small14, &bmwind_small15, &bmwind_small16,
		&bmwind_small17, &bmwind_small18, &bmwind_small19, &bmwind_small20,
		&bmwind_small21, &bmwind_small22, &bmwind_small23, &bmwind_small24,
};
static WM_HWIN _hMenuBar = WM_HMEM_NULL;
static GUI_TIMER_HANDLE _hWindTimer = WM_HMEM_NULL;
static U8 _AnimIsStart = 0;
static U8 _CurAnimIndex = 0;
static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;

	GUI_FullRectStyle BkStyle = {
			.MainColor = 0xff080808,
			.GradColor = 0xff080808,
			.Radius = 0,
			.Opacity = 0xff,
	};

	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, 0);
	WINDOW_SetBkColor(hParent, &BkStyle);

	//灯光按钮
	hItem = WM_GetDialogItem(hParent, ID_MENU_LIGHT);
	IMAGEVIEW_SetBitmap(hItem, &bmlight_unfocus);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//v line 1
	hItem = WM_GetDialogItem(hParent, ID_MENU_V_LINE1);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//小风按钮
	hItem = WM_GetDialogItem(hParent, ID_MENU_WIND_SMALL);
	IMAGEVIEW_SetBitmap(hItem, &bmwind_small);
	//IMAGEVIEW_SetBitmapHasTrans(hItem, 0xff070707);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//v line 2
	hItem = WM_GetDialogItem(hParent, ID_MENU_V_LINE2);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//中风按钮
	hItem = WM_GetDialogItem(hParent, ID_MENU_WIND_MIDDLE);
	IMAGEVIEW_SetBitmap(hItem, &bmwind_middle);
	//IMAGEVIEW_SetBitmapHasTrans(hItem, 0xff070707);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//v line 3
	hItem = WM_GetDialogItem(hParent, ID_MENU_V_LINE3);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//大风按钮
	hItem = WM_GetDialogItem(hParent, ID_MENU_WIND_LARGE);
	IMAGEVIEW_SetBitmap(hItem, &bmwind_large);
	//IMAGEVIEW_SetBitmapHasTrans(hItem, 0xff070707);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//v line 4
	hItem = WM_GetDialogItem(hParent, ID_MENU_V_LINE4);
	IMAGEVIEW_SetBkColor(hItem, 0xff404040);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	hBase = hItem;
	//一键智能按钮
	hItem = WM_GetDialogItem(hParent, ID_MENU_SMART);
	IMAGEVIEW_SetBitmap(hItem, &bmonekey_smart_unfocus);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, DEF_PART_PIXEL, 0);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 25, 0);
	hBase = hItem;

	WM_ShowWindowAndChild(hParent);
}

static void _AnimTimer_cb(GUI_TIMER_MESSAGE *pContext)
{
	if(_AnimIsStart){
		switch(Setting_GetWindStatus()){
			case WIND_SMALL:
				IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_WIND_SMALL), WindSmallAnimArray[_CurAnimIndex]);
			break;
			case WIND_MIDDLE:
				IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_WIND_MIDDLE), WindMiddleAnimArray[_CurAnimIndex]);
			break;
			case WIND_LARGE:
				IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_WIND_LARGE), WindLargeAnimArray[_CurAnimIndex]);
			break;
			default:
				_AnimIsStart = 0;
				_CurAnimIndex = 0;
				IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_WIND_SMALL), &bmwind_small);
				IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_WIND_MIDDLE), &bmwind_middle);
				IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_WIND_LARGE), &bmwind_large);
			break;
		}
		if(_CurAnimIndex < DEF_WIND_ANIM_NUM - 1){
			_CurAnimIndex++;
		}else{
			_CurAnimIndex = 0;
		}
	}
	if(LIGHT_OPEN == Setting_GetLightStatus()){
		IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_LIGHT), &bmlight_focus);
	}else{
		IMAGEVIEW_SetBitmap(WM_GetDialogItem(pContext->Context, ID_MENU_LIGHT), &bmlight_unfocus);
	}
	GUI_TIMER_Restart(_hWindTimer);
}

static void _WindAnimTimerInit(WM_HWIN hWin)
{
	if(WM_HMEM_NULL == _hWindTimer){
		_hWindTimer = GUI_TIMER_Create(_AnimTimer_cb, WM_TIMER + 1, hWin, 0);
		GUI_TIMER_SetPeriod(_hWindTimer, 100);
		GUI_TIMER_Restart(_hWindTimer);
	}
}
/*
static void _WindAnimTimerDelete(void)
{
	if(_hWindTimer){
		GUI_TIMER_Delete(_hWindTimer);
	}
}
*/
static void _cbWindowsMenuBarDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			_DialogInit(pMsg->hWin);
			_WindAnimTimerInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hMenuBar = WM_HMEM_NULL;
			_hWindTimer = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_MENU_LIGHT:
						if(LIGHT_OPEN == Setting_GetLightStatus()){
							Setting_SetLightStatus(LIGHT_CLOSE);
							IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_LIGHT), &bmlight_unfocus);
						}else{
							Setting_SetLightStatus(LIGHT_OPEN);
							IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_LIGHT), &bmlight_focus);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_MENU_WIND_SMALL:
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_MIDDLE), &bmwind_middle);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_LARGE), &bmwind_large);
						if(WIND_SMALL == Setting_GetWindStatus()){
							IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_SMALL), &bmwind_small);
							Setting_SetWindStatus(WIND_NONE);
						}else{
							_CurAnimIndex = 0;
							_AnimIsStart = 1;
							Setting_SetWindStatus(WIND_SMALL);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_MENU_WIND_MIDDLE:
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_SMALL), &bmwind_small);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_LARGE), &bmwind_large);
						if(WIND_MIDDLE == Setting_GetWindStatus()){
							IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_MIDDLE), &bmwind_middle);
							Setting_SetWindStatus(WIND_NONE);
						}else{
							_CurAnimIndex = 0;
							_AnimIsStart = 1;
							Setting_SetWindStatus(WIND_MIDDLE);
						}
						HoodCom_SendTouchVoice();
					break;
					case ID_MENU_WIND_LARGE:
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_SMALL), &bmwind_small);
						IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_MIDDLE), &bmwind_middle);
						if(WIND_LARGE == Setting_GetWindStatus()){
							IMAGEVIEW_SetBitmap(WM_GetDialogItem(pMsg->hWin, ID_MENU_WIND_LARGE), &bmwind_large);
							Setting_SetWindStatus(WIND_NONE);
						}else{
							_CurAnimIndex = 0;
							_AnimIsStart = 1;
							Setting_SetWindStatus(WIND_LARGE);
						}
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

WM_HWIN PageMenuBarCreate(void)
{
	if(WM_HMEM_NULL == _hMenuBar){
		GUI_Debug("menu bar create\n");
		_hMenuBar = GUI_CreateDialogBox(_aWindowsMenuBarCreate, GUI_COUNTOF(_aWindowsMenuBarCreate), _cbWindowsMenuBarDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("menu bar %d create end\n", _hMenuBar);
	}
	return _hMenuBar;
}
