

#include "GUI_Protected.h"
#include "WIDGET.h"
#include "LISTVIEW.h"
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

static I32 lastTouchYPos = 0;
static char isFirstTouch = 0;

typedef struct
{
	LISTVIEW_ITEM *pItem;
	GUI_RECT	Rect;
	I16 		xReduce;
	I32			ItemIndex;
}ItemDrawInfo;

/* ��ȡitem��Y���С */
/*
static I32 _GetItemSizeY(const LISTVIEW_Obj* pObj)
{
	return pObj->ItemYSize;
}*/
/* ��ȡListView�ܹ���item��Ŀ */
static unsigned LISTVIEW__GetNumItems(const LISTVIEW_Obj* pObj)
{
	return GUI_ARRAY_GetNumItems(&pObj->ItemArray);
}

/* ��ȡitem */
static LISTVIEW_ITEM *_GetItem(const LISTVIEW_Obj* pObj,unsigned Index)
{
	LISTVIEW_ITEM *pItem;
	pItem = (LISTVIEW_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
	return pItem;
}


static void LISTVIEW_OwnerDraw(LISTVIEW_Obj* pObj, ItemDrawInfo *pInfo)
{
	if(!pInfo){
		return;
	}
	/* �ж��ǲ���ѡ�е�item */
	if(pObj->CurSel == pInfo->ItemIndex){
		GUI_SetColor(pObj->Props.aTextColor[1]);
		GUI_SetBkColor(pObj->Props.aBackColor[1]);
	}
	else {
		GUI_SetColor(pObj->Props.aTextColor[0]);
		GUI_SetBkColor(pObj->Props.aBackColor[0]);
	}
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_DrawHLine(pInfo->Rect.y1 - 1,pInfo->Rect.x0 - pInfo->xReduce, pInfo->Rect.x1);
	/* ��ָ��RECT����ʾ�ַ��� */
	GUI_SetFont(pObj->Props.pFont);
	GUI_DispStringInRect(pInfo->pItem->acText, &pInfo->Rect, GUI_TA_VCENTER);
	/* �Ƿ���Ҫ��item */
	if(pInfo->pItem->IconBuffer){
		U32 width = 0;
		U32 height = 0;
		U32 RectHeight = 0;
		U32 DisPosX = 0;
		U32 DisPosY = 0;
		//U32 RectWidth = 0;
		width = GUI_BMP_GetXSize(pInfo->pItem->IconBuffer);
		height = GUI_BMP_GetYSize(pInfo->pItem->IconBuffer);
		//RectWidth = RectItem.x1 - RectItem.x0;
		RectHeight = pInfo->Rect.y1 - pInfo->Rect.y0;
		/* �Ҷ��� */
		DisPosX = pInfo->Rect.x1 - width;
		/* ���ж��� */
		if(height < RectHeight){
			DisPosY = (RectHeight - height)/2;
		}
		GUI_BMP_Draw(pInfo->pItem->IconBuffer,DisPosX,DisPosY);
	}
}
static void _Paint(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj)
{
	ItemDrawInfo	_DrawInfo;
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
	/* ��ȡlistview��rect */
	ListViewHeight = WM_GetWindowSizeY(hObj);
	ListViewWidth = WM_GetWindowSizeX(hObj);
	TotalItem = LISTVIEW__GetNumItems(pObj);
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
		_DrawInfo.xReduce = LISTVIEW_STRING_X_REDUCE;
		_DrawInfo.pItem = _GetItem(pObj,i);
		_DrawInfo.Rect.x0 = 0;
		_DrawInfo.Rect.x1 = ListViewWidth;
		if(_DrawInfo.Rect.y0 > ListViewHeight){
			return;
		}
		WM_SetUserClipArea(&_DrawInfo.Rect);
		_DrawInfo.Rect.x0 = _DrawInfo.xReduce;
		LISTVIEW_OwnerDraw(pObj,&_DrawInfo);
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

	if(TouchItem > LISTVIEW__GetNumItems(pObj)){
		return -1;
	}else{
		return TouchItem;
	}
}
static void _FreeAttached(LISTVIEW_Obj* pObj)
{
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
			if(0 == pObj->isMove){
				_OnListViewReleased(hObj,pObj,WM_NOTIFICATION_RELEASED);
			}
			pObj->isMove = 0;
			LISTVIEW_SetSel(hObj,-1);
		}
	}else {
		_OnListViewReleased(hObj,pObj,WM_NOTIFICATION_MOVED_OUT);
	}
}
static void _CalculateMoveDistanceY(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, I32 TouchPosY)
{
	U8  IsNeedPaint = 0;
	I32 MoveDistY = 0;
	I32 CurrentOffestY = 0;
	I32 ListViewSizeY = 0;
	if(TouchPosY == lastTouchYPos){
		return;
	}
	CurrentOffestY = pObj->MoveDistanceY;
	MoveDistY = TouchPosY - lastTouchYPos;
	lastTouchYPos = TouchPosY;
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
		isFirstTouch = 0;
		lastTouchYPos = 0;
		return;
	}
	/* �ͷ� */
	if(0 == pState->Pressed){
		if(1 == isFirstTouch){
			_CreateListAnim(hObj, lastTouchYPos, pState->y);
		}
		isFirstTouch = 0;
		//lastTouchYPos = 0;
		WM_ReleaseCapture();
		return;
	}else{/* ���� */
		WM_SetCapture(hObj,1);
	}
	if(0 == isFirstTouch){
		isFirstTouch = 1;
		SCROLLBAR_DeleteAlphaAnim(pObj->hScrollbar);
		GUI_AnimationDeleteByContext(hObj);
		lastTouchYPos = pState->y;
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
/* LISTVIEW���һ��item */
void LISTVIEW_AddItem(LISTVIEW_Handle hObj,LISTVIEW_ITEM *item,const char * s)
{
	LISTVIEW_Obj* pObj;
    LISTVIEW_ITEM tItem = {0,0};
	if((NULL == item) || (0 == hObj)){
		return;
	}
	pObj = LISTVIEW_H2P(hObj);
	/* ��ItemArray�����һ��item Ԫ�� */
	if (GUI_ARRAY_AddItem(&pObj->ItemArray, &tItem, sizeof(LISTVIEW_ITEM) + GUI_strlen(s)) == 0) {
		/* ��ȡ�ո���ӵ�item������ */
		unsigned ItemIndex = GUI_ARRAY_GetNumItems(&pObj->ItemArray) - 1;
		/* ���item����Ϣ */
		LISTVIEW_ITEM* pItem= (LISTVIEW_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, ItemIndex);
		GUI_strcpy(pItem->acText, s);
		pItem->Flag = item->Flag;
		pItem->IconBuffer = item->IconBuffer;
		pObj->TotalLenghtV = pObj->ItemYSize * LISTVIEW__GetNumItems(pObj);
		WM_InvalidateWindow(hObj);
		SCROLLBAR_SetActualLength(pObj->hScrollbar, pObj->TotalLenghtV);
	}
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
			pObj->TotalLenghtV = pObj->ItemYSize * LISTVIEW__GetNumItems(pObj);
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
LISTVIEW_ITEM LISTVIEW_GetItemInfo(LISTVIEW_Handle hObj, I32 itemIndex)
{
	LISTVIEW_Obj* pObj;
	LISTVIEW_ITEM *pItem;
	if(hObj && (-1 != itemIndex)){
		pObj = LISTVIEW_H2P(hObj);
		pItem = (LISTVIEW_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, itemIndex);
	}
	return *pItem;
}
LISTVIEW_ITEM *LISTVIEW_GetSelItemInfo(LISTVIEW_Handle hObj)
{
	LISTVIEW_Obj* pObj;
	LISTVIEW_ITEM *pItem;
	if(hObj){
		pObj = LISTVIEW_H2P(hObj);
		pItem = (LISTVIEW_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, pObj->CurSel);
	}
	return pItem;
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
#endif 


