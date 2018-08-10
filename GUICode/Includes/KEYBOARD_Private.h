/*
 * KEYBOARD_Private.h
 *
 *  Created on: 2018年5月17日
 *      Author: Administrator
 */

#ifndef _KEYBOARD_PRIVATE_H_
#define _KEYBOARD_PRIVATE_H_


#include "WM.h"
#include "WIDGET.h"
#include "GUI_StyleDraw.h"

#define KEYBOARD_STYLE_NULL		0x00
#define KEYBOARD_STYLE_NUMBER		0x01
#define KEYBOARD_STYLE_LOWERCASE	0x02
#define KEYBOARD_STYLE_UPPERCASE	0x04
#define KEYBOARD_STYLE_SYMBOL		0x08
#define KEYBOARD_PRESS_NULL		0x00
#define KEYBOARD_PRESS_PRESS		0x01
#define KEYBOARD_PRESS_REALEASE	0x02

#define KEYBOARD_CHAR_CAP			0x80
#define KEYBOARD_CHAR_DELETE		0x81
#define KEYBOARD_CHAR_123			0x82
#define KEYBOARD_CHAR_SYMBOL		0x83
#define KEYBOARD_CHAR_SPACE		0x84
#define KEYBOARD_CHAR_POINT		0x85
#define KEYBOARD_CHAR_ENTER		0x86
#define KEYBOARD_NUMBER_ABC		0x87
#define KEYBOARD_NUMBER_ENTER		0x88
#define KEYBOARD_NUMBER_DELETE	0x89
#define KEYBOARD_TRIANGLE			0x90

#define KEYBOARD_LOCK_NULL		0x00
#define KEYBOARD_LOCK_STYLE_NUMBER	0x01
#define KEYBOARD_LOCK_REPORT_NUMBER	0x02

typedef void (*_cb_Delete)(WM_HWIN hObj);
typedef void (*_cb_Enter)(void);

typedef struct
{
	GUI_FullRectStyle FocusStyle;
	GUI_FullRectStyle UnfocusStyle;
	const GUI_FONT GUI_UNI_PTR * pFont;
	GUI_COLOR aTextColor;
	GUI_COLOR BkColor;
	U8 Spacing;
} ucKEYOBARD_PROPS;

typedef struct
{
	WIDGET	Widget;
	U8		Style;
	U8		StyleLock;
	U8		PressIndex;
	U8		PressStatus;
	U8		IsPress;
	U8		SwitchFlag;
	_cb_Delete	DeleteCb;
	_cb_Enter	EnterCb;
	ucKEYOBARD_PROPS Props;
}KEYBOARD_Obj;

#endif /* _KEYBOARD_PRIVATE_H_ */
