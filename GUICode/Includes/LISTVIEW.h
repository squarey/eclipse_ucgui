
#ifndef UC_LISTVIEW_H
#define UC_LISTVIEW_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"
#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT && LISTVIEW_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM LISTVIEW_Handle;

LISTVIEW_Handle LISTVIEW_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags);
LISTVIEW_Handle LISTVIEW_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
LISTVIEW_Handle LISTVIEW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo,
								WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);
void LISTVIEW_SetSel(LISTVIEW_Handle hObj, I32 NewSel);
void LISTVIEW_SetItemYSize(LISTVIEW_Handle hObj, U32 size);
void LISTVIEW_SetFont(LISTVIEW_Handle hObj, const GUI_FONT GUI_UNI_PTR* pFont);
void LISTVIEW_AddItem(LISTVIEW_Handle hObj,LISTVIEW_ITEM *item,const char * s);
LISTVIEW_ITEM LISTVIEW_GetItemInfo(LISTVIEW_Handle hObj, I32 itemIndex);
LISTVIEW_ITEM *LISTVIEW_GetSelItemInfo(LISTVIEW_Handle hObj);
I32 LISTVIEW_GetSel(LISTVIEW_Handle hObj);

#if defined(__cplusplus)
  }

#endif
#endif

#endif 
