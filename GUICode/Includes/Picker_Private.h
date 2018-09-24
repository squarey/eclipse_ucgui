


#ifndef UC_PICKER_PRIVATE_H
#define UC_PICKER_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "Picker.h"

#if GUI_WINSUPPORT && PICKER_SUPPORT

typedef struct Picker_Obj_t
{
	WIDGET Widget;	
	U8 TouchVaildDist;
	I32 CurValue;
	I32 MaxValue;
	I32 MinValue;
	GUI_COLOR	LargeColor;
	GUI_COLOR	MiddleColor;
	GUI_COLOR	SmallColor;
	GUI_COLOR	BkColor;
	GUI_COLOR	DisableFontColor;
	U8 IsMove;
	const GUI_FONT *pMiddleFont;
	const GUI_FONT *pLargeFont;
	const GUI_FONT *pSmallFont;
	void (*CustomDraw)(WM_HMEM hObj,struct Picker_Obj_t *pObj);
}Picker_Obj;

#define Picker_H2P(h) (Picker_Obj *)GUI_ALLOC_h2p(h)
#define Picker_INIT_ID(p)

#endif 


#endif


