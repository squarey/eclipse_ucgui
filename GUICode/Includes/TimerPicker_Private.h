


#ifndef TIMERPICKER_PRIVATE_H
#define TIMERPICKER_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "TimerPicker.h"

#if GUI_WINSUPPORT && TIMERPICKER_SUPPORT

typedef struct 
{
	WIDGET Widget;	
	U8 TouchFlag;
	U8 TouchVaildDist;
	I8 CurHours;
	I8 CurMinutes;
}TimerPicker_Obj;

#define TimerPicker_H2P(h) (TimerPicker_Obj *)GUI_ALLOC_h2p(h)
#define TimerPicker_INIT_ID(p)

#endif 


#endif


