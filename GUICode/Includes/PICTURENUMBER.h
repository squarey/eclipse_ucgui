
#ifndef PICTURENUMBER_H
#define PICTURENUMBER_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && PICTURENUMBER_SUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM PICTURENUMBER_Handle;

PICTURENUMBER_Handle PICTURENUMBER_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
PICTURENUMBER_Handle PICTURENUMBER_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, 
								WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);

void PICTURENUMBER_SetNumberBitmap(PICTURENUMBER_Handle hObj, void *buffer, U8 number);
void PICTURENUMBER_SetNumber(PICTURENUMBER_Handle hObj, U32 number);

#if defined(__cplusplus)
  }

#endif
#endif

#endif 
