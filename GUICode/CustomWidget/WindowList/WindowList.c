/*
 * WindowList.c
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */


#include "WindowList_Private.h"

#define DEF_ANIM_CONTINUE_TIME	300		//ms

static I32 _LastTouchYPos = 0;
static I32 _LastTouchXPos = 0;


static const char *_GetWinNameByWin(WM_HWIN hObj, WM_HWIN hCurWin);

static void _ShowNextWinCallback(WM_HWIN hWin, I32 Value)
{
	WindowList_Obj *pObj;
	pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hWin);
	//GUI_Debug("Value:%d, Window size:%d\n", Value, WM_GetWindowSizeX(hWin));
	WM_SetWindowPosX(pObj->hCurShowWin, Value);
	WM_SetWindowPosX(pObj->hNextShowWin, Value + WM_GetWindowSizeX(pObj->hCurShowWin));
}
static void _ShowPreWinCallback(WM_HWIN hWin, I32 Value)
{
	WindowList_Obj *pObj;
	pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hWin);
	WM_SetWindowPosX(pObj->hCurShowWin, Value);
	WM_SetWindowPosX(pObj->hNextShowWin, WM_GetWindowOrgX(pObj->hCurShowWin) - WM_GetWindowSizeX(pObj->hNextShowWin));
}
static void _MoveAnimEnd(WM_HWIN hWin)
{
	WindowList_Obj *pWinList;
	pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWin);
	if(1 == pWinList->FlagSwitchPage){
		WindowList_Obj *pWinList;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWin);
		pWinList->hCurShowWin = pWinList->hNextShowWin;
		if(pWinList->fWinShowChange){
				pWinList->fWinShowChange(pWinList->hNextShowWin, _GetWinNameByWin(hWin, pWinList->hCurShowWin));
		}
	}
	pWinList->hAnim = WM_HMEM_NULL;
	pWinList->FlagSwitchPage = 0;
}

