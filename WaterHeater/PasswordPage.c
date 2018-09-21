/*
 * PasswordPage.c
 *
 *  Created on: 2018年5月16日
 *      Author: Administrator
 */

#include <GUI_main.h>
#include "ImageResource.h"
#include "DialogPageNotice.h"
#include "PasswordPage.h"
#include "SettingPage.h"
#include "SettingPage2.h"
#include "TOTAST.h"

#define DEFAULT_PASSWORD				"123"

#define ID_WINDOW_PASSWORD					(ID_PASSWORD_PAGE_BASE + 0)
#define ID_PASSWORD_BG						(ID_PASSWORD_PAGE_BASE + 1)
#define ID_PASSWORD_EDIT					(ID_PASSWORD_PAGE_BASE + 2)
#define ID_PASSWORD_NUM_1_BG				(ID_PASSWORD_PAGE_BASE + 3)
#define ID_PASSWORD_NUM_1_TEXT				(ID_PASSWORD_PAGE_BASE + 4)
#define ID_PASSWORD_NUM_2_BG				(ID_PASSWORD_PAGE_BASE + 5)
#define ID_PASSWORD_NUM_2_TEXT				(ID_PASSWORD_PAGE_BASE + 6)
#define ID_PASSWORD_NUM_3_BG				(ID_PASSWORD_PAGE_BASE + 7)
#define ID_PASSWORD_NUM_3_TEXT				(ID_PASSWORD_PAGE_BASE + 8)
#define ID_PASSWORD_NUM_4_BG				(ID_PASSWORD_PAGE_BASE + 9)
#define ID_PASSWORD_NUM_4_TEXT				(ID_PASSWORD_PAGE_BASE + 10)
#define ID_PASSWORD_NUM_5_BG				(ID_PASSWORD_PAGE_BASE + 11)
#define ID_PASSWORD_NUM_5_TEXT				(ID_PASSWORD_PAGE_BASE + 12)
#define ID_PASSWORD_NUM_6_BG				(ID_PASSWORD_PAGE_BASE + 13)
#define ID_PASSWORD_NUM_6_TEXT				(ID_PASSWORD_PAGE_BASE + 14)
#define ID_PASSWORD_NUM_7_BG				(ID_PASSWORD_PAGE_BASE + 15)
#define ID_PASSWORD_NUM_7_TEXT				(ID_PASSWORD_PAGE_BASE + 16)
#define ID_PASSWORD_NUM_8_BG				(ID_PASSWORD_PAGE_BASE + 17)
#define ID_PASSWORD_NUM_8_TEXT				(ID_PASSWORD_PAGE_BASE + 18)
#define ID_PASSWORD_NUM_9_BG				(ID_PASSWORD_PAGE_BASE + 19)
#define ID_PASSWORD_NUM_9_TEXT				(ID_PASSWORD_PAGE_BASE + 20)
#define ID_PASSWORD_NUM_0_BG				(ID_PASSWORD_PAGE_BASE + 21)
#define ID_PASSWORD_NUM_0_TEXT				(ID_PASSWORD_PAGE_BASE + 22)
#define ID_PASSWORD_COMFIRM					(ID_PASSWORD_PAGE_BASE + 23)
#define ID_PASSWORD_DEL						(ID_PASSWORD_PAGE_BASE + 24)
#define ID_PASSWORD_RESTART					(ID_PASSWORD_PAGE_BASE + 25)
#define ID_PASSWORD_BACK					(ID_PASSWORD_PAGE_BASE + 26)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH48;
extern GUI_CONST_STORAGE GUI_BITMAP bmbg_srmm;
extern GUI_CONST_STORAGE GUI_BITMAP bmnum_bg_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmnum_bg_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_confirm_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_confirm_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_comeback_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_comeback_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_rewrite_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_rewrite_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_back2_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_back2_unfocus;

