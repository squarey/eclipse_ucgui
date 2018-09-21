/*
 * WindowList.c
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */


#include "WindowList_Private.h"

static void _MoveAnimCallback(WM_HWIN hWin, I32 Value)
{
	WindowList_Obj *pObj;
	pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hWin);
	//GUI_Debug("Value:%d, Window size:%d\n", Value, WM_GetWindowSizeX(hWin));
	WM_SetWindowPosX(pObj->hCurShowWin, Value - WM_GetWindowSizeX(hWin));
	WM_SetWindowPosX(pObj->hNextShowWin, Value);
}
static void _MoveAnimEnd(WM_HWIN hWin)
{
	WindowList_Obj *pObj;
	pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hWin);
	pObj->hLastShowWin = pObj->hCurShowWin;
	pObj->hCurShowWin = pObj->hNextShowWin;
}

static void _StartWindowSwitchAnim(WM_HWIN hMoveOutWin, WM_HWIN hMoveInWin)
{
	GUI_Animation_Obj Anim;
	WM_HWIN hParent;
	hParent = WM_GetParent(hMoveOutWin);
	GUI_AnimationObjInit(&Anim);
	Anim.Start = WM_GetWindowSizeX(hParent);
	Anim.End = WM_GetWindowOrgX(hParent);
	Anim.Time = 300;
	Anim.pFunc = _MoveAnimCallback;
	Anim.pEnd = _MoveAnimEnd;
	GUI_AnimationCreate(hParent, &Anim);
}


static void _WinowList_Callback (WM_MESSAGE *pMsg)
{
	WM_HWIN hObj;
	WindowList_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
//	GUI_Debug("pMsg->MsgId:%d\n", pMsg->MsgId);
//	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
//		return;
//	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			///GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
			//_Paint(pObj, hObj);
		return;
		case WM_TOUCH:
			//_OnTouch(hObj, pObj, pMsg);
		break;
		case WM_DELETE:
			GUI_ARRAY_Delete(&pObj->WinArray);
		break;
		case WM_KEY:
		break;
	}
	WM_DefaultProc(pMsg);
}

WM_HWIN WindowList_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	WM_HWIN hObj;
	/* Create the window */
	//WinFlags |= WM_SF_HASTRANS;
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _WinowList_Callback, sizeof(WindowList_Obj) - sizeof(WM_Obj));
	if (hObj) {
		WindowList_Obj * pObj;
		pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* Handle SpecialFlags */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		GUI_ARRAY_CREATE(&(pObj->WinArray));
		//WM_DisableWindow(hObj);
		pObj->hCurShowWin = WM_HWIN_NULL;
		pObj->hNextShowWin = WM_HWIN_NULL;
		pObj->hLastShowWin = WM_HWIN_NULL;
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "WindowList_CreateEx failed");
	}
	return hObj;
}

void WindowList_AddWin(WM_HWIN hWinList, WM_HWIN hAddWin, const char *pWinName)
{
	if(hWinList && hAddWin){
		WindowList_Obj *pWinList;
		WindowListItem Item;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		if (GUI_ARRAY_AddItem(&pWinList->WinArray, &Item, sizeof(WindowListItem) + GUI_strlen(pWinName)) == 0) {
			unsigned ItemIndex = GUI_ARRAY_GetNumItems(&pWinList->WinArray) - 1;
			WindowListItem* pItem= (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, ItemIndex);
			pItem->hWin = hAddWin;
			GUI_strcpy(pItem->WinName, pWinName);
			WM_SetParent(hWinList, hAddWin);
			if(WM_HWIN_NULL == pWinList->hCurShowWin){
				pWinList->hCurShowWin = hAddWin;
				WM_SetAlignParent(hAddWin, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
			}else{
				WM_SetAlignParent(hAddWin, OBJ_ALIGN_PARENT_RIGHT_CENTER, WM_GetWindowSizeX(hAddWin) + 5, 0);
			}
		}
	}
}

void WindowList_RemoveWinByName(WM_HWIN hWinList, const char *pWinName)
{
	if((NULL != pWinName) && hWinList){
		WindowList_Obj *pWinList;
		U32 i = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		U32 ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			WindowListItem* pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if(0 == GUI_strcmp(pWinName, pItem->WinName)){
				if(pWinList->hCurShowWin == pItem->hWin){
					WindowListItem* sItem;
					if(i == ItemNumber - 1){
						sItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i - 1);
					}else{
						sItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i + 1);
					}
					WM_SetAlignParent(pWinList->hCurShowWin, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
					pWinList->hCurShowWin = sItem->hWin;
				}
				GUI_ARRAY_DeleteItem(&pWinList->WinArray, i);
				//return;
			}
		}
	}
}

