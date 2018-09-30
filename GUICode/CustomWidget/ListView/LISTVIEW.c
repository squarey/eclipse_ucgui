

#include "GUI_Protected.h"
#include "WIDGET.h"
#include "LISTVIEW.h"
#include "LISTVIEW_Private.h"
#include "GUI_Animation.h"



#if GUI_WINSUPPORT && LISTVIEW_SUPPORT

#ifndef LISTVIEW_FONT_DEFAULT
  #define LISTVIEW_FONT_DEFAULT GUI_DEFAULT_FONT    /* Default Text Font */
#endif

#ifndef LISTVIEW_BKCOLOR0_DEFAULT
  #define LISTVIEW_BKCOLOR0_DEFAULT 0     /* Not selected Background Color */
#endif
#ifndef LISTVIEW_BKCOLOR1_DEFAULT
  #define LISTVIEW_BKCOLOR1_DEFAULT GUI_RED     /* Selected Background Color */
#endif

#ifndef LISTVIEW_TEXTCOLOR0_DEFAULT
  #define LISTVIEW_TEXTCOLOR0_DEFAULT GUI_WHITE   /* Not Selected Text Color */
#endif

#ifndef LISTVIEW_TEXTCOLOR1_DEFAULT
  #define LISTVIEW_TEXTCOLOR1_DEFAULT GUI_WHITE   /* Selected Text Color */
#endif

#define LISTVIEW_STRING_X_REDUCE	10

static LISTVIEW_PROPS LISTVIEW_DefaultProps = {
	LISTVIEW_FONT_DEFAULT,				//.pFont
	LISTVIEW_BKCOLOR0_DEFAULT,			//.aBackColor[0]
	LISTVIEW_BKCOLOR1_DEFAULT,			//.aBackColor[1]
	LISTVIEW_TEXTCOLOR0_DEFAULT,		//.aTextColor[0]
	LISTVIEW_TEXTCOLOR1_DEFAULT,		//.aTextColor[1]
};

static I32 LastTouchYPos = 0;
static char IsFirstTouch = 0;


/* ��ȡitem��Y���С */
/*
static I32 _GetItemSizeY(const LISTVIEW_Obj* pObj)
{
	return pObj->ItemYSize;
}*/
/* get item numbers */
static unsigned _LISTVIEW__GetNumItems(const LISTVIEW_Obj* pObj)
{
	return GUI_ARRAY_GetNumItems(&pObj->ItemArray);
}

