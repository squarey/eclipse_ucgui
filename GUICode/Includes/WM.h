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
File        : WM.h
Purpose     : Windows manager include
----------------------------------------------------------------------
*/

#ifndef WM_H            /* Make sure we only include it once */
#define WM_H


#include "GUI_ConfDefaults.h"
#include "GUIType.h"      /* Needed because of typedefs only */
#include "WM_GUI.h"       /* Some functions needed by GUI routines */

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/* This is for tests only. It will fill the invalid area of a window.
   Can be used for debugging. */
#ifndef WM_SUPPORT_DIAG
  #ifdef WIN32   /* In simulation */
    #define WM_SUPPORT_DIAG GUI_WINSUPPORT
  #else
    #define WM_SUPPORT_DIAG 0
  #endif
#endif

/* Make sure we actually have configured windows. If we have not,
  there is no point for a windows manager and it will therefor not
  generate any code !
*/

#if GUI_WINSUPPORT

/*********************************************************************
*
*              Config defaults
*
**********************************************************************
*/

#ifndef WM_ASSERT
  #define WM_ASSERT(expr) GUI_DEBUG_ASSERT(expr)
#endif

#ifndef WM_SUPPORT_TOUCH
  #define WM_SUPPORT_TOUCH        GUI_SUPPORT_TOUCH
#endif

#ifndef WM_SUPPORT_OBSTRUCT
  #define WM_SUPPORT_OBSTRUCT 1
#endif

/* Allow older API calls */
#ifndef WM_COMPATIBLE_MODE
  #define WM_COMPATIBLE_MODE 1
#endif

/* Send a message if visibility of a window has changed */
#ifndef WM_SUPPORT_NOTIFY_VIS_CHANGED
  #define WM_SUPPORT_NOTIFY_VIS_CHANGED 1
#endif


/*
      *************************************************************
      *                                                           *
      *               Configuration check                         *
      *                                                           *
      *************************************************************
*/

/*
      *************************************************************
      *                                                           *
      *               Locking macros                              *
      *                                                           *
      *************************************************************
  For performance reasons, the windows manager uses the same locking mechanisms
  as the GUI layer. The advantage is that wiht a single call to GUI_LOCK both
  the graphic level and the WM level are covered.
*/

/************************************************************
*
*          Data types
*
*************************************************************
*/

typedef struct
{
	I32 Key, PressedCnt;
} WM_KEY_INFO;

typedef struct
{
	I32 Done;
	I32 ReturnValue;
} WM_DIALOG_STATUS;

typedef struct
{
	I32 x,y;
	U8  State;
	U8  StatePrev;
} WM_PID_STATE_CHANGED_INFO;



/*********************************************************************
*
*               Messages Ids

The following is the list of windows messages.
*/


#define WM_CREATE                   0x0001  /* The first message received, right after client has actually been created */
#define WM_MOVE                     0x0003  /* window has been moved (Same as WIN32) */

#define WM_SIZE                     0x0005  /* Is sent to a window after its size has changed (Same as WIN32, do not change !) */

#define WM_DELETE                   11      /* Delete (Destroy) command: This tells the client to free its data strutures since the window
                                               it is associates with no longer exists.*/
#define WM_TOUCH                    12      /* Touch screen message */
#define WM_TOUCH_CHILD              13      /* Touch screen message to ancestors */
#define WM_KEY                      14      /* Key has been pressed */

#define WM_PAINT                    0x000F  /* Repaint window (because content is (partially) invalid */

#define WM_PID_STATE_CHANGED        17      /* Pointer input device state has changed */
#define WM_SCREEN_TIMEOUT			  18
#define WM_GET_INSIDE_RECT          20      /* get inside rectangle: client rectangle minus pixels lost to effect */
#define WM_GET_ID                   21      /* Get id of widget */
#define WM_SET_ID                   22      /* Set id of widget */
#define WM_GET_CLIENT_WINDOW        23      /* Get window handle of client window. Default is the same as window */
#define WM_CAPTURE_RELEASED         24      /* Let window know that mouse capture is over */

