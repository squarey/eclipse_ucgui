
#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT && IMAGEBUTTON_SUPPORT

#define IMAGEBUTTON_STATE_PRESSED    WIDGET_STATE_USER0
#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef WM_HMEM IMAGEBUTTON_Handle;

IMAGEBUTTON_Handle IMAGEBUTTON_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                              I32 WinFlags, I32 ExFlags, I32 Id);
IMAGEBUTTON_Handle IMAGEBUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, 
								WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb);

void IMAGEBUTTON_SetFocusFile(IMAGEBUTTON_Handle hObj, void *focus_buffer, U8 Flag);
void IMAGEBUTTON_SetUnFocusFile(IMAGEBUTTON_Handle hObj, void *unfocus_buffer, U8 Flag);
void IMAGEBUTTON_SetState(IMAGEBUTTON_Handle hObj, U8 State);
void IMAGEBUTTON_SetBkColor(IMAGEBUTTON_Handle hObj, GUI_COLOR Color);
void IMAGEBUTTON_SetUnFocusMapping(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Handle hMap);
void IMAGEBUTTON_SetFocusMapping(IMAGEBUTTON_Handle hObj, IMAGEBUTTON_Handle hMap);
void IMAGEBUTTON_SetUnFocusBitmap(IMAGEBUTTON_Handle hObj, const GUI_BITMAP *pBitmap);
void IMAGEBUTTON_SetFocusBitmap(IMAGEBUTTON_Handle hObj, const GUI_BITMAP *pBitmap);
void IMAGEBUTTON_SetUnFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj, GUI_COLOR TransColor);
void IMAGEBUTTON_ClearUnFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj);
void IMAGEBUTTON_SetFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj, GUI_COLOR TransColor);
void IMAGEBUTTON_ClearFocusBitmapHasTrans(IMAGEBUTTON_Handle hObj);

#if defined(__cplusplus)
  }

#endif
#endif

#endif 