/* get item by index */
static void *_GetItem(const LISTVIEW_Obj* pObj,unsigned Index)
{
	void *pItem;
	pItem = (void*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
	return pItem;
}


static void _LISTVIEW_OwnerDraw(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, LISTVIEW_DrawItemInfo *pInfo)
{
	if(!pInfo){
		return;
	}
	/* �ж��ǲ���ѡ�е�item */
	if(pObj->CurSel == pInfo->ItemIndex){
		GUI_SetColor(pObj->Props.aTextColor[1]);
		GUI_SetBkColor(pObj->Props.aBackColor[1]);
	}else {
		GUI_SetColor(pObj->Props.aTextColor[0]);
		GUI_SetBkColor(pObj->Props.aBackColor[0]);
	}
	GUI_Clear();
	/* ��ָ��RECT����ʾ�ַ��� */
	if(pObj->DrawItemMethod){
		pObj->DrawItemMethod(pInfo);
	}else{
		char *pString;
		LISTVIEW_ItemDef *pDefItem;
		GUI_SetColor(GUI_WHITE);
		GUI_DrawHLine(pInfo->Rect.y1 - 1,pInfo->Rect.x0 - LISTVIEW_STRING_X_REDUCE, pInfo->Rect.x1);
		GUI_SetFont(pObj->Props.pFont);
		pDefItem = (LISTVIEW_ItemDef *)pInfo->pItem;
		pString = pDefItem->acText;
		WM_RectReduceX(&pInfo->Rect, LISTVIEW_STRING_X_REDUCE);
		GUI_DispStringInRect(pString, &pInfo->Rect, GUI_TA_VCENTER);
	}

}
static void _Paint(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj)
{
	LISTVIEW_DrawItemInfo	_DrawInfo;
	//GUI_RECT RectListView;
	I32 ListViewHeight = 0, ListViewWidth = 0;
	I32 TopItem = 0, TopItemOffest = 0, Diff = 0;
	I32 ReasultOffest = 0;
	U32 i = 0;
	U32 TotalItem = 0;
	U8 Flag = 0;
	if(!WM__IsEnabled(hObj)){
		return;
	}
	/* get listview rect width and height */
	ListViewHeight = WM_GetWindowSizeY(hObj);
	ListViewWidth = WM_GetWindowSizeX(hObj);
	TotalItem = _LISTVIEW__GetNumItems(pObj);
	TopItem = pObj->MoveDistanceY/pObj->ItemYSize;
	TopItemOffest = TopItem * pObj->ItemYSize;
	Diff = pObj->MoveDistanceY - TopItemOffest;
	if(0 != Diff){
		Flag = 1;
		_DrawInfo.Rect.y0 = -Diff;
		_DrawInfo.Rect.y1 = _DrawInfo.Rect.y0 + pObj->ItemYSize;
	}else{
		Flag = 0;
		_DrawInfo.Rect.y0 = 0;
		_DrawInfo.Rect.y1 = pObj->ItemYSize;
	}
	GUI_SetBkColor(pObj->Props.aBackColor[0]);
	GUI_Clear();
	for(i = TopItem; i < TotalItem; i++){
		/* �����item�Ƿ�����Ч����ʾ��Χ�� */
		if(2 == Flag){
			_DrawInfo.Rect.y0 += pObj->ItemYSize;
			_DrawInfo.Rect.y1 += pObj->ItemYSize;
		}else if(1 == Flag){
			Flag = 2;
			_DrawInfo.Rect.y0 = -Diff;
			_DrawInfo.Rect.y1 = _DrawInfo.Rect.y0 + pObj->ItemYSize;
		}else if(0 == Flag){
			Flag = 2;
			_DrawInfo.Rect.y0 = 0;
			_DrawInfo.Rect.y1 = pObj->ItemYSize;
		}
		_DrawInfo.ItemIndex = i;
		_DrawInfo.pItem = _GetItem(pObj,i);
		_DrawInfo.Rect.x0 = 0;
		_DrawInfo.Rect.x1 = ListViewWidth;
		if(_DrawInfo.Rect.y0 > ListViewHeight){
			return;
		}
		WM_SetUserClipArea(&_DrawInfo.Rect);
		_LISTVIEW_OwnerDraw(hObj, pObj, &_DrawInfo);
		ReasultOffest += pObj->ItemYSize;
	}
	WM_SetUserClipArea(NULL);
}
static void LISTVIEW_InvalidateItemRect(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, I32 Index)
{
	GUI_RECT Rect;
	I32 ListViewHeight = 0;
	I32 TopItem = 0, LastItem = 0;
	I32 TopItemOffest = 0, Diff = 0;
	TopItem = pObj->MoveDistanceY/pObj->ItemYSize;
	TopItemOffest = TopItem * pObj->ItemYSize;
	Diff = pObj->MoveDistanceY - TopItemOffest;
	ListViewHeight = WM_GetWindowSizeY(hObj);
	LastItem = TopItem + ((ListViewHeight - Diff)/pObj->ItemYSize) + 1;
	if((Index < TopItem) || (Index > LastItem)){
		GUI_Debug("Index %d is not in the area, TopItem:%d, LastItem:%d\n",Index, TopItem, LastItem);
		return;
	}
	WM_GetClientRectEx(hObj, &Rect);
	/* �����ڿɼ������ڵ����ƫ�� */
	if(Index == TopItem){
		Rect.y0 = 0;
		Rect.y1 = pObj->ItemYSize - Diff;
	}else{
		Rect.y0 = pObj->ItemYSize - Diff + (Index - TopItem - 1) * pObj->ItemYSize;
		Rect.y1 = Rect.y0 + pObj->ItemYSize;
	}
	WM_InvalidateRect(hObj, &Rect);
	//WM_InvalidateWindow(hObj);
}
static I32 _GetPressItem(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, I32 x, I32 y)
{
	I32 YPosArea = 0;
	I32 TopItem = 0, TouchItem;
	I32 TopItemOffest = 0, Diff = 0;
	TopItem = pObj->MoveDistanceY/pObj->ItemYSize;
	TopItemOffest = TopItem * pObj->ItemYSize;
	Diff = pObj->MoveDistanceY - TopItemOffest;
	if(0 != Diff){
		Diff = pObj->ItemYSize - Diff;
		if(y <= Diff){
			return TopItem;
		}
	}
	YPosArea = y - Diff;
	if(0 == pObj->MoveDistanceY){
		TouchItem = YPosArea/pObj->ItemYSize + TopItem;
	}else{
		TouchItem = YPosArea/pObj->ItemYSize + TopItem + 1;
	}

	if(TouchItem > _LISTVIEW__GetNumItems(pObj)){
		return -1;
	}else{
		return TouchItem;
	}
}

static void _DeleteArrayItem(LISTVIEW_Obj* pObj)
{
	if(pObj->DrawItemMethod){
		I32 i = 0;
		void* pItem;
		unsigned ItemTotal = GUI_ARRAY_GetNumItems(&pObj->ItemArray);
		for(i = 0; i < ItemTotal; i++){
			pItem = (void *)GUI_ARRAY_GetpItem(&pObj->ItemArray, i);
			if(pObj->DeleteItemMedthod){
				pObj->DeleteItemMedthod(pItem);
			}
		}
		for(i = ItemTotal - 1; i >= 0; i--){
			GUI_ARRAY_DeleteItem(&pObj->ItemArray, i);
		}
	}
	pObj->DrawItemMethod = NULL;
}
static void _FreeAttached(LISTVIEW_Obj* pObj)
{
	_DeleteArrayItem(pObj);
	GUI_ARRAY_Delete(&pObj->ItemArray);
}
/*
static void _OnListViewPressed(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj)
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) 
	{
		WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
	}
}
*/
static void _OnListViewReleased(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, I32 Notification)
{
	if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
		WM_NotifyParent(hObj, Notification);
	}
}
static void _OnTouch(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	if(pMsg->Data.p){
		if(0 == pState->Pressed){
			if((0 == pObj->isMove) && (pObj->CurSel == _GetPressItem(hObj, pObj, pState->x, pState->y))){
				_OnListViewReleased(hObj,pObj,WM_NOTIFICATION_RELEASED);
			}
			pObj->isMove = 0;
			LISTVIEW_SetSel(hObj,-1);
		}
	}else {
		LISTVIEW_SetSel(hObj,-1);
		_OnListViewReleased(hObj,pObj,WM_NOTIFICATION_MOVED_OUT);
	}
}
static void _CalculateMoveDistanceY(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, I32 TouchPosY)
{
	U8  IsNeedPaint = 0;
	I32 MoveDistY = 0;
	I32 CurrentOffestY = 0;
	I32 ListViewSizeY = 0;
	if(TouchPosY == LastTouchYPos){
		return;
	}
	CurrentOffestY = pObj->MoveDistanceY;
	MoveDistY = TouchPosY - LastTouchYPos;
	LastTouchYPos = TouchPosY;
	CurrentOffestY -= MoveDistY;
	pObj->isMove = 1;
	ListViewSizeY = WM_GetWindowSizeY(hObj);
	if((CurrentOffestY < 0) && (pObj->MoveDistanceY >= 0)){
		if(0 != pObj->MoveDistanceY){
			IsNeedPaint = 1;
		}
		pObj->MoveDistanceY = 0;
	}else if(CurrentOffestY + ListViewSizeY >= pObj->TotalLenghtV){
		if(pObj->MoveDistanceY + ListViewSizeY < pObj->TotalLenghtV){
			IsNeedPaint = 1;
		}
		pObj->MoveDistanceY = pObj->TotalLenghtV - ListViewSizeY;
	}else{
		IsNeedPaint = 1;
		pObj->MoveDistanceY = CurrentOffestY;
	}
	if((1 == pObj->isMove) && (1 == IsNeedPaint)){
		SCROLLBAR_SetOffest(pObj->hScrollbar, pObj->MoveDistanceY);
		WM_InvalidateWindow(hObj);
	}
}
static void _ListAutoMoveV(LISTVIEW_Handle hObj, I32 Value)
{
	_CalculateMoveDistanceY(hObj, (LISTVIEW_Obj *)GUI_ALLOC_h2p(hObj), Value);
}
static void _ListAnimEnd(WM_HWIN hObj)
{
	LISTVIEW_Obj *pObj;
	pObj = (LISTVIEW_Obj *)GUI_ALLOC_h2p(hObj);
	SCROLLBAR_CreateAlphaAnim(pObj->hScrollbar);
}
static void _CreateListAnim(LISTVIEW_Handle hObj, I32 Start, I32 End)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = Start;
	Anim.End = End;
	Anim.Time = 500;
	Anim.pFunc = _ListAutoMoveV;
	Anim.pEnd =_ListAnimEnd;
	GUI_AnimationCreate(hObj, &Anim);
}
/* �������� */
static void _OnTouchMoveV(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	/* ���pStateΪ����˵��������Ч */
	if((!(pMsg->Data.p)) || (pObj->TotalLenghtV <= WM_GetWindowSizeY(hObj))){
		IsFirstTouch = 0;
		LastTouchYPos = 0;
		return;
	}
	/* �ͷ� */
	if(0 == pState->Pressed){
		if(1 == IsFirstTouch){
			_CreateListAnim(hObj, LastTouchYPos, pState->y);
		}
		IsFirstTouch = 0;
		//lastTouchYPos = 0;
		WM_ReleaseCapture();
		return;
	}else{/* ���� */
		WM_SetCapture(hObj,1);
		WM_SetCaptureVWin(hObj);
	}
	if(0 == IsFirstTouch){
		IsFirstTouch = 1;
		SCROLLBAR_DeleteAlphaAnim(pObj->hScrollbar);
		GUI_AnimationDeleteByContext(hObj);
		LastTouchYPos = pState->y;
		return;
	}
	_CalculateMoveDistanceY(hObj, pObj, pState->y);
}
static void LISTVIEW_Callback (WM_MESSAGE *pMsg)
{
	LISTVIEW_Handle hObj;
	LISTVIEW_Obj* pObj;
	hObj = pMsg->hWin;
	pObj = (LISTVIEW_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) 
	{
		return;
	}
	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_DEBUG_LOG("LISTVIEW: _Callback(WM_PAINT)\n");
			_Paint(hObj, pObj);
		return;
		case WM_PID_STATE_CHANGED:
			{
				const WM_PID_STATE_CHANGED_INFO* pInfo = (const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p;
				if(pInfo->State){
					I32 Sel = -1;
					Sel = _GetPressItem(hObj, pObj, pInfo->x, pInfo->y);
					if(Sel >= 0){
						LISTVIEW_SetSel(hObj,Sel);
					}
				}
			}
		break;
		case WM_TOUCH:
			GUI_DEBUG_LOG("LISTVIEW: _Callback(WM_TOUCH)\n");
			_OnTouchMoveV(hObj, pObj, pMsg);
			_OnTouch(hObj, pObj, pMsg);
		break;
		case WM_DELETE:
			_FreeAttached(pObj);
		break;
		case WM_KEY:
		break;
	}
	WM_DefaultProc(pMsg);
}
LISTVIEW_Handle LISTVIEW_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id)
{
	LISTVIEW_Handle hObj;
	/* Create the window */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, LISTVIEW_Callback, sizeof(LISTVIEW_Obj) - sizeof(WM_Obj));
	if (hObj) 
	{
		LISTVIEW_Obj * pObj;
		pObj = (LISTVIEW_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		
		/* ����item ARRAY */
		GUI_ARRAY_CREATE(&(pObj->ItemArray)); 
		
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, ExFlags);//WIDGET_STATE_FOCUSSABLE
		/* init member variables */
		LISTVIEW_INIT_ID(pObj);
		pObj->Props = LISTVIEW_DefaultProps;
		pObj->CurSel = -1;
		pObj->ItemYSize = 35;
		pObj->MoveDistanceY = 0;
		pObj->DrawItemMethod = NULL;
		pObj->hScrollbar = SCROLLBAR_CreateAttached(hObj, 0);
	} 
	else 
	{
		GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
	}
	return hObj;
}


