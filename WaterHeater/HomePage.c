/*
 * HomePage.c
 *
 *  Created on: 2018年5月11日
 *      Author: Administrator
 */



#include <GUI_main.h>
#include "ImageResource.h"
#include "HomePage.h"
#include "TimerPage.h"
#include "KitchenPage.h"
#include "BathroomPage.h"
#include "BathtubPage.h"
#include "EnergyPage.h"
#include "SettingInfo.h"
#include "Lockscreen.h"
#include "PageListCreate.h"

#define ID_WINDOW_HOME				(ID_HOME_PAGE_BASE + 0)
#define ID_HOME_SWITCH				(ID_HOME_PAGE_BASE + 1)
#define ID_HOME_FIRE				(ID_HOME_PAGE_BASE + 2)
#define ID_HOME_TIMER				(ID_HOME_PAGE_BASE + 3)
#define ID_HOME_TEMPERATURE			(ID_HOME_PAGE_BASE + 4)
#define ID_HOME_KITCHEN				(ID_HOME_PAGE_BASE + 5)
#define ID_HOME_BATHROOM			(ID_HOME_PAGE_BASE + 6)
#define ID_HOME_BATHTUB				(ID_HOME_PAGE_BASE + 7)
#define ID_HOME_ENERGY				(ID_HOME_PAGE_BASE + 8)
#define ID_HOME_TEMP_VALUE			(ID_HOME_PAGE_BASE + 9)
#define ID_HOME_TEMP_UNIT			(ID_HOME_PAGE_BASE + 10)
/*
#define ID_HOME_FUNC_KITCHEN		(ID_HOME_PAGE_BASE + 9)
#define ID_HOME_FUNC_BATHROOM		(ID_HOME_PAGE_BASE + 10)
#define ID_HOME_FUNC_BATHTUB		(ID_HOME_PAGE_BASE + 11)
#define ID_HOME_FUNC_ENERGY			(ID_HOME_PAGE_BASE + 12)
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontFUN_YH35;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontFUN_YH48;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontNUM_YH75;
extern GUI_CONST_STORAGE GUI_BITMAP bmfire_anim1;
extern GUI_CONST_STORAGE GUI_BITMAP bmfire_anim2;
extern GUI_CONST_STORAGE GUI_BITMAP bmfire_anim3;
extern GUI_CONST_STORAGE GUI_BITMAP bmfire_anim4;
extern GUI_CONST_STORAGE GUI_BITMAP bmfire_anim5;
extern GUI_CONST_STORAGE GUI_BITMAP bmbtn_wd03;
extern GUI_CONST_STORAGE GUI_BITMAP bmwendu_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbathroom_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbathroom_unfocus1;
extern GUI_CONST_STORAGE GUI_BITMAP bmbathroom_unfocus2;
extern GUI_CONST_STORAGE GUI_BITMAP bmbathtub_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmbathtub_unfocus1;
extern GUI_CONST_STORAGE GUI_BITMAP bmbathtub_unfocus2;
extern GUI_CONST_STORAGE GUI_BITMAP bmfire_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmjieneng_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmjieneng_unfocus1;
extern GUI_CONST_STORAGE GUI_BITMAP bmjieneng_unfocus2;
extern GUI_CONST_STORAGE GUI_BITMAP bmkitchen_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmkitchen_unfocus1;
extern GUI_CONST_STORAGE GUI_BITMAP bmkitchen_unfocus2;
extern GUI_CONST_STORAGE GUI_BITMAP bmswitch_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmswitch_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmtimer_focus;
extern GUI_CONST_STORAGE GUI_BITMAP bmtimer_unfocus;
extern GUI_CONST_STORAGE GUI_BITMAP bmunit_temp_y;

static const GUI_WIDGET_CREATE_INFO _aWindowsHomeCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_HOME, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "switch",			ID_HOME_SWITCH, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "fire", 			ID_HOME_FIRE, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "timer",			ID_HOME_TIMER, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "temperature",		ID_HOME_TEMPERATURE, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "kitchen",			ID_HOME_KITCHEN, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "bathroom",			ID_HOME_BATHROOM, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "bathtub",			ID_HOME_BATHTUB, 0, 0, 250, 265, 0, 0x0,0},
	{ IMAGEBUTTON_CreateIndirect, "energy",			ID_HOME_ENERGY, 0, 0, 250, 265, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"temp value", 			ID_HOME_TEMP_VALUE, 0, 0, 90, 50, 0, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "temp unit", 			ID_HOME_TEMP_UNIT, 0, 0, 38, 33, 0, 0x0,0},
/*	{ TEXT_CreateIndirect, 	"func kitchen", 		ID_HOME_FUNC_KITCHEN, 0, 0, 80, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"func bathroom", 		ID_HOME_FUNC_BATHROOM, 0, 0, 80, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"func bathtub", 		ID_HOME_FUNC_BATHTUB, 0, 0, 80, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"func energy", 			ID_HOME_FUNC_ENERGY, 0, 0, 80, 50, 0, 0x0,0},
*/
};

