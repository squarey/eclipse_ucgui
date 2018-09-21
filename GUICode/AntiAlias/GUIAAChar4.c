/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUICharAA.C
Purpose     : Display antialiased
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

#if GUI_SUPPORT_AA

#include <stdio.h>
//#include <string.h>

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static void _DrawFontScale(I32 x0, I32 y0, I32 XSize, I32 YSize, I32 BytesPerLine, const U8 *pData, U32 Scale)
{
	I32 x, y;
	const U8 *pData0 = pData;
	U8 FontBuffer[YSize][XSize];
	U32 Alpha1 = 0, Alpha2 = 0, Alpha3 = 0, Alpha4 = 0;
	U32 Alpha = 0;
	float ScaleFloat = 0;
	U32 Value1, Value2, Value3, Value4;
	U32 FloatSizeX, FloatSizeY;
	U32 MagnPointX = 0, MagnPointY = 0, MagnScale = 0;
	//I32 Magnification = 0;
	I32 ScaleXSize = 0, ScaleYSize = 0;
	I32 SrcX = 0, SrcY = 0;
	ScaleXSize = (XSize * Scale) >> GUI_FIX_DIV_BIT;
	ScaleYSize = (YSize * Scale) >> GUI_FIX_DIV_BIT;
	ScaleFloat = (float)XSize/ScaleXSize;
	MagnScale = ScaleFloat * GUI_FIX_DIV;
	for (y = 0; y < YSize; y++) {
		pData0 = pData;
		for (x = 0; x < XSize - 1; x += 2) {
			FontBuffer[y][x] = ((*pData0) >> 4)*255/15; /* x0+x changed -> x+x0 to avoid problems with IAR's ICCMC80 */
			FontBuffer[y][x + 1] = ((*pData0++) & 15)*255/15;
		}
		if (XSize & 1) {
			FontBuffer[y][x] = ((*pData0) & 15)*255/15;
		}
		pData += BytesPerLine;
	}
	for(y = 0; y < ScaleYSize; y++){
		FloatSizeY = y * MagnScale;
		SrcY = FloatSizeY >> GUI_FIX_DIV_BIT;
		if(SrcY >= YSize){
			return;
		}
		MagnPointY = FloatSizeY & GUI_FIX_DIV_1;
		for(x = 0; x < ScaleXSize; x++){
			FloatSizeX = x * MagnScale;
			SrcX = FloatSizeX >> GUI_FIX_DIV_BIT;
			MagnPointX = FloatSizeX & GUI_FIX_DIV_1;
			if(SrcX >= XSize){
				continue;
			}
			Value1 = (GUI_FIX_DIV - MagnPointX) * (GUI_FIX_DIV - MagnPointY);
			Value2 = (GUI_FIX_DIV - MagnPointX) * MagnPointY;
			Value3 = MagnPointX * (GUI_FIX_DIV - MagnPointY);
			Value4 = MagnPointX * MagnPointY;
			if((SrcX < XSize) && (SrcY < YSize)){
				Alpha1 = Value1 * FontBuffer[SrcY][SrcX];
			}else{
				Alpha1 = 0;
			}
			if((SrcX < XSize) && ((SrcY + 1) < YSize)){
				Alpha2 = Value2 * FontBuffer[SrcY + 1][SrcX];
			}else{
				Alpha2 = 0;
			}
			if(((SrcX + 1) < XSize) && (SrcY < YSize)){
				Alpha3 = Value3 * FontBuffer[SrcY][SrcX + 1];
			}else{
				Alpha3 = 0;
			}
			if(((SrcX + 1) < XSize) && ((SrcY + 1) < YSize)){
				Alpha4 = Value4 * FontBuffer[SrcY + 1][SrcX + 1];
			}else{
				Alpha4 = 0;
			}
			Alpha = (((Alpha1 + Alpha2 + Alpha3 + Alpha4) >> (GUI_FIX_DIV_BIT << 1)) * 15)/255;
			//Alpha = FontBuffer[SrcY * BytesPerLine * 2 + SrcX];
			LCD_SetPixelAA(x0 + x, y0 + y, (Alpha >= 10) ? 15 : Alpha);
		}
		/*if (ScaleXSize & 1) {

		}*/
	}
}
/*********************************************************************
*
*       Draw
*/
static void Draw(I32 x0, I32 y0, I32 XSize, I32 YSize, I32 BytesPerLine, const U8*pData)
{
	if(GUI_FIX_DIV == GUI_Context.FontScale){
		I32 x, y;
		tLCD_SetPixelAA* pfSetPixelAA;
		pfSetPixelAA = (GUI_Context.TextMode && GUI_TM_TRANS) ? LCD_SetPixelAA : LCD_SetPixelAA_NoTrans;
		for (y = 0; y < YSize; y++) {
			const U8 *pData0 = pData;
			for (x = 0; x < XSize - 1; x += 2) {
				(*pfSetPixelAA)(x + x0, y0 + y,   (*pData0) >> 4); /* x0+x changed -> x+x0 to avoid problems with IAR's ICCMC80 */
				(*pfSetPixelAA)(x0 + x + 1, y0 + y, (*pData0++) & 15);
			}
			if (XSize & 1) {
				(*pfSetPixelAA)(x0 + x,y0 + y, (*pData0) & 15);
			}
			pData += BytesPerLine;
		}
	}else{
		_DrawFontScale(x0, y0, XSize, YSize, BytesPerLine, pData, GUI_Context.FontScale);
	}

}

