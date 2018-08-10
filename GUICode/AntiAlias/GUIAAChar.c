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
*       Types
*
**********************************************************************
*/

typedef void tSetPixelAA(I32 x, I32 y, U8 Intens);

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const U8 Bit2Mask0[] = {1<<7, 1<<5, 1<<3, 1<<1};
static const U8 Bit2Mask1[] = {1<<6, 1<<4, 1<<2, 1<<0};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       Draw
*/
static void Draw(I32 x0, I32 y0, I32 XSize, I32 YSize, I32 BytesPerLine, const U8*pData)
{
	I32 x, y;
	tSetPixelAA* pfSetPixelAA;
	pfSetPixelAA = (GUI_Context.TextMode & GUI_TM_TRANS) ? LCD_SetPixelAA : LCD_SetPixelAA_NoTrans;
	for (y = 0; y < YSize; y++) {
		const U8* pData0 = pData;
		const U8* pData1 = pData + BytesPerLine;
		for (x = 0; x < XSize; x++) {
			I32 PixelCnt=0;
			I32 Mask0 = Bit2Mask0[x & 3];
			I32 Mask1 = Bit2Mask1[x & 3];
			if ((*pData0) & Mask0){
				PixelCnt++;
			}
			if ((*pData0) & Mask1){
				PixelCnt++;
			}
			if ((*pData1) & Mask0){
				PixelCnt++;
			}
			if ((*pData1) & Mask1){
				PixelCnt++;
			}
			if ((x & 3) ==3) {
				pData0++;
				pData1++;
			}
			switch (PixelCnt) {
				case 4:
					LCD_HL_DrawPixel(x0+x,y0+y);
				break;
				case 3:
					(*pfSetPixelAA) (x0+x,y0+y, 12);
				break;
				case 2:
					(*pfSetPixelAA) (x0+x,y0+y, 8);
				break;
				case 1:
					(*pfSetPixelAA) (x0+x,y0+y, 4);
				break;
			}
		}
		pData += 2 * BytesPerLine;
	}
}

/*********************************************************************
*
*       GUIPROP_FindChar
*/
static const GUI_FONT_PROP* GUIPROP_FindChar(const GUI_FONT_PROP* pProp, U16P c) {
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
*       GUIPROPAA_DispChar
*/
void GUIPROPAA_DispChar(U16P c) {
  I32 BytesPerLine;
  GUI_DRAWMODE DrawMode = GUI_Context.TextMode;
  const GUI_FONT_PROP* pProp = GUIPROP_FindChar(GUI_Context.pAFont->p.pProp, c);
  if (pProp) {
    GUI_DRAWMODE OldDrawMode;
    const GUI_CHARINFO* pCharInfo = pProp->paCharInfo+(c-pProp->First);
    BytesPerLine = pCharInfo->BytesPerLine;
    OldDrawMode  = LCD_SetDrawMode(DrawMode);
    Draw  ( GUI_Context.DispPosX, GUI_Context.DispPosY,
                       (pCharInfo->XSize+1)/2,
                       GUI_Context.pAFont->YSize,
                       BytesPerLine,
                       (U8 const*) pCharInfo->pData
                       );
    LCD_SetDrawMode(OldDrawMode); /* Restore draw mode */
    GUI_Context.DispPosX += (pCharInfo->XDist+1)/2;
  }
}

/*********************************************************************
*
*       GUIPROPAA_GetCharDistX
*/
I32 GUIPROPAA_GetCharDistX(U16P c) {
  I32 r;
  const GUI_FONT_PROP* pProp = GUIPROP_FindChar(GUI_Context.pAFont->p.pProp, c);
  r = (pProp) ? (pProp->paCharInfo+(c-pProp->First))->XSize : 0;
  return (r+1)/2;
}

/*********************************************************************
*
*       GUIPROPAA_GetFontInfo
*/
void GUIPROPAA_GetFontInfo(const GUI_FONT * pFont, GUI_FONTINFO* pfi) {
  GUI_USE_PARA(pFont);
  pfi->Flags = GUI_FONTINFO_FLAG_PROP | GUI_FONTINFO_FLAG_AA;
}

/*********************************************************************
*
*       GUIPROPAA_IsInFont
*/
char GUIPROPAA_IsInFont(const GUI_FONT * pFont, U16 c) {
  const GUI_FONT_PROP* pProp = GUIPROP_FindChar(pFont->p.pProp, c);
  return (pProp==NULL) ? 0 : 1;
}

#else                            /* Avoid problems with empty object modules */
  void GUIAAChar_C(void);
  void GUIAAChar_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