static WM_HWIN hHomePage = WM_HMEM_NULL;


static void DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;
	/* btn switch */
	hItem = WM_GetDialogItem(hParent, ID_HOME_SWITCH);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmswitch_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmswitch_focus);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_SWITCH_REALEASE, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_SWITCH_PRESS, 0);
	GUI_Debug("home switch win:%d\n", hItem);
	/* btn fire */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_FIRE);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_FIRE_OFF, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_FIRE_ANIM_FIRE1, 1);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmfire_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmfire_anim1);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_DisableWindow(hItem);
	//IMAGEBUTTON_SetState(hItem, 1);
	/* btn timer */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_TIMER);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmtimer_unfocus);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmtimer_focus);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_TIMER_REALEASE, 1);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_TIMER_PRESS, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* btn temperature */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_TEMPERATURE);
	//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_TEMP_OFF, 1);
	//IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmwendu_unfocus);
	IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmwendu_unfocus);
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_TEMP_ON, 1);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbtn_wd03);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_DisableWindow(hItem);
	/* temperature value */
	BaseWin = hItem;
	//GUI_sprintf(Buffer, "%d", GetEnergyTempValue());
	hItem = WM_GetDialogItem(hParent, ID_HOME_TEMP_VALUE);
	TEXT_SetTextColor(hItem, 0xff812bed);
	TEXT_SetText(hItem, "36");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH75);
	TEXT_SetBkColor(hItem, GUI_WHITE);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER | GUI_TA_HCENTER);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 60, 80);
	WM_HideWindow(hItem);
	/* temperature unit */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_TEMP_UNIT);
	//IMAGEVIEW_SetFile(hItem, IMAGE_TEMP_UNIT, 0);
	IMAGEVIEW_SetBitmap(hItem, &bmunit_temp_y);
	IMAGEVIEW_SetChangeColor(hItem, 0xff812bed);
	//WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, -5);
	WM_HideWindow(hItem);
	/* btn kitchen */
	BaseWin = WM_GetDialogItem(hParent, ID_HOME_SWITCH);
	hItem = WM_GetDialogItem(hParent, ID_HOME_KITCHEN);
	if(FUNC_KITCHEN == GetWaterHeaterFuncSelect()){
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_KITCHEN_SELECT, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmkitchen_unfocus2);
	}else{
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_KITCHEN_REALEASE, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmkitchen_unfocus1);
	}
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_KITCHEN_PRESS, 0);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmkitchen_focus);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	/* btn bathroom */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_BATHROOM);
	if(FUNC_BATHROOM == GetWaterHeaterFuncSelect()){
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHROOM_SELECT, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbathroom_unfocus2);
	}else{
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHROOM_REALEASE, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbathroom_unfocus1);
	}
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_BATHROOM_PRESS, 0);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbathroom_focus);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_HOME_FIRE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	/* btn bathtub */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_BATHTUB);
	if(FUNC_BATHTUB == GetWaterHeaterFuncSelect()){
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHTUB_SELECT, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbathtub_unfocus2);
	}else{
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHTUB_REALEASE, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmbathtub_unfocus1);
	}
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_BATHTUB_PRESS, 0);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmbathtub_focus);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_HOME_TIMER), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	/* btn energy */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_ENERGY);
	if(FUNC_ENERGY == GetWaterHeaterFuncSelect()){
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_ENERGY_SELECT, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmjieneng_unfocus2);
	}else{
		//IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_ENERGY_REALEASE, 1);
		IMAGEBUTTON_SetUnFocusBitmap(hItem, &bmjieneng_unfocus1);
	}
	//IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_ENERGY_PRESS, 0);
	IMAGEBUTTON_SetFocusBitmap(hItem, &bmjieneng_focus);
	IMAGEBUTTON_SetUnFocusBitmapHasTrans(hItem, GUI_BLACK);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_HOME_TIMER), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
}


