


#ifndef UC_PICKER_PRIVATE_H
#define UC_PICKER_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "Picker.h"

#if GUI_WINSUPPORT && PICKER_SUPPORT

typedef struct 
{
	WIDGET Widget;	
	U8 TouchVaildDist;
	I8 CurValue;
	I8 MaxValue;
	U8 IsMove;
}Picker_Obj;

#define Picker_H2P(h) (Picker_Obj *)GUI_ALLOC_h2p(h)
#define Picker_INIT_ID(p)

#endif 


#endif


