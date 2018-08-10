
#ifndef UC_PICKER_H
#define UC_PICKER_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && PICKER_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM Picker_Handle;

Picker_Handle Picker_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
Picker_Handle Picker_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo,
								WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);

void Picker_SetMaxValue(Picker_Handle hObj, U8 Value);
U8 Picker_GetCurValue(Picker_Handle hObj);
void Picker_SetValue(Picker_Handle hObj, U8 Value);


#if defined(__cplusplus)
  }

#endif
#endif

#endif 


