/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCD_GetEx.C
Purpose     : Routines returning info at runtime
---------------------------END-OF-HEADER------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.h"		          /* interface definitions */
#include "LCD_Private.h"      /* private modul definitions & config */


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_GetXSizeEx
*/
I32 LCD_GetXSizeEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_XSIZE;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_XSIZE_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_XSIZE_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_XSIZE_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_XSIZE_4;
	}
#endif
  return 0;
}
/*********************************************************************
*
*       LCD_GetYSizeEx
*/
I32 LCD_GetYSizeEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_YSIZE;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_YSIZE_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_YSIZE_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_YSIZE_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_YSIZE_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetVXSizeEx
*/
I32 LCD_GetVXSizeEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_VXSIZE;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_VXSIZE_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
	  	return LCD_VXSIZE_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
	  	return LCD_VXSIZE_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
	  	return LCD_VXSIZE_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetVYSizeEx
*/
I32 LCD_GetVYSizeEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_VYSIZE;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_VYSIZE_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_VYSIZE_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_VYSIZE_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_VYSIZE_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetBitsPerPixelEx
*/
I32 LCD_GetBitsPerPixelEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_BITSPERPIXEL;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_BITSPERPIXEL_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_BITSPERPIXEL_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_BITSPERPIXEL_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_BITSPERPIXEL_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetBitsPerPixel_L0Ex
*/
I32 LCD_GetBitsPerPixel_L0Ex(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_BITSPERPIXEL_L0;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_BITSPERPIXEL_L0_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_BITSPERPIXEL_L0_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_BITSPERPIXEL_L0_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_BITSPERPIXEL_L0_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetNumColorsEx
*/
U32 LCD_GetNumColorsEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_NUM_COLORS;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_NUM_COLORS_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_NUM_COLORS_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_NUM_COLORS_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_NUM_COLORS_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetYMagEx
*/
I32 LCD_GetYMagEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_YMAG;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_YMAG_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_YMAG_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_YMAG_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_YMAG_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetXMagEx
*/
I32 LCD_GetXMagEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_XMAG;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_XMAG_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_XMAG_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_XMAG_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_XMAG_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetFixedPaletteEx
*/
I32 LCD_GetFixedPaletteEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_FIXEDPALETTE;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_FIXEDPALETTE_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_FIXEDPALETTE_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_FIXEDPALETTE_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_FIXEDPALETTE_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetMirrorXEx
*/
I32 LCD_GetMirrorXEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_MIRROR_X;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_MIRROR_X_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_MIRROR_X_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_MIRROR_X_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_MIRROR_X_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetMirrorYEx
*/
I32 LCD_GetMirrorYEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_MIRROR_Y;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_MIRROR_Y_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_MIRROR_Y_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_MIRROR_Y_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_MIRROR_Y_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetSwapXYEx
*/
I32 LCD_GetSwapXYEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_SWAP_XY;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_SWAP_XY_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_SWAP_XY_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_SWAP_XY_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_SWAP_XY_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetSwapRBEx
*/
I32 LCD_GetSwapRBEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_SWAP_RB;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_SWAP_RB_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_SWAP_RB_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_SWAP_RB_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_SWAP_RB_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetDeltaModeEx
*/
I32 LCD_GetDeltaModeEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_DELTA_MODE;
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_DELTA_MODE_1;
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_DELTA_MODE_2;
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_DELTA_MODE_3;
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_DELTA_MODE_4;
	}
#endif
	return 0;
}

/*********************************************************************
*
*       LCD_GetpfIndex2ColorEx
*/
tLCDDEV_Index2Color * LCD_GetpfIndex2ColorEx(I32 LayerIndex) 
{
	if (LayerIndex == 0) {
		return LCD_L0_GetpfIndex2Color();
	}
#if GUI_NUM_LAYERS > 1
	if (LayerIndex == 1) {
		return LCD_L0_1_GetpfIndex2Color();
	}
#endif
#if GUI_NUM_LAYERS > 2
	if (LayerIndex == 2) {
		return LCD_L0_2_GetpfIndex2Color();
	}
#endif
#if GUI_NUM_LAYERS > 3
	if (LayerIndex == 3) {
		return LCD_L0_3_GetpfIndex2Color();
	}
#endif
#if GUI_NUM_LAYERS > 4
	if (LayerIndex == 4) {
		return LCD_L0_4_GetpfIndex2Color();
	}
#endif
	return 0;
}


/************************* End of file ******************************/

	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
