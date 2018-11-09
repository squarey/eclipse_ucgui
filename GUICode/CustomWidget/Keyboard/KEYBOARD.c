/*
 * KEYBOARD.c
 *
 *  Created on: 2018年5月17日
 *      Author: Administrator
 */

#include "KEYBOARD.h"


#ifndef   KEYBOARD_FONT_DEFAULT
    #define KEYBOARD_FONT_DEFAULT GUI_DEFAULT_FONT
#endif

#ifndef   KEYBOARD_FOCUS_BKCOLOR_DEFAULT
  #define KEYBOARD_FOCUS_BKCOLOR_DEFAULT   	0xECA307
#endif

#ifndef   KEYBOARD_UNFOCUS_BKCOLOR_DEFAULT
  #define KEYBOARD_UNFOCUS_BKCOLOR_DEFAULT     GUI_GRAY
#endif

#ifndef   KEYBOARD_TEXT_COLOR_DEFAULT
  #define KEYBOARD_TEXT_COLOR_DEFAULT 		GUI_WHITE
#endif

#ifndef   KEYBOARD_BKCOLOR_DEFAULT
  #define KEYBOARD_BKCOLOR_DEFAULT 			GUI_BLACK
#endif

#ifndef   KEYBOARD_STYLE_RADIUS_DEFAULT
  #define KEYBOARD_STYLE_RADIUS_DEFAULT 		3
#endif

#ifndef   KEYBOARD_STYLE_OPACITY_DEFAULT
  #define KEYBOARD_STYLE_OPACITY_DEFAULT 		0xFF
#endif

#define KEYBOARD_SPACING						4
#define KEYBOARD_TRIANGLE_SCALE				10

static char NumberText[] =
{
	'/', '1', '2', '3',
	'+', '4', '5', '6',
	'-', '7', '8', '9',
	'*', '.', '0', ' '
};
static char LowercaseText[] =
{
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
	'z', 'x', 'c', 'v', 'b', 'n', 'm'
};
static char UppercaseText[] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M'
};
static char SymbolText[] =
{
	'~', '!', '#', '$', '%', '^', '&', '*', '(', ')',
	'=', '_', '`', '{', '}', '|', '\\', ':', ';',
	'"', '\'', ',', '?', '/', '<', '>'
};

