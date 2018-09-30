


#ifndef UC_LISTVIEW_PRIVATE_H
#define UC_LISTVIEW_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "GUI_ARRAY.h"
#include "LISTVIEW.h"

#if GUI_WINSUPPORT && LISTVIEW_SUPPORT




typedef struct
{
	char acText[1];
} LISTVIEW_ItemDef;

typedef struct 
{
	const GUI_FONT GUI_UNI_PTR* pFont;

	GUI_COLOR aBackColor[2];
	GUI_COLOR aTextColor[2];
//  I16 Align;
} LISTVIEW_PROPS;

typedef struct 
{
	WIDGET Widget;
	GUI_ARRAY ItemArray;
	LISTVIEW_PROPS Props;
	WM_HWIN hScrollbar;
	I32 CurSel;
	U32 ItemYSize;
	U32 TotalLenghtV;
	I32 MoveDistanceY;
	U8	isMove;
	LISTVIEW_DrawItem DrawItemMethod;
	LISTVIEW_DeleteItem DeleteItemMedthod;
}LISTVIEW_Obj;

#define LISTVIEW_H2P(h) (LISTVIEW_Obj *)GUI_ALLOC_h2p(h)
#define LISTVIEW_INIT_ID(p)

#endif 


#endif


