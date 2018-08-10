

#include "Picker.h"


#if GUI_WINSUPPORT && PICKER_SUPPORT


Picker_Handle Picker_Create(I32 x0, I32 y0, I32 xsize, I32 ysize, WM_HWIN hParent, I32 Id, I32 WinFlags, I32 SpecialFlags) {
  return Picker_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}

#else  /* avoid empty object files */
  void Picker_Create(void) {}
#endif