static void _StartWindowSwitchAnim(WM_HWIN hObj, I32 Start, I32 End, I32 Time, U8 Flag)
{
	WindowList_Obj *pWinList;
	pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hObj);
	//WM_HWIN hParent;
	//hParent = WM_GetParent(hMoveOutWin);
	if(WM_HMEM_NULL == pWinList->hAnim){
		GUI_Animation_Obj Anim;
		GUI_AnimationObjInit(&Anim);
		Anim.Start = Start;
		Anim.End = End;
		Anim.Time = Time;
		if(Flag){
			Anim.pFunc = _ShowNextWinCallback;
		}else{
			Anim.pFunc = _ShowPreWinCallback;
		}
		Anim.pEnd = _MoveAnimEnd;
		pWinList->hAnim = GUI_AnimationCreate(hObj, &Anim);
	}
}
static WM_HWIN _GetNextWinByCurWinFromList(WM_HWIN hObj, WM_HWIN hCurWin)
{
	WindowList_Obj *pWinList;
	WindowListItem* pItem;
	U32 i = 0;
	U32 ItemNumber = 0;
	pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hObj);
	ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
	for(i = 0; i < ItemNumber; i++){
		pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
		if((pItem->hWin == hCurWin) && (i < ItemNumber - 1)){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i + 1);
			return pItem->hWin;
		}
	}
	return WM_HWIN_NULL;
}
static WM_HWIN _GetPreWinByCurWinFromList(WM_HWIN hObj, WM_HWIN hCurWin)
{
	WindowList_Obj *pWinList;
	WindowListItem* pItem;
	U32 i = 0;
	U32 ItemNumber = 0;
	pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hObj);
	ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
	for(i = 0; i < ItemNumber; i++){
		pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
		if((pItem->hWin == hCurWin) && (0 != i)){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i - 1);
			return pItem->hWin;
		}
	}
	return WM_HWIN_NULL;
}
static const char *_GetWinNameByWin(WM_HWIN hObj, WM_HWIN hCurWin)
{
	WindowList_Obj *pWinList;
	WindowListItem* pItem;
	U32 i = 0;
	U32 ItemNumber = 0;
	pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hObj);
	ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
	for(i = 0; i < ItemNumber; i++){
		pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
		if((pItem->hWin == hCurWin)){
			return pItem->WinName;
		}
	}
	return NULL;
}
static void _OnTouch(WM_HWIN hObj, WindowList_Obj* pObj, WM_MESSAGE *pMsg)
{
	//const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	GUI_PID_STATE tState;
	WM_PID__GetCurState(&tState);
	if(tState.Pressed){
		if(0 == pObj->FirstTouch){
			pObj->FirstTouch = 1;
			pObj->LastTouchXPos = tState.x;
			_LastTouchYPos = tState.y;
			_LastTouchXPos = tState.x;
		}else{
			//I16 WinWidth = WM_GetWindowSizeX(hObj);
			I32 CurPos = 0;
			I32 Dist = pObj->LastTouchXPos - tState.x;

			if((0 == pObj->IsMove) && ((Dist >= 30) || (Dist <= -30)) && (WM_HWIN_NULL == WM_GetCaptureHWin())){
				//WM_SetCapture(hObj, 1);
				WM_SetCaptureHWin(hObj);
				pObj->IsMove = 1;
			}
			if((_LastTouchYPos - tState.y > 50) || (tState.y - _LastTouchYPos > 50)){
				return;
			}
			if((1 == pObj->IsMove) && (hObj == WM_GetCaptureHWin())){
				if(pObj->UseAnim){
					WM_HWIN hNext;
					pObj->LastTouchXPos = tState.x;
					if((_LastTouchXPos - tState.x) > 0){
						hNext = _GetNextWinByCurWinFromList(hObj, pObj->hCurShowWin);
						if(WM_HWIN_NULL == hNext){
							return;
						}
						WM_SetWindowPosX(pObj->hCurShowWin, WM_GetWindowOrgX(pObj->hCurShowWin) - Dist);
						pObj->hNextShowWin = hNext;
						CurPos = WM_GetWindowOrgX(pObj->hCurShowWin) + WM_GetWindowSizeX(pObj->hCurShowWin);
						WM_SetWindowPosX(hNext, CurPos);
						if(CurPos <= WM_GetWindowOrgX(hObj)){
							pObj->hCurShowWin = pObj->hNextShowWin;
							WM_SetWindowPosX(pObj->hCurShowWin, WM_GetWindowOrgX(hObj));
						}
					}else{
						hNext = _GetPreWinByCurWinFromList(hObj, pObj->hCurShowWin);
						if(WM_HWIN_NULL == hNext){
							return;
						}
						WM_SetWindowPosX(pObj->hCurShowWin, WM_GetWindowOrgX(pObj->hCurShowWin) - Dist);
						pObj->hNextShowWin = hNext;
						CurPos = WM_GetWindowOrgX(pObj->hCurShowWin) - WM_GetWindowSizeX(hNext);
						WM_SetWindowPosX(hNext, CurPos);
						if(CurPos >= WM_GetWindowOrgX(hObj)){
							pObj->hCurShowWin = pObj->hNextShowWin;
							WM_SetWindowPosX(pObj->hCurShowWin, WM_GetWindowOrgX(hObj));
						}
					}
				}else{
					Dist = _LastTouchXPos - tState.x;
					if(Dist > (WM_GetWindowSizeX(hObj)/5)){
						WindowList_ShowNextWin(hObj);
					}else if((WM_GetWindowSizeX(hObj)/5) < -Dist){
						WindowList_ShowPrevWin(hObj);
					}
				}
				//WM_ShowWindow(pObj->hNextShowWin);
				WM_SetCapture(hObj, 2);
			}
		}
	}else{
		if(pObj->IsMove && pObj->UseAnim){
			I32 Dist = _LastTouchXPos - tState.x;
			if(Dist > 0){
				if(Dist > WM_GetWindowSizeX(hObj)/5){
					pObj->FlagSwitchPage = 1;
					WindowList_ShowNextWin(hObj);
				}else{
					I32 Time = 0;
					pObj->FlagSwitchPage = 0;
					Dist = WM_GetWindowOrgX(hObj) - WM_GetWindowOrgX(pObj->hCurShowWin);
					Time = (Dist * DEF_ANIM_CONTINUE_TIME)/WM_GetWindowSizeX(pObj->hCurShowWin);
					_StartWindowSwitchAnim(hObj, WM_GetWindowOrgX(pObj->hCurShowWin),
							WM_GetWindowOrgX(hObj), Time * 2, 1);
				}
			}else{
				Dist = -Dist;
				if(Dist > WM_GetWindowSizeX(hObj)/5){
					pObj->FlagSwitchPage = 1;
					WindowList_ShowPrevWin(hObj);
				}else{
					pObj->FlagSwitchPage = 0;
					I32 Time = 0;
					Dist = WM_GetWindowOrgX(pObj->hCurShowWin) - WM_GetWindowOrgX(hObj);
					Time = (Dist * DEF_ANIM_CONTINUE_TIME)/WM_GetWindowSizeX(pObj->hCurShowWin);
					_StartWindowSwitchAnim(hObj, WM_GetWindowOrgX(pObj->hCurShowWin),
							WM_GetWindowOrgX(hObj), Time, 0);
				}
			}
		}
		pObj->IsMove = 0;
		pObj->FirstTouch = 0;
		pObj->LastTouchXPos = -1;
		_LastTouchYPos = 0;
		_LastTouchXPos = 0;
		//WM_ReleaseCapture();
	}
}

