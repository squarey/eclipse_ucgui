
#ifndef TIMERPICKER_H
#define TIMERPICKER_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && TIMERPICKER_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM TimerPicker_Handle;

TimerPicker_Handle TimerPicker_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
TimerPicker_Handle TimerPicker_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, 
								WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);



#if defined(__cplusplus)
  }

#endif
#endif

#endif 