#define WM_INIT_DIALOG              29      /* Inform dialog that it is ready for init */

#define WM_SET_FOCUS                30      /* Inform window that it has gotten or lost the focus */
#define WM_GET_ACCEPT_FOCUS         31      /* Find out if window can accept the focus */
#define WM_NOTIFY_CHILD_HAS_FOCUS   32      /* Sent to parent when child receives / loses focus */

#define WM_NOTIFY_OWNER_KEY         33      /* Some widgets (e.g. listbox) notify owner when receiving key messages */

#define WM_GET_BKCOLOR              34      /* Return back ground color (only frame window and similar) */
#define WM_GET_SCROLL_STATE         35      /* Query state of scroll bar */

#define WM_SET_SCROLL_STATE         36      /* Set scroll info ... only effective for scrollbars */

#define WM_NOTIFY_CLIENTCHANGE      37      /* Client area may have changed */
#define WM_NOTIFY_PARENT            38      /* Notify parent. Information is detailed as notification code */
#define WM_NOTIFY_PARENT_REFLECTION 39      /* Notify parent reflection. 
                                               Sometimes send back as a result of the WM_NOTIFY_PARENT message
                                               to let child react on behalf of its parent.
                                               Information is detailed as notification code */
#define WM_NOTIFY_ENABLE            40      /* Enable or disable widget */
#define WM_NOTIFY_VIS_CHANGED       41      /* Visibility of a window has or may have changed */

#define WM_HANDLE_DIALOG_STATUS     42      /* Set or get dialog status */
#define WM_GET_RADIOGROUP           43      /* Send to all siblings and children of a radio control when
                                               selection changed */
#define WM_MENU                     44      /* Send to owner window of menu widget */
#define WM_SCREENSIZE_CHANGED       45      /* Send to all windows when size of screen has changed */
#define WM_TOUCH_PRESSING			  46

#define WM_TIMER                    0x0113  /* Timer has expired              (Keep the same as WIN32) */
#define WM_WIDGET                   0x0300  /* 256 messages reserved for Widget messages */
#define WM_USER                     0x0400  /* Reserved for user messages ... (Keep the same as WIN32) */



/*********************************************************************
*
*               Notification codes
*
* The following is the list of notification codes send
* with the WM_NOTIFY_PARENT message
*/
#define WM_NOTIFICATION_CLICKED             1
#define WM_NOTIFICATION_RELEASED            2
#define WM_NOTIFICATION_MOVED_OUT           3
#define WM_NOTIFICATION_SEL_CHANGED         4
#define WM_NOTIFICATION_VALUE_CHANGED       5
#define WM_NOTIFICATION_SCROLLBAR_ADDED     6      /* Scroller added */
#define WM_NOTIFICATION_CHILD_DELETED       7      /* Inform window that child is about to be deleted */
#define WM_NOTIFICATION_GOT_FOCUS           8
#define WM_NOTIFICATION_LOST_FOCUS          9
#define WM_NOTIFICATION_SCROLL_CHANGED     10

#define WM_NOTIFICATION_WIDGET             11      /* Space for widget defined notifications */
#define WM_NOTIFICATION_USER               16      /* Space for  application (user) defined notifications */
/*********************************************************************
*
*       Memory management
*/

#define WM_HWIN        GUI_HWIN
#define WM_HWIN_NULL   GUI_HMEM_NULL
#define WM_HMEM        GUI_HMEM
#define WM_HMEM_NULL   GUI_HMEM_NULL

/*********************************************************************
*
*       Window defines
*/
#define WM_HBKWIN      WM_GetDesktopWindow()                /* Handle of background window */
#define WM_UNATTACHED  ((WM_HMEM)-1)                        /* Do not attach to a window */


