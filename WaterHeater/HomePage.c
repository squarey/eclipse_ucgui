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
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_SWITCH_REALEASE, 1);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_SWITCH_PRESS, 0);
	GUI_Debug("home win %d, switch win %d\n", hParent, hItem);
	/* btn fire */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_FIRE);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_FIRE_OFF, 1);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_FIRE_ANIM_FIRE1, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_DisableWindow(hItem);
	//IMAGEBUTTON_SetState(hItem, 1);
	/* btn timer */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_TIMER);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_TIMER_REALEASE, 1);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_TIMER_PRESS, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	/* btn temperature */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_TEMPERATURE);
	IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_TEMP_OFF, 0);
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_TEMP_ON, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_DisableWindow(hItem);
	/* temperature value */
	BaseWin = hItem;
	//GUI_sprintf(Buffer, "%d", GetEnergyTempValue());
	hItem = WM_GetDialogItem(hParent, ID_HOME_TEMP_VALUE);
	TEXT_SetTextColor(hItem, 0xff812bed);
	TEXT_SetText(hItem, "36");
	TEXT_SetFont(hItem, &GUI_FontNUM_YH75);
	TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER | GUI_TA_HCENTER);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT, 60, 80);
	WM_HideWindow(hItem);
	/* temperature unit */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_TEMP_UNIT);
	IMAGEVIEW_SetFile(hItem, IMAGE_TEMP_UNIT, 0);
	IMAGEVIEW_SetChangeColor(hItem, 0xff812bed);
	//WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_RIGHT, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_BOTTOM, 0, -5);
	WM_HideWindow(hItem);
	/* btn kitchen */
	BaseWin = WM_GetDialogItem(hParent, ID_HOME_SWITCH);
	hItem = WM_GetDialogItem(hParent, ID_HOME_KITCHEN);
	if(FUNC_KITCHEN == GetWaterHeaterFuncSelect()){
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_KITCHEN_SELECT, 1);
	}else{
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_KITCHEN_REALEASE, 1);
	}
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_KITCHEN_PRESS, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	/* btn bathroom */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_BATHROOM);
	if(FUNC_BATHROOM == GetWaterHeaterFuncSelect()){
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHROOM_SELECT, 1);
	}else{
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHROOM_REALEASE, 1);
	}
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_BATHROOM_PRESS, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_HOME_FIRE), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	GUI_Debug("hwin bathroom:%d\n", hItem);
	/* btn bathtub */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_BATHTUB);
	if(FUNC_BATHTUB == GetWaterHeaterFuncSelect()){
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHTUB_SELECT, 1);
	}else{
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_BATHTUB_REALEASE, 1);
	}
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_BATHTUB_PRESS, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_HOME_TIMER), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	GUI_Debug("hwin bathtub:%d\n", hItem);
	/* btn energy */
	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_HOME_ENERGY);
	if(FUNC_ENERGY == GetWaterHeaterFuncSelect()){
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_ENERGY_SELECT, 1);
	}else{
		IMAGEBUTTON_SetUnFocusFile(hItem, IMAGE_HOME_ENERGY_REALEASE, 1);
	}
	IMAGEBUTTON_SetFocusFile(hItem, IMAGE_HOME_ENERGY_PRESS, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_OUT_RIGHT, 0, 0);
	WM_SetAlignWindow(WM_GetDialogItem(hParent, ID_HOME_TIMER), hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	GUI_Debug("hwin energy:%d\n", hItem);
	/* func kitchen */
//	BaseWin = WM_GetDialogItem(hParent, ID_HOME_KITCHEN);
//	hItem = WM_GetDialogItem(hParent, ID_HOME_FUNC_KITCHEN);
//	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 85, -72);
//	TEXT_SetTextColor(hItem, GUI_WHITE);
//	//TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
//	TEXT_SetFont(hItem, &GUI_FontFUN_YH48);
//	TEXT_SetTextColor(hItem, GUI_BLUE);
//	TEXT_SetText(hItem, "厨房");
//	TEXT_SetBkColor(hItem, GUI_BLACK);
//	WM_ClrHasTrans(hItem);
//	/* func bathroom */
//	//BaseWin = WM_GetDialogItem(hParent, ID_HOME_KITCHEN);
//	hItem = WM_GetDialogItem(hParent, ID_HOME_FUNC_BATHROOM);
//	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 85 + 250 + 2, -72);
//	TEXT_SetTextColor(hItem, GUI_WHITE);
//	//TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
//	TEXT_SetFont(hItem, &GUI_FontFUN_YH48);
//	TEXT_SetTextColor(hItem, GUI_BLUE);
//	TEXT_SetText(hItem, "浴室");
//	TEXT_SetBkColor(hItem, GUI_BLACK);
//	WM_ClrHasTrans(hItem);
//	/* func bathtub */
//	//BaseWin = WM_GetDialogItem(hParent, ID_HOME_KITCHEN);
//	hItem = WM_GetDialogItem(hParent, ID_HOME_FUNC_BATHTUB);
//	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 85 + 250*2 + 5, -73);
//	TEXT_SetTextColor(hItem, GUI_WHITE);
//	//TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
//	TEXT_SetFont(hItem, &GUI_FontFUN_YH48);
//	TEXT_SetTextColor(hItem, GUI_BLUE);
//	TEXT_SetText(hItem, "浴缸");
//	TEXT_SetBkColor(hItem, GUI_BLACK);
//	WM_ClrHasTrans(hItem);
//	/* func energy */
//	//BaseWin = WM_GetDialogItem(hParent, ID_HOME_KITCHEN);
//	hItem = WM_GetDialogItem(hParent, ID_HOME_FUNC_ENERGY);
//	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 85 + 250*3 + 6, -73);
//	TEXT_SetTextColor(hItem, GUI_WHITE);
//	//TEXT_SetTextAlign(hItem, TEXT_CF_VCENTER);
//	TEXT_SetFont(hItem, &GUI_FontFUN_YH48);
//	TEXT_SetTextColor(hItem, GUI_BLUE);
//	TEXT_SetText(hItem, "节能");
//	TEXT_SetBkColor(hItem, GUI_BLACK);
//	WM_ClrHasTrans(hItem);
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
						LockscreenPageCreate();
					break;
					case  ID_HOME_TIMER:
						TimerPageCreate();
					return;
					case ID_HOME_TEMPERATURE:
						GUI_Debug("to hide\n");
						//WM_HideWindow(WM_GetDialogItem(pMsg->hWin, ID_HOME_FIRE));
					break;
					case ID_HOME_KITCHEN:
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_SELECT, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_REALEASE, 1);
						KitchenPageCreate();
						SetWaterHeaterFuncSelect(FUNC_KITCHEN);
					return;
					case ID_HOME_BATHROOM:
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_SELECT, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_REALEASE, 1);
						BathroomPageCreate();
						SetWaterHeaterFuncSelect(FUNC_BATHROOM);
					break;
					case ID_HOME_BATHTUB:
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_SELECT, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_REALEASE, 1);
						BathtubPageCreate();
						SetWaterHeaterFuncSelect(FUNC_BATHTUB);
					break;
					case ID_HOME_ENERGY:
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_ENERGY), IMAGE_HOME_ENERGY_SELECT, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_KITCHEN), IMAGE_HOME_KITCHEN_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHROOM), IMAGE_HOME_BATHROOM_REALEASE, 1);
						IMAGEBUTTON_SetUnFocusFile(WM_GetDialogItem(pMsg->hWin, ID_HOME_BATHTUB), IMAGE_HOME_BATHTUB_REALEASE, 1);
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

void HomePageCreate(void)
{
	WaterHeaterDataInit();
	if(WM_HMEM_NULL == hHomePage){
		GUI_Debug("home page create\n");
		hHomePage = GUI_CreateDialogBox(_aWindowsHomeCreate, GUI_COUNTOF(_aWindowsHomeCreate), _cbWindowsHomeDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("home page %d create end\n", hHomePage);
	}
}
