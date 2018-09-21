/*
 * WindowList_Create.c
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */
#include "WindowList.h"


WM_HWIN WindowList_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags)
{
	return WindowList_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}
