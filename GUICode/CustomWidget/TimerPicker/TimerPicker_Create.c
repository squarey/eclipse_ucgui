

#include "TimerPicker.h"


#if GUI_WINSUPPORT

#if GUI_WINSUPPORT && TIMERPICKER_SUPPORT

TimerPicker_Handle TimerPicker_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags) {
  return TimerPicker_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}

#else  /* avoid empty object files */
  void TimerPicker_Create(void) {}
#endif



#endif 

