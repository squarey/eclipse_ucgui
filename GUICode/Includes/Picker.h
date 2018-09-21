
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

void Picker_SetMaxValue(Picker_Handle hObj, I32 Value);
void Picker_SetMinValue(Picker_Handle hObj, I32 Value);
I32 Picker_GetCurValue(Picker_Handle hObj);
void Picker_SetValue(Picker_Handle hObj, I32 Value);
void Picker_SetFontColor(Picker_Handle hObj, GUI_COLOR LargeColor, GUI_COLOR MiddleColor, GUI_COLOR SmallColor);
void Picker_SetBkColor(Picker_Handle hObj, GUI_COLOR BkColor);


#if defined(__cplusplus)
  }

#endif
#endif

#endif 