void WindowList_RemoveWin(WM_HWIN hWinList, WM_HWIN hRemoveWin)
{
	if(hRemoveWin && hWinList){
		WindowList_Obj *pWinList;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			WindowListItem* pItem= (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if(hRemoveWin == pItem->hWin){
				if(pWinList->hCurShowWin == pItem->hWin){
					WindowListItem* sItem;
					if(i == ItemNumber - 1){
						sItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i - 1);
					}else{
						sItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i + 1);
					}
					WM_SetAlignParent(pWinList->hCurShowWin, OBJ_ALIGN_PARENT_CENTRE, 0, 0);
					pWinList->hCurShowWin = sItem->hWin;
				}
				GUI_ARRAY_DeleteItem(&pWinList->WinArray, i);
				return;
			}
		}
	}
}

void WindowList_SetShowByNameWin(WM_HWIN hWinList, const char *pShowWinName, U8 UseAnim)
{
	if((NULL != pShowWinName) && hWinList){
		WindowList_Obj *pWinList;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			WindowListItem* pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if(0 == GUI_strcmp(pShowWinName, pItem->WinName)){
				if(pWinList->hCurShowWin != pItem->hWin){
					pWinList->hNextShowWin = pItem->hWin;
					if(UseAnim){
						_StartWindowSwitchAnim(pWinList->hCurShowWin, pWinList->hNextShowWin);
					}else{
						WM_SetWindowPosX(pWinList->hCurShowWin, -2000);
						WM_SetWindowPosX(pWinList->hNextShowWin, WM_GetWindowOrgX(hWinList));
						pWinList->hLastShowWin = pWinList->hCurShowWin;
						pWinList->hCurShowWin = pWinList->hNextShowWin;
					}
					return;
				}
			}
		}
	}
}

void WindowList_SetShowWin(WM_HWIN hWinList, WM_HWIN hShowWin)
{
	if(hShowWin && hWinList){
		WindowList_Obj *pWinList;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			WindowListItem* pItem= (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if(hShowWin == pItem->hWin){
				if(pWinList->hCurShowWin != pItem->hWin){
					pWinList->hNextShowWin = pItem->hWin;
					return;
				}
			}
		}
	}
}

void WindowList_ShowNextWin(WM_HWIN hWinList)
{
	if(hWinList){
		WindowList_Obj *pWinList;
		WindowListItem* pItem;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if((pItem->hWin == pWinList->hCurShowWin) && (i < ItemNumber - 1)){
				pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i + 1);
				pWinList->hNextShowWin = pItem->hWin;
				_StartWindowSwitchAnim(pWinList->hCurShowWin, pWinList->hNextShowWin);
				return;
			}
		}
	}
}

void WindowList_ShowPrevWin(WM_HWIN hWinList)
{
	if(hWinList){
		WindowList_Obj *pWinList;
		WindowListItem* pItem;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if((pItem->hWin == pWinList->hCurShowWin) && (0 != i)){
				pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i - 1);
				pWinList->hNextShowWin = pItem->hWin;
				_StartWindowSwitchAnim(pWinList->hCurShowWin, pWinList->hNextShowWin);
				return;
			}
		}
	}
}
