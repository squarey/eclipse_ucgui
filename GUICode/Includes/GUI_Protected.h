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
File        : GUI_Protected.h
Purpose     : GUI internal declarations
---------------------------END-OF-HEADER------------------------------
*/

#ifndef  GUI_PROTECTED_H
#define  GUI_PROTECTED_H

#include "GUI.h"
#include "LCD_Protected.h"
#include "GUIDebug.h"
#if GUI_WINSUPPORT
  #include "WM_GUI.h"
#endif

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/**********************************************************************
*
*                        Defaults for config switches
*
***********************************************************************

  The config switches below do not affect the interface in GUI.h and
  are therefor not required to be in GUI.h.
*/

/* Short address area.
   For  most compilers, this is "near" or "__near"
   We do not use this except for some CPUs which we know to always have some
   near memory, because the GUI_Context ans some other data will be declared
   to be in this short address (near) memory area as it has a major effect
   on performance.
   Please define in GUIConf.h (if you want to use it)
*/
#ifndef GUI_SADDR
  #define GUI_SADDR
#endif

#ifndef GUI_DEFAULT_FONT
  #define GUI_DEFAULT_FONT    &GUI_Font6x8
#endif

#ifndef GUI_DEFAULT_CURSOR
  #define GUI_DEFAULT_CURSOR  &GUI_CursorArrowM
#endif

#ifndef GUI_DEFAULT_BKCOLOR
  #define GUI_DEFAULT_BKCOLOR GUI_BLACK
#endif

#ifndef GUI_DEFAULT_COLOR
  #define GUI_DEFAULT_COLOR   GUI_WHITE
#endif

#ifndef GUI_X_SIGNAL_EVENT
  #define GUI_X_SIGNAL_EVENT()
#endif

#ifndef GUI_X_WAIT_EVENT
  #define GUI_X_WAIT_EVENT() GUI_X_ExecIdle()
#endif


/*      *********************************
        *                               *
        *      Angles                   *
        *                               *
        *********************************
*/

#define GUI_45DEG  512
#define GUI_90DEG  (2*GUI_45DEG)
#define GUI_180DEG (4*GUI_45DEG)
#define GUI_360DEG (8*GUI_45DEG)





/*****************************************************
*
*        Locking checks
*
******************************************************
*/

#if defined (WIN32) && defined (_DEBUG) && GUI_OS
  #define GUI_ASSERT_LOCK()   GUITASK_AssertLock()
  #define GUI_ASSERT_NO_LOCK() GUITASK_AssertNoLock()
  void GUITASK_AssertLock(void);
  void GUITASK_AssertNoLock(void);
#else
  #define GUI_ASSERT_LOCK()
  #define GUI_ASSERT_NO_LOCK()
#endif


/*******************************************************************
*
*                   LCD_HL_ level defines
*
********************************************************************
*/

#if GUI_SUPPORT_AA
  #define LCD_HL_DrawHLine             GUI_Context.pLCD_HL->pfDrawHLine
  #define LCD_HL_DrawPixel             GUI_Context.pLCD_HL->pfDrawPixel
#else
  #define LCD_HL_DrawHLine             LCD_DrawHLine
  #define LCD_HL_DrawPixel             LCD_DrawPixel
#endif


/*********************************************************************
*
*                     Helper functions
*
***********************************************************************
*/

#define GUI_ZEROINIT(Obj) GUI_MEMSET(Obj, 0, sizeof(Obj))
I32  GUI_cos(I32 angle);
I32  GUI_sin(I32 angle);
extern const U32 GUI_Pow10[10];

/* GUIAALib.c --- direct anti-aliased drawing */
I32  GUI_AA_Init(I32 x0, I32 x1);
I32  GUI_AA_Init_HiRes(I32 x0, I32 x1);
void GUI_AA_Exit(void);
I16 GUI_AA_HiRes2Pixel(I32 HiRes);

void GL_FillCircleAA_HiRes(I32 x0, I32 y0, I32 r);

void GUI_AA__DrawCharAA2NoTrans(I32 x0, I32 y0, I32 XSize, I32 YSize, I32 BytesPerLine, const U8*pData);
void GUI_AA__DrawCharAA2Trans  (I32 x0, I32 y0, I32 XSize, I32 YSize, I32 BytesPerLine, const U8*pData);
void GUI_AA__DrawCharAA4       (I32 x0, I32 y0, I32 XSize, I32 YSize, I32 BytesPerLine, const U8*pData);

/* System independent font routines */
I32        GUI_SIF__GetCharDistX(U16P c);
void       GUI_SIF__GetFontInfo (const GUI_FONT GUI_UNI_PTR * pFont, GUI_FONTINFO * pfi);
char       GUI_SIF__IsInFont    (const GUI_FONT GUI_UNI_PTR * pFont, U16 c);
const U8 * GUI_SIF__GetpCharInfo(const GUI_FONT GUI_UNI_PTR * pFont, U16P c);