/*********************************************************************
*
*           Window create flags.
* These flags can be passed to the create window
* function as flag-parameter. The flags are combinable using the
* binary or operator.
*/

#define WM_CF_HASTRANS         (1 << 0)  /* Has transparency. Needs to be defined for windows which do not fill the entire
                                          section of their (client) rectangle. */
#define WM_CF_HIDE             (0 << 1)  /* Hide window after creation (default !) */
#define WM_CF_SHOW             (1 << 1)  /* Show window after creation */
#define WM_CF_MEMDEV           (1 << 2)  /* Use memory device for redraws */
#define WM_CF_STAYONTOP        (1 << 3)  /* Stay on top */
#define WM_CF_DISABLED         (1 << 4)  /* Disabled: Does not receive PID (mouse & touch) input */
/* Create only flags ... Not available as status flags */
#define WM_CF_ACTIVATE         (1 << 5)  /* If automatic activation upon creation of window is desired */
#define WM_CF_FGND             (0 << 6)  /* Put window in foreground after creation (default !) */
#define WM_CF_BGND             (1 << 6)  /* Put window in background after creation */
#define WM_CF_DELETE        	 (1 << 7)
/* Anchor flags */
#define WM_CF_ANCHOR_RIGHT     (1 << 8)  /* Right anchor ... If parent is resized, distance to right will remain const (left is default) */
#define WM_CF_ANCHOR_BOTTOM    (1 << 9)  /* Bottom anchor ... If parent is resized, distance to bottom will remain const (top is default) */
#define WM_CF_ANCHOR_LEFT      (1 << 10)  /* Left anchor ... If parent is resized, distance to left will remain const (left is default) */
#define WM_CF_ANCHOR_TOP       (1 << 11) /* Top anchor ... If parent is resized, distance to top will remain const (top is default) */

#define WM_CF_CONST_OUTLINE    (1 << 12) /* Constant outline. This is relevant for transparent windows only. If a window is transparent
                                       and does not have a constant outline, its background is invalided instead of the window itself.
                                       This causes add. computation time when redrawing. */
#define WM_CF_LATE_CLIP        (1 << 13)
#define WM_CF_MEMDEV_ON_REDRAW (1 << 14)
#define WM_CF_RESERVED         (1 << 15)

/*********************************************************************
*
*           Window manager types
*/

typedef struct WM_Obj     WM_Obj;
typedef struct WM_OBJ_X   WM_OBJ_X;
typedef struct WM_MESSAGE WM_MESSAGE;

typedef void WM_CALLBACK( WM_MESSAGE* pMsg);

struct WM_MESSAGE
{
	I32 MsgId;            /* type of message */
	WM_HWIN hWin;         /* Destination window */
	WM_HWIN hWinSrc;      /* Source window  */
	union {
		const void* p;            /* Some messages need more info ... Pointer is declared "const" because some systems (M16C) have 4 byte const, byte 2 byte default ptrs */
		I32 v;
		GUI_COLOR Color;
	} Data;
};

struct WM_Obj
{
	GUI_RECT Rect;        /* Outer dimensions of window */
	GUI_RECT InvalidRect; /* Invalid rectangle */
	WM_CALLBACK* cb;      /* Ptr to notification callback */
	WM_HWIN hNextLin;     /* Next window in linear list */
	WM_HWIN hParent;
	WM_HWIN hFirstChild;
	WM_HWIN hNext;
	U16 Status;	          /* Some status flags */
};

/* For debugging only if a pointer-based memory management is used */
struct WM_OBJ_X
{
	I32    Dummy;
	struct WM_Obj Win;
};

typedef void WM_tfPollPID(void);
typedef void WM_tfForEach(WM_HWIN hWin, void * pData);

#define GUI_MATH_MIN(a, b) (a < b ? a : b)
#define GUI_MATH_MAX(a, b) (a > b ? a :b)
#define GUI_MATH_ABS(x) ((x) > 0 ? (x) : (-(x)))

