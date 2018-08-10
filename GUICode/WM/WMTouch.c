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
File        : WMTouch.c
Purpose     : Windows manager, touch support
----------------------------------------------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"
#include "GUIDebug.h"

#if (GUI_WINSUPPORT)

#define SCREEN_TIMEOUT_NONE			0x00
#define SCREEN_TIMEOUT_IS_USED		0x01
#define SCREEN_TIMEOUT_IS_HAPPEN	0x02

typedef void (*pScreenTimeoutCallback)(void);
/*********************************************************************
*
*          Public data
*
**********************************************************************
*/

WM_CRITICAL_HANDLE  WM__CHWinModal;
WM_CRITICAL_HANDLE  WM__CHWinLast;
/*********************************************************************
*
*          Static data
*
**********************************************************************
*/
static U8 _WaitTouchRelease = 0;
static U8 _ScreenTimeOutStatus = 0;
static U32 _TouchReleaseTimeRecorde = 0;
static U32 _ScreenTimeOutTime = 0;
static pScreenTimeoutCallback _ScreenTimeout_cb = NULL;
/*********************************************************************
*
*          Modul internal routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__IsInModalArea
*/
I32 WM__IsInModalArea(WM_HWIN hWin)
{
	if ((WM__CHWinModal.hWin == 0) || WM__IsAncestor(hWin, WM__CHWinModal.hWin) || (hWin == WM__CHWinModal.hWin)) {
		return 1;
	}
	return 0;
}
/*
 *
 * */
void WM__SetWaitTouchRelease(void)
{
	_WaitTouchRelease = 1;
}
/*********************************************************************
*
*       WM__SendPIDMessage
*
* Purpose:
*   Sends a PID -type message to the affected window.
*   All ancestors are notified of this by sending a WM_TOUCH_CHILD
*   message.
*
*/
void WM__SendPIDMessage(WM_HWIN hWin, WM_MESSAGE* pMsg)
{
#if 1
	WM_HWIN iWin;
	WM_MESSAGE Msg;
	Msg = *pMsg;                 /* Save message as it may be modified in callback (as return value) */
	/* Send notification to all ancestors.
	We need to check if the window which has received the last message still exists,
	since it may have deleted itself and its parent as result of the message.
	*/
	Msg.hWinSrc = hWin;
	Msg.MsgId   = WM_TOUCH_CHILD;
	iWin = hWin;
	while (WM_IsWindow(iWin)) {
		if(_WaitTouchRelease){
			return;
		}
		iWin = WM_GetParent(iWin);
		if (iWin) {
			Msg.Data.p  = pMsg;            /* Needs to be set for each window, as callback is allowed to modify it */
			WM__SendMessageIfEnabled(iWin, &Msg);    /* Send message to the ancestors */
		}
	}
	/* Send message to the affected window */
	if(0 == _WaitTouchRelease){
		WM__SendMessageIfEnabled(hWin, pMsg);
	}
#else
	WM_MESSAGE Msg;
	/* Send message to the affected window */
	Msg = *pMsg;                 /* Save message as it may be modified in callback (as return value) */
	WM__SendMessageIfEnabled(hWin, &Msg);
	/* Send notification to all ancestors.
	We need to check if the window which has received the last message still exists,
	since it may have deleted itself and its parent as result of the message.
	*/
	Msg.hWinSrc = hWin;
	Msg.MsgId   = WM_TOUCH_CHILD;
	while (WM_IsWindow(hWin)) {
		hWin = WM_GetParent(hWin);
		if (hWin) {
			Msg.Data.p  = pMsg;            /* Needs to be set for each window, as callback is allowed to modify it */
			WM__SendMessageIfEnabled(hWin, &Msg);    /* Send message to the ancestors */
		}
	}
#endif
}
static void _SendTouchPressingMessage(WM_HWIN hWin)
{
	U8 Flag = 0;
	WM_HWIN iWin;
	WM_MESSAGE Msg;
	Msg.hWinSrc = hWin;
	Msg.MsgId   = WM_TOUCH_PRESSING;
	iWin = hWin;
	while (WM_IsWindow(iWin)) {
		if(0 == Flag){
			Flag = 1;
			WM__SendMessageIfEnabled(hWin, &Msg);
		}
		iWin = WM_GetParent(iWin);
		if (iWin) {
			WM__SendMessageIfEnabled(iWin, &Msg);    /* Send message to the ancestors */
		}
	}

}
/*********************************************************************
*
*       WM__SendTouchMessage
*/
void WM__SendTouchMessage(WM_HWIN hWin, WM_MESSAGE* pMsg)
{
	GUI_PID_STATE* pState;
	pState     = (GUI_PID_STATE*)pMsg->Data.p;
	if (pState) {
		WM_Obj* pWin;
		pWin       = WM_H2P(hWin);
		pState->x -= pWin->Rect.x0;
		pState->y -= pWin->Rect.y0;
	}
	WM__SendPIDMessage(hWin, pMsg);
}

