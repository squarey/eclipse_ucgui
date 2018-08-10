/*
*********************************************************************************************************
*                                             uC/GUI V3.98
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
File        : LCD_Protected.h
Purpose     : Internals of the LCD level
----------------------------------------------------------------------
*/

#ifndef UC_LCD_INTERN_H
#define UC_LCD_INTERN_H

#include "LCD.h"

/*********************************************************************
*
*      Data types
*
**********************************************************************
*/

typedef struct {
  I32              NumEntries; 
  const LCD_COLOR* pPalEntries; 
} LCD_PHYSPALETTE; 

/*********************************************************************
*
*      Data
*
**********************************************************************
*/
extern GUI_CONST_STORAGE U8 LCD_aMirror[256];


/********************************************************
*
*     Color conversion routines (used internally only !
*
*********************************************************
*/
unsigned LCD_Color2Index_User    (LCD_COLOR Color);
unsigned LCD_Color2Index_0       (LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal);
unsigned LCD_Color2Index_1       (LCD_COLOR Color);
unsigned LCD_Color2Index_M1      (LCD_COLOR Color);
unsigned LCD_Color2Index_2       (LCD_COLOR Color);
unsigned LCD_Color2Index_M2      (LCD_COLOR Color);
unsigned LCD_Color2Index_4       (LCD_COLOR Color);
unsigned LCD_Color2Index_M4      (LCD_COLOR Color);
unsigned LCD_Color2Index_111     (LCD_COLOR Color);
unsigned LCD_Color2Index_222     (LCD_COLOR Color);
unsigned LCD_Color2Index_233     (LCD_COLOR Color);
unsigned LCD_Color2Index_323     (LCD_COLOR Color);
unsigned LCD_Color2Index_332     (LCD_COLOR Color);
unsigned LCD_Color2Index_444_12  (LCD_COLOR Color);
unsigned LCD_Color2Index_444_12_1(LCD_COLOR Color);
unsigned LCD_Color2Index_444_16  (LCD_COLOR Color);
unsigned LCD_Color2Index_555     (LCD_COLOR Color);
unsigned LCD_Color2Index_565     (LCD_COLOR Color);
unsigned LCD_Color2Index_556     (LCD_COLOR Color);
unsigned LCD_Color2Index_655     (LCD_COLOR Color);
unsigned LCD_Color2Index_666     (LCD_COLOR Color);
unsigned LCD_Color2Index_8666    (LCD_COLOR Color);
unsigned LCD_Color2Index_8666_1  (LCD_COLOR Color);
unsigned LCD_Color2Index_888     (LCD_COLOR Color);
unsigned LCD_Color2Index_M888    (LCD_COLOR Color);
unsigned LCD_Color2Index_M111    (LCD_COLOR Color);
unsigned LCD_Color2Index_M222    (LCD_COLOR Color);
unsigned LCD_Color2Index_M233    (LCD_COLOR Color);
unsigned LCD_Color2Index_M323    (LCD_COLOR Color);
unsigned LCD_Color2Index_M332    (LCD_COLOR Color);
unsigned LCD_Color2Index_M444_12 (LCD_COLOR Color);
unsigned LCD_Color2Index_M444_16 (LCD_COLOR Color);
unsigned LCD_Color2Index_M555    (LCD_COLOR Color);
unsigned LCD_Color2Index_M565    (LCD_COLOR Color);
unsigned LCD_Color2Index_M556    (LCD_COLOR Color);
unsigned LCD_Color2Index_M655    (LCD_COLOR Color);
unsigned LCD_Color2Index_M666    (LCD_COLOR Color);
unsigned LCD_Color2Index_8888	 (LCD_COLOR Color);

LCD_COLOR LCD_Index2Color_User    (I32 Index);
LCD_COLOR LCD_Index2Color_0       (I32 Index, const LCD_PHYSPALETTE* pPhysPal);
LCD_COLOR LCD_Index2Color_1       (I32 Index);
LCD_COLOR LCD_Index2Color_2       (I32 Index);
LCD_COLOR LCD_Index2Color_4       (I32 Index);
LCD_COLOR LCD_Index2Color_111     (I32 Index);
LCD_COLOR LCD_Index2Color_222     (I32 Index);
LCD_COLOR LCD_Index2Color_233     (I32 Index);
LCD_COLOR LCD_Index2Color_323     (I32 Index);
LCD_COLOR LCD_Index2Color_332     (I32 Index);
LCD_COLOR LCD_Index2Color_444_12  (I32 Index);
LCD_COLOR LCD_Index2Color_444_12_1(I32 Index);
LCD_COLOR LCD_Index2Color_444_16  (I32 Index);
LCD_COLOR LCD_Index2Color_555     (I32 Index);
LCD_COLOR LCD_Index2Color_565     (I32 Index);
LCD_COLOR LCD_Index2Color_556     (I32 Index);
LCD_COLOR LCD_Index2Color_655     (I32 Index);
LCD_COLOR LCD_Index2Color_666     (I32 Index);
LCD_COLOR LCD_Index2Color_8666    (I32 Index);
LCD_COLOR LCD_Index2Color_8666_1  (I32 Index);
LCD_COLOR LCD_Index2Color_888     (I32 Index);
LCD_COLOR LCD_Index2Color_M888    (I32 Index);
LCD_COLOR LCD_Index2Color_M111    (I32 Index);
LCD_COLOR LCD_Index2Color_M222    (I32 Index);
LCD_COLOR LCD_Index2Color_M233    (I32 Index);
LCD_COLOR LCD_Index2Color_M323    (I32 Index);
LCD_COLOR LCD_Index2Color_M332    (I32 Index);
LCD_COLOR LCD_Index2Color_M444_12 (I32 Index);
LCD_COLOR LCD_Index2Color_M444_16 (I32 Index);
LCD_COLOR LCD_Index2Color_M555    (I32 Index);
LCD_COLOR LCD_Index2Color_M565    (I32 Index);
LCD_COLOR LCD_Index2Color_M556    (I32 Index);
LCD_COLOR LCD_Index2Color_M655    (I32 Index);
LCD_COLOR LCD_Index2Color_M666    (I32 Index);
LCD_COLOR LCD_Index2Color_8888	  (I32 Index);