typedef enum
{
	OBJ_ALIGN_BROTHER_LEFT = 0,
	OBJ_ALIGN_BROTHER_RIGHT,
	OBJ_ALIGN_BROTHER_TOP,
	OBJ_ALIGN_BROTHER_BOTTOM,
	OBJ_ALIGN_BROTHER_CENTER,
	OBJ_ALIGN_BROTHER_H_CENTER,
	OBJ_ALIGN_BROTHER_V_CENTER,
    OBJ_ALIGN_BROTHER_OUT_LEFT,
	OBJ_ALIGN_BROTHER_OUT_RIGHT,
	OBJ_ALIGN_BROTHER_ABOVE_TOP,
	OBJ_ALIGN_BROTHER_UNDER_BOTTOM,
	OBJ_ALIGN_BROTHER_NUM,
	OBJ_ALIGN_PARENT_V_CENTRE,
	OBJ_ALIGN_PARENT_H_CENTRE,
	OBJ_ALIGN_PARENT_TOP_CENTRE,
	OBJ_ALIGN_PARENT_BOTTOM_CENTRE,
	OBJ_ALIGN_PARENT_CENTRE,
	OBJ_ALIGN_PARENT_LEFT,
	OBJ_ALIGN_PARENT_RIGHT,
	OBJ_ALIGN_PARENT_LEFT_TOP,
	OBJ_ALIGN_PARENT_RIGHT_TOP,
	OBJ_ALIGN_PARENT_LEFT_BOTTOM,
	OBJ_ALIGN_PARENT_RIGHT_BOTTOM,
	OBJ_ALIGN_PARENT_NUM,
}GUI_ALIGN_em;

/*
**********************************************************************
*
*              General control routines
*
**********************************************************************
*/


void WM_Activate  (void);
void WM_Deactivate(void);
void WM_Init      (void);
I32  WM_Exec      (void);    /* Execute all jobs ... Return 0 if nothing was done. */
I32  WM_Exec1     (void);    /* Execute one job  ... Return 0 if nothing was done. */
U16  WM_SetCreateFlags(U16 Flags);
WM_tfPollPID* WM_SetpfPollPID(WM_tfPollPID* pf);
void WM_SetCapture(WM_HWIN hObj, I32 AutoRelease);
void WM_SetCaptureMove(WM_HWIN hWin, const GUI_PID_STATE* pState, I32 MinVisibility, I32 LimitTop); /* Not yet documented */
void WM_ReleaseCapture(void);

/*********************************************************************
*
*           Window manager interface
*
**********************************************************************
*/

void    WM_AttachWindow              (WM_HWIN hWin, WM_HWIN hParent);
void    WM_AttachWindowAt            (WM_HWIN hWin, WM_HWIN hParent, I32 x, I32 y);
void    WM_ClrHasTrans               (WM_HWIN hWin);
WM_HWIN WM_CreateWindow              (I32 x0, I32 y0, I32 xSize, I32 ySize, U16 Style, WM_CALLBACK* cb, I32 NumExtraBytes);
WM_HWIN WM_CreateWindowAsChild       (I32 x0, I32 y0, I32 xSize, I32 ySize, WM_HWIN hWinParent, U16 Style, WM_CALLBACK* cb, I32 NumExtraBytes);
void    WM_DeleteWindow              (WM_HWIN hWin);
void    WM_DetachWindow              (WM_HWIN hWin);
I32     WM_GetHasTrans               (WM_HWIN hWin);
WM_HWIN WM_GetFocussedWindow         (void);
void    WM_HideWindow                (WM_HWIN hWin);
void    WM_InvalidateArea            (const GUI_RECT* pRect);
void    WM_InvalidateRect            (WM_HWIN hWin, const GUI_RECT*pRect);
void    WM_InvalidateWindow          (WM_HWIN hWin);
I32     WM_IsEnabled                 (WM_HWIN hObj);
I32     WM_IsFocussable              (WM_HWIN hWin);
I32     WM_IsVisible                 (WM_HWIN hWin);
I32     WM_IsWindow                  (WM_HWIN hWin);    /* Check validity */
void    WM_SetHasTrans               (WM_HWIN hWin);
void    WM_SetId                     (WM_HWIN hObj, I32 Id);
void    WM_SetTransState             (WM_HWIN hWin, unsigned State);
void    WM_ShowWindow                (WM_HWIN hWin);
I32     WM_GetInvalidRect            (WM_HWIN hWin, GUI_RECT * pRect);
void    WM_SetStayOnTop              (WM_HWIN hWin, I32 OnOff);
I32     WM_GetStayOnTop              (WM_HWIN hWin);
void    WM_SetAnchor                 (WM_HWIN hWin, U16 AnchorFlags);

