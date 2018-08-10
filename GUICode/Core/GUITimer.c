/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUITimer.c
Purpose     : Supplies timers
----------------------------------------------------------------------
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define GUI_TIMER_H2P(h) (GUI_TIMER_Obj*)GUI_ALLOC_h2p(h)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct
{
	GUI_TIMER_CALLBACK* cb;
	GUI_TIMER_HANDLE hNext;
	U8 Act;
	GUI_TIMER_TIME Context;
	GUI_TIMER_TIME ActTime;
	GUI_TIMER_TIME Period;
} GUI_TIMER_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

GUI_TIMER_HANDLE hFirstTimer = 0;
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Unlink
*/
static U8 _Unlink(GUI_TIMER_HANDLE hTimer)
{
	U8 IsDo = 0;
	GUI_TIMER_HANDLE hNext;
	GUI_TIMER_Obj* pNext, *pTimer;
	if(0 == hTimer){
		return 0;
	}
	pTimer = GUI_TIMER_H2P(hTimer);
	if(hTimer == hFirstTimer){
		pNext = GUI_TIMER_H2P(hFirstTimer);
		hFirstTimer = pNext->hNext;
		IsDo = 1;
	}else{
		hNext = hFirstTimer;
		while(hNext){
			pNext = GUI_TIMER_H2P(hNext);
			if(pNext->hNext == hTimer){
				pNext->hNext = pTimer->hNext;
				IsDo = 1;
				break;
			}else{
				hNext = pNext->hNext;
			}
		}
	}
	return IsDo;
}

/*********************************************************************
*
*       _Link
*
* Purpose:
*   This routine inserts the new timer (referenced by its handle) into
*	  the linked list. The linked list is sorted according to timestamps.
*	  The first element is the timer which expires first.
*/
static void _Link(GUI_TIMER_HANDLE hNew)
{
	if(0 == hFirstTimer){
		hFirstTimer = hNew;
	}else{
		GUI_TIMER_HANDLE hNext;
		GUI_TIMER_Obj* pNext;
		hNext = hFirstTimer;
		while(hNext){
			pNext = GUI_TIMER_H2P(hNext);
			if(0 == pNext->hNext){
				pNext->hNext = hNew;
				break;
			}else{
				hNext = pNext->hNext;
			}
		}
	}
}
static U8 _TimerIsInLink(GUI_TIMER_HANDLE hTimer)
{
	GUI_TIMER_HANDLE hNext;
	GUI_TIMER_Obj* pNext;
	hNext = hFirstTimer;
	while(hNext){
		pNext = GUI_TIMER_H2P(hNext);
		if(hNext == hTimer){
			return 1;
		}else{
			hNext = pNext->hNext;
		}
	}
	return 0;
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TIMER_Exec
*/
I32 GUI_TIMER_Exec(void)
{
	I32 r = 0;
	U32 CurrentSystemTime = 0;
	GUI_TIMER_HANDLE hTimer;
	GUI_TIMER_Obj* pTimer;
	CurrentSystemTime = GUI_GetTime();
	hTimer = hFirstTimer;
	while (hTimer){
		pTimer = GUI_TIMER_H2P(hTimer);
		/* 放在前面以防在定时器的回调函数中将此定时器删除  */
		hTimer = pTimer->hNext;
		if ((pTimer->Act) && ((pTimer->ActTime + pTimer->Period) <= CurrentSystemTime)){
			GUI_TIMER_MESSAGE tm;
			pTimer->Act = 0;
			tm.Time = pTimer->ActTime;
			tm.Context = pTimer->Context;
			pTimer->cb(&tm);
			r = 1;
		}
		if(0 == _TimerIsInLink(hTimer)){
			return r;
		}
	}
	/*
	GUI_TIMER_Obj* pObj = GUI_TIMER_H2P(hObj);
	pObj->t0 = Time;
	*/
	return r;
}

/*********************************************************************
*
*       GUI_TIMER_Create
*/
GUI_TIMER_HANDLE GUI_TIMER_Create(GUI_TIMER_CALLBACK* cb, I32 Time, U32 Context, I32 Flags)
{
	GUI_TIMER_HANDLE hObj;
	GUI_TIMER_Obj* pObj;
	GUI_USE_PARA(Flags);
	GUI_USE_PARA(Time);
	GUI_pfTimerExec = GUI_TIMER_Exec;
	/* Alloc memory for obj */
	hObj = GUI_ALLOC_AllocZero(sizeof(GUI_TIMER_Obj));
	pObj = GUI_TIMER_H2P(hObj);
	/* init member variables */
	pObj->cb = cb;
	pObj->Context = Context;
	pObj->hNext = 0;
	pObj->Act = 0;
	/* Link it */
	_Link(hObj);
	return hObj;
}

/*********************************************************************
*
*       GUI_TIMER_Delete
*/
void GUI_TIMER_Delete(GUI_TIMER_HANDLE hObj)
{
	/* Unlink Timer */
	if(hObj){
		if(_Unlink(hObj)){
			GUI_Debug("Delete timer %d\n", hObj);
			GUI_ALLOC_Free(hObj);
		}
	}
}
void GUI_TIMER_DeleteByContext(U32 Context)
{
	GUI_TIMER_HANDLE hNextTimer, hTemp;
	GUI_TIMER_Obj* pNextTimer;
	hNextTimer = hFirstTimer;
	while(hNextTimer){
		pNextTimer = GUI_TIMER_H2P(hNextTimer);
		if(pNextTimer->Context == Context){
			hTemp = pNextTimer->hNext;
			GUI_TIMER_Delete(hNextTimer);
			hNextTimer = hTemp;
		}else{
			hNextTimer = pNextTimer->hNext;
		}
	}
}

/*********************************************************************
*
*       GUI_TIMER_SetPeriod
*/
void GUI_TIMER_SetPeriod(GUI_TIMER_HANDLE hObj, GUI_TIMER_TIME Period)
{
	if(hObj){
		GUI_TIMER_Obj* pObj;
		pObj = GUI_TIMER_H2P(hObj);
		pObj->Period = Period;
	}
}

/*********************************************************************
*
*       GUI_TIMER_SetTime
*/
void GUI_TIMER_SetTime(GUI_TIMER_HANDLE hObj, GUI_TIMER_TIME Time)
{
	if(hObj){
		GUI_TIMER_Obj* pObj;
		pObj = GUI_TIMER_H2P(hObj);
		pObj->ActTime = Time;
	}
}

/*********************************************************************
*
*       GUI_TIMER_SetDelay
*/
void GUI_TIMER_SetDelay(GUI_TIMER_HANDLE hObj, GUI_TIMER_TIME Delay)
{
	if(hObj){
		GUI_TIMER_Obj* pObj;
		pObj = GUI_TIMER_H2P(hObj);
		pObj->ActTime = Delay + GUI_GetTime();
		pObj->Act = 1;
	}
}

/*********************************************************************
*
*       GUI_TIMER_Restart
*/
void GUI_TIMER_Restart(GUI_TIMER_HANDLE hObj)
{
	if(hObj){
		GUI_TIMER_Obj* pObj;
		pObj = GUI_TIMER_H2P(hObj);
		pObj->ActTime = GUI_GetTime();
		pObj->Act = 1;
	}else{
		GUI_Debug("hObj is null\n");
	}
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
