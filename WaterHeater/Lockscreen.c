/*
 * Lockscreen.c
 *
 *  Created on: 2018年5月28日
 *      Author: Administrator
 */

#include "Lockscreen.h"
#include "TimeSetPage.h"
#include "ImageResource.h"
#include "PageListCreate.h"


#define ID_WINDOW_LOCKSCREEN		(ID_LOCKSCREEN_PAGE_BASE + 0)
#define ID_LOCKSCREEN_BG			(ID_LOCKSCREEN_PAGE_BASE + 1)
#define ID_LOCKSCREEN_HOUR			(ID_LOCKSCREEN_PAGE_BASE + 2)
#define ID_LOCKSCREEN_MINUTE		(ID_LOCKSCREEN_PAGE_BASE + 3)
#define ID_LOCKSCREEN_UP_BAKC		(ID_LOCKSCREEN_PAGE_BASE + 4)
#define ID_LOCKSCREEN_WEEK			(ID_LOCKSCREEN_PAGE_BASE + 5)
#define ID_LOCKSCREEN_DATE			(ID_LOCKSCREEN_PAGE_BASE + 6)
#define ID_LOCKSCREEN_PICKER		(ID_LOCKSCREEN_PAGE_BASE + 7)
#define ID_LOCKSCREEN_TEST			(ID_LOCKSCREEN_PAGE_BASE + 10)

extern GUI_CONST_STORAGE GUI_FONT GUI_FontCHN_YH72;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCHN_YH40_1;
extern GUI_CONST_STORAGE GUI_BITMAP bmup_back;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalogclock_bg;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalogclock_pin_hour;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalogclock_pin_minute;

static const GUI_WIDGET_CREATE_INFO _aWindowsLockscreenCreate[] = {
	{ WINDOW_CreateIndirect,	"Window",				ID_WINDOW_LOCKSCREEN, 0, TITLE_BAR_HEIGHT, 1024, 600 - TITLE_BAR_HEIGHT, 0, 0x0, 0},
	{ IMAGEVIEW_CreateIndirect, "clock bg", 			ID_LOCKSCREEN_BG, 0, 0, 380, 383, WM_SF_HASTRANS, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "hour", 				ID_LOCKSCREEN_HOUR, 600, 200, 20, 178, WM_SF_HASTRANS, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "minute", 			ID_LOCKSCREEN_MINUTE, 30, 0, 4, 240, WM_SF_HASTRANS, 0x0,0},
	{ IMAGEVIEW_CreateIndirect, "upback", 			ID_LOCKSCREEN_UP_BAKC, 0, 0, 77, 52, WM_SF_HASTRANS, 0x0,0},
	//{ IMAGEVIEW_CreateIndirect, "minute", 			ID_LOCKSCREEN_TEST, 60, 20, 20, 178, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"week", 				ID_LOCKSCREEN_WEEK, 640, 275 - TITLE_BAR_HEIGHT, 180, 80, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"func bathroom", 		ID_LOCKSCREEN_DATE, 0, 0, 240, 50, 0, 0x0,0},
//	{ Picker_CreateIndirect, "picker",				ID_LOCKSCREEN_PICKER, 0, 0, 100, 230, 0, 0, 0},
/*	{ TEXT_CreateIndirect, 	"func bathtub", 		ID_HOME_FUNC_BATHTUB, 0, 0, 80, 50, 0, 0x0,0},
	{ TEXT_CreateIndirect, 	"func energy", 			ID_HOME_FUNC_ENERGY, 0, 0, 80, 50, 0, 0x0,0},
*/
};


static WM_HWIN hLockscreenPage = WM_HMEM_NULL;
static GUI_TIMER_HANDLE hTimer;
static I32 LastTouchPosY = 0;
static U8 FlagFirstTouch = 0;
static U16	Angle = 0;


