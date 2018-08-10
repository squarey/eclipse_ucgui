

#include "LISTVIEW.h"


#if GUI_WINSUPPORT && LISTVIEW_SUPPORT
LISTVIEW_Handle LISTVIEW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, I32 x0, I32 y0, WM_CALLBACK* cb)
{
  LISTVIEW_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = LISTVIEW_CreateEx(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize,
                          hWinParent, 0, pCreateInfo->Flags, pCreateInfo->Id);
  return hThis;
}

#else  /* avoid empty object files */
  void LISTVIEW_CreateIndirect_C(void) {}
#endif