/* Move/resize windows */
void WM_MoveWindow                (WM_HWIN hWin, I32 dx, I32 dy);
void WM_ResizeWindow              (WM_HWIN hWin, I32 dx, I32 dy);
void WM_MoveTo                    (WM_HWIN hWin, I32 x, I32 y);
void WM_MoveChildTo               (WM_HWIN hWin, I32 x, I32 y);
void WM_SetSize                   (WM_HWIN hWin, I32 XSize, I32 YSize);
void WM_SetWindowPos              (WM_HWIN hWin, I32 xPos, I32 yPos);
void WM_SetWindowPosAndSize		(WM_HWIN hWin, I32 xPos, I32 yPos, I32 xSize, I32 ySize);
void WM_SetWindowPosX				(WM_HWIN hWin, I32 xPos);
void WM_SetWindowPosY				(WM_HWIN hWin, I32 yPos);
I32  WM_SetXSize                  (WM_HWIN hWin, I32 xSize);
I32  WM_SetYSize                  (WM_HWIN hWin, I32 ySize);
#if SCROLLBAR_SUPPORT
I32  WM_SetScrollbarH             (WM_HWIN hWin, I32 OnOff); /* not to be documented (may change in future version) */
I32  WM_SetScrollbarV             (WM_HWIN hWin, I32 OnOff); /* not to be documented (may change in future version) */
#endif
void WM_SetWindowRect				(WM_HWIN hWin, GUI_RECT Rect);
I16 WM_GetRectSizeX				(GUI_RECT Rect);
I16 WM_GetRectSizeY				(GUI_RECT Rect);
void WM_SetAlignWindow			(WM_HWIN hObjBasic, WM_HWIN hObjSrc, GUI_ALIGN_em Align, I16 OffestX, I16 OffestY);
void WM_SetAlignParent			(WM_HWIN hObj, GUI_ALIGN_em Align, I16 OffestX, I16 OffestY);

/* Diagnostics */
I32 WM_GetNumWindows(void);


/* Get / Set (new) callback function */
WM_CALLBACK * WM_SetCallback(WM_HWIN hWin, WM_CALLBACK * cb);
WM_CALLBACK * WM_GetCallback(WM_HWIN hWin);

