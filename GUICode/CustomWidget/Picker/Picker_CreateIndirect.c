

#include "Picker.h"


#if GUI_WINSUPPORT && PICKER_SUPPORT
Picker_Handle Picker_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb)
{
  Picker_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = Picker_CreateEx(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                          hWinParent, pCreateInfo->Flags, pCreateInfo->Flags, pCreateInfo->Id);
  return hThis;
}

#else  /* avoid empty object files */
  void Picker_CreateIndirect_C(void) {}
#endif