static void HomePageTimerInit(WM_HWIN hParent)
{

}
static U8 _FireIndex = 0;
static GUI_TIMER_HANDLE hAnimTimer;
static void _cbFireAnimationTimer(GUI_TIMER_MESSAGE *pTM)
{
	if(_FireIndex < 5){
		_FireIndex++;
	}else{
		_FireIndex = 1;
	}
	/*switch(_FireIndex){
		case 1:
			IMAGEBUTTON_SetFocusFile(WM_GetDialogItem(pTM->Context, ID_HOME_FIRE), IMAGE_FIRE_ANIM_FIRE1, 0);
		break;
		case 2:
			IMAGEBUTTON_SetFocusFile(WM_GetDialogItem(pTM->Context, ID_HOME_FIRE), IMAGE_FIRE_ANIM_FIRE2, 0);
		break;
		case 3:
			IMAGEBUTTON_SetFocusFile(WM_GetDialogItem(pTM->Context, ID_HOME_FIRE), IMAGE_FIRE_ANIM_FIRE3, 0);
		break;
		case 4:
			IMAGEBUTTON_SetFocusFile(WM_GetDialogItem(pTM->Context, ID_HOME_FIRE), IMAGE_FIRE_ANIM_FIRE4, 0);
		break;
		case 5:
			IMAGEBUTTON_SetFocusFile(WM_GetDialogItem(pTM->Context, ID_HOME_FIRE), IMAGE_FIRE_ANIM_FIRE5, 0);
		break;
		default:
			IMAGEBUTTON_SetFocusFile(WM_GetDialogItem(pTM->Context, ID_HOME_FIRE), IMAGE_HOME_FIRE_OFF, 0);
		break;
	}*/
	GUI_TIMER_Restart(hAnimTimer);
}
static void _FireAnimationTimerInit(WM_HWIN hParent)
{
	hAnimTimer = GUI_TIMER_Create(_cbFireAnimationTimer, 0, hParent, 0);
	GUI_TIMER_SetPeriod(hAnimTimer, 200);
	GUI_TIMER_Restart(hAnimTimer);
}
static void _cbWindowsHomeDialog(WM_MESSAGE * pMsg)
{
	int     NCode;
	int     Id;
	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			GUI_SetBkColor(GUI_GREEN);
			DialogInit(pMsg->hWin);
			HomePageTimerInit(pMsg->hWin);
			_FireAnimationTimerInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hHomePage = WM_HMEM_NULL;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				switch(Id){
					case ID_HOME_SWITCH:
						//IMAGEBUTTON_SetState(WM_GetDialogItem(pMsg->hWin, ID_HOME_TEMPERATURE), 1);
						//LockscreenPageCreate(WM_HBKWIN);
						PageListShowWinByName(PAGE_LOCKSCREEN);
					break;
					case  ID_HOME_TIMER:
						TimerPageCreate();
					return;
					case ID_HOME_TEMPERATURE:
						GUI_Debug("to hide\n");
						//WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_HOME_FIRE));
					break;
					case ID_HOME_KITCHEN:
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), &bmkitchen_unfocus2);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), &bmbathroom_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), &bmbathtub_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), &bmjieneng_unfocus1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_SELECT, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_REALEASE, 1);
						KitchenPageCreate();
						SetWaterHeaterFuncSelect(FUNC_KITCHEN);
					return;
					case ID_HOME_BATHROOM:
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), &bmkitchen_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), &bmbathroom_unfocus2);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), &bmbathtub_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), &bmjieneng_unfocus1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_SELECT, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_REALEASE, 1);
						BathroomPageCreate();
						SetWaterHeaterFuncSelect(FUNC_BATHROOM);
					break;
					case ID_HOME_BATHTUB:
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), &bmkitchen_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), &bmbathroom_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), &bmbathtub_unfocus2);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), &bmjieneng_unfocus1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_SELECT, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_REALEASE, 1);
						BathtubPageCreate();
						SetWaterHeaterFuncSelect(FUNC_BATHTUB);
					break;
					case ID_HOME_ENERGY:
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), &bmkitchen_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), &bmbathroom_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), &bmbathtub_unfocus1);
						IMAGEBUTTON_SetUnFocusBitmap(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), &bmjieneng_unfocus2);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_SELECT, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_REALEASE, 1);
						// IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_REALEASE, 1);
						EnergyPageCreate();
						SetWaterHeaterFuncSelect(FUNC_ENERGY);
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

WM_HWIN HomePageCreate(void)
{
	WaterHeaterDataInit();
	if(WM_HMEM_NULL == hHomePage){
		GUI_Debug("home page create\n");
		hHomePage = GUI_CreateDialogBox(_aWindowsHomeCreate, GUI_COUNTOF(_aWindowsHomeCreate), _cbWindowsHomeDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("home page %d create end\n", hHomePage);
	}
	return hHomePage;
}