/* Get size/origin of a window */
void WM_GetClientRect             (GUI_RECT* pRect);
void WM_GetClientRectEx           (WM_HWIN hWin, GUI_RECT* pRect);
void WM_GetInsideRect             (GUI_RECT* pRect);
void WM_GetInsideRectEx           (WM_HWIN hWin, GUI_RECT* pRect);
void WM_GetInsideRectExScrollbar  (WM_HWIN hWin, GUI_RECT* pRect); /* not to be documented (may change in future version) */
void WM_GetWindowRect             (GUI_RECT* pRect);
void WM_GetWindowRectEx           (WM_HWIN hWin, GUI_RECT* pRect);
I32  WM_GetOrgX                   (void);
I32  WM_GetOrgY                   (void);
I32  WM_GetWindowOrgX             (WM_HWIN hWin);
I32  WM_GetWindowOrgY             (WM_HWIN hWin);
I32  WM_GetWindowSizeX            (WM_HWIN hWin);
I32  WM_GetWindowSizeY            (WM_HWIN hWin);
WM_HWIN WM_GetFirstChild          (WM_HWIN hWin);
WM_HWIN WM_GetNextSibling         (WM_HWIN hWin);
WM_HWIN WM_GetParent              (WM_HWIN hWin);
WM_HWIN WM_GetPrevSibling         (WM_HWIN hWin);
I32     WM_GetId                  (WM_HWIN hWin);
WM_HWIN WM_GetScrollbarV          (WM_HWIN hWin);
WM_HWIN WM_GetScrollbarH          (WM_HWIN hWin);
WM_HWIN WM_GetScrollPartner       (WM_HWIN hWin);
WM_HWIN WM_GetClientWindow        (WM_HWIN hObj);
GUI_COLOR WM_GetBkColor           (WM_HWIN hObj);

/* Change Z-Order of windows */
void WM_BringToBottom(WM_HWIN hWin);
void WM_BringToTop(WM_HWIN hWin);

GUI_COLOR WM_SetDesktopColor(GUI_COLOR Color);
GUI_COLOR WM_SetDesktopColorEx(GUI_COLOR Color, U32 LayerIndex);
void WM_SetDesktopColors(GUI_COLOR Color);

/* Select window used for drawing operations */
WM_HWIN WM_SelectWindow           (WM_HWIN  hWin);
WM_HWIN WM_GetActiveWindow        (void);

/* Get foreground/background windows */
WM_HWIN WM_GetDesktopWindow    (void);
WM_HWIN WM_GetDesktopWindowEx  (U32 LayerIndex);

/* Reduce clipping area of a window */
const GUI_RECT* WM_SetUserClipRect(const GUI_RECT* pRect);
void            WM_SetDefault     (void);

/* Use of memory devices */
void WM_EnableMemdev              (WM_HWIN hWin);
void WM_DisableMemdev             (WM_HWIN hWin);

I32 WM_OnKey(I32 Key, I32 Pressed);
void WM_MakeModal(WM_HWIN hWin);

/* Invalid win function */
void WM_AddToInvalidateRectLink(GUI_RECT Rect);
#define WM_UpdateRectEnd	LCD_UpdateRectEnd
#define WM_UpdateAllEnd	LCD_UpdateAllEnd

U8 WM_RectIntersect(GUI_RECT* pRectResult, const GUI_RECT* pRect1, const GUI_RECT* pRect2);
U8 WM_RectIntersectLCD(GUI_RECT* pRectResult, const GUI_RECT* pRect);
void WM_RectToMax(GUI_RECT* pRectResult, const GUI_RECT* pRect1, const GUI_RECT* pRect2);
U8 WM_RectIsIn(const GUI_RECT * pRect1, const GUI_RECT * pRect2);
void WM_RectSet(GUI_RECT * pRect, I16 x0, I16 y0, I16 x1, I16 y1);
I16 WM_RectGetWidth(const GUI_RECT * pRect);
I16 WM_RectGetHeight(const GUI_RECT * pRect);
/******************************************************************
*
*           Message related funcions
*
*******************************************************************
  Please note that some of these functions do not yet show up in the
  documentation, as they should not be required by application program.
*/

