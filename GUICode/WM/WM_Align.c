/*
 * WM_Align.c
 *
 *  Created on: 2018年5月6日
 *      Author: Administrator
 */
#include "WM.h"
#include "WM_Intern.h"

I16 WM_GetRectSizeX(GUI_RECT Rect)
{
	return Rect.x1 - Rect.x0 + 1;
}
I16 WM_GetRectSizeY(GUI_RECT Rect)
{
	return Rect.y1 - Rect.y0 + 1;
}
void WM_SetAlignWindow(WM_HWIN hObjBasic, WM_HWIN hObjSrc, GUI_ALIGN_em Align,
							I16 OffestX, I16 OffestY)
{
	if(Align >= OBJ_ALIGN_BROTHER_NUM){
		return;
	}
	if((0 == hObjBasic) || (0 == hObjSrc)){
		return;
	}else{
		I16 SrcWidth, SrcHeight, BaseWidth, BaseHeight;
		//WM_HWIN hBasicParent, hSrcParent;
		GUI_RECT BasicRect, SrcRect, ResultRect;
		I32 dx = 0, dy = 0;
		/*hBasicParent = WM_GetParent(hObjBasic);
		hSrcParent = WM_GetParent(hObjSrc);
		if((hBasicParent != hSrcParent) || (0 == hBasicParent) || (0 == hSrcParent)){
			return;
		}*/
		WM_GetWindowRectEx(hObjBasic, &BasicRect);
		WM_GetWindowRectEx(hObjSrc, &SrcRect);
		SrcWidth = WM_GetRectSizeX(SrcRect);
		SrcHeight = WM_GetRectSizeY(SrcRect);
		BaseWidth = WM_GetRectSizeX(BasicRect);
		BaseHeight = WM_GetRectSizeY(BasicRect);
		ResultRect = SrcRect;
		switch(Align){
			case OBJ_ALIGN_BROTHER_LEFT:
				ResultRect.x0 = BasicRect.x0;
				ResultRect.x1 = ResultRect.x0 + SrcWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_RIGHT:
				ResultRect.x0 = BasicRect.x1 + 1;
				ResultRect.x1 = ResultRect.x0 + SrcWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_TOP:
				ResultRect.y0 = BasicRect.y0;
				ResultRect.y1 = ResultRect.y0 + SrcHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 += OffestX;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_BOTTOM:
				ResultRect.y1 = BasicRect.y1;
				ResultRect.y0 = ResultRect.y1 - SrcHeight + OffestY + 1;
				ResultRect.y1 += OffestY;
				ResultRect.x0 += OffestX;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_CENTER:
				if((BaseWidth < SrcWidth) || (BaseHeight < SrcHeight)){
					GUI_Debug("BaseWidth:%d, SrcWidth:%d\n", BaseWidth, SrcWidth);
					GUI_Debug("BaseHeight:%d, SrcHeight:%d\n", BaseHeight, SrcHeight);
					return;
				}
				ResultRect.x0 = BasicRect.x0 + BaseWidth/2 - SrcWidth/2;
				ResultRect.x1 = ResultRect.x0 + SrcWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 = BasicRect.y0 + BaseHeight/2 - SrcHeight/2;
				ResultRect.y1 = ResultRect.y0 + SrcHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				//GUI_Debug("ResultRect %d, %d, %d, %d\n", ResultRect.x0, ResultRect.y0, ResultRect.x1, ResultRect.y1);
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_H_CENTER:
				if(BaseWidth < SrcWidth){
					return;
				}
				ResultRect.x0 = BasicRect.x0 + BaseWidth/2 - SrcWidth/2;
				ResultRect.x1 = ResultRect.x0 + SrcWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_V_CENTER:
				if(BaseHeight < SrcHeight){
					return;
				}
				ResultRect.y0 = BasicRect.y0 + BaseHeight/2 - SrcHeight/2;
				ResultRect.y1 = ResultRect.y0 + SrcHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 += OffestX;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_OUT_LEFT:
				ResultRect.x1 = BasicRect.x0 -1;
				ResultRect.x0 = ResultRect.x1 - SrcWidth + OffestX + 1;
				ResultRect.x1 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_OUT_RIGHT:
				ResultRect.x0 = BasicRect.x1 + 1;
				ResultRect.x1 = ResultRect.x0 + SrcWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_ABOVE_TOP:
				ResultRect.y1 = BasicRect.y0 - 1;
				ResultRect.y0 = ResultRect.y1 - SrcHeight + OffestY + 1;
				ResultRect.y1 += OffestY;
				ResultRect.x0 += OffestX;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			case OBJ_ALIGN_BROTHER_UNDER_BOTTOM:
				ResultRect.y0 = BasicRect.y1 + 1;
				ResultRect.y1 = ResultRect.y0 + SrcHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 += OffestX;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObjSrc, ResultRect);
			break;
			default:
			break;
		}
		dx = ResultRect.x0 - SrcRect.x0;
		dy = ResultRect.y0 - SrcRect.y0;
		WM__MoveWindow(hObjSrc, dx, dy);
	}
}

