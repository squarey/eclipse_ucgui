
#ifndef UC_LISTVIEW_H
#define UC_LISTVIEW_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && LISTVIEW_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM LISTVIEW_Handle;



typedef struct
{
	void 		*pItem;
	GUI_RECT	Rect;
	I32			ItemIndex;
}LISTVIEW_DrawItemInfo;

typedef U8 (*LISTVIEW_DrawItem)(const LISTVIEW_DrawItemInfo *pInfo);
typedef U8 (*LISTVIEW_DeleteItem)(void *pInfo);

LISTVIEW_Handle LISTVIEW_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags);
LISTVIEW_Handle LISTVIEW_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
LISTVIEW_Handle LISTVIEW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo,
								WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
void LISTVIEW_SetSel(LISTVIEW_Handle hObj, I32 NewSel);
void LISTVIEW_SetItemYSize(LISTVIEW_Handle hObj, U32 size);
void LISTVIEW_SetFont(LISTVIEW_Handle hObj, const GUI_FONT GUI_UNI_PTR* pFont);
void LISTVIEW_AddStringItem(LISTVIEW_Handle hObj, const char * s);
U8 LISTVIEW_InsertStringItem(LISTVIEW_Handle hObj, U32 ItemIndex, const char * s);
void LISTVIEW_AddExternItem(LISTVIEW_Handle hObj, void *pExternItem, U32 ItemSize);
void LISTVIEW_ClearItem(LISTVIEW_Handle hObj);
U8 ListView_InsertExternItem(LISTVIEW_Handle hObj, U32 ItemIndex, void *pExternItem, U32 ItemSize);
void LISTVIEW_SetDrawItemMethod(LISTVIEW_Handle hObj, void *pDrawMethod, void *pDeleteMethod);
void ListView_DeleteItemByIndex(LISTVIEW_Handle hObj, U32 DeleteIndex);
void LISTVIEW_GetItemInfo(LISTVIEW_Handle hObj, I32 itemIndex, void *pGetItem);
void LISTVIEW_GetSelItemInfo(LISTVIEW_Handle hObj, void *pSelItem);
I32 LISTVIEW_GetSel(LISTVIEW_Handle hObj);
void LISTVIEW_HideScrollbar(LISTVIEW_Handle hObj);

#if defined(__cplusplus)
  }

#endif
#endif

#endif 
