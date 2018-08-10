/*
 * GUI_StyleDraw.h
 *
 *  Created on: 2018年4月28日
 *      Author: Administrator
 */

#ifndef GUI_STYLEDRAW_H_
#define GUI_STYLEDRAW_H_


#include "WM.h"

typedef enum
{
	GUI_BORDER_NONE =   0x00,
	GUI_BORDER_BOTTOM = 0x01,
	GUI_BORDER_TOP =    0x02,
	GUI_BORDER_LEFT =   0x04,
	GUI_BORDER_RIGHT =  0x08,
	GUI_BORDER_FULL =   0x0F,
}GUI_BorderPart;

typedef struct
{
	I16 Radius;
	U8 Opacity;
	GUI_COLOR MainColor;
	GUI_COLOR GradColor;
}GUI_FullRectStyle;

typedef struct
{
	U16 Radius;
	U16 Width;
	GUI_BorderPart Part;
	GUI_COLOR	Color;
	//U8  Opacity;
}GUI_BorderStyle;


GUI_COLOR GUI_ColorMix(GUI_COLOR Color1, GUI_COLOR Color2, U8 Mix);
void GUI_DrawRectMainMiddle(const GUI_RECT * pRect, const GUI_FullRectStyle *pStyle);
void GUI_DrawRectMainCorner(const GUI_RECT * pRect, const GUI_FullRectStyle * pStyle);
void GUI_DrawRectBorderStraight(const GUI_RECT * pRect, const GUI_BorderStyle * pStyle);
void GUI_DrawRectBorderCorner(const GUI_RECT* pRect, const GUI_BorderStyle * pStyle);

#endif /* GUI_STYLEDRAW_H_ */
