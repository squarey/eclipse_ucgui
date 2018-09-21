/*
 * BootPage.c
 *
 *  Created on: 2018年8月8日
 *      Author: Administrator
 */


#include "BootPage.h"
#include "ImageResource.h"
#include "TitleBar.h"
#include "HomePage.h"
#include "Lockscreen.h"
#include "PageListCreate.h"


#define ID_WINDOW_BOOT		(ID_BOOT_PAGE + 0)
#define ID_IMAGE_ANIM		(ID_BOOT_PAGE + 1)

extern GUI_CONST_STORAGE GUI_BITMAP bmboot_anim;

static const GUI_WIDGET_CREATE_INFO _WindowBootPageCreate[] =
{
		{WINDOW_CreateIndirect, "window", ID_WINDOW_BOOT, 0, 0, 1024, 600, 0, 0, 0},
		{IMAGEVIEW_CreateIndirect, "anim", ID_IMAGE_ANIM, 0, 0, 584, 144, WM_SF_HASTRANS, 0x0, 0},
};

static WM_HWIN	hBoot = WM_HWIN_NULL;


static void _BootImageSetAlphaMethod(WM_HWIN hWin, I32 Value)
{
	IMAGEVIEW_SetAlpha(hWin, Value & 0xff);
}
static void _BootImageAnimEnd(WM_HWIN hWin)
{
	WM_DeleteWindow(WM_GetParent(hWin));
	TitleBarCreate();
	//HomePageCreate();
	//LockscreenPageCreate();
	PageListCreate();
}
static void _BootAnimCreate(WM_HWIN hWin)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = 0;
	Anim.End = 0xff;
	Anim.Time = 1500;
	Anim.Playback = 0;
	Anim.pEnd = _BootImageAnimEnd;
	Anim.pFunc = _BootImageSetAlphaMethod;
	GUI_AnimationCreate(hWin, &Anim);
}

static void _DialogInit(WM_HWIN hParent)
{
	WM_HWIN hItem;
	hItem = WM_GetDialogItem(hParent, ID_IMAGE_ANIM);
	//IMAGEVIEW_SetFile(hItem, IMAGE_BOOT_ANIM, 1);
	IMAGEVIEW_SetBitmap(hItem, &bmboot_anim);
	WM_SetAlignParent(hItem, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
	IMAGEVIEW_SetAlpha(hItem, 0);
	_BootAnimCreate(hItem);
}


static void _cbWindowBootDialog(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId){
		case WM_INIT_DIALOG:
			_DialogInit(pMsg->hWin);
		break;
		case WM_DELETE:
			hBoot = WM_HWIN_NULL;
		break;
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}

void BootPageCreate(void)
{
	if(WM_HWIN_NULL == hBoot){
		hBoot = GUI_CreateDialogBox(_WindowBootPageCreate, GUI_COUNTOF(_WindowBootPageCreate),
				_cbWindowBootDialog, WM_HBKWIN, 0, 0);
		GUI_Debug("boot page:%d\n", hBoot);
	}
}