void LISTVIEW_SetSel(LISTVIEW_Handle hObj, I32 NewSel)
{
	I32 OldSel = 0;
	LISTVIEW_Obj* pObj;
	pObj = LISTVIEW_H2P(hObj);
	OldSel = pObj->CurSel;
	if(OldSel == NewSel){
		return;
	}
	pObj->isMove = 0;
	/* invalid action */
	if((-1 == OldSel) && (-1 == NewSel)){
		return;
	}else if(-1 == OldSel){
		/* press action */
		pObj->CurSel = NewSel;
		LISTVIEW_InvalidateItemRect(hObj, pObj, NewSel);
	}else if(-1 == NewSel){
		pObj->CurSel = -1;
		LISTVIEW_InvalidateItemRect(hObj, pObj, OldSel);
	}
}
/* LISTVIEW add string item*/
void LISTVIEW_AddStringItem(LISTVIEW_Handle hObj, const char * s)
{
	LISTVIEW_Obj* pObj;
	LISTVIEW_ItemDef tItem;
	if((NULL == s) || (0 == hObj)){
		return;
	}
	pObj = LISTVIEW_H2P(hObj);
	_DeleteArrayItem(pObj);
	/* add item to item array */
	if (GUI_ARRAY_AddItem(&pObj->ItemArray, &tItem, sizeof(LISTVIEW_ItemDef) + GUI_strlen(s) + 1) == 0) {
		unsigned ItemIndex = GUI_ARRAY_GetNumItems(&pObj->ItemArray) - 1;
		LISTVIEW_ItemDef* pItem= (LISTVIEW_ItemDef*)GUI_ARRAY_GetpItem(&pObj->ItemArray, ItemIndex);
		//focus to set extern draw item method to NULL
		GUI_strcpy(pItem->acText, s);
		pObj->TotalLenghtV = pObj->ItemYSize * _LISTVIEW__GetNumItems(pObj);
		WM_InvalidateWindow(hObj);
		SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
	}
}
U8 LISTVIEW_InsertStringItem(LISTVIEW_Handle hObj, U32 ItemIndex, const char * s)
{
	if(hObj && (NULL != s)){
		LISTVIEW_Obj* pObj;
		LISTVIEW_ItemDef* pItem;
		U16 TotalNum;
		WM_HMEM hNewItem;
		pObj = LISTVIEW_H2P(hObj);
		TotalNum = GUI_ARRAY_GetNumItems(&pObj->ItemArray);
		if(ItemIndex >= TotalNum){
			return 0;
		}
		if(0 == TotalNum){
			LISTVIEW_AddStringItem(hObj, s);
			return 1;
		}
		hNewItem = GUI_ARRAY_InsertItem(&pObj->ItemArray, ItemIndex, GUI_strlen(s) + 1);
		if(hNewItem){
			pItem = (LISTVIEW_ItemDef *)GUI_ALLOC_h2p(hNewItem);
			GUI_strcpy(pItem->acText, s);
			pObj->TotalLenghtV = pObj->ItemYSize * _LISTVIEW__GetNumItems(pObj);
			SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
			WM_InvalidateWindow(hObj);
			return 1;
		}
	}
	return 0;
}
void LISTVIEW_AddExternItem(LISTVIEW_Handle hObj, void *pExternItem, U32 ItemSize)
{
	LISTVIEW_Obj* pObj;
	if((NULL == pExternItem) || (0 == hObj) || (0 == ItemSize)){
		return;
	}
	pObj = LISTVIEW_H2P(hObj);
	if (GUI_ARRAY_AddItem(&pObj->ItemArray, pExternItem, ItemSize) == 0) {
		pObj->TotalLenghtV = pObj->ItemYSize * _LISTVIEW__GetNumItems(pObj);
		SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
		WM_InvalidateWindow(hObj);
	}
}
U8 ListView_InsertExternItem(LISTVIEW_Handle hObj, U32 ItemIndex, void *pExternItem, U32 ItemSize)
{
	if(hObj){
		LISTVIEW_Obj* pObj;
		void *pNewItemBuffer;
		U16 TotalNum;
		WM_HMEM hNewItem;
		pObj = LISTVIEW_H2P(hObj);
		TotalNum = GUI_ARRAY_GetNumItems(&pObj->ItemArray);
		if(0 == TotalNum){
			LISTVIEW_AddExternItem(hObj, pExternItem, ItemSize);
			return 1;
		}
		if(ItemIndex >= TotalNum){
			return 0;
		}
		hNewItem = GUI_ARRAY_InsertItem(&pObj->ItemArray, ItemIndex, ItemSize);
		if(hNewItem){
			pNewItemBuffer = (void *)GUI_ALLOC_h2p(hNewItem);
			GUI_memcpy(pNewItemBuffer, pExternItem, ItemSize);
			pObj->TotalLenghtV = pObj->ItemYSize * _LISTVIEW__GetNumItems(pObj);
			SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
			WM_InvalidateWindow(hObj);
			return 1;
		}
	}
	return 0;
}
void ListView_DeleteItemByIndex(LISTVIEW_Handle hObj, U32 DeleteIndex)
{
	if(hObj){
		LISTVIEW_Obj* pObj;
		pObj = LISTVIEW_H2P(hObj);
		if(DeleteIndex >= GUI_ARRAY_GetNumItems(&pObj->ItemArray)){
			return;
		}
		if(pObj->DrawItemMethod){
			void *pItem = (void *)GUI_ARRAY_GetpItem(&pObj->ItemArray, DeleteIndex);
			if(pObj->DeleteItemMedthod){
				pObj->DeleteItemMedthod(pItem);
			}
		}
		GUI_ARRAY_DeleteItem(&pObj->ItemArray, DeleteIndex);
		pObj->TotalLenghtV = pObj->ItemYSize * _LISTVIEW__GetNumItems(pObj);
		SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
		WM_InvalidateWindow(hObj);
	}
}
void LISTVIEW_ClearItem(LISTVIEW_Handle hObj)
{
	if(hObj){
		I32 i = 0;
		U32 ItemTotal;
		LISTVIEW_Obj* pObj;
		pObj = LISTVIEW_H2P(hObj);
		ItemTotal = GUI_ARRAY_GetNumItems(&pObj->ItemArray);
		if(0 == ItemTotal){
			return;
		}
		if(pObj->DrawItemMethod){
			void* pItem;
			for(i = 0; i < ItemTotal; i++){
				pItem = (void *)GUI_ARRAY_GetpItem(&pObj->ItemArray, i);
				if(pObj->DeleteItemMedthod){
					pObj->DeleteItemMedthod(pItem);
				}
			}
		}
		for(i = ItemTotal - 1; i >= 0; i--){
			GUI_ARRAY_DeleteItem(&pObj->ItemArray, i);
		}
		pObj->TotalLenghtV = 0;
		pObj->MoveDistanceY = 0;
		SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
		SCROLLBAR_SetOffest(pObj->hScrollbar, pObj->MoveDistanceY);
	}
}
void LISTVIEW_SetDrawItemMethod(LISTVIEW_Handle hObj, void *pDrawMethod, void *pDeleteMethod)
{
	LISTVIEW_Obj* pObj;
	if(WM_HWIN_NULL == hObj){
		return;
	}
	pObj = LISTVIEW_H2P(hObj);
	pObj->DrawItemMethod = (LISTVIEW_DrawItem)pDrawMethod;
	pObj->DeleteItemMedthod = (LISTVIEW_DeleteItem)pDeleteMethod;
	WM_InvalidateWindow(hObj);
}
void LISTVIEW_SetItemYSize(LISTVIEW_Handle hObj, U32 size)
{
	LISTVIEW_Obj* pObj;
	if(0 == size){
		return;
	}
	if(hObj){
		pObj = LISTVIEW_H2P(hObj);
		if(pObj->ItemYSize != size){
			pObj->ItemYSize = size;
			pObj->TotalLenghtV = pObj->ItemYSize * _LISTVIEW__GetNumItems(pObj);
			WM_InvalidateWindow(hObj);
			SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
		}
	}
}
void LISTVIEW_SetFont(LISTVIEW_Handle hObj, const GUI_FONT GUI_UNI_PTR* pFont)
{
	LISTVIEW_Obj* pObj;
	if(NULL == pFont){
		return;
	}
	if(hObj){
		pObj = LISTVIEW_H2P(hObj);
		if(pObj->Props.pFont != pFont){
			pObj->Props.pFont = pFont;
			WM_InvalidateWindow(hObj);
		}
	}
}
void LISTVIEW_GetItemInfo(LISTVIEW_Handle hObj, I32 itemIndex, void *pGetItem)
{
	LISTVIEW_Obj* pObj;
	if(hObj && (-1 != itemIndex) && (NULL != pGetItem)){
		void *pItem;
		U32 ItemNum;
		pObj = LISTVIEW_H2P(hObj);
		ItemNum = GUI_ARRAY_GetNumItems(&pObj->ItemArray) - 1;
		if(ItemNum < itemIndex){
			return;
		}
		pItem = (void*)GUI_ARRAY_GetpItem(&pObj->ItemArray, itemIndex);
		pGetItem = pItem;
	}
	//return *pGetItem;
}
void LISTVIEW_GetSelItemInfo(LISTVIEW_Handle hObj, void *pSelItem)
{
	LISTVIEW_Obj* pObj;
	if(hObj && (NULL != pSelItem)){
		void *pItem;
		WM_HMEM hItem;
		pObj = LISTVIEW_H2P(hObj);
		hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, pObj->CurSel);
		pItem = (void*)GUI_ARRAY_GetpItem(&pObj->ItemArray, pObj->CurSel);
		GUI_memcpy(pSelItem, pItem, GUI_ALLOC_GetSize(hItem));
	}
}
I32 LISTVIEW_GetSel(LISTVIEW_Handle hObj)
{
	I32 r = -1;
	LISTVIEW_Obj* pObj;
	if(hObj){
		pObj = LISTVIEW_H2P(hObj);
		r = pObj->CurSel;
	}
	return r;
}
void LISTVIEW_HideScrollbar(LISTVIEW_Handle hObj)
{
	if(hObj){
		LISTVIEW_Obj* pObj;
		pObj = LISTVIEW_H2P(hObj);
		WM_HideWindow(pObj->hScrollbar);
	}
}
#endif 