ucKEYOBARD_PROPS ucKEYOBARD__DefaultProps =
{
	KEYBOARD_STYLE_RADIUS_DEFAULT,			//.FocusStyle.Radius
	KEYBOARD_STYLE_OPACITY_DEFAULT,			//.FocusStyle.Opacity
	KEYBOARD_FOCUS_BKCOLOR_DEFAULT,			//.FocusStyle.MainColor
	KEYBOARD_FOCUS_BKCOLOR_DEFAULT,			//.FocusStyle.GradColor
	KEYBOARD_STYLE_RADIUS_DEFAULT,			//.UnfocusStyle.Radius
	KEYBOARD_STYLE_OPACITY_DEFAULT,			//.UnfocusStyle.Opacity
	KEYBOARD_UNFOCUS_BKCOLOR_DEFAULT,		//.UnfocusStyle.MainColor
	KEYBOARD_UNFOCUS_BKCOLOR_DEFAULT,		//.UnfocusStyle.GradColor
	KEYBOARD_FONT_DEFAULT,					//.pFont
	KEYBOARD_TEXT_COLOR_DEFAULT,			//.aTextColor
	KEYBOARD_BKCOLOR_DEFAULT,				//.BkColor
	KEYBOARD_SPACING						//.Spacing
};
static void _DrawButton(KEYBOARD_Obj* pObj, GUI_RECT *pRect, const char *pText, U8 IsFocus)
{
	if(0 == IsFocus){
		GUI_FillRoundRect(pRect, &pObj->Props.UnfocusStyle);
		LCD_SetColor(pObj->Props.aTextColor);
		GUI_DispStringInRectWrap(pText, pRect, GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
	}else{
		GUI_FillRoundRect(pRect, &pObj->Props.FocusStyle);
		LCD_SetColor(pObj->Props.aTextColor);
		pRect->x0 += 2;
		pRect->y0 += 2;
		GUI_DispStringInRectWrap(pText, pRect, GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
	}
}

static void _PaintNumberStyle(KEYBOARD_Obj* pObj, KEYBOARD_Handle hObj)
{
	I16 Height = 0, Width = 0;
	U32 Index = 0;
	I16 OneButtonWidth = 0, OneButtonHeight = 0;
	I16 StatusHeight = 0;
	GUI_RECT Rect;
	U8 i = 0, j = 0;
	char CharBuffer[3] = "";
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	StatusHeight = Height/KEYBOARD_TRIANGLE_SCALE;
	OneButtonWidth = (Width - pObj->Props.Spacing * 6)/5;
	OneButtonHeight = (Height - pObj->Props.Spacing * 5 - StatusHeight)/4;
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(pObj->Props.pFont);
	pObj->SwitchFlag = KEYBOARD_STYLE_NULL;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			Index = i * 4 + j;
			Rect.x0 = OneButtonWidth * j + pObj->Props.Spacing * (j + 1);
			Rect.x1 = Rect.x0 + OneButtonWidth;
			Rect.y0 = OneButtonHeight * i + pObj->Props.Spacing * (i + 1) + StatusHeight;
			Rect.y1 = Rect.y0 + OneButtonHeight;
			if((3 == i) && (3 == j)){
				CharBuffer[0] = '~';
				CharBuffer[1] = '*';
				CharBuffer[2] = '\0';
			}else{
				CharBuffer[0] = NumberText[Index];
				CharBuffer[1] = '\0';
			}
			if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
				_DrawButton(pObj, &Rect, CharBuffer, 0);
			}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
				if(pObj->PressIndex == Index){
					_DrawButton(pObj, &Rect, CharBuffer, 1);
					if((3 == i) && (3 == j)){
						pObj->SwitchFlag = KEYBOARD_STYLE_SYMBOL;
					}
					return;
				}
			}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
				if(pObj->PressIndex == Index){
					_DrawButton(pObj, &Rect, CharBuffer, 0);
					pObj->PressStatus = KEYBOARD_PRESS_NULL;
					return;
				}
			}
		}
	}
	OneButtonHeight = (Height - pObj->Props.Spacing * 4 - StatusHeight)/3;
	for(i = 0; i < 3; i++){
		Rect.x0 = OneButtonWidth * j + pObj->Props.Spacing * (j + 1);
		Rect.x1 = Rect.x0 + OneButtonWidth;
		Rect.y0 = OneButtonHeight * i + pObj->Props.Spacing * (i + 1) + StatusHeight;
		Rect.y1 = Rect.y0 + OneButtonHeight;
		if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
			if(0 == i){
				_DrawButton(pObj, &Rect, "Del", 0);
			}else if(1 == i){
				_DrawButton(pObj, &Rect, "Enter", 0);
			}else{
				_DrawButton(pObj, &Rect, "abc", 0);
			}
		}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
			if((KEYBOARD_NUMBER_DELETE == pObj->PressIndex) && (0 == i)){
				_DrawButton(pObj, &Rect, "Del", 1);
				return;
			}else if((KEYBOARD_NUMBER_ENTER == pObj->PressIndex) && (1 == i)){
				_DrawButton(pObj, &Rect, "Enter", 1);
				return;
			}else if((KEYBOARD_NUMBER_ABC == pObj->PressIndex) && (2 == i)){
				_DrawButton(pObj, &Rect, "abc", 1);
				pObj->SwitchFlag = KEYBOARD_STYLE_LOWERCASE;
				return;
			}
		}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
			if((KEYBOARD_NUMBER_DELETE == pObj->PressIndex) && (0 == i)){
				_DrawButton(pObj, &Rect, "Del", 0);
				pObj->PressStatus = KEYBOARD_PRESS_NULL;
				return;
			}else if((KEYBOARD_NUMBER_ENTER == pObj->PressIndex) && (1 == i)){
				_DrawButton(pObj, &Rect, "Enter", 0);
				pObj->PressStatus = KEYBOARD_PRESS_NULL;
				return;
			}else if((KEYBOARD_NUMBER_ABC == pObj->PressIndex) && (2 == i)){
				_DrawButton(pObj, &Rect, "abc", 0);
				pObj->PressStatus = KEYBOARD_PRESS_NULL;
				return;
			}
		}
	}
}
static void _PaintCharStyle(KEYBOARD_Obj* pObj, KEYBOARD_Handle hObj)
{
	I16 Height = 0, Width = 0;
	U32 Index = 0;
	I16 OneButtonWidth = 0, OneButtonHeight = 0;
	I16 StatusHeight = 0;
	I16 OffestX = 0 ,EndX = 0, StartX = 0;
	GUI_RECT Rect;
	U8 i = 0;
	char CharBuffer[2] = "";
	char *pCharText;
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	StatusHeight = Height/KEYBOARD_TRIANGLE_SCALE;
	OneButtonHeight = (Height - pObj->Props.Spacing * 5 - StatusHeight)/4;
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(pObj->Props.pFont);

	if(KEYBOARD_STYLE_LOWERCASE == pObj->Style){
		pCharText = LowercaseText;
	}else if(KEYBOARD_STYLE_UPPERCASE == pObj->Style){
		pCharText = UppercaseText;
	}else if(KEYBOARD_STYLE_SYMBOL == pObj->Style){
		pCharText = SymbolText;
	}
	if(KEYBOARD_STYLE_LOWERCASE == pObj->SwitchFlag){
		pCharText = LowercaseText;
		pObj->Style = KEYBOARD_STYLE_LOWERCASE;
		pObj->PressStatus = KEYBOARD_PRESS_NULL;
	}else if(KEYBOARD_STYLE_UPPERCASE == pObj->SwitchFlag){
		pCharText = UppercaseText;
		pObj->Style = KEYBOARD_STYLE_UPPERCASE;
		pObj->PressStatus = KEYBOARD_PRESS_NULL;
	}
	pObj->SwitchFlag = KEYBOARD_STYLE_NULL;
	/* draw english keyboard first line */
	OneButtonWidth = (Width - pObj->Props.Spacing * 11)/10;
	for(i = 0; i < 10; i++){
		Index = i;
		Rect.x0 = OneButtonWidth * i + pObj->Props.Spacing * (i + 1);
		Rect.x1 = Rect.x0 + OneButtonWidth;
		Rect.y0 = pObj->Props.Spacing + StatusHeight;
		Rect.y1 = Rect.y0 + OneButtonHeight;
		CharBuffer[0] = pCharText[Index];
		CharBuffer[1] = '\0';
		if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
			_DrawButton(pObj, &Rect, CharBuffer, 0);
		}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
			if(Index == pObj->PressIndex){
				_DrawButton(pObj, &Rect, CharBuffer, 1);
				return;
			}
		}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
			if(Index == pObj->PressIndex){
				_DrawButton(pObj, &Rect, CharBuffer, 0);
				pObj->PressStatus = KEYBOARD_PRESS_NULL;
				return;
			}
		}
	}
	/* draw english keyboard second line*/
	OffestX = OneButtonWidth/2;
	for(i = 0; i < 9; i++){
		Index = i + 10;
		Rect.x0 = OneButtonWidth * i + pObj->Props.Spacing * (i + 1) + OffestX;
		Rect.x1 = Rect.x0 + OneButtonWidth;
		Rect.y0 = OneButtonHeight + pObj->Props.Spacing * 2 + StatusHeight;
		Rect.y1 = Rect.y0 + OneButtonHeight;
		CharBuffer[0] = pCharText[Index];
		CharBuffer[1] = '\0';
		if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
			_DrawButton(pObj, &Rect, CharBuffer, 0);
		}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
			if(Index == pObj->PressIndex){
				_DrawButton(pObj, &Rect, CharBuffer, 1);
				return;
			}
		}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
			if(Index == pObj->PressIndex){
				_DrawButton(pObj, &Rect, CharBuffer, 0);
				pObj->PressStatus = KEYBOARD_PRESS_NULL;
				return;
			}
		}
	}
	/* draw english keyboard third line */
	OffestX += OneButtonWidth + pObj->Props.Spacing;
	for(i = 0; i < 7; i++){
		Index = i + 19;
		Rect.x0 = OneButtonWidth * i + pObj->Props.Spacing * (i + 1) + OffestX;
		Rect.x1 = Rect.x0 + OneButtonWidth;
		Rect.y0 = OneButtonHeight * 2 + pObj->Props.Spacing * 3 + StatusHeight;
		Rect.y1 = Rect.y0 + OneButtonHeight;
		CharBuffer[0] = pCharText[Index];
		CharBuffer[1] = '\0';
		if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
			_DrawButton(pObj, &Rect, CharBuffer, 0);
		}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
			if(Index == pObj->PressIndex){
				_DrawButton(pObj, &Rect, CharBuffer, 1);
				return;
			}
		}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
			if(Index == pObj->PressIndex){
				_DrawButton(pObj, &Rect, CharBuffer, 0);
				pObj->PressStatus = KEYBOARD_PRESS_NULL;
				return;
			}
		}
	}
	Rect.y0 = OneButtonHeight * 2 + pObj->Props.Spacing * 3 + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	/* draw button "Cap"*/
	Rect.x0 = pObj->Props.Spacing;
	Rect.x1 = OffestX;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		if(KEYBOARD_CHAR_CAP == pObj->PressIndex){
			if(pObj->Style == KEYBOARD_STYLE_UPPERCASE){
				_DrawButton(pObj, &Rect, "Cap", 1);
			}else{
				_DrawButton(pObj, &Rect, "Cap", 0);
			}
			return;
		}else{
			_DrawButton(pObj, &Rect, "Cap", 0);
		}
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_CAP == pObj->PressIndex){
			if(pObj->Style == KEYBOARD_STYLE_UPPERCASE){
				_DrawButton(pObj, &Rect, "Cap", 1);
			}else{
				_DrawButton(pObj, &Rect, "Cap", 0);
			}
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_CAP == pObj->PressIndex){
			//_DrawButton(pObj, &Rect, "Cap", 0);
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			return;
		}
	}
	/* draw button "Del"*/
	Rect.x0 = OneButtonWidth * 8 + pObj->Props.Spacing * 9 + OneButtonWidth/2;
	Rect.x1 = OneButtonWidth * 10 + pObj->Props.Spacing * 10;
	EndX = Rect.x1;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		_DrawButton(pObj, &Rect, "Del", 0);
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_DELETE == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "Del", 1);
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_DELETE == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "Del", 0);
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			return;
		}
	}
	/* draw english fouth line */
	Rect.y0 = OneButtonHeight * 3 + pObj->Props.Spacing * 4 + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	/* draw button "123" */
	Rect.x0 = pObj->Props.Spacing;
	Rect.x1 = Rect.x0 + OneButtonWidth * 2;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		_DrawButton(pObj, &Rect, "123", 0);
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_123 == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "123", 1);
			pObj->SwitchFlag = KEYBOARD_STYLE_NUMBER;
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_123 == pObj->PressIndex){
			//_DrawButton(pObj, &Rect, "123", 0);
			//pObj->Style = KEYBOARD_STYLE_NUMBER;
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			//WM_InvalidateWindow(hObj);
			return;
		}
	}
	/* draw button "~*" */
	Rect.x0 = Rect.x1 + pObj->Props.Spacing;
	Rect.x1 = Rect.x0 + OneButtonWidth + OneButtonWidth/2;
	StartX = Rect.x1;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		_DrawButton(pObj, &Rect, (KEYBOARD_STYLE_SYMBOL != pObj->Style) ? "~*" : "abc", 0);
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_SYMBOL == pObj->PressIndex){
			_DrawButton(pObj, &Rect, (KEYBOARD_STYLE_SYMBOL != pObj->Style) ? "~*" : "abc", 1);
			if(KEYBOARD_STYLE_SYMBOL == pObj->Style){
				pObj->SwitchFlag = KEYBOARD_STYLE_LOWERCASE;
			}else{
				pObj->SwitchFlag = KEYBOARD_STYLE_SYMBOL;
			}
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_SYMBOL == pObj->PressIndex){
			_DrawButton(pObj, &Rect, (KEYBOARD_STYLE_SYMBOL != pObj->Style) ? "~*" : "abc", 0);
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			return;
		}
	}
	/* draw button Enter */
	Rect.x1 = EndX;
	Rect.x0 = EndX - OneButtonWidth * 2;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
			_DrawButton(pObj, &Rect, "Enter", 0);
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_ENTER == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "Enter", 1);
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_ENTER == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "Enter", 0);
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			return;
		}
	}
	/* draw button "." */
	Rect.x1 = Rect.x0 - pObj->Props.Spacing;
	Rect.x0 = Rect.x1 - (OneButtonWidth + OneButtonWidth/2);
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		_DrawButton(pObj, &Rect, ".", 0);
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_POINT == pObj->PressIndex){
			_DrawButton(pObj, &Rect, ".", 1);
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_POINT == pObj->PressIndex){
			_DrawButton(pObj, &Rect, ".", 0);
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			return;
		}
	}
	/* draw button "Space" */
	Rect.x1 = Rect.x0 - pObj->Props.Spacing;
	Rect.x0 = StartX + pObj->Props.Spacing;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		_DrawButton(pObj, &Rect, "Space", 0);
	}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
		if(KEYBOARD_CHAR_SPACE == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "Space", 1);
			return;
		}
	}else if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
		if(KEYBOARD_CHAR_SPACE == pObj->PressIndex){
			_DrawButton(pObj, &Rect, "Space", 0);
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			return;
		}
	}
}
static U8 _DrawTriangle(KEYBOARD_Obj* pObj, KEYBOARD_Handle hObj)
{
	GUI_POINT Points[4];
	U8 IsVaild = 0;
	I16 Height = 0, Width = 0;
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	Points[0].x = Width - Width/KEYBOARD_TRIANGLE_SCALE;
	Points[0].y = 1;
	Points[1].x = Width;
	Points[1].y = 1;
	Points[2].x = Points[0].x + Width/(KEYBOARD_TRIANGLE_SCALE * 2);
	Points[2].y = Height/KEYBOARD_TRIANGLE_SCALE - 1;
	Points[3].x = Width - Width/KEYBOARD_TRIANGLE_SCALE;
	Points[3].y = 1;
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		GUI_SetColor(pObj->Props.UnfocusStyle.MainColor);
		GUI_AA_FillPolygon(Points, 4, 0, 0);
	}else {
		if(pObj->PressIndex == KEYBOARD_TRIANGLE){
			if(KEYBOARD_PRESS_REALEASE == pObj->PressStatus){
				IsVaild = 1;
				GUI_SetColor(pObj->Props.UnfocusStyle.MainColor);
				GUI_AA_FillPolygon(Points, 4, 0, 0);
			}else if(KEYBOARD_PRESS_PRESS == pObj->PressStatus){
				IsVaild = 1;
				GUI_SetColor(pObj->Props.FocusStyle.MainColor);
				GUI_AA_FillPolygon(Points, 4, 0, 0);
			}
		}
	}
	return IsVaild;
}
/*
static U8 _CheckIsInParentTop(KEYBOARD_Handle hObj)
{
	WM_HWIN hParent, hChild, hTop;
	WM_Obj *pParent, *pChild;
	hParent = WM_GetParent(hObj);
	pParent = WM_H2P(hParent);
	for(hChild = pParent->hFirstChild; hChild; hChild = pChild->hNext){
		hTop = hChild;
		GUI_Debug("hChild:%d\n", hChild);
		pChild = WM_H2P(hChild);
	}
	//GUI_Debug("hTop:%d, hObj:%d\n", hTop, hObj);
	if(hTop == hObj){
		return 1;
	}else{
		return 0;
	}
}*/
static void _Paint(KEYBOARD_Obj* pObj, KEYBOARD_Handle hObj)
{
	WM_Obj *pWin;

	pWin = WM_H2P(hObj);
	if(WM_SF_ISVIS != (pWin->Status & WM_SF_ISVIS)){
		return;
	}
	/*if(0 == _CheckIsInParentTop(hObj)){
		return;
	}*/
	if(KEYBOARD_PRESS_NULL == pObj->PressStatus){
		//GUI_SetBkColor(pObj->Props.BkColor);
		GUI_SetBkColor(pObj->Props.BkColor);
		GUI_Clear();
	}
	if(_DrawTriangle(pObj, hObj)){
		return;
	}
	if(KEYBOARD_STYLE_NUMBER == pObj->Style){
		_PaintNumberStyle(pObj, hObj);
	}else{
		_PaintCharStyle(pObj, hObj);
	}
}
static U8 _PointInRect(GUI_RECT *pRect, I32 x, I32 y)
{
	if ((x >= pRect->x0)
		&& (x <= pRect->x1)
		&& (y >= pRect->y0)
		&& (y <= pRect->y1)){
		return 1;
	}
	return 0;
}
static U8 _OnNumberStylePress(KEYBOARD_Handle hObj, KEYBOARD_Obj* pObj, I32 x, I32 y)
{
	I16 Height = 0, Width = 0;
	I16 StatusHeight = 0;
	I16 OneButtonWidth, OneButtonHeight = 0;
	GUI_RECT Rect;
	U8 i = 0, j = 0;
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	StatusHeight = Height/10;
	OneButtonWidth = (Width - pObj->Props.Spacing * 6)/5;
	OneButtonHeight = (Height - pObj->Props.Spacing * 5 - StatusHeight)/4;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			Rect.x0 = OneButtonWidth * j + pObj->Props.Spacing * (j + 1);
			Rect.x1 = Rect.x0 + OneButtonWidth;
			Rect.y0 = OneButtonHeight * i + pObj->Props.Spacing * (i + 1) + StatusHeight;
			Rect.y1 = Rect.y0 + OneButtonHeight;
			if(_PointInRect(&Rect, x, y)){
				pObj->PressIndex = i * 4 + j;
				return 1;
			}
		}
	}
	OneButtonHeight = (Height - pObj->Props.Spacing * 4)/3;
	for(i = 0; i < 3; i++){
		Rect.x0 = OneButtonWidth * j + pObj->Props.Spacing * (j + 1);
		Rect.x1 = Rect.x0 + OneButtonWidth;
		Rect.y0 = OneButtonHeight * i + pObj->Props.Spacing * (i + 1) + StatusHeight;
		Rect.y1 = Rect.y0 + OneButtonHeight;
		if(_PointInRect(&Rect, x, y)){
			if(0 == i){
				pObj->PressIndex = KEYBOARD_NUMBER_DELETE;
			}else if(1 == i){
				pObj->PressIndex = KEYBOARD_NUMBER_ENTER;
			}else{
				pObj->PressIndex = KEYBOARD_NUMBER_ABC;
			}
			return 1;
		}
	}
	return 0;
}
static U8 _OnCharStylePress(KEYBOARD_Handle hObj, KEYBOARD_Obj* pObj, I32 x, I32 y)
{
	I16 Height = 0, Width = 0;
	U32 Index = 0;
	I16 OneButtonWidth = 0, OneButtonHeight = 0;
	I16 StatusHeight = 0;
	I16 OffestX = 0 ,EndX = 0, StartX = 0;
	GUI_RECT Rect;
	U8 i = 0;
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	StatusHeight = Height/10;
	OneButtonHeight = (Height - pObj->Props.Spacing * 5 - StatusHeight)/4;
	/* draw english keyboard first line */
	OneButtonWidth = (Width - pObj->Props.Spacing * 11)/10;
	Rect.y0 = pObj->Props.Spacing + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	for(i = 0; i < 10; i++){
		Index = i;
		Rect.x0 = OneButtonWidth * i + pObj->Props.Spacing * (i + 1);
		Rect.x1 = Rect.x0 + OneButtonWidth;
		if(_PointInRect(&Rect, x, y)){
			pObj->PressIndex = Index;
			return 1;
		}
	}
	/* draw english keyboard second line*/
	Rect.y0 = OneButtonHeight + pObj->Props.Spacing * 2 + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	OffestX = OneButtonWidth/2;
	for(i = 0; i < 9; i++){
		Index = i + 10;
		Rect.x0 = OneButtonWidth * i + pObj->Props.Spacing * (i + 1) + OffestX;
		Rect.x1 = Rect.x0 + OneButtonWidth;
		if(_PointInRect(&Rect, x, y)){
			pObj->PressIndex = Index;
			return 1;
		}
	}
	/* draw english keyboard third line */
	Rect.y0 = OneButtonHeight * 2 + pObj->Props.Spacing * 3 + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	OffestX += OneButtonWidth + pObj->Props.Spacing;
	for(i = 0; i < 7; i++){
		Index = i + 19;
		Rect.x0 = OneButtonWidth * i + pObj->Props.Spacing * (i + 1) + OffestX;
		Rect.x1 = Rect.x0 + OneButtonWidth;
		if(_PointInRect(&Rect, x, y)){
			pObj->PressIndex = Index;
			return 1;
		}
	}
	Rect.y0 = OneButtonHeight * 2 + pObj->Props.Spacing * 3 + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	/* draw button "Cap"*/
	Rect.x0 = pObj->Props.Spacing;
	Rect.x1 = OffestX;
	if(_PointInRect(&Rect, x, y)){
		if(KEYBOARD_STYLE_SYMBOL != pObj->Style){
			pObj->PressIndex = KEYBOARD_CHAR_CAP;
			if(KEYBOARD_STYLE_UPPERCASE == pObj->Style){
				pObj->SwitchFlag = KEYBOARD_STYLE_LOWERCASE;
			}else{
				pObj->SwitchFlag = KEYBOARD_STYLE_UPPERCASE;
			}
			return 1;
		}
		return 0;
	}
	/* draw button "Del"*/
	Rect.x0 = OneButtonWidth * 8 + pObj->Props.Spacing * 9 + OneButtonWidth/2;
	Rect.x1 = OneButtonWidth * 10 + pObj->Props.Spacing * 10;
	EndX = Rect.x1;
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_CHAR_DELETE;
		return 1;
	}
	/* draw english fouth line */
	Rect.y0 = OneButtonHeight * 3 + pObj->Props.Spacing * 4 + StatusHeight;
	Rect.y1 = Rect.y0 + OneButtonHeight;
	/* draw button "123" */
	Rect.x0 = pObj->Props.Spacing;
	Rect.x1 = Rect.x0 + OneButtonWidth * 2;
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_CHAR_123;
		return 1;
	}
	/* draw button "~*" */
	Rect.x0 = Rect.x1 + pObj->Props.Spacing;
	Rect.x1 = Rect.x0 + OneButtonWidth + OneButtonWidth/2;
	StartX = Rect.x1;
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_CHAR_SYMBOL;
		return 1;
	}
	/* draw button Enter */
	Rect.x1 = EndX;
	Rect.x0 = EndX - OneButtonWidth * 2;
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_CHAR_ENTER;
		return 1;
	}
	/* draw button "." */
	Rect.x1 = Rect.x0 - pObj->Props.Spacing;
	Rect.x0 = Rect.x1 - (OneButtonWidth + OneButtonWidth/2);
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_CHAR_POINT;
		return 1;
	}
	/* draw button "Space" */
	Rect.x1 = Rect.x0 - pObj->Props.Spacing;
	Rect.x0 = StartX + pObj->Props.Spacing;
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_CHAR_SPACE;
		return 1;
	}
	return 0;
}
static U8 _OnStatusPress(KEYBOARD_Handle hObj, KEYBOARD_Obj* pObj, I32 x, I32 y)
{
	GUI_RECT Rect;
	I16 Height = 0, Width = 0;
	Width = WM_GetWindowSizeX(hObj);
	Height = WM_GetWindowSizeY(hObj);
	Rect.x0 = Width - Width/10;
	Rect.y0 = 1;
	Rect.x1 = Width;
	Rect.y1 = Height/10 - 1;
	if(_PointInRect(&Rect, x, y)){
		pObj->PressIndex = KEYBOARD_TRIANGLE;
		return 1;
	}else{
		return 0;
	}
}
static U8 _OnKeyboardPress(KEYBOARD_Handle hObj, KEYBOARD_Obj* pObj, I32 x, I32 y)
{
	if(_OnStatusPress(hObj, pObj, x, y)){
		return 1;
	}else{
		if(KEYBOARD_STYLE_NUMBER == pObj->Style){
			return _OnNumberStylePress(hObj, pObj, x, y);
		}else{
			return _OnCharStylePress(hObj, pObj, x, y);
		}
	}
}
static U8 _ToCheckChangeStyle(KEYBOARD_Obj* pObj)
{
	if(pObj->StyleLock & KEYBOARD_LOCK_STYLE_NUMBER){
		pObj->SwitchFlag = KEYBOARD_STYLE_NULL;
		pObj->PressStatus = KEYBOARD_PRESS_NULL;
		return 1;
	}
	switch(pObj->SwitchFlag){
		case KEYBOARD_STYLE_NUMBER:
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			pObj->Style = KEYBOARD_STYLE_NUMBER;
			return 0;
		break;
		case KEYBOARD_STYLE_SYMBOL:
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			pObj->Style = KEYBOARD_STYLE_SYMBOL;
			return 0;
		break;
		case KEYBOARD_STYLE_LOWERCASE:
			pObj->PressStatus = KEYBOARD_PRESS_NULL;
			pObj->Style = KEYBOARD_STYLE_LOWERCASE;
			return 0;
		break;
		default:
			pObj->PressStatus = KEYBOARD_PRESS_REALEASE;
			return 1;
		break;
	}
}
static void _OnGetTouchKey(KEYBOARD_Handle hObj, KEYBOARD_Obj* pObj)
{
	char *pCharBuffer;
	if(KEYBOARD_TRIANGLE == pObj->PressIndex){
		if(pObj->DeleteCb){
			pObj->DeleteCb(hObj);
		}
		return;
	}
	if(KEYBOARD_STYLE_NUMBER != pObj->Style){
		if(KEYBOARD_STYLE_LOWERCASE == pObj->Style){
			pCharBuffer = LowercaseText;
		}else if(KEYBOARD_STYLE_UPPERCASE == pObj->Style){
			pCharBuffer = UppercaseText;
		}else if(KEYBOARD_STYLE_SYMBOL == pObj->Style){
			pCharBuffer = SymbolText;
		}
		switch(pObj->PressIndex){
			case KEYBOARD_CHAR_CAP:
				//GUI_Debug("Click cap button\n");
			break;
			case KEYBOARD_CHAR_DELETE:
				//GUI_Debug("Click delete button\n");
				WM_OnKey(GUI_KEY_BACKSPACE, 1);
			break;
			case KEYBOARD_CHAR_123:
				//GUI_Debug("Click 123 button\n");
			break;
			case KEYBOARD_CHAR_SYMBOL:
				//GUI_Debug("Click symbol button\n");
			break;
			case KEYBOARD_CHAR_SPACE:
				//GUI_Debug("Click space button\n");
				WM_OnKey(' ', 1);
			break;
			case KEYBOARD_CHAR_POINT:
			//	GUI_Debug("Click point button\n");
			break;
			case KEYBOARD_CHAR_ENTER:
				if(pObj->EnterCb){
					pObj->EnterCb();
				}
				//GUI_Debug("Click Enter button\n");
			break;
			default:
				WM_OnKey(pCharBuffer[pObj->PressIndex],1);
				//GUI_Debug("Click char %c\n", pCharBuffer[pObj->PressIndex]);
			break;
		}
	}else{
		char Key = 0;
		pCharBuffer = NumberText;
		switch(pObj->PressIndex){
			case KEYBOARD_NUMBER_ABC:
				//GUI_Debug("Click number abc button\n");
			break;
			case KEYBOARD_NUMBER_ENTER:
				if(pObj->EnterCb){
					pObj->EnterCb();
				}
				//GUI_Debug("Click number Enter button\n");
			break;
			case KEYBOARD_NUMBER_DELETE:
				//GUI_Debug("Click number delete button\n");
				WM_OnKey(GUI_KEY_BACKSPACE, 1);
			break;
			default:
				Key = pCharBuffer[pObj->PressIndex];
				if(pObj->StyleLock & KEYBOARD_LOCK_REPORT_NUMBER){
					if((Key >= '0') && (Key <= '9')){
						WM_OnKey(Key, 1);
					}
				}else{
					WM_OnKey(Key, 1);
				}
				//GUI_Debug("Click char %c\n", pCharBuffer[pObj->PressIndex]);
			break;
		}
	}
}
static void _OnTouch(KEYBOARD_Handle hObj, KEYBOARD_Obj* pObj, WM_MESSAGE*pMsg)
{
	const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
	if(pMsg->Data.p){
		if(0 == pState->Pressed){
			if(1 == pObj->IsPress){
				pObj->IsPress = 0;
				if(_ToCheckChangeStyle(pObj)){
					_OnGetTouchKey(hObj, pObj);
				}
				WM_InvalidateWindow(hObj);
			}
		}else{
			if(0 == pObj->IsPress){
				if(_OnKeyboardPress(hObj, pObj, pState->x, pState->y)){
					pObj->IsPress = 1;
					pObj->PressStatus = KEYBOARD_PRESS_PRESS;
					WM_InvalidateWindow(hObj);
				}
			}
		}
	}else {
		//if(0 == pState->Pressed){
			if(1 == pObj->IsPress){
				pObj->IsPress = 0;
				pObj->PressStatus = KEYBOARD_PRESS_REALEASE;
				WM_InvalidateWindow(hObj);
			}
		//}
	}
}

