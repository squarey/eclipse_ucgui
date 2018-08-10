


#ifndef IMAGEBUTTON_PRIVATE_H
#define IMAGEBUTTON_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "IMAGEBUTTON.h"

#if GUI_WINSUPPORT && IMAGEBUTTON_SUPPORT

#define IMAGE_DECODE_SAVE_NONE		0x00
#define IMAGE_FOCUS_DECODE_SAVE		0x01
#define IMAGE_UNFOCUS_DECODE_SAVE	0x02

#define IMAGE_FOCUS_IS_MAPPING		0x04
#define IMAGE_UNFOCUS_IS_MAPPING	0x08

typedef struct 
{
	WIDGET Widget;
	ImageViewInfo_t FocusViewInfo;
	ImageViewInfo_t UnFocusViewInfo;
	WM_HMEM hFocusText;
	WM_HMEM hUnFocusText;
	GUI_COLOR	BkColor;
	U8	  Status;
}IMAGEBUTTON_Obj;

#define IMAGEBUTTON_H2P(h) (IMAGEBUTTON_Obj *)GUI_ALLOC_h2p(h)
#define IMAGEBUTTON_INIT_ID(p)

#endif 


#endif


