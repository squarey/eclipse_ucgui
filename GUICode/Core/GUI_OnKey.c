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
File        : GUI_OnKey.c
Purpose     : Implementation of GUI_StoreKeyMsg
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

#if GUI_WINSUPPORT
  #include "WM_Intern.h"
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#if GUI_WINSUPPORT

static I32 _KeyMsgCnt;
static struct {
  I32 Key;
  I32 PressedCnt;
} _KeyMsg;

#endif

static I32 _Key;

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

GUI_KEY_MSG_HOOK* GUI_pfKeyMsgHook;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetKey
*/
I32 GUI_GetKey(void) {
  I32 r = _Key;
  _Key = 0;
  return r;
}

/*********************************************************************
*
*       GUI_StoreKey
*/
void GUI_StoreKey(I32 Key) {
  if (!_Key) {
    _Key = Key;
  }
  GUI_X_SIGNAL_EVENT();
}

/*********************************************************************
*
*       GUI_ClearKeyBuffer
*/
void GUI_ClearKeyBuffer(void) {
  while (GUI_GetKey());
}

/*********************************************************************
*
*       GUI_StoreKeyMsg
*/
void GUI_StoreKeyMsg(I32 Key, I32 PressedCnt) 
{
	#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
		_KeyMsg.Key = Key;
		_KeyMsg.PressedCnt = PressedCnt;
		_KeyMsgCnt = 1;
		#ifdef GUI_X_ON_UNPROCESSED_KEY
		if (!WM_IsActive) 
		{
		  /* If the WM is deactivated, key messages are not polled by the WM.
			 So call the macro in this case here.
		  */
			GUI_X_ON_UNPROCESSED_KEY(Key, PressedCnt);
		}
		#endif
		GUI_X_SIGNAL_EVENT();
	#else
			GUI_USE_PARA(PressedCnt);
			GUI_StoreKey(Key);
		#ifdef GUI_X_ON_UNPROCESSED_KEY
			GUI_X_ON_UNPROCESSED_KEY(Key, PressedCnt);
		#endif
	#endif
}

/*********************************************************************
*
*       GUI_PollKeyMsg
*/
#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
I32 GUI_PollKeyMsg(void) 
{
	I32 r = 0;
	if (_KeyMsgCnt) {
		I32 Key;
		_KeyMsgCnt--;
		Key = _KeyMsg.Key;
		if (!WM_OnKey(Key, _KeyMsg.PressedCnt)) {
#ifdef GUI_X_ON_UNPROCESSED_KEY
			GUI_X_ON_UNPROCESSED_KEY(Key, _KeyMsg.PressedCnt);
#endif
		}
		if (_KeyMsg.PressedCnt == 1) {
			GUI_StoreKey(Key);
		}
		r = 1;              /* We have done something */
	}
	return r;
}
#endif

/*********************************************************************
*
*       GUI_SendKeyMsg
*
* Purpose:
*   Send the key to a window using the window manager (if available).
*   If no window is ready to take the input, we call the store routine
*   and wait for somebody to poll the buffer.
*/
void GUI_SendKeyMsg(I32 Key, I32 PressedCnt) {
  #if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
    /*if (!WM_OnKey(Key, PressedCnt)) {
      #ifdef GUI_X_ON_UNPROCESSED_KEY
        GUI_X_ON_UNPROCESSED_KEY(Key, PressedCnt);
      #endif
      GUI_StoreKeyMsg(Key, PressedCnt);
    }*/
    WM_HWIN hWin;
    WM_MESSAGE Msg;
	WM_KEY_INFO KeyInfo;
	hWin = WM_GetFocussedWindow();
	KeyInfo.Key = Key;
  	Msg.MsgId = WM_KEY;
	Msg.hWin = hWin;
	Msg.Data.p = &KeyInfo;
	WM_SendMessage(hWin,&Msg);
  #else
    GUI_StoreKeyMsg(Key, PressedCnt);
  #endif
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
