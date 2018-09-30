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
File        : ProgBar.c
Purpose     : Implementation of progress bar
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "PROGBAR_Private.h"

#if GUI_WINSUPPORT && PROGBAR_SUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef PROGBAR_DEFAULT_FONT
#define PROGBAR_DEFAULT_FONT GUI_DEFAULT_FONT
  #if   WIDGET_USE_SCHEME_SMALL
    #define PROGBAR_DEFAULT_FONT &GUI_Font6x8
  #elif WIDGET_USE_SCHEME_MEDIUM
    #define PROGBAR_DEFAULT_FONT &GUI_Font8x12_ASCII
  #elif WIDGET_USE_SCHEME_LARGE
    #define PROGBAR_DEFAULT_FONT &GUI_Font8x16
  #endif
#endif

#ifndef PROGBAR_DEFAULT_BARCOLOR0
  #define PROGBAR_DEFAULT_BARCOLOR0 0xff555555
#endif

#ifndef PROGBAR_DEFAULT_BARCOLOR1
  #define PROGBAR_DEFAULT_BARCOLOR1 0xffAAAAAA
#endif

#ifndef PROGBAR_DEFAULT_TEXTCOLOR0
  #define PROGBAR_DEFAULT_TEXTCOLOR0 0xffFFFFFF
#endif

#ifndef PROGBAR_DEFAULT_TEXTCOLOR1
  #define PROGBAR_DEFAULT_TEXTCOLOR1 0xff000000
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
PROGBAR_PROPS PROGBAR_DefaultProps =
{
	PROGBAR_DEFAULT_FONT,
	PROGBAR_DEFAULT_BARCOLOR0,
	PROGBAR_DEFAULT_BARCOLOR1,
	PROGBAR_DEFAULT_TEXTCOLOR0,
	PROGBAR_DEFAULT_TEXTCOLOR1
};

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

/*********************************************************************
*
*       _Paint
*/
static void _cbStyleCirleAnim(WM_HWIN hWin, I32 Value)
{
	PROGBAR_Obj * pObj;
	pObj = (PROGBAR_Obj *)GUI_ALLOC_h2p(hWin);
	I32 Diff = 0;
	Diff = Value - pObj->StyleCirle.Angle1;
	pObj->StyleCirle.Angle1 = Value;
	pObj->StyleCirle.Angle2 += Diff;
	WM_InvalidateWindow(hWin);
}
static I32 _StyleCirleAnimPath(const GUI_Animation_Obj *pAnim)
{
	I32 Diff, Value;
	Diff = pAnim->End - pAnim->Start;
	Value = (Diff * pAnim->ActTime * pAnim->ActTime)/(pAnim->Time * pAnim->Time);
	return Value + pAnim->Start;
}
static void _StyleCirleAnimInit(WM_HWIN hWin)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Time = 1000;
	Anim.Start = 90;
	Anim.End = 420;
	Anim.Repeat = 1;
	//Anim.RepeatDelay = -500;
	Anim.pFunc = _cbStyleCirleAnim;
	Anim.pPath = _StyleCirleAnimPath;
	//Anim.pEnd = _cbAnimEnd;
	GUI_AnimationCreate(hWin, &Anim);
}

