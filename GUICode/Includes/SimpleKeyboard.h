/*
 * ucSimpleKeyboard.h
 *
 *  Created on: 2018年6月20日
 *      Author: Administrator
 */

#ifndef _SIMPLEKEYBOARD_H_
#define _SIMPLEKEYBOARD_H_

#include "KEYBOARD.h"



void SimpleKeyboardCreate(I32 x0, I32 y0);
void SimpleKeyboardDelete(void);
void SimpleKeyboardSetPos(I32 x0, I32 y0);
void SimpleKeyboardReSize(I32 Width, I32 Height);
void SimpleKeyboardShow(void);
void SimpleKeyboardHide(void);
void SimpleKeyboardSetStyle(U8 Style);
void SimpleKeyboardLockStyle(void);
void SimpleKeyboardUnLockStyle(void);
void SimpleKeyboardReportNumberOnly(void);
void SimpleKeyboardClearReportNumberOnly(void);
void SimpleKeyboardSetBkColor(GUI_COLOR BkColor);
void SimpleKeyboardSetPressStyle(GUI_FullRectStyle Style);
void SimpleKeyboardSetReleaseStyle(GUI_FullRectStyle Style);
void SimpleKeyboardSetEnterCb(_cb_Enter pCb);

#endif /* _SIMPLEKEYBOARD_H_ */