unsigned LCD_GetIndexMask_User    (void);
unsigned LCD_GetIndexMask_0       (void);
unsigned LCD_GetIndexMask_1       (void);
unsigned LCD_GetIndexMask_M1      (void);
unsigned LCD_GetIndexMask_2       (void);
unsigned LCD_GetIndexMask_M2      (void);
unsigned LCD_GetIndexMask_4       (void);
unsigned LCD_GetIndexMask_M4      (void);
unsigned LCD_GetIndexMask_111     (void);
unsigned LCD_GetIndexMask_222     (void);
unsigned LCD_GetIndexMask_233     (void);
unsigned LCD_GetIndexMask_323     (void);
unsigned LCD_GetIndexMask_332     (void);
unsigned LCD_GetIndexMask_444_12  (void);
unsigned LCD_GetIndexMask_444_12_1(void);
unsigned LCD_GetIndexMask_444_16  (void);
unsigned LCD_GetIndexMask_555     (void);
unsigned LCD_GetIndexMask_565     (void);
unsigned LCD_GetIndexMask_556     (void);
unsigned LCD_GetIndexMask_655     (void);
unsigned LCD_GetIndexMask_666     (void);
unsigned LCD_GetIndexMask_8666    (void);
unsigned LCD_GetIndexMask_8666_1  (void);
unsigned LCD_GetIndexMask_888     (void);
unsigned LCD_GetIndexMask_M888    (void);
unsigned LCD_GetIndexMask_M111    (void);
unsigned LCD_GetIndexMask_M222    (void);
unsigned LCD_GetIndexMask_M233    (void);
unsigned LCD_GetIndexMask_M323    (void);
unsigned LCD_GetIndexMask_M332    (void);
unsigned LCD_GetIndexMask_M444_12 (void);
unsigned LCD_GetIndexMask_M444_16 (void);
unsigned LCD_GetIndexMask_M555    (void);
unsigned LCD_GetIndexMask_M565    (void);
unsigned LCD_GetIndexMask_M556    (void);
unsigned LCD_GetIndexMask_M655    (void);
unsigned LCD_GetIndexMask_M666    (void);
unsigned LCD_GetIndexMask_8888	  (void);


void LCD_SelectLCD(void);

/*********************************************************************
*
*              Declarations for LCD_L0_
*
**********************************************************************

  Prefixes are as follows:
  LCD_L0_xxx       ... Driver for first  LCD
  LCD_L0_1_xxx     ... Driver for second LCD/layer
  LCD_L0_2_xxx     ... Driver for third  LCD/layer
  LCD_L0_MAG_xxx   ... Driver for first  LCD, magnification level (calling LCD_L0_xxx after magnification)
  LCD_L0_DELTA_xxx ... Driver for first  LCD, delta mode

*/

