

#include "IMAGEBUTTON.h"


#if GUI_WINSUPPORT && IMAGEBUTTON_SUPPORT


IMAGEBUTTON_Handle IMAGEBUTTON_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags) {
  return IMAGEBUTTON_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}

#else  /* avoid empty object files */
  void IMAGEBUTTON_Create(void) {}
#endif



