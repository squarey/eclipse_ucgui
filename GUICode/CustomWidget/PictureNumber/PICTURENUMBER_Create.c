

#include "PICTURENUMBER.h"


#if GUI_WINSUPPORT && PICTURENUMBER_SUPPORT


PICTURENUMBER_Handle PICTURENUMBER_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags) {
  return PICTURENUMBER_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}

#else  /* avoid empty object files */
  void PICTURENUMBER_Create(void) {}
#endif


