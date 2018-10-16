/*
 * PageLightSet.c
 *
 *  Created on: 2018年9月27日
 *      Author: Administrator
 */


#include "PageBrightnessSet.h"
#if COMPILE_ON_C600
#include "LCDControl.h"
#endif

#define ID_WINDOW_BRIGHTNESS_SET_SET 				(ID_PAGE_BRIGHTNESS_SET_BASE + 0)
#define ID_BRIGHTNESS_SET_SILDER					(ID_PAGE_BRIGHTNESS_SET_BASE + 1)
#define ID_BRIGHTNESS_SET_LEFT_ICON					(ID_PAGE_BRIGHTNESS_SET_BASE + 2)
#define ID_BRIGHTNESS_SET_RIGHT_ICON				(ID_PAGE_BRIGHTNESS_SET_BASE + 3)

static const GUI_WIDGET_CREATE_INFO _aDialogBrightnessSetCreate[] =
{
		{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_BRIGHTNESS_SET_SET, 161, 0, 700, DEF_DIALOG_HEIGHT, 0, 0x0,0},
		{ SLIDER_CreateIndirect,	"Silder", 				ID_BRIGHTNESS_SET_SILDER, 0, 0, 500, 60, 0, 0, 0},
		{ IMAGEVIEW_CreateIndirect,	"left icon", 			ID_BRIGHTNESS_SET_LEFT_ICON, 0, 0, 48, 49, 0, 0, 0},
		{ IMAGEVIEW_CreateIndirect,	"right icon", 			ID_BRIGHTNESS_SET_RIGHT_ICON, 0, 0, 58, 58, 0, 0, 0},
};
static WM_HWIN _hBrightnessSet = WM_HMEM_NULL;
static void _BrightnessSetDialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, hBase;
	/*GUI_FullRectStyle BgStyle = {
			.MainColor = GUI_GREEN,
			.GradColor = GUI_GREEN,
			.Radius = 0,
			.Opacity = 0xff,
	};*/
	WM_SetAlignParent(hParent, OBJ_ALIGN_PARENT_V_CENTRE, 0, 6);
	//WINDOW_SetBkColor(hParent, &BgStyle);

	hItem = WM_GetDialogItem(hParent, ID_BRIGHTNESS_SET_SILDER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	SLIDER_SetRange(hItem, 10, 99);
	SLIDER_SetValue(hItem, 60);
#if COMPILE_ON_C600
	SLIDER_SetValue(hItem, LCD_GetBrightness());
#endif
	hBase = hItem;

	hItem = WM_GetDialogItem(hParent, ID_BRIGHTNESS_SET_LEFT_ICON);
	IMAGEVIEW_SetBitmap(hItem, &bmlight_left_icon);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_LEFT, -10, 0);

	hItem = WM_GetDialogItem(hParent, ID_BRIGHTNESS_SET_RIGHT_ICON);
	IMAGEVIEW_SetBitmap(hItem, &bmlight_right_icon);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, 0);
	WM_SetAlignWindow(hBase, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 10, 0);

	WM_ShowWindowAndChild(hParent);
}

static void _cbBrightnessSetDialog(WM_MESSAGE * pMsg) {
	int     NCode;
	int     Id;

	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			_BrightnessSetDialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			_hBrightnessSet = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_BRIGHTNESS_SET_LEFT_ICON:
						SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, ID_BRIGHTNESS_SET_SILDER), 10);
						break;
					case ID_BRIGHTNESS_SET_RIGHT_ICON:
						SLIDER_SetValue(WM_GetDialogItem(pMsg->hWin, ID_BRIGHTNESS_SET_SILDER), 99);
						break;
				}
			}else if(NCode == WM_NOTIFICATION_VALUE_CHANGED){
				if(ID_BRIGHTNESS_SET_SILDER == Id){
#if COMPILE_ON_C600
					LCD_SetBrightness(SLIDER_GetValue(WM_GetDialogItem(pMsg->hWin, ID_BRIGHTNESS_SET_SILDER)));
#endif
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN PageBrightnessSetCreate(WM_HWIN hParent)
{
	if(WM_HMEM_NULL == _hBrightnessSet){
		_hBrightnessSet = GUI_CreateDialogBox(_aDialogBrightnessSetCreate, GUI_COUNTOF(_aDialogBrightnessSetCreate), _cbBrightnessSetDialog, hParent, 0, 0);
		GUI_Debug("_hBrightnessSet:%d\n", _hBrightnessSet);
	}
	return _hBrightnessSet;
}

WM_HWIN PageBrightnessGetHander(void)
{
	return _hBrightnessSet;
}