static void _Paint(PROGBAR_Handle hObj, PROGBAR_Obj * pObj)
{
	if(pObj->Style == PROGBAR_STYLE_CIRCLE){
		I16 Width = 0, Height = 0;
		I16 R = 0;
		U8 PrevPenSize = 0;
		Width = WM_GetWindowSizeX(hObj);
		Height = WM_GetWindowSizeY(hObj);
		if(Width >= Height){
			R = Width/2;
		}else{
			R = Height/2;
		}
		R -= 3;
		GUI_SetColor(pObj->Props.aBarColor[1]);
		PrevPenSize = GUI_SetPenSize(3);
		GUI_AA_DrawArc(R + 1, R + 1, R, R, pObj->StyleCirle.Angle1, pObj->StyleCirle.Angle2);
		GUI_SetPenSize(PrevPenSize);
	}else{

	}
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(PROGBAR_Handle hObj)
{
	PROGBAR_FreeText(hObj);
}

/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
PROGBAR_Obj * PROGBAR_h2p(PROGBAR_Handle h)
{
	PROGBAR_Obj * p = (PROGBAR_Obj *)GUI_ALLOC_h2p(h);
	if (p) {
		if (p->DebugId != PROGBAR_ID) {
			GUI_DEBUG_ERROROUT("PROGBAR.c: Wrong handle type or Object not init'ed");
			return 0;
		}
	}
	return p;
}
#endif

/*********************************************************************
*
*       PROGBAR_FreeText
*/
void PROGBAR_FreeText(PROGBAR_Handle hObj)
{
	PROGBAR_Obj* pObj = PROGBAR_H2P(hObj);
	if(pObj->hpText){
		GUI_ALLOC_FreePtr(&pObj->hpText);
	}

}

/*********************************************************************
*
*       PROGBAR_GetText
*/
const char * PROGBAR_GetText(const PROGBAR_Obj* pObj, char* pBuffer)
{
	char* pText;
	if (pObj->hpText) {
		pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
	} else {
		pText = pBuffer;
		GUI_AddDecMin((100 * (I32)(pObj->v - pObj->Min)) / (pObj->Max - pObj->Min), &pBuffer);
		*pBuffer++ = '%';
		*pBuffer   = 0;
	}
	return (const char*)pText;
}



/*********************************************************************
*
*       Exported routines:  Callback
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_Callback
*/
void PROGBAR_Callback(WM_MESSAGE * pMsg)
{
	PROGBAR_Handle hObj;
	PROGBAR_Obj * pObj;
	hObj = pMsg->hWin;
	pObj = (PROGBAR_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
	/* Let widget handle the standard messages */
	if (WIDGET_HandleActive(hObj, pMsg) == 0) {
		return;
	}
	switch (pMsg->MsgId) {
		case WM_PAINT:
			_Paint(hObj, pObj);
			return;
		case WM_DELETE:
			_Delete(hObj);
			break;
	}
	WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_CreateEx
*/
PROGBAR_Handle PROGBAR_CreateEx(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent,
                                I32 WinFlags, I32 ExFlags, I32 Id)
{
	PROGBAR_Handle hObj;
	hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, PROGBAR_Callback,
								sizeof(PROGBAR_Obj) - sizeof(WM_Obj));
	if (hObj) {
		PROGBAR_Obj* pObj;
		pObj = (PROGBAR_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
		/* init widget specific variables */
		WIDGET__Init(&pObj->Widget, Id, 0);
		WIDGET_SetEffect(hObj, &WIDGET_Effect_None); /* Standard effect for progbar: None */
		PROGBAR_INIT_ID(pObj);
		/* init member variables */
		pObj->Props        = PROGBAR_DefaultProps;
		pObj->TextAlign    = GUI_TA_CENTER;
		pObj->Max          = 100;
		pObj->Min          = 0;
		pObj->Flags        = ExFlags;
		pObj->Style		   = PROGBAR_STYLE_RECT;
		pObj->StyleCirle.Angle1 = 90;
		pObj->StyleCirle.Angle2 = 420;
	}
	return hObj;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_SetValue
*/ 
void PROGBAR_SetValue(PROGBAR_Handle hObj, I32 v)
{
	if (hObj) {
		//PROGBAR_Obj* pObj;
	}
}

void PROGBAR_SetStyle(PROGBAR_Handle hObj, U8 Style)
{
	if(hObj){
		PROGBAR_Obj* pObj;
		pObj = (PROGBAR_Obj *)GUI_ALLOC_h2p(hObj);
		if(pObj->Style == Style){
			return;
		}
		if(Style == PROGBAR_STYLE_RECT){
			if(PROGBAR_STYLE_CIRCLE == pObj->Style){
				GUI_AnimationDeleteByContext(hObj);
				pObj->Style = PROGBAR_STYLE_RECT;
				WM_InvalidateWindow(hObj);
			}
		}else if(Style == PROGBAR_STYLE_CIRCLE){
			_StyleCirleAnimInit(hObj);
			pObj->Style = PROGBAR_STYLE_CIRCLE;
		}
	}
}
#else

void WIDGET_Progbar(void) {} /* avoid empty object files */

#endif /* GUI_WINSUPPORT */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