U32 LCD_L0_Color2Index       (LCD_COLOR Color);
U32 LCD_L0_1_Color2Index     (LCD_COLOR Color);
U32 LCD_L0_2_Color2Index     (LCD_COLOR Color);
U32 LCD_L0_3_Color2Index     (LCD_COLOR Color);
U32 LCD_L0_4_Color2Index     (LCD_COLOR Color);
void         LCD_L0_DrawHLine         (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_1_DrawHLine       (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_2_DrawHLine       (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_3_DrawHLine       (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_4_DrawHLine       (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_MAG_DrawHLine     (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_DELTA_DrawHLine   (I32 x0, I32 y0,  I32 x1);
void         LCD_L0_DrawVLine         (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_1_DrawVLine       (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_2_DrawVLine       (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_3_DrawVLine       (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_4_DrawVLine       (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_MAG_DrawVLine     (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_DELTA_DrawVLine   (I32 x,  I32 y0,  I32 y1);
void         LCD_L0_FillRect          (I32 x0, I32 y0, I32 x1, I32 y1);
void         LCD_L0_1_FillRect        (I32 x0, I32 y0, I32 x1, I32 y1);
void         LCD_L0_2_FillRect        (I32 x0, I32 y0, I32 x1, I32 y1);
void         LCD_L0_3_FillRect        (I32 x0, I32 y0, I32 x1, I32 y1);
void         LCD_L0_4_FillRect        (I32 x0, I32 y0, I32 x1, I32 y1);
void         LCD_L0_MAG_FillRect      (I32 x0, I32 y0, I32 x1, I32 y1);
void         LCD_L0_DELTA_FillRect      (I32 x0, I32 y0, I32 x1, I32 y1);
U32 LCD_L0_GetPixelIndex     (I32 x,  I32 y);
U32 LCD_L0_1_GetPixelIndex   (I32 x,  I32 y);
U32 LCD_L0_2_GetPixelIndex   (I32 x,  I32 y);
U32 LCD_L0_3_GetPixelIndex   (I32 x,  I32 y);
U32 LCD_L0_4_GetPixelIndex   (I32 x,  I32 y);
U32 LCD_L0_MAG_GetPixelIndex (I32 x,  I32 y);
U32 LCD_L0_DELTA_GetPixelIndex (I32 x,  I32 y);
void         LCD_L0_GetRect           (LCD_RECT * pRect);
void         LCD_L0_1_GetRect         (LCD_RECT * pRect);
void         LCD_L0_2_GetRect         (LCD_RECT * pRect);
void         LCD_L0_3_GetRect         (LCD_RECT * pRect);
void         LCD_L0_4_GetRect         (LCD_RECT * pRect);
void         LCD_L0_SetPixelIndex     (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_1_SetPixelIndex   (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_2_SetPixelIndex   (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_3_SetPixelIndex   (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_4_SetPixelIndex   (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_MAG_SetPixelIndex (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_DELTA_SetPixelIndex (I32 x,  I32 y, I32 ColorIndex, unsigned char Alpha);
void         LCD_L0_XorPixel          (I32 x,  I32 y);
void         LCD_L0_1_XorPixel        (I32 x,  I32 y);
void         LCD_L0_2_XorPixel        (I32 x,  I32 y);
void         LCD_L0_3_XorPixel        (I32 x,  I32 y);
void         LCD_L0_4_XorPixel        (I32 x,  I32 y);
void         LCD_L0_MAG_XorPixel      (I32 x,  I32 y);
void         LCD_L0_DELTA_XorPixel      (I32 x,  I32 y);
I32          LCD_L0_Init              (void);
I32          LCD_L0_1_Init            (void);
I32          LCD_L0_2_Init            (void);
I32          LCD_L0_3_Init            (void);
I32          LCD_L0_4_Init            (void);
I32          LCD_L0_MAG_Init          (void);
I32          LCD_L0_DELTA_Init          (void);
void         LCD_L0_On                (void);
void         LCD_L0_1_On              (void);
void         LCD_L0_2_On              (void);
void         LCD_L0_3_On              (void);
void         LCD_L0_4_On              (void);
void         LCD_L0_Off               (void);
void         LCD_L0_1_Off             (void);
void         LCD_L0_2_Off             (void);
void         LCD_L0_3_Off             (void);
void         LCD_L0_4_Off             (void);
void         LCD_L0_SetLUTEntry       (U8 Pos, LCD_COLOR color);
void         LCD_L0_1_SetLUTEntry     (U8 Pos, LCD_COLOR color);
void         LCD_L0_2_SetLUTEntry     (U8 Pos, LCD_COLOR color);
void         LCD_L0_3_SetLUTEntry     (U8 Pos, LCD_COLOR color);
void         LCD_L0_4_SetLUTEntry     (U8 Pos, LCD_COLOR color);
void *       LCD_L0_GetDevFunc        (I32 Index);
void *       LCD_L0_1_GetDevFunc      (I32 Index);
void *       LCD_L0_2_GetDevFunc      (I32 Index);
void *       LCD_L0_3_GetDevFunc      (I32 Index);
void *       LCD_L0_4_GetDevFunc      (I32 Index);
tLCDDEV_Index2Color * LCD_L0_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_1_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_2_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_3_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_4_GetpfIndex2Color(void);

void LCD_L0_ReInit       (void); /* Reinitialize LCD using config-paramters */
void LCD_L0_1_ReInit     (void);
void LCD_L0_2_ReInit     (void);
void LCD_L0_3_ReInit     (void);
void LCD_L0_4_ReInit     (void);
void LCD_L0_Refresh      (void); /* Refresh entire LCD */
                                 /* Refresh LCD partially. Could be one line, depends on what
                                    the LCD controller can handle efficiently */
void LCD_L0_1_Refresh    (void);
void LCD_L0_2_Refresh    (void);
void LCD_L0_3_Refresh    (void);
void LCD_L0_4_Refresh    (void);
void LCD_L0_SetOrg       (I32 x, I32 y);
void LCD_L0_1_SetOrg     (I32 x, I32 y);
void LCD_L0_2_SetOrg     (I32 x, I32 y);
void LCD_L0_3_SetOrg     (I32 x, I32 y);
void LCD_L0_4_SetOrg     (I32 x, I32 y);


#endif /* LCD_INTERN_H */



/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