static void _UpBackSetAlphaMethod(WM_HWIN hWin, I32 Value)
{
	IMAGEVIEW_SetAlpha(hWin, Value & 0xff);
}
static void _UpBackAnim(WM_HWIN hWin)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = 64;
	Anim.End = 0xff;
	Anim.Time = 2000;
	Anim.Playback = 1;
	Anim.PlaybackDelay = 500;
	Anim.pFunc = _UpBackSetAlphaMethod;
	GUI_AnimationCreate(hWin, &Anim);
}
/*
static void _PointRotatAnim(WM_HWIN hWin)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = 0;
	Anim.End = 360;
	Anim.Time = 60000;
	Anim.Repeat = 1;
	Anim.pFunc = IMAGEVIEW_SetRotateAngle;
	GUI_AnimationCreate(hWin, &Anim);
}
*/
static void __Timercb(GUI_TIMER_MESSAGE* pTM)
{
	Angle += 6;
	if(Angle >= 360){
		Angle = 0;
	}
	IMAGEVIEW_SetRotateAngle(WM_GetDialogItem(pTM->Context, ID_LOCKSCREEN_MINUTE), Angle);
	GUI_TIMER_Restart(hTimer);
}
static void _PonitRefreshTimerInit(WM_HWIN hParent)
{
	hTimer = GUI_TIMER_Create(__Timercb, 0, hParent, 0);
	GUI_TIMER_SetPeriod(hTimer, 1000);
	GUI_TIMER_Restart(hTimer);
}
static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem, BaseWin;
	//GUI_Debug("x:%d, y:%d\n", WM_GetWindowOrgX(hParent), WM_GetWindowOrgY(hParent));
	hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_BG);
	//IMAGEVIEW_SetFile(hItem, IMAGE_LOCKSCREEN_CLOCK_BG, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmanalogclock_bg);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_V_CENTRE, 40, 0);
	GUI_Debug("clock bg win %d\n", hItem);

	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_HOUR);
	//IMAGEVIEW_SetFile(hItem, IMAGE_LOCKSCREEN_CLOCK_HOUR, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmanalogclock_pin_hour);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 1, 1);
	IMAGEVIEW_SetRotateAngle(hItem, 0);
	GUI_Debug("hour point win %d\n", hItem);

	hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_MINUTE);
	//IMAGEVIEW_SetFile(hItem, IMAGE_LOCKSCREEN_CLOCK_MINUTE, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmanalogclock_pin_minute);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_CENTER, 1, 1);
	//IMAGEVIEW_SetRotateAngle(hItem, 35);
	GUI_Debug("minute point win %d\n", hItem);

	hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_UP_BAKC);
	//IMAGEVIEW_SetFile(hItem, IMAGE_LOCKSCREEN_UP_BACK, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmup_back);
	IMAGEVIEW_SetAlpha(hItem, 100);
	_UpBackAnim(hItem);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_BOTTOM_CENTRE, 0, -10);
	GUI_Debug("upback win %d\n", hItem);

	hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_WEEK);
	TEXT_SetFont(hItem, &GUI_FontCHN_YH72);
	TEXT_SetText(hItem, "星期三");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	GUI_Debug("week win %d\n", hItem);

	BaseWin = hItem;
	hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_DATE);
	TEXT_SetFont(hItem, &GUI_FontCHN_YH40_1);
	TEXT_SetText(hItem, "2018年7月11日");
	TEXT_SetTextAlign(hItem, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	TEXT_SetTextColor(hItem, GUI_WHITE);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_UNDER_BOTTOM, 0, 0);
	WM_SetAlignWindow(BaseWin, hItem, OBJ_ALIGN_BROTHER_LEFT,-30, 0);
	//WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 20, 20);
	GUI_Debug("date win %d\n", hItem);

	/*hItem = WM_GetDialogItem(hParent, ID_LOCKSCREEN_PICKER);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);*/
	_PonitRefreshTimerInit(hParent);

}

static U8 _DeleteFlag= 0;
static void _cbWindowsLockscreenDialog(WM_MESSAGE * pMsg)
{
	int     NCode;
	int     Id;
	switch (pMsg->MsgId){
		case WM_INIT_DIALOG:
			GUI_Debug("WM_INIT_DIALOG\n");
			_DialogInit(pMsg->hWin);
		return;
		case WM_DELETE:
			hLockscreenPage = WM_HMEM_NULL;
			FlagFirstTouch = 0;
			LastTouchPosY = 0;
			WM__SetWaitTouchRelease();
			_DeleteFlag = 0;
		return;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(NCode == WM_NOTIFICATION_RELEASED){
				if(ID_LOCKSCREEN_WEEK == Id){
					//TimeSetPageCreate();
					PageListShowWinByName(PAGE_TIME_SET);
				}
			}
		return;
		case WM_TOUCH:
		case WM_TOUCH_CHILD:
			{
				GUI_PID_STATE State;
				GUI_PID_GetState(&State);
				/*GUI_Debug("Touch week x:%d, y:%d\n", State.x, State.y);
				WM_SetWindowPos(WM_GetDialogItem(pMsg->hWin, ID_LOCKSCREEN_WEEK), State.x, State.y);
				return;*/
				if(State.Pressed){
					if(0 == FlagFirstTouch){
						FlagFirstTouch = 1;
						LastTouchPosY = State.y;
					}else{
						if(LastTouchPosY - State.y > 120){
							GUI_Debug("Delete lockscreen page\n");
							//WM_DeleteWindow(hLockscreenPage);
							//if(0 == _DeleteFlag){
								//_DeleteFlag = 1;
								//GUI_StartPageAnimationMoveOut(pMsg->hWin, 0, 1024, 300);
								PageListShowWinByName(PAGE_HOME);
							//}
						}
					}
				}else{
					LastTouchPosY = 0;
					FlagFirstTouch = 0;
				}
			}
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}


WM_HWIN LockscreenPageCreate(void)
{

	if(WM_HMEM_NULL == hLockscreenPage){
		hLockscreenPage = GUI_CreateDialogBox(_aWindowsLockscreenCreate, GUI_COUNTOF(_aWindowsLockscreenCreate), _cbWindowsLockscreenDialog, WM_HBKWIN, 0, 0);
		//GUI_SetPageSwitchAnimation(hLockscreenPage);
		GUI_Debug("hLockscreenPage:%d\n", hLockscreenPage);
	}
	return hLockscreenPage;
}
