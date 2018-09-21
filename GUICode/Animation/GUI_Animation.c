/*
 * GUI_Animation.c
 *
 *  Created on: 2018年5月26日
 *      Author: Administrator
 */
#include "GUI.h"
#include "GUI_Animation.h"

#define GUI_ANIMATION_H2P(h) (GUI_Animation_Obj*)GUI_ALLOC_h2p(h)

static GUI_HANIMATION hFirstAnimation = WM_HWIN_NULL;
static U32 LastSystemTime = 0;

static U8 _CheckAnimationIsInList(GUI_HANIMATION hAnimation)
{
	GUI_HANIMATION hNext;
	GUI_Animation_Obj *pNext;
	for(hNext = hFirstAnimation; hNext; hNext = pNext->hNext){
		pNext = GUI_ANIMATION_H2P(hNext);
		if(hNext == hAnimation){
			return 1;
		}
	}
	return 0;
}

static void GUI_AnimationReadyHandler(GUI_HANIMATION hAnimation, GUI_Animation_Obj *pAnimation)
{
	I32 Tmp = 0;
	pAnimation->ActTime = 0;
	if(pAnimation->pEnd){
		pAnimation->pEnd(pAnimation->hContext);
	}
	if(0 == _CheckAnimationIsInList(hAnimation)){
		return;
	}
	if(pAnimation->Playback){
		Tmp = pAnimation->Start;
		pAnimation->Start = pAnimation->End;
		pAnimation->End = Tmp;
		pAnimation->ActTime += pAnimation->PlaybackDelay;
	}else if(pAnimation->Repeat){
		pAnimation->ActTime += pAnimation->RepeatDelay;
	}else{
		GUI_AnimationDelete(hAnimation);
	}
}
GUI_HANIMATION GUI_AnimationCreate(WM_HWIN hWin, GUI_Animation_Obj *pAnim)
{
	GUI_HANIMATION hNew;
	GUI_Animation_Obj* pNew;
	hNew = GUI_ALLOC_AllocZero(sizeof(GUI_Animation_Obj));
	pNew = GUI_ANIMATION_H2P(hNew);
	GUI_memcpy(pNew, pAnim, sizeof(GUI_Animation_Obj));
	//pNew->ActTime = 0;
	pNew->hNext = 0;
	pNew->hContext = hWin;
	if(NULL == pNew->pPath){
		pNew->pPath = GUI_AnimationPathLiner;
	}
	if(0 == hFirstAnimation){
		hFirstAnimation = hNew;
	}else{
		GUI_HANIMATION hNext;
		GUI_Animation_Obj *pNext;
		hNext = hFirstAnimation;
		while(hNext){
			pNext = GUI_ANIMATION_H2P(hNext);
			if(0 == pNext->hNext){
				pNext->hNext = hNew;
				break;
			}
			hNext = pNext->hNext;
		}
	}
	return hNew;
}

void GUI_AnimationDelete(GUI_HANIMATION hAnimation)
{
	GUI_HANIMATION hNext;
	GUI_Animation_Obj *pNext, *pLast;
	if(0 == hAnimation){
		return;
	}
	pNext = GUI_ANIMATION_H2P(hFirstAnimation);
	if(hAnimation == hFirstAnimation){
		hFirstAnimation = pNext->hNext;
		GUI_ALLOC_Free(hAnimation);
		return;
	}
	pLast = pNext;
	hNext = pNext->hNext;
	while(hNext){
		pNext = GUI_ANIMATION_H2P(hNext);
		if(hNext == hAnimation){
			pLast->hNext = pNext->hNext;
			GUI_ALLOC_Free(hAnimation);
			break;
		}
		hNext = pNext->hNext;
		pLast = pNext;
	}
}

void GUI_AnimationDeleteByContext(WM_HWIN hContext)
{
	GUI_HANIMATION hAnimation, hNextAnimation;
	GUI_Animation_Obj *pAnimation;
	hAnimation = hFirstAnimation;
	while(hAnimation){
		pAnimation = GUI_ANIMATION_H2P(hAnimation);
		hNextAnimation = pAnimation->hNext;
		if(pAnimation->hContext == hContext){
			GUI_AnimationDelete(hAnimation);
		}
		hAnimation = hNextAnimation;
	}
}
I32 GUI_Animation_Exec(void)
{
	U32 Elapsed = 0;
	I32 IsDo = 0;
	GUI_HANIMATION hAnimation, hNextAnimation;
	GUI_Animation_Obj *pAnimation;
	hAnimation = hFirstAnimation;
	Elapsed = GUI_GetTimeElapsed(LastSystemTime);
	if(Elapsed < 50){
		return IsDo;
	}
	while(hAnimation){
		pAnimation = GUI_ANIMATION_H2P(hAnimation);
		pAnimation->ActTime += Elapsed;
		//以防hAnimation被删除
		hNextAnimation = pAnimation->hNext;
		if(pAnimation->ActTime > 0){
			I32 Value = 0;
			if(pAnimation->ActTime > pAnimation->Time) {
				pAnimation->ActTime = pAnimation->Time;
			}
			Value = pAnimation->pPath(pAnimation);
			if(pAnimation->pFunc){
				pAnimation->pFunc(pAnimation->hContext, Value);
			}
			if(pAnimation->ActTime == pAnimation->Time){
				GUI_AnimationReadyHandler(hAnimation, pAnimation);
			}
			IsDo = 1;
		}
		hAnimation = hNextAnimation;
	}
	LastSystemTime = GUI_GetTime();
	return IsDo;
}

I32 GUI_AnimationPathLiner(const GUI_Animation_Obj *pAnimation)
{
	U16 Step = 0;
	I32 NewValue = 0;
	if(pAnimation->Time == pAnimation->ActTime){
		 Step = 1024; /*Use the last value id the time fully elapsed*/
	}
	else {
		Step = (pAnimation->ActTime * 1024) / pAnimation->Time;
	}
	NewValue =  (I32) Step * (pAnimation->End - pAnimation->Start);
	NewValue = NewValue >> 10;
	NewValue += pAnimation->Start;
	return NewValue;
}

void GUI_AnimationObjInit(GUI_Animation_Obj *pAnim)
{
	GUI_memset(pAnim, 0, sizeof(GUI_Animation_Obj));
	pAnim->pEnd = NULL;
	pAnim->pFunc = NULL;
	pAnim->pPath = NULL;
}

void GUI_StartPageAnimationMoveIn(WM_HWIN hWin, I32 StartPosX, I32 EndPosX, I32 Duration)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = StartPosX;
	Anim.End = EndPosX;
	Anim.Time = Duration;
	Anim.pFunc = WM_SetWindowPosX;
	GUI_AnimationCreate(hWin, &Anim);
}
static void _AnimEndDeleteWindow(WM_HWIN hWin)
{
	WM_DeleteWindow(hWin);
	GUI_Debug("free bytes %d\n", GUI_ALLOC_GetNumFreeBytes());
}
void GUI_StartPageAnimationMoveOut(WM_HWIN hWin, I32 StartPosX, I32 EndPosX, I32 Duration)
{
	GUI_Animation_Obj Anim;
	GUI_AnimationObjInit(&Anim);
	Anim.Start = StartPosX;
	Anim.End = EndPosX;
	Anim.Time = Duration;
	Anim.pFunc = WM_SetWindowPosX;
	Anim.pEnd = _AnimEndDeleteWindow;
	GUI_AnimationCreate(hWin, &Anim);
}
