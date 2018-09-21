/*
 * GUI_Animation.h
 *
 *  Created on: 2018年5月26日
 *      Author: Administrator
 */

#ifndef GUI_ANIMATION_H_
#define GUI_ANIMATION_H_

#include "GUI_Types.h"
#include "WM.h"

#define GUI_HANIMATION    WM_HWIN
struct _GUI_Animation_Obj;

typedef I32(*GUI_AnimPath)(const struct _GUI_Animation_Obj *);

typedef void (*GUI_AnimFunction)(GUI_HANIMATION, I32);
typedef void (*GUI_AnimFunctionEnd)(GUI_HANIMATION);

typedef struct _GUI_Animation_Obj
{
	WM_HWIN hContext;			/*Context to animate*/
	GUI_AnimFunction pFunc;	/*Animator function*/
	GUI_AnimFunctionEnd pEnd;	/*Call it when the animation is end*/
	GUI_AnimPath pPath;		/*An array with the steps of animations*/
	I32 Start;					/*Start value*/
	I32 End;					/*End value*/
	I32 Time;					/*Animation time in ms*/
	I32 ActTime;				/*Current time in animation. Set to negative to make delay.*/
	I16 PlaybackDelay;			/*Wait before play back*/
	I16 RepeatDelay;
	GUI_HANIMATION hNext;
	U8 Playback :1;				/*When the animation is ready play it back*/
	U8 Repeat :1;				/*Repeat the animation infinitely*/
	/*Animation system use these - user shouldn't set*/
}GUI_Animation_Obj;


GUI_HANIMATION GUI_AnimationCreate(WM_HWIN hWin, GUI_Animation_Obj *pAnim);
I32 GUI_Animation_Exec(void);
void GUI_AnimationDelete(GUI_HANIMATION hAnimation);
void GUI_AnimationDeleteByContext(WM_HWIN hContext);
I32 GUI_AnimationPathLiner(const GUI_Animation_Obj *pAnimation);
void GUI_AnimationObjInit(GUI_Animation_Obj *pAnim);
void GUI_StartPageAnimationMoveIn(WM_HWIN hWin, I32 StartPosX, I32 EndPosX, I32 Duration);
void GUI_StartPageAnimationMoveOut(WM_HWIN hWin, I32 StartPosX, I32 EndPosX, I32 Duration);

#endif /* GUI_ANIMATION_H_ */
