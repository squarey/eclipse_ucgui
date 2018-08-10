/*
 * TOTAST.h
 *
 *  Created on: 2018年6月19日
 *      Author: Administrator
 */

#ifndef TOTAST_H_
#define TOTAST_H_

#include "TOTAST_Private.h"

typedef WM_HMEM TOTAST_Handle;



TOTAST_Handle TOTAST_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                          I32 WinFlags, I32 ExFlags, I32 Id, const char* pText);
void TOTAST_SetText			(TOTAST_Handle hObj, const char *pTest);
void TOTAST_SetFont			(TOTAST_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont);
void TOTAST_SetColor			(TOTAST_Handle hObj, GUI_COLOR BkColor, GUI_COLOR TextColor);
TOTAST_Handle 				TOTAST_StaticShow(const char *pTest);
void 							TOTAST_StaticSetText(const char *pTest);
void 							TOTAST_StaticSetFont(const GUI_FONT GUI_UNI_PTR * pFont);
void 							TOTAST_StaticSetColor(GUI_COLOR BkColor, GUI_COLOR TextColor);
#endif /* TOTAST_H_ */