static void KEYBOARD_Callback(WM_MESSAGE *pMsg)
{
	KEYBOARD_Handle hObj = pMsg->hWin;
	KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_TOUCH:
			_OnTouch(hObj, pObj, pMsg);
		return;      /* Message handled. Do not call WM_DefaultProc, because the window may have been destroyed */
		case WM_PAINT:
			_Paint(pObj, hObj);
		return;
		case WM_DELETE:
//			_Delete(pObj);
		break;       /* No return here ... WM_DefaultProc needs to be called */
		default:
		break;
	}
	WM_DefaultProc(pMsg);
}

KEYBOARD_Handle KEYBOARD_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 WinFlags, I32 ExFlags, I32 Id)
{
	KEYBOARD_Handle hObj;
	GUI_USE_PARA(ExFlags);
	/* Create the window */
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, KEYBOARD_Callback,
									sizeof(KEYBOARD_Obj) - sizeof(WM_Obj));
	if (hObj) {
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		pObj->Props = ucKEYOBARD__DefaultProps;
		pObj->Style = KEYBOARD_STYLE_LOWERCASE;
		pObj->StyleLock = KEYBOARD_LOCK_NULL;
		pObj->DeleteCb = NULL;
		pObj->EnterCb = NULL;
	} else {
		GUI_DEBUG_ERROROUT_IF(hObj==0, "KEYBOARD_Create failed")
	}
	return hObj;
}
void KEYBOARD_SetNoticeDeleteCb(KEYBOARD_Handle hWin, _cb_Delete pCb)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->DeleteCb = pCb;
	}
}
void KEYBOARD_SetNoticeEnterCb(KEYBOARD_Handle hWin, _cb_Enter pCb)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->EnterCb = pCb;
	}
}
void KEYBOARD_ResetStatus(KEYBOARD_Handle hWin)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->PressStatus = KEYBOARD_PRESS_NULL;
		pObj->StyleLock = 0;
	}
}
void KEYBOARD_SetStyle(KEYBOARD_Handle hWin, U8 Style)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		if(pObj->Style != Style){
			pObj->Style = Style;
			pObj->StyleLock = KEYBOARD_LOCK_NULL;
			WM_InvalidateWindow(hWin);
		}
	}
}
void KEYBOARD_LockStyle(KEYBOARD_Handle hWin)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->StyleLock |= KEYBOARD_LOCK_STYLE_NUMBER;
	}
}
void KEYBOARD_UnLockStyle(KEYBOARD_Handle hWin)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->StyleLock = KEYBOARD_LOCK_NULL;
	}
}
void KEYBOARD_SetReportNumberOnly(KEYBOARD_Handle hWin)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->StyleLock |= KEYBOARD_LOCK_REPORT_NUMBER;
	}
}
void KEYBOARD_ClearReportNumberOnly(KEYBOARD_Handle hWin)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		pObj->StyleLock &= ~KEYBOARD_LOCK_REPORT_NUMBER;
	}
}
void KEYBOARD_SetBkColor(KEYBOARD_Handle hWin, GUI_COLOR BkColor)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		if(pObj->Props.BkColor != BkColor){
			pObj->Props.BkColor = BkColor;
			WM_InvalidateWindow(hWin);
		}
	}
}
void KEYBOARD_SetPressStyle(KEYBOARD_Handle hWin, GUI_FullRectStyle Style)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		if(GUI_memcmp(&pObj->Props.FocusStyle, &Style, sizeof(GUI_FullRectStyle))){
			GUI_memcpy(&pObj->Props.FocusStyle, &Style, sizeof(GUI_FullRectStyle));
			WM_InvalidateWindow(hWin);
		}
	}
}
void KEYBOARD_SetReleaseStyle(KEYBOARD_Handle hWin, GUI_FullRectStyle Style)
{
	if(hWin){
		KEYBOARD_Obj * pObj = (KEYBOARD_Obj *)GUI_ALLOC_h2p(hWin);
		if(GUI_memcmp(&pObj->Props.UnfocusStyle, &Style, sizeof(GUI_FullRectStyle))){
			GUI_memcpy(&pObj->Props.UnfocusStyle, &Style, sizeof(GUI_FullRectStyle));
			WM_InvalidateWindow(hWin);
		}
	}
}
