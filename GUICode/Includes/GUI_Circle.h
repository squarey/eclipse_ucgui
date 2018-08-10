/*
 * GUI_Circle.h
 *
 *  Created on: 2018年4月28日
 *      Author: Administrator
 */

#ifndef GUI_CIRCLE_H_
#define GUI_CIRCLE_H_

#include "WM.h"

#define GUI_CIRC_OCT1_X(p) (p.x)
#define GUI_CIRC_OCT1_Y(p) (p.y)
#define GUI_CIRC_OCT2_X(p) (p.y)
#define GUI_CIRC_OCT2_Y(p) (p.x)
#define GUI_CIRC_OCT3_X(p) (-p.y)
#define GUI_CIRC_OCT3_Y(p) (p.x)
#define GUI_CIRC_OCT4_X(p) (-p.x)
#define GUI_CIRC_OCT4_Y(p) (p.y)
#define GUI_CIRC_OCT5_X(p) (-p.x)
#define GUI_CIRC_OCT5_Y(p) (-p.y)
#define GUI_CIRC_OCT6_X(p) (-p.y)
#define GUI_CIRC_OCT6_Y(p) (-p.x)
#define GUI_CIRC_OCT7_X(p) (p.y)
#define GUI_CIRC_OCT7_Y(p) (-p.x)
#define GUI_CIRC_OCT8_X(p) (p.x)
#define GUI_CIRC_OCT8_Y(p) (-p.y)

void GUI_CircleInit(GUI_POINT *pCircle, I16 *pTemp, I16 Radius);
U8 GUI_CircleCont(GUI_POINT *pCircle);
void GUI_CircleGetNext(GUI_POINT *pCircle, I16 *pTemp);

#endif /* GUI_CIRCLE_H_ */
