

#include "PICTURENUMBER.h"


#if GUI_WINSUPPORT && PICTURENUMBER_SUPPORT
PICTURENUMBER_Handle PICTURENUMBER_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb) 
{
  PICTURENUMBER_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = PICTURENUMBER_CreateEx(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                          hWinParent, 0, pCreateInfo->Flags, pCreateInfo->Id);
  return hThis;
}

#else  /* avoid empty object files */
  void PICTURENUMBER_CreateIndirect_C(void) {}
#endif

