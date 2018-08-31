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
File        : IMAGEVIEW_Private.h
Purpose     : IMAGEVIEW private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef IMAGEVIEW_PRIVATE_H
#define IMAGEVIEW_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "IMAGEVIEW.h"

#if GUI_WINSUPPORT && IMAGEVIEW_SUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
#define IMAGE_DECODE_NONE	0x00
#define IMAGE_DECODE_SAVE	0x01
#define IMAGE_IS_MAPPING	0x02
#define IMAGE_BITMAP_HAS_TRANS	0x10

typedef struct
{
	WIDGET Widget;
	U8 Status;
	ImageViewInfo_t ImageViewInfo;
	WM_HMEM hpText;
	GUI_COLOR	BackgroundColor;
	GUI_COLOR	BitmapTransColor;
	I16	RotateAngle;
	U8	AlphaValue;
#if GUI_DEBUG_LEVEL >1
	I32 DebugId;
#endif
} IMAGEVIEW_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  IMAGEVIEW_Obj * IMAGEVIEW_h2p(IMAGEVIEW_Handle h);
  #define IMAGEVIEW_H2P(h) IMAGEVIEW_h2p(h)
  #define IMAGEVIEW_INIT_ID(p) p->DebugId = IMAGEVIEW_ID
#else
  #define IMAGEVIEW_H2P(h) (IMAGEVIEW_Obj *)GUI_ALLOC_h2p(h)
  #define IMAGEVIEW_INIT_ID(p)
#endif


#endif

#endif/* IMAGEVIEW_PRIVATE_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
