/*
 * CHECKBOX_StyleCircle.c
 *
 *  Created on: 2018年5月14日
 *      Author: Administrator
 */


#include "CHECKBOX_Private.h"


#if GUI_WINSUPPORT && CHECKBOX_SUPPORT


void CHECKBOX_SetStyleCircleRadius(CHECKBOX_Handle hObj, I16 RadiusExt, I16 RadiusIn)
{
	if(hObj){
		CHECKBOX_Obj * pObj;
		pObj = CHECKBOX_H2P(hObj);
		if ((pObj->Props.StyleCircle.RadiusExt != RadiusExt) || (pObj->Props.StyleCircle.RadiusIn != RadiusIn)) {
			if(RadiusIn > RadiusExt){
				RadiusIn = RadiusExt - 2;
			}
			pObj->Props.StyleCircle.RadiusExt = RadiusExt;
			pObj->Props.StyleCircle.RadiusIn = RadiusIn;
			if(pObj->Props.StyleCircleUsed){
				WM_Invalidate(hObj);
			}
		}
	}
}
void CHECKBOX_SetStyleCircleColor(CHECKBOX_Handle hObj, GUI_COLOR ColorExt, GUI_COLOR ColorIn)
{
	if(hObj){
		CHECKBOX_Obj * pObj;
		pObj = CHECKBOX_H2P(hObj);
		if((pObj->Props.StyleCircle.ColorExt != ColorExt) || (pObj->Props.StyleCircle.ColorIn != ColorIn)){
			pObj->Props.StyleCircle.ColorExt = ColorExt;
			pObj->Props.StyleCircle.ColorIn = ColorIn;
			if(pObj->Props.StyleCircleUsed){
				WM_Invalidate(hObj);
			}
		}
	}
}
void CHECKBOX_EnableStyleCircle(CHECKBOX_Handle hObj)
{
	if(hObj){
		CHECKBOX_Obj * pObj;
		pObj = CHECKBOX_H2P(hObj);
		if(0 == pObj->Props.StyleCircleUsed){
			pObj->Props.StyleCircleUsed = 1;
			WM_Invalidate(hObj);
		}
	}
}

void CHECKBOX_DisableStyleCircle(CHECKBOX_Handle hObj)
{
	if(hObj){
		CHECKBOX_Obj * pObj;
		pObj = CHECKBOX_H2P(hObj);
		if(1 == pObj->Props.StyleCircleUsed){
			pObj->Props.StyleCircleUsed = 0;
			WM_Invalidate(hObj);
		}
	}
}


#endif