static const GUI_WIDGET_CREATE_INFO _aWindowsPasswordCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_PASSWORD, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "keyboard bg",		ID_PASSWORD_BG, 0, 0, 787, 404, 0, 0x0,0},
	{ EDIT_CreateIndirect, 	"password", 			ID_PASSWORD_EDIT, 0, 0, 200, 50, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num1 bg", 			ID_PASSWORD_NUM_1_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num1 text", 			ID_PASSWORD_NUM_1_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num2 bg",			ID_PASSWORD_NUM_2_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num2 text", 			ID_PASSWORD_NUM_2_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num3 bg",			ID_PASSWORD_NUM_3_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num3 text", 			ID_PASSWORD_NUM_3_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num4 bg",			ID_PASSWORD_NUM_4_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num4 text", 			ID_PASSWORD_NUM_4_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num5 bg",			ID_PASSWORD_NUM_5_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num5 text", 			ID_PASSWORD_NUM_5_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num6 bg",			ID_PASSWORD_NUM_6_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num6 text", 			ID_PASSWORD_NUM_6_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num7 bg",			ID_PASSWORD_NUM_7_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num7 text", 			ID_PASSWORD_NUM_7_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num8 bg",			ID_PASSWORD_NUM_8_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num8 text", 			ID_PASSWORD_NUM_8_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num9 bg",			ID_PASSWORD_NUM_9_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num9 text", 			ID_PASSWORD_NUM_9_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "num0 bg",			ID_PASSWORD_NUM_0_BG, 0, 0, 92, 94, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"num0 text", 			ID_PASSWORD_NUM_0_TEXT, 0, 0, 48, 48, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "comfirm",			ID_PASSWORD_COMFIRM, 0, 0, 172, 76, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "delete",			ID_PASSWORD_DEL, 0, 0, 172, 76, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "restart",			ID_PASSWORD_RESTART, 0, 0, 172, 76, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "back",				ID_PASSWORD_BACK, 0, 0, 92, 117, 0, 0x0,0},
};

static WM_HWIN hPasswordPage = WM_HMEM_NULL;

static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;
	/* setting keybord bg */
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_BG);
	//IMAGEVIEW_SetFile(hItem, IMAGE_PASSWORD_BG, 0);
	IMAGEVIEW_SetBitmap(hItem, &bmbg_srmm);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	GUI_Debug("password background win:%d, parent:%d\n", hItem, hParent);
	/* password edit */
	BaseWin = hItem,
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_EDIT);
	EDIT_SetFont(hItem, &GUI_FontNUM_YH48);
	EDIT_SetMaxLen(hItem, 3);
	EDIT_SetTextAlign(hItem, EDIT_CF_VCENTER | EDIT_CF_HCENTER);
	EDIT_DisableCursorBlink(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 80);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_H_CENTRE, -10, 0);
	GUI_Debug("Edit win:%d\n", hItem);
	/* num 1 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_1_BG);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 1);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 0, -20);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 100, 0);
	/* num 1 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_1_TEXT);
	TEXT_SetText(hItem, "1");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 2 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_1_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_2_BG);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* num 2 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_2_TEXT);
	TEXT_SetText(hItem, "2");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 3 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_2_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_3_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* num 3 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_3_TEXT);
	TEXT_SetText(hItem, "3");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 4 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_3_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_4_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* num 4 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_4_TEXT);
	TEXT_SetText(hItem, "4");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 5 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_4_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_5_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* num 5 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_5_TEXT);
	TEXT_SetText(hItem, "5");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 6 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_1_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_6_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	/* num 6 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_6_TEXT);
	TEXT_SetText(hItem, "6");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 7 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_6_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_7_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	/* num 7 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_7_TEXT);
	TEXT_SetText(hItem, "7");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 8 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_7_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_8_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	/* num 8 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_8_TEXT);
	TEXT_SetText(hItem, "8");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 9 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_8_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_9_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	/* num 9 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_9_TEXT);
	TEXT_SetText(hItem, "9");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* num 0 bg */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_9_BG),
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_0_BG);
//	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_NUM_REALEASE, 0);
//	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_NUM_PRESS, 0);
	//IMAGEBUTTON_SetUnFocusMapping(hItem, MapWin);
	//IMAGEBUTTON_SetFocusMapping(hItem, MapWin);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmnum_bg_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmnum_bg_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	/* num 0 text */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_0_TEXT);
	TEXT_SetText(hItem, "0");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH48);
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	WM_DisableWindow(hItem);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 0, 0);
	/* btn confirm */
	BaseWin = WM_GetDialogItem(hParent, ID_PASSWORD_NUM_6_BG);
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_COMFIRM);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_COMFIRM_REALEASE, 0);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_COMFIRM_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_confirm_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_confirm_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 0, 0);
	/* btn delete */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_DEL);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_DELETE_REALEASE, 0);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_DELETE_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_comeback_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_comeback_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* btn restart */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_RESTART);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_RESTART_REALEASE, 0);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_RESTART_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_rewrite_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_rewrite_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_TOP, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* btn back */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_PASSWORD_BACK);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_PASSWORD_BACK_REALEASE, 0);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_PASSWORD_BACK_PRESS, 0);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbtn_back2_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_back2_focus);
	WM_ClrHasTrans(hItem);
	IMAGEBUTTON_SetBkColor(hItem, GUI_DARKGRAY);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
}

