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

typedef enum
{
	GUI_SHADOW_FULL =   0x00,
	GUI_SHADOW_BOTTOM = 0x01,
}GUI_ShadowPart;

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

typedef struct
{
	U16 Radius;
	I16 Width;
	U8 Type;
	U8 Opacity;
	GUI_COLOR Color;
}GUI_ShadowStyle;

GUI_COLOR GUI_ColorMix(GUI_COLOR Color1, GUI_COLOR Color2, U8 Mix);
void GUI_DrawRectShadow(const GUI_RECT *pRect, const GUI_ShadowStyle *pStyle);
/*
 * 填充圆角矩形
 * pRect: 所需填充的区域
 * pStyle: 填充的风格
 * pStyle->Radius: 圆角的半径
 * pStyle->Opacity: 填充颜色的透明度
 * pStyle->MainColor: 主色调
 * pStyle->GradColor: 渐变色调
 * */
void GUI_FillRoundRect(const GUI_RECT *pRect, const GUI_FullRectStyle *pStyle);
/*
 * 绘制圆角矩形(不填充)
 * pRect: 所需绘制的区域
 * pStyle: 绘制的风格
 * pStyle->Radius: 圆角的半径
 * pStyle->Width: 圆角矩形的线宽
 * pStyle->Part: 绘制的部分
 * pStyle->Color: 绘制的颜色
 * */
void GUI_DrawRoundRect(const GUI_RECT* pRect, const GUI_BorderStyle * pStyle);

#endif /* GUI_STYLEDRAW_H_ */
