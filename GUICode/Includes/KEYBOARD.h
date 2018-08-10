/*
 * KEYBOARD.h
 *
 *  Created on: 2018年5月17日
 *      Author: Administrator
 */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */
#include "WIDGET.h"
#include "KEYBOARD_Private.h"


typedef WM_HMEM KEYBOARD_Handle;

KEYBOARD_Handle KEYBOARD_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 WinFlags, I32 ExFlags, I32 Id);

void KEYBOARD_SetNoticeDeleteCb(KEYBOARD_Handle hWin, _cb_Delete pCb);
void KEYBOARD_SetNoticeEnterCb(KEYBOARD_Handle hWin, _cb_Enter pCb);
void KEYBOARD_ResetStatus(KEYBOARD_Handle hWin);
void KEYBOARD_SetStyle(KEYBOARD_Handle hWin, U8 Style);
void KEYBOARD_LockStyle(KEYBOARD_Handle hWin);
void KEYBOARD_UnLockStyle(KEYBOARD_Handle hWin);
void KEYBOARD_SetReportNumberOnly(KEYBOARD_Handle hWin);
void KEYBOARD_ClearReportNumberOnly(KEYBOARD_Handle hWin);
void KEYBOARD_SetBkColor(KEYBOARD_Handle hWin, GUI_COLOR BkColor);
void KEYBOARD_SetPressStyle(KEYBOARD_Handle hWin, GUI_FullRectStyle Style);
void KEYBOARD_SetReleaseStyle(KEYBOARD_Handle hWin, GUI_FullRectStyle Style);

#endif /* CORE_INCLUDES_KEYBOARD_H_ */