void WM_SetAlignParent(WM_HWIN hObj, GUI_ALIGN_em Align,
		I16 OffestX, I16 OffestY)
{
	if((Align <= OBJ_ALIGN_BROTHER_NUM) || (Align >= OBJ_ALIGN_PARENT_NUM)){
		return;
	}
	if(hObj){
		I16 ObjWidth, ObjHeight, ParentWidth, ParentHeight;
		I32 dx = 0, dy = 0;
		WM_HWIN hParent;
		GUI_RECT ObjRect, ParentRect, ResultRect;
		hParent = WM_GetParent(hObj);
		if(0 == hParent){
			return;
		}
		WM_GetWindowRectEx(hObj, &ObjRect);
		WM_GetWindowRectEx(hParent, &ParentRect);
		ObjWidth = WM_GetRectSizeX(ObjRect);
		ObjHeight = WM_GetRectSizeY(ObjRect);
		ParentWidth = WM_GetRectSizeX(ParentRect);
		ParentHeight = WM_GetRectSizeY(ParentRect);
		ResultRect = ObjRect;
		switch(Align){
			case OBJ_ALIGN_PARENT_V_CENTRE:
				ResultRect.y0 = (ParentHeight >> 1) - (ObjHeight >> 1) + ParentRect.y0;
				ResultRect.y1 = ResultRect.y0 + ObjHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 += OffestX;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_H_CENTRE:
				ResultRect.x0 = (ParentWidth >> 1) - (ObjWidth >> 1) + ParentRect.x0;
				ResultRect.x1 = ResultRect.x0 + ObjWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_TOP_CENTRE:
				ResultRect.y0 = ParentRect.y0;
				ResultRect.y1 = ResultRect.y0 + ObjHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 = (ParentWidth >> 1) - (ObjWidth >> 1) + ParentRect.x0;
				ResultRect.x1 += ResultRect.x0 + OffestX - 1;
				ResultRect.x0 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_BOTTOM_CENTRE:
				ResultRect.y1 = ParentRect.y1;
				ResultRect.y0 = ResultRect.y1 - ObjHeight + OffestY;
				ResultRect.y1 += OffestY;
				ResultRect.x0 = (ParentWidth >> 1) - (ObjWidth >> 1) + ParentRect.x0;
				ResultRect.x1 = ResultRect.x0 + ObjWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_CENTRE:
				ResultRect.y0 = (ParentHeight >> 1) - (ObjHeight >> 1) + ParentRect.y0;
				ResultRect.y1 = ResultRect.y0 + ObjHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 = (ParentWidth >> 1) - (ObjWidth >> 1) + ParentRect.x0;
				ResultRect.x1 = ResultRect.x0 + ObjWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_LEFT:
				ResultRect.x0 = ParentRect.x0;
				ResultRect.x1 = ResultRect.x0 + ObjWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_RIGHT:
				ResultRect.x1 = ParentRect.x1;
				ResultRect.x0 = ResultRect.x1 - ObjWidth + OffestX + 1;
				ResultRect.x1 += OffestX;
				ResultRect.y0 += OffestY;
				ResultRect.y1 += OffestY;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_LEFT_TOP:
				ResultRect.y0 = ParentRect.y0;
				ResultRect.y1 = ResultRect.y0 + ObjHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x0 = ParentRect.x0;
				ResultRect.x1 = ResultRect.x0 + ObjWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_RIGHT_TOP:
				ResultRect.y0 = ParentRect.y0;
				ResultRect.y1 = ResultRect.y0 + ObjHeight + OffestY - 1;
				ResultRect.y0 += OffestY;
				ResultRect.x1 = ParentRect.x1;
				ResultRect.x0 = ResultRect.x1 - ObjWidth + OffestX + 1;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_LEFT_BOTTOM:
				ResultRect.y1 = ParentRect.y1;
				ResultRect.y0 = ResultRect.y1 - ObjHeight + OffestY + 1;
				ResultRect.y1 += OffestY;
				ResultRect.x0 = ParentRect.x0;
				ResultRect.x1 = ResultRect.x0 + ObjWidth + OffestX - 1;
				ResultRect.x0 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_RIGHT_BOTTOM:
				ResultRect.y1 = ParentRect.y1;
				ResultRect.y0 = ResultRect.y1 - ObjHeight + OffestY + 1;
				ResultRect.y1 += OffestY;
				ResultRect.x1 = ParentRect.x1;
				ResultRect.x0 = ResultRect.x1 - ObjWidth + OffestX + 1;
				ResultRect.x1 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_RIGHT_CENTER:
				ResultRect.y0 = ParentRect.y0 + (ParentHeight - ObjHeight)/2;
				ResultRect.y1 = ResultRect.y0 + ObjHeight - 1 + OffestY;
				ResultRect.y0 += OffestY;
				ResultRect.x1 = ParentRect.x1;
				ResultRect.x0 = ResultRect.x1 - ObjWidth + 1 + OffestX;
				ResultRect.x1 += OffestX;
				//GUI_Debug("x0:%d, y0:%d\n", ResultRect.x0, ResultRect.y0);
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			case OBJ_ALIGN_PARENT_LEFT_CENTER:
				ResultRect.y0 = ParentRect.y0 + (ParentHeight - ObjHeight)/2;
				ResultRect.y1 = ResultRect.y0 + ObjHeight - 1 + OffestY;
				ResultRect.y0 += OffestY;
				ResultRect.x0 = ParentRect.x0;
				ResultRect.x1 = ResultRect.x1 + ObjWidth - 1 + OffestY;
				ResultRect.x0 += OffestX;
				//WM_SetWindowRect(hObj, ResultRect);
			break;
			default:
			return;
		}
		dx = ResultRect.x0 - ObjRect.x0;
		dy = ResultRect.y0 - ObjRect.y0;
		//GUI_Debug("Set Win %d Align parent\n", hObj);
		WM__MoveWindow(hObj, dx, dy);
	}
}
