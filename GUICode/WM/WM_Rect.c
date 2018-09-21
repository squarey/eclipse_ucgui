/*
 * GUI_Rect.c
 *
 *  Created on: 2018年5月16日
 *      Author: Administrator
 */


#include "GUI_Protected.h"
#include "WM.h"


U8 WM_RectIntersect(GUI_RECT* pRectResult, const GUI_RECT* pRect1, const GUI_RECT* pRect2)
{
	U8 IsDo = 0;
	pRectResult->x0 = GUI_MATH_MAX(pRect1->x0, pRect2->x0);
	pRectResult->y0 = GUI_MATH_MAX(pRect1->y0, pRect2->y0);
	pRectResult->x1 = GUI_MATH_MIN(pRect1->x1, pRect2->x1);
	pRectResult->y1 = GUI_MATH_MIN(pRect1->y1, pRect2->y1);

	if((pRectResult->x0 > pRectResult->x1) ||
	       (pRectResult->y0 > pRectResult->y1)){
		 IsDo = 0;
	}else{
		IsDo = 1;
	}
	return IsDo;
}
U8 WM_RectIntersectLCD(GUI_RECT* pRectResult, const GUI_RECT* pRect)
{
	U8 IsDo = 0;
	GUI_RECT LCDRect;
	LCD_L0_GetRect(&LCDRect);
	pRectResult->x0 = GUI_MATH_MAX(LCDRect.x0, pRect->x0);
	pRectResult->y0 = GUI_MATH_MAX(LCDRect.y0, pRect->y0);
	pRectResult->x1 = GUI_MATH_MIN(LCDRect.x1, pRect->x1);
	pRectResult->y1 = GUI_MATH_MIN(LCDRect.y1, pRect->y1);
	if((pRectResult->x0 > pRectResult->x1) ||
		   (pRectResult->y0 > pRectResult->y1)){
		 IsDo = 0;
	}else{
		IsDo = 1;
	}
	return IsDo;
}
/*
 * 从两个rect中获取最大的rect把两个rect都包含在里面
 * */
void WM_RectToMax(GUI_RECT* pRectResult, const GUI_RECT* pRect1, const GUI_RECT* pRect2)
{
	pRectResult->x0 = GUI_MATH_MIN(pRect1->x0, pRect2->x0);
	pRectResult->x1 = GUI_MATH_MAX(pRect1->x1, pRect2->x1);
	pRectResult->y0 = GUI_MATH_MIN(pRect1->y0, pRect2->y0);
	pRectResult->y1 = GUI_MATH_MAX(pRect1->y1, pRect2->y1);
}
/* 判断 pRect1是否在pRect2中
 * 返回 1  pRect1 在  pRect2 中
 * 返回 2  pRect2 在  pRect1 中
 * 返回0  都不在
 * */
U8 WM_RectIsIn(const GUI_RECT * pRect1, const GUI_RECT * pRect2)
{
	U8 IsIn = 0;
	GUI_RECT LCDRect, RectResult1, RectResult2;
	LCD_L0_GetRect(&LCDRect);
	WM_RectIntersect(&RectResult1, pRect1, &LCDRect);
	WM_RectIntersect(&RectResult2, pRect2, &LCDRect);
    if( RectResult1.x0  >= RectResult2.x0 &&
    	RectResult1.y0  >= RectResult2.y0 &&
		RectResult1.x1  <= RectResult2.x1 &&
		RectResult1.y1  <= RectResult2.y1){
    	return 1;
    }
    if( RectResult2.x0  >= RectResult1.x0 &&
       	RectResult2.y0  >= RectResult1.y0 &&
   		RectResult2.x1  <= RectResult1.x1 &&
   		RectResult2.y1  <= RectResult1.y1){
       	return 2;
   }
    return IsIn;
}

void WM_RectSet(GUI_RECT * pRect, I16 x0, I16 y0, I16 x1, I16 y1)
{
    pRect->x0 = x0;
    pRect->y0 = y0;
    pRect->x1 = x1;
    pRect->y1 = y1;
}
I16 WM_RectGetWidth(const GUI_RECT * pRect)
{
    return pRect->x1 - pRect->x0 + 1;
}
I16 WM_RectGetHeight(const GUI_RECT * pRect)
{
    return pRect->y1 - pRect->y0 + 1;
}
void WM_RectReduceX(GUI_RECT *pRect, I16 xReduce)
{
	if(pRect){
		pRect->x0 += xReduce;
		pRect->x1 -= xReduce;
	}
}
void WM_RectReduceY(GUI_RECT *pRect, I16 yReduce)
{
	if(pRect){
		pRect->y0 += yReduce;
		pRect->y1 -= yReduce;
	}
}
void WM_RectReduce(GUI_RECT *pRect, I16 Reduce)
{
	if(pRect){
		pRect->x0 += Reduce;
		pRect->x1 -= Reduce;
		pRect->y0 += Reduce;
		pRect->y1 -= Reduce;
	}
}