/*********************************************************************
*
*          Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Screen2Win
*/
static WM_HWIN _Screen2Win(GUI_PID_STATE* pState)
{
	if (WM__hCapture == 0) {
		return WM_Screen2hWin(pState->x, pState->y);
	}
	return WM__hCapture;
}
static void _ScreenTimeOutCalculation(U8 IsPress)
{
	if(IsPress){
		_ScreenTimeOutStatus &= ~SCREEN_TIMEOUT_IS_HAPPEN;
		_TouchReleaseTimeRecorde = GUI_GetTime();
	}else{
		U32 Elapsed = 0;
		Elapsed = GUI_GetTimeElapsed(_TouchReleaseTimeRecorde);
		if((SCREEN_TIMEOUT_IS_USED & _ScreenTimeOutStatus) && (Elapsed >= _ScreenTimeOutTime)){
			if(0 == (_ScreenTimeOutStatus & SCREEN_TIMEOUT_IS_HAPPEN)){
				_ScreenTimeOutStatus |= SCREEN_TIMEOUT_IS_HAPPEN;
				if(_ScreenTimeout_cb){
					_ScreenTimeout_cb();
				}
			}
		}
	}
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_HandlePID       
*
* Polls the touch screen. If something has changed,
* sends a message to the concerned window.
*
* Return value:
*   0 if nothing has been done
*   1 if touch message has been sent
*/
I32 WM_HandlePID(void)
{
	I32 r = 0;
	WM_MESSAGE Msg;
	WM_CRITICAL_HANDLE CHWin;
	GUI_PID_STATE State = {0}, StateNew;
	GUI_PID_GetState(&StateNew);
	StateNew.x += GUI_OrgX;
	StateNew.y += GUI_OrgY;
	WM__AddCriticalHandle(&CHWin);
	if ((WM_PID__StateLast.x != StateNew.x) || (WM_PID__StateLast.y != StateNew.y) || (WM_PID__StateLast.Pressed != StateNew.Pressed)) {
		CHWin.hWin = _Screen2Win(&StateNew);
		if (WM__IsInModalArea(CHWin.hWin)) {
			/*
			 * Send WM_PID_STATE_CHANGED message if state has changed (just pressed or just released)
			 */
			if ((WM_PID__StateLast.Pressed != StateNew.Pressed) && CHWin.hWin) {
				GUI_PID_STATE PID_StateOld;
				WM_HWIN hWinOld;
				WM_PID_STATE_CHANGED_INFO Info;
				WM_Obj* pWin;
				pWin = WM_H2P(CHWin.hWin);
				Info.State     = StateNew.Pressed;
				Info.StatePrev = WM_PID__StateLast.Pressed;
				Info.x         = StateNew.x - pWin->Rect.x0;
				Info.y         = StateNew.y - pWin->Rect.y0;
				Msg.Data.p = &Info;
				Msg.MsgId  = WM_PID_STATE_CHANGED;
				/* Make sure that this routine does not react a second time on the same press event.
				 * This could happen if for example a dialog is executed during the WM_PID_STATE_CHANGED message processing
				 */
				PID_StateOld = WM_PID__StateLast;
				/* Make sure that in case of creating a new window over the current PID position
				 * during the WM_PID_STATE_CHANGED message processing the old window
				 * will be informed that it is no longer pressed.
				 */
				WM_PID__StateLast.Pressed = StateNew.Pressed;
				if (State.Pressed) {
					hWinOld            = WM__CHWinLast.hWin;
					WM__CHWinLast.hWin = CHWin.hWin;
				} else {
					hWinOld            = 0;
				}
				WM__SendMessageIfEnabled(CHWin.hWin, &Msg);
				/* Restore state for further processing */
				WM_PID__StateLast = PID_StateOld;
				if (hWinOld) {
					/* hWinOld could be deleted during message processing. So check if it is a Window
					 * before using it.
					 */
					if (WM_IsWindow(hWinOld)) {
						WM__CHWinLast.hWin        = hWinOld;
					}
				}
			}
			if(0 == StateNew.Pressed){
				_WaitTouchRelease = 0;
			}
			/*
			 * Send WM_TOUCH message(s)
			 * Note that we may have to send 2 touch messages.
			 */
			if (WM_PID__StateLast.Pressed | StateNew.Pressed) {    /* Only if pressed or just released */
				Msg.MsgId = WM_TOUCH;
				r = 1;
				/*
				 * Tell window if it is no longer pressed
				 * This happens for 2 possible reasons:
				 * a) PID is released
				 * b) PID is moved out
				 */
				if (WM__CHWinLast.hWin != CHWin.hWin) {
					if (WM__CHWinLast.hWin != 0) {
						if (StateNew.Pressed) {
							/* Moved out -> no longer in this window
							 * Send a NULL pointer as data
							 */
							Msg.Data.p = NULL;
						} else {
							/* Last window needs to know that it has been "Released"
							 * Send last coordinates
							 */
							State.x       = WM_PID__StateLast.x;
							State.y       = WM_PID__StateLast.y;
							State.Pressed = 0;
							Msg.Data.p = (void*)&State;
						}
						GUI_DEBUG_LOG1 ("\nSending WM_Touch to LastWindow %d (out of area)", WM__CHWinLast.hWin);
						WM__SendTouchMessage(WM__CHWinLast.hWin, &Msg);
						WM__CHWinLast.hWin = 0;
					}
				}
				/* Make sure that this routine does not react a second time on the same event.
				 * This could happen if for example a dialog is executed during the WM_TOUCH message processing
				 */
				WM_PID__StateLast.Pressed = StateNew.Pressed;
				/* Sending WM_Touch to current window */
				if (CHWin.hWin) {
					/* convert screen into window coordinates */
					State = StateNew;
					/* Remember window */
					if (State.Pressed) {
						WM__CHWinLast.hWin = CHWin.hWin;
					} else {
						/* Handle automatic capture release */
						if (WM__CaptureReleaseAuto) {
							WM_ReleaseCapture();
						}
						WM__CHWinLast.hWin = 0;
					}
					Msg.Data.p = (void*)&State;
					WM__SendTouchMessage(CHWin.hWin, &Msg);
				}
			}
		}
		/* Store the new state */
		WM_PID__StateLast = StateNew;
		WM_PID__SetPrevState(&StateNew);
	}
	if(StateNew.Pressed && CHWin.hWin){
		_SendTouchPressingMessage(CHWin.hWin);
	}
	WM__RemoveCriticalHandle(&CHWin);
	_ScreenTimeOutCalculation(StateNew.Pressed);
	return r;
}
/*
 * 获取未触摸屏幕的时间  单位:ms
 * */
U32 WM_GetScreenTimeoutTime(void)
{
	if(SCREEN_TIMEOUT_IS_USED & _ScreenTimeOutStatus){
		return GUI_GetTimeElapsed(_TouchReleaseTimeRecorde);
	}else{
		return 0;
	}
}
void WM_EnableScreenTimeout(void)
{
	_ScreenTimeOutStatus |= SCREEN_TIMEOUT_IS_USED;
	_TouchReleaseTimeRecorde = GUI_GetTime();
}
void WM_DisableScreenTimeout(void)
{
	_ScreenTimeOutStatus &= ~SCREEN_TIMEOUT_IS_USED;
}
void WM_InitScreenTimeout(void)
{
	_ScreenTimeOutStatus = SCREEN_TIMEOUT_NONE;
	_TouchReleaseTimeRecorde = 0;
}
void WM_ClearScreenIsHappen(void)
{
	_ScreenTimeOutStatus &= ~SCREEN_TIMEOUT_IS_HAPPEN;
	_TouchReleaseTimeRecorde = GUI_GetTime();
}
void WM_SetScreenTimeoutTime(U32 Time)
{
	_ScreenTimeOutTime = Time;
}
void WM_SetScreenTimeoutCallback(void *pMethod)
{
	_ScreenTimeout_cb = (pScreenTimeoutCallback)pMethod;
}
#else
  void WM_Touch_c(void) {} /* avoid empty object files */
#endif  /* (GUI_WINSUPPORT & GUI_SUPPORT_TOUCH) */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
