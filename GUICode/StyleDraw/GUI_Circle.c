/*
 * GUI_Circle.c
 *
 *  Created on: 2018年4月28日
 *      Author: Administrator
 */

#include "GUI_Circle.h"

void GUI_CircleInit(GUI_POINT *pCircle, I16 *pTemp, I16 Radius)
{
	pCircle->x = Radius;
	pCircle->y = 0;
    *pTemp = 1 - Radius;
}


U8 GUI_CircleCont(GUI_POINT *pCircle)
{
    return pCircle->y <= pCircle->x ? 1 : 0;
}

void GUI_CircleGetNext(GUI_POINT *pCircle, I16 *pTemp)
{
	pCircle->y++;

    if (*pTemp <= 0) {
       (*pTemp) += 2 * pCircle->y + 1;  	 		// Change in decision criterion for y -> y+1
    } else {
    	pCircle->x--;
      (*pTemp) += 2 * (pCircle->y - pCircle->x) + 1;   // Change for y -> y+1, x -> x-1
    }
}