/*********************************************************************
*
*       GUIPROP_FindChar
*/
static const GUI_FONT_PROP* GUIPROP_FindChar(const GUI_FONT_PROP* pProp, U16P c)
{
	for (pProp = GUI_Context.pAFont->p.pProp; pProp; pProp=(const GUI_FONT_PROP*) pProp->pNext) {
		if ((c>=pProp->First) && (c<=pProp->Last))
			break;
		}
	return pProp;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIPROP_AA4_DispChar
*/
void GUIPROP_AA4_DispChar(U16P c)
{
	I32 BytesPerLine;
	GUI_DRAWMODE DrawMode = GUI_Context.TextMode;
	const GUI_FONT_PROP* pProp = GUIPROP_FindChar(GUI_Context.pAFont->p.pProp, c);
	if (pProp) {
		GUI_DRAWMODE OldDrawMode;
		const GUI_CHARINFO* pCharInfo = pProp->paCharInfo+(c-pProp->First);
		BytesPerLine = pCharInfo->BytesPerLine;
		OldDrawMode  = LCD_SetDrawMode(DrawMode);
		Draw  ( GUI_Context.DispPosX, GUI_Context.DispPosY,
				pCharInfo->XSize,
				GUI_Context.pAFont->YSize,
				BytesPerLine,
				(U8 const*)pCharInfo->pData);
		LCD_SetDrawMode(OldDrawMode); /* Restore draw mode */
		GUI_Context.DispPosX += (GUI_Context.FontScale * pCharInfo->XDist) >> GUI_FIX_DIV_BIT;
	}
}

/*********************************************************************
*
*       GUIPROP_AA4_GetCharDistX
*/
I32 GUIPROP_AA4_GetCharDistX(U16P c)
{
	const GUI_FONT_PROP* pProp = GUIPROP_FindChar(GUI_Context.pAFont->p.pProp, c);
	return (pProp) ? (pProp->paCharInfo+(c-pProp->First))->XSize : 0;
}

/*********************************************************************
*
*       GUIPROP_AA4_GetFontInfo
*/
void GUIPROP_AA4_GetFontInfo(const GUI_FONT * pFont, GUI_FONTINFO* pfi)
{
	GUI_USE_PARA(pFont);
	pfi->Flags = GUI_FONTINFO_FLAG_PROP | GUI_FONTINFO_FLAG_AA4;
}

/*********************************************************************
*
*       GUIPROP_AA4_IsInFont
*/
char GUIPROP_AA4_IsInFont(const GUI_FONT * pFont, U16 c)
{
	const GUI_FONT_PROP* pProp = GUIPROP_FindChar(pFont->p.pProp, c);
	return (pProp==NULL) ? 0 : 1;
}

#else                            /* Avoid problems with empty object modules */
  void GUIAAChar4_C(void);
  void GUIAAChar4_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