void      WM_NotifyParent         (WM_HWIN hWin, I32 Notification);
void      WM_SendMessage          (WM_HWIN hWin, WM_MESSAGE* p);
void      WM_SendMessageNoPara    (WM_HWIN hWin, I32 MsgId);             /* not to be documented (may change in future versionumented */
void      WM_DefaultProc          (WM_MESSAGE* pMsg);
I32       WM_BroadcastMessage     (WM_MESSAGE* pMsg);
void      WM_SetEnableState       (WM_HWIN hItem, I32 State);
void      WM_SendToParent         (WM_HWIN hWin, WM_MESSAGE* pMsg);
I32       WM_HasCaptured          (WM_HWIN hWin);
I32       WM_HasFocus             (WM_HWIN hWin);
I32       WM_SetFocus             (WM_HWIN hWin);
void 		WM_EnableFocuss		(WM_HWIN hWin);
void 		WM_DisableFocuss		(WM_HWIN hWin);
WM_HWIN   WM_SetFocusOnNextChild  (WM_HWIN hParent);     /* Set the focus to the next child */
WM_HWIN   WM_SetFocusOnPrevChild  (WM_HWIN hParent);     /* Set the focus to the previous child */
WM_HWIN   WM_GetDialogItem        (WM_HWIN hWin, I32 Id);
void      WM_EnableWindow         (WM_HWIN hWin);
void      WM_DisableWindow        (WM_HWIN hWin);
I32       WM_GetUserData          (WM_HWIN hWin,       void* pDest, I32 SizeOfBuffer);
I32       WM_SetUserData          (WM_HWIN hWin, const void* pSrc,  I32 SizeOfBuffer);

/*
 * Screen timeout function
 * */
U32 WM_GetScreenTimeoutTime(void);
void WM_SetScreenTimeoutTime(U32 Time);
void WM_EnableScreenTimeout(void);
void WM_DisableScreenTimeout(void);
void WM_InitScreenTimeout(void);
void WM_ClearScreenIsHappen(void);
void WM_SetScreenTimeoutCallback(void *pMethod);
void WM_SetScreenTouchWakeCallback(void *pMethod);
/*********************************************************************
*
*           Misc routines
*/

I32       WM_HandlePID      (void);
WM_HWIN   WM_Screen2hWin    (I32 x, I32 y);
WM_HWIN   WM_Screen2hWinEx  (WM_HWIN hStop, I32 x, I32 y);
/*********************************************************************
*
*           Diagnostics routines
*/
#if (WM_SUPPORT_DIAG)
void WM_DIAG_EnableInvalidationColoring(I32 OnOff);
#endif

/*
      *************************************************
      *                                               *
      *  Macros for compatibility with older versions *
      *                                               *
      *************************************************
*/

#if WM_COMPATIBLE_MODE
  #define HBWIN             WM_HWIN
  #define HBWIN_NULL        WM_HWIN_NULL

  #define WM_HideWin        WM_HideWindow
  #define WM_ShowWin        WM_ShowWindow
  #define WM_GetKey         GUI_GetKey
  #define WM_WaitKey        GUI_WaitKey

  #define WM_ExecIdle       WM_Exec
  #define WM_ExecIdle1      WM_Exec1

  #define WM_Invalidate     WM_InvalidateWindow
  #define WM_GetWinRect     WM_GetWindowRect
  #define WM_GetWinOrgX     WM_GetWindowOrgX
  #define WM_GetWinOrgY     WM_GetWindowOrgY
  #define WM_GetWinSizeX    WM_GetWindowSizeX
  #define WM_GetWinSizeY    WM_GetWindowSizeY
  #define WM_GetXSize       WM_GetWindowSizeX
  #define WM_GetYSize       WM_GetWindowSizeY
  #define WM_SelWin         WM_SelectWindow
  #define WM_GetBackgroundWindow  WM_GetDesktopWindow
  #define WM_GetForegroundWindow    0
  #define WM_SetForegroundWindow    WM_BringToTop
  #define WM_SetUserClipArea WM_SetUserClipRect


  #define WM_Start()
  #define WM_Stop()
  #define WM_SetBkWindowColor(Color)  WM_SetDesktopColor(Color)

#endif


#endif   /* GUI_WINSUPPORT */

#if defined(__cplusplus)
}
#endif 

#endif   /* WM_H */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