/* Conversion routines */
void GUI_AddHex     (U32 v, U8 Len, char**ps);
void GUI_AddBin     (U32 v, U8 Len, char**ps);
void GUI_AddDecMin  (I32 v, char**ps);
void GUI_AddDec     (I32 v, U8 Len, char**ps);
void GUI_AddDecShift(I32 v, U8 Len, U8 Shift, char**ps);
long GUI_AddSign    (long v, char**ps);
I32  GUI_Long2Len   (I32 v);

#if GUI_SUPPORT_UNICODE
  #define GUI_UC__GetCharSize(sText)  GUI_Context.pUC_API->pfGetCharSize(sText)
  #define GUI_UC__GetCharCode(sText)  GUI_Context.pUC_API->pfGetCharCode(sText)
#else
  #define GUI_UC__GetCharSize(sText)  GUI_UC_GetCharSize(sText)
  #define GUI_UC__GetCharCode(sText)  GUI_UC_GetCharCode(sText)
#endif

I32   GUI_UC__CalcSizeOfChar   (U16 Char);
U16   GUI_UC__GetCharCodeInc   (const char GUI_UNI_PTR ** ps);
I32   GUI_UC__NumChars2NumBytes(const char GUI_UNI_PTR * s, I32 NumChars);
I32   GUI_UC__NumBytes2NumChars(const char GUI_UNI_PTR * s, I32 NumBytes);

I32  GUI__GetLineNumChars  (const char GUI_UNI_PTR *s, I32 MaxNumChars);
I32  GUI__GetNumChars      (const char GUI_UNI_PTR *s);
I32  GUI__GetLineDistX     (const char GUI_UNI_PTR *s, I32 Len);
I32  GUI__GetFontSizeY     (void);
I32  GUI__HandleEOLine     (const char GUI_UNI_PTR **ps);
void GUI__DispLine         (const char GUI_UNI_PTR *s, I32 Len, const GUI_RECT* pr);
void GUI__AddSpaceHex      (U32 v, U8 Len, char**ps);
void GUI__CalcTextRect     (const char GUI_UNI_PTR* pText, const GUI_RECT* pTextRectIn, GUI_RECT* pTextRectOut, I32 TextAlign);

I32  GUI__WrapGetNumCharsDisp       (const char GUI_UNI_PTR * pText, I32 xSize, GUI_WRAPMODE WrapMode);
I32  GUI__WrapGetNumCharsToNextLine (const char GUI_UNI_PTR * pText, I32 xSize, GUI_WRAPMODE WrapMode);
I32  GUI__WrapGetNumBytesToNextLine (const char GUI_UNI_PTR * pText, I32 xSize, GUI_WRAPMODE WrapMode);
void GUI__memset    (U8 * p, U8 Fill, I32 NumBytes);
void GUI__memset16  (U16* p, U16 Fill, I32 NumWords);
/* @shiquanyong add GUI__memset32 20171230 */
void GUI__memset32  (U32 *p, U32 Fill, I32 NumWords);
I32  GUI__strlen    (const char GUI_UNI_PTR * s);
I32  GUI__strcmp    (const char GUI_UNI_PTR * s0, const char GUI_UNI_PTR * s1);
I32  GUI__strcmp_hp (GUI_HMEM hs0, const char GUI_UNI_PTR * s1);

/* Get cursor position */
I32  GUI__GetCursorPosX     (const char GUI_UNI_PTR * s, I32 Index, I32 MaxNumChars);
I32  GUI__GetCursorPosChar  (const char GUI_UNI_PTR * s, I32 x, I32 NumCharsToNextLine);
U16  GUI__GetCursorCharacter(const char GUI_UNI_PTR * s, I32 Index, I32 MaxNumChars, I32 * pIsRTL);

/* Arabic support */
U16  GUI__GetPresentationForm     (U16 Char, U16 Next, U16 Prev, I32 * pIgnoreNext);
void GUI__DispLineArabic          (const char GUI_UNI_PTR * s, I32 MaxNumChars, const GUI_RECT * pRect);
I32  GUI__GetLineDistXArabic      (const char GUI_UNI_PTR * s, I32 MaxNumChars);
I32  GUI__IsArabicCharacter       (U16 c);
I32  GUI__GetCursorPosXArabic     (const char GUI_UNI_PTR * s, I32 Index, I32 MaxNumChars);
I32  GUI__GetCursorPosCharArabic  (const char GUI_UNI_PTR * s, I32 x, I32 MaxNumChars);
U16  GUI__GetCursorCharacterArabic(const char GUI_UNI_PTR * s, I32 Index, I32 MaxNumChars, I32 * pIsRTL);

/* Reading data routines */
U16 GUI__Read16(const U8 ** ppData);
U32 GUI__Read32(const U8 ** ppData);

/* Virtual screen support */
void GUI__GetOrg(I32 * px, I32 * py);

/*********************************************************************
*
*             2d - GL
*
**********************************************************************
*/