static void _WinowList_Callback (WM_MESSAGE *pMsg)
{
	WM_HWIN hObj;
	WindowList_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (WindowList_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	//GUI_Debug("pMsg->MsgId:%d\n", pMsg->MsgId);
//	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
//		return;
//	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			///GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
			//_Paint(pObj, hObj);
		return;
		case WM_TOUCH:
		case WM_TOUCH_CHILD:
			if(WM_HMEM_NULL != pObj->hAnim){
				return;
			}
			_OnTouch(hObj, pObj, pMsg);
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
		pObj->hDestShowWin = WM_HWIN_NULL;
		pObj->UseAnim = 0;
		pObj->hAnim = WM_HMEM_NULL;
		pObj->FlagSwitchPage = 0;
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

void WindowList_SetShowByNameWin(WM_HWIN hWinList, const char *pShowWinName)
{
	if((NULL != pShowWinName) && hWinList){
		WindowList_Obj *pWinList;
		WindowListItem* pItem;
		U32 i = 0;
		U32 ItemNumber = 0;
		U32 CurWinPos = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if(pItem->hWin == pWinList->hCurShowWin){
				CurWinPos = i;
				break;
			}
		}
		for(i = 0; i < ItemNumber; i++){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if(0 == GUI_strcmp(pShowWinName, pItem->WinName)){
				if(pWinList->hCurShowWin != pItem->hWin){
					pWinList->hNextShowWin = pItem->hWin;
					if(pWinList->UseAnim){
						pWinList->FlagSwitchPage = 1;
						if(CurWinPos > i){
							_StartWindowSwitchAnim(hWinList, WM_GetWindowOrgX(pWinList->hCurShowWin),
									WM_GetWindowOrgX(hWinList) + WM_GetWindowSizeX(hWinList), DEF_ANIM_CONTINUE_TIME, 0);
						}else{
							_StartWindowSwitchAnim(hWinList, WM_GetWindowOrgX(pWinList->hCurShowWin),
									WM_GetWindowOrgX(hWinList) - WM_GetWindowSizeX(pWinList->hCurShowWin), DEF_ANIM_CONTINUE_TIME, 1);
						}
					}else{
						WM_SetWindowPosX(pWinList->hCurShowWin, -2000);
						WM_SetWindowPosX(pWinList->hNextShowWin, WM_GetWindowOrgX(hWinList));
						pWinList->hCurShowWin = pWinList->hNextShowWin;
						if(pWinList->fWinShowChange){
							pWinList->fWinShowChange(pWinList->hNextShowWin, pItem->WinName);
						}
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
		char *pWinName;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if((pItem->hWin == pWinList->hCurShowWin) && (i < ItemNumber - 1)){
				pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i + 1);
				pWinList->hNextShowWin = pItem->hWin;
				pWinName = pItem->WinName;
				if(pWinList->UseAnim){
					pWinList->FlagSwitchPage = 1;
					_StartWindowSwitchAnim(hWinList, WM_GetWindowOrgX(pWinList->hCurShowWin),
							WM_GetWindowOrgX(hWinList) - WM_GetWindowSizeX(pWinList->hCurShowWin), DEF_ANIM_CONTINUE_TIME, 1);
				}else{
					WM_SetWindowPosX(pWinList->hCurShowWin, -2000);
					WM_SetWindowPosX(pWinList->hNextShowWin, WM_GetWindowOrgX(hWinList));
					pWinList->hCurShowWin = pWinList->hNextShowWin;
					if(pWinList->fWinShowChange){
						pWinList->fWinShowChange(pWinList->hNextShowWin, pWinName);
					}
				}
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
		char *pWinName;
		U32 i = 0;
		U32 ItemNumber = 0;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		ItemNumber = GUI_ARRAY_GetNumItems(&pWinList->WinArray);
		for(i = 0; i < ItemNumber; i++){
			pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i);
			if((pItem->hWin == pWinList->hCurShowWin) && (0 != i)){
				pItem = (WindowListItem*)GUI_ARRAY_GetpItem(&pWinList->WinArray, i - 1);
				pWinList->hNextShowWin = pItem->hWin;
				pWinName = pItem->WinName;
				//_StartWindowSwitchAnim(pWinList->hCurShowWin, pWinList->hNextShowWin);
				if(pWinList->UseAnim){
					pWinList->FlagSwitchPage = 1;
					_StartWindowSwitchAnim(hWinList, WM_GetWindowOrgX(pWinList->hCurShowWin),
							WM_GetWindowOrgX(hWinList) + WM_GetWindowSizeX(hWinList), DEF_ANIM_CONTINUE_TIME, 0);
				}else{
					WM_SetWindowPosX(pWinList->hCurShowWin, -2000);
					WM_SetWindowPosX(pWinList->hNextShowWin, WM_GetWindowOrgX(hWinList));
					pWinList->hCurShowWin = pWinList->hNextShowWin;
					if(pWinList->fWinShowChange){
						pWinList->fWinShowChange(pWinList->hNextShowWin, pWinName);
					}
				}
				return;
			}
		}
	}
}
void WindowList_EnableAnim(WM_HWIN hWinList)
{
	if(hWinList){
		WindowList_Obj *pWinList;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		pWinList->UseAnim = 1;
	}
}
void WindowList_DisableAnim(WM_HWIN hWinList)
{
	if(hWinList){
		WindowList_Obj *pWinList;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		pWinList->UseAnim = 0;
	}
}
void WindowList_SetShowWinChangeCallback(WM_HWIN hWinList, void *pFunc)
{
	if(hWinList){
		WindowList_Obj *pWinList;
		pWinList = (WindowList_Obj *)GUI_ALLOC_h2p(hWinList);
		pWinList->fWinShowChange = (WinListShowChange)pFunc;
	}
}