static void _cbWindowsPasswordDialog(WM_MESSAGE * pMsg)
{
	int     NCode;
	int     Id;
	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hPasswordPage = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_PASSWORD_NUM_1_BG:
						WM_OnKey('1',1);
					break;
					case ID_PASSWORD_NUM_2_BG:
						WM_OnKey('2',1);
					break;
					case ID_PASSWORD_NUM_3_BG:
						WM_OnKey('3',1);
					break;
					case ID_PASSWORD_NUM_4_BG:
						WM_OnKey('4',1);
					break;
					case ID_PASSWORD_NUM_5_BG:
						WM_OnKey('5',1);
					break;
					case ID_PASSWORD_NUM_6_BG:
						WM_OnKey('6',1);
					break;
					case ID_PASSWORD_NUM_7_BG:
						WM_OnKey('7',1);
					break;
					case ID_PASSWORD_NUM_8_BG:
						WM_OnKey('8',1);
					break;
					case ID_PASSWORD_NUM_9_BG:
						WM_OnKey('9',1);
					break;
					case ID_PASSWORD_NUM_0_BG:
						WM_OnKey('0',1);
					break;
					case ID_PASSWORD_COMFIRM:
					{
						char PassBuffer[5];
						EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_PASSWORD_EDIT), PassBuffer, 3);
						GUI_Debug("password:%s\n", PassBuffer);
						if(0 == GUI_strcmp(DEFAULT_PASSWORD, PassBuffer)){
							WM_DeleteWindow(pMsg->hWin);
							SettingPageCreate();
						}else if(0 == GUI_strcmp("456", PassBuffer)){
							WM_DeleteWindow(pMsg->hWin);
							SettingPage2Create();
						}else{
							DialgPageNoticeCreate(ERROR_PASSWORD);
						}
					}
					break;
					case ID_PASSWORD_DEL:
						WM_OnKey(GUI_KEY_BACKSPACE,1);
					break;
					case ID_PASSWORD_RESTART:
						EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_PASSWORD_EDIT), "");
					break;
					case ID_PASSWORD_BACK:
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
void PasswordPageCreate(void)
{
	if(WM_HMEM_NULL == hPasswordPage){
		hPasswordPage = GUI_CreateDialogBox(_aWindowsPasswordCreate, GUI_COUNTOF(_aWindowsPasswordCreate), _cbWindowsPasswordDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("Password page create\n");
	}
}