void GL_DispChar         (U16 c);
void GL_DrawArc          (I32 x0, I32 y0, I32 rx, I32 ry, I32 a0, I32 a1);
void GL_DrawBitmap       (const GUI_BITMAP GUI_UNI_PTR * pBM, I32 x0, I32 y0);
void GL_DrawCircle       (I32 x0, I32 y0, I32 r);
void GL_DrawEllipse      (I32 x0, I32 y0, I32 rx, I32 ry);
void GL_DrawHLine        (I32 y0, I32 x0, I32 x1);
void GL_DrawPolygon      (const GUI_POINT* pPoints, I32 NumPoints, I32 x0, I32 y0);
void GL_DrawPoint        (I32 x, I32 y);
void GL_DrawLine1        (I32 x0, I32 y0, I32 x1, I32 y1);
void GL_DrawLine1Ex      (I32 x0, I32 y0, I32 x1, I32 y1, unsigned * pPixelCnt);
void GL_DrawLineRel      (I32 dx, I32 dy);
void GL_DrawLineTo       (I32 x, I32 y);
void GL_DrawLineToEx     (I32 x, I32 y, unsigned * pPixelCnt);
void GL_DrawLine         (I32 x0, I32 y0, I32 x1, I32 y1);
void GL_DrawLineEx       (I32 x0, I32 y0, I32 x1, I32 y1, unsigned * pPixelCnt);
void GL_MoveTo           (I32 x, I32 y);
void GL_FillCircle       (I32 x0, I32 y0, I32 r);
void GL_FillCircleAA     (I32 x0, I32 y0, I32 r);
void GL_FillEllipse      (I32 x0, I32 y0, I32 rx, I32 ry);
void GL_FillPolygon      (const GUI_POINT* pPoints, I32 NumPoints, I32 x0, I32 y0);
void GL_SetDefault       (void);

/************************************************************
*
*                 Callback pointers for dynamic linkage
*
*************************************************************
Dynamic linkage pointers reduces configuration hassles.
*/
typedef I32  GUI_tfTimer(void);
typedef char GUI_CURSOR_tfTempHide  (const GUI_RECT* pRect);
typedef void GUI_CURSOR_tfTempUnhide(void);
typedef I32  WM_tfHandlePID(void);


/************************************************************
*
*        Cursors 
*
*************************************************************
*/

extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_ArrowS[45];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_ArrowM[60];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_ArrowL[150];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_CrossS[33];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_CrossM[126];
extern GUI_CONST_STORAGE unsigned char  GUI_Pixels_CrossL[248];
extern GUI_CONST_STORAGE unsigned char  GUI_PixelsHeaderM[5 * 17];


extern GUI_CONST_STORAGE GUI_LOGPALETTE GUI_CursorPal;
extern GUI_CONST_STORAGE GUI_LOGPALETTE GUI_CursorPalI;

/************************************************************
*
*        Text rotation
*
*************************************************************
*/

extern GUI_RECT  GUI_RectDispString; /* Used by LCD_Rotate...() and GUI_DispStringInRect() */

/*********************************************************************
*
*       Multitasking support
*
**********************************************************************
*/
extern I32 GUITASK__EntranceCnt;

/*********************************************************************
*
*             Bitmap related functions
*
**********************************************************************
*/

I32       GUI_GetBitmapPixelIndex(const GUI_BITMAP GUI_UNI_PTR * pBMP, unsigned x, unsigned y);
GUI_COLOR GUI_GetBitmapPixelColor(const GUI_BITMAP GUI_UNI_PTR * pBMP, unsigned x, unsigned y);

void      GUI__DrawBitmap16bpp(I32 x0, I32 y0, I32 xsize, I32 ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, I32 xMag, I32 yMag, tLCDDEV_Index2Color * pfIndex2Color);

extern const GUI_UC_ENC_APILIST GUI_UC_None;

/************************************************************
*
*         EXTERNs for GL_CORE
*
*************************************************************
*/

#ifdef  GL_CORE_C
  #define GUI_EXTERN
#else
  #define GUI_EXTERN extern
#endif

GUI_EXTERN GUI_SADDR GUI_CONTEXT        GUI_Context;        /* Thread wide globals */
GUI_EXTERN GUI_SADDR char               GUI_DecChar;
GUI_EXTERN           GUI_tfTimer*       GUI_pfTimerExec;
GUI_EXTERN           WM_tfHandlePID*    WM_pfHandlePID;
GUI_EXTERN      void (*GUI_pfDispCharStyle)(U16 Char);

#if GUI_COMPILER_SUPPORTS_FP && GUI_SUPPORT_ROTATION
  GUI_EXTERN const     tLCD_APIList *     GUI_pLCD_APIList;   /* Used for rotating text */
#endif

GUI_EXTERN I16 GUI_OrgX, GUI_OrgY;
GUI_EXTERN U8  GUI_MoveRTL;

#undef GUI_EXTERN


#if defined(__cplusplus)
}
#endif 

#endif   /* Avoid multiple inclusion */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
