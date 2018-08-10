/*
 * GUI_ImageRotate.h
 *
 *  Created on: 2018年5月30日
 *      Author: Administrator
 */

#ifndef _GUI_IMAGEROTATE_H_
#define _GUI_IMAGEROTATE_H_

#include "IMAGEVIEW.h"

typedef struct
{
	U32 	ImageWidth;		//图像的宽度
	U32 	ImageHeight;	//图像的高度
	U32		DstWidth;		//绘制区域的宽度
	U32		DstHeight;		//绘制区域的高度
	I16		RotatX;			//图片中任意一点坐标X
	I16		RotatY;			//图片中任意一点坐标Y (RotatX, RotatY) 旋转的中心点
	I16		RotatAngle;		//旋转的角度	0-360
	U8		ImageColorDepth;//图像的色深	24, 32
	U8* 	pImageData;		//图像的有效数据流
}ImageRotateInfo;


void GUI_ImageDrawRotate(U32 PosX, U32 PosY, ImageRotateInfo *pInfo);

#endif /* _GUI_IMAGEROTATE_H_ */
