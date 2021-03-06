/*
 * GUI_ImageRotate.c
 *
 *  Created on: 2018年5月30日
 *      Author: Administrator
 */


#include "GUI_ImageRotate.h"
#include <math.h>

#if 0
void GUI_ImageDrawRotate(U32 PosX, U32 PosY, ImageRotateInfo *pInfo)
{
	U8 a = 0, r = 0, g = 0, b = 0;

	U8	ColorBytes = 0;
	U32 Finally_Color = 0;
	U32	BytesPerLine = 0;
	I32 x = 0, y = 0;
	I32 i = 0, j = 0;
	float Rad = 0.0;
	float PosSinValue = 0, PosCosValue = 0, NegSinValue = 0;
	float VarX = 0, VarY = 0;
	const U8 *pData;
	I16 OffestX = 0, OffestY = 0;
	I32 DstWidth = 0, DstHeight = 0;
	//原图四个点的坐标
	I32 SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	//旋转后四个点的坐标
	I32 DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;

	pData = pInfo->pImageData;
	Rad = pInfo->RotatAngle*3.14159/180;		//角度转化成弧度
	PosSinValue = sin(Rad);
	PosCosValue = cos(Rad);
	NegSinValue = sin(-Rad);
	//NegCosValue = cos(-Rad);

	//计算原图四个点的坐标
	SrcX1 = -(pInfo->ImageWidth/2);
	SrcY1 = pInfo->ImageHeight/2;
	SrcX2 = pInfo->ImageWidth/2;
	SrcY2 = pInfo->ImageHeight/2;
	SrcX3 = pInfo->ImageWidth/2;
	SrcY3 = -(pInfo->ImageHeight/2);
	SrcX4 = -(pInfo->ImageWidth/2);
	SrcY4 = -(pInfo->ImageHeight/2);
	GUI_Debug("SrcX1:%d, SrcY1:%d\n", SrcX1, SrcY1);
	GUI_Debug("SrcX2:%d, SrcY2:%d\n", SrcX2, SrcY2);
	GUI_Debug("SrcX3:%d, SrcY3:%d\n", SrcX3, SrcY3);
	GUI_Debug("SrcX4:%d, SrcY4:%d\n", SrcX4, SrcY4);
	//计算旋转后四个点的坐标
	DstX1 = (I32)((PosCosValue * SrcX1 + PosSinValue * SrcY1) + 0.5);
	DstY1 = (I32)((NegSinValue * SrcX1 + PosCosValue * SrcY1) + 0.5);
	DstX2 = (I32)((PosCosValue * SrcX2 + PosSinValue * SrcY2) + 0.5);
	DstY2 = (I32)((NegSinValue * SrcX2 + PosCosValue * SrcY2) + 0.5);
	DstX3 = (I32)((PosCosValue * SrcX3 + PosSinValue * SrcY3) + 0.5);
	DstY3 = (I32)((NegSinValue * SrcX3 + PosCosValue * SrcY3) + 0.5);
	DstX4 = (I32)((PosCosValue * SrcX4 + PosSinValue * SrcY4) + 0.5);
	DstY4 = (I32)((NegSinValue * SrcX4 + PosCosValue * SrcY4) + 0.5);
	GUI_Debug("DstX1:%d, DstY1:%d\n", DstX1, DstY1);
	GUI_Debug("DstX2:%d, DstY2:%d\n", DstX2, DstY2);
	GUI_Debug("DstX3:%d, DstY3:%d\n", DstX3, DstY3);
	GUI_Debug("DstX4:%d, DstY4:%d\n", DstX4, DstY4);
	//计算旋转后外接矩形的高度和宽度
	DstWidth = GUI_MATH_MAX(abs(DstX1 - DstX3), abs(DstX2 - DstX4)) + 1;
	DstHeight = GUI_MATH_MAX(abs(DstY1 - DstY3), abs(DstY2 - DstY4)) + 1;
	/* 在绘制区域居中对齐 */
	if(pInfo->DstWidth > DstWidth){
		OffestX = (pInfo->DstWidth - DstWidth)/2;
	}
	if(pInfo->DstHeight > DstHeight){
		OffestY = (pInfo->DstHeight - DstHeight)/2;
	}
	VarX = (float)((-DstWidth * PosCosValue - DstHeight * PosSinValue + pInfo->ImageWidth)/2 + 0.5);
	VarY = (float)((DstWidth * PosSinValue - DstHeight * PosCosValue + pInfo->ImageHeight)/2 + 0.5);

	//计算旋转后x,y的最小值
	ColorBytes = pInfo->ImageColorDepth/8;
	BytesPerLine = pInfo->ImageWidth * ColorBytes;
	GUI_Debug("DstWidth:%d, DstHeight:%d, VarX:%f, VarY:%f\n", DstWidth, DstHeight, VarX, VarY);
	if(pInfo->RotatAngle == 0){
		for (y = 0; y < pInfo->ImageHeight; y++){
			for (x = 0; x < pInfo->ImageWidth; x++){
				pData = pInfo->pImageData + ColorBytes * x;
				b = *(pData + 0);
				g = *(pData + 1);
				r = *(pData + 2);
				if(4 == ColorBytes){
					a = *(pData + 3);
				}else{
					a = 0xff;
				}
				Finally_Color = ((U32)a << 24) |((U32)r << 16) | (g << 8) | b;
				LCD_SetPixelIndex(PosX + x, PosY + y, LCD_Color2Index(Finally_Color), a);
			}
			pData += BytesPerLine;
		}
	}else{
	//	eDbug("angle%90 != 0!\r\n");
		U8 Alpha = 0;
		U32 A = 0, B = 0, C = 0, D = 0;
		I32 NewIntX = 0, NewIntY = 0;
		float RotatePosX = 0, RotatePosY = 0;
		float PointFloatX = 0, PointFloatY = 0;
		for(i = 0; i < DstHeight; i++){

			for(j = 0; j < DstWidth; j++){
				RotatePosX = PosCosValue * j + PosSinValue * i + VarX; //X，Y为原来图中的像素坐标
				RotatePosY = NegSinValue * j+ PosCosValue * i + VarY;
				NewIntX = (I32)RotatePosX;
				NewIntY = (I32)RotatePosY;
				PointFloatX = RotatePosX - NewIntX;
				PointFloatY = RotatePosY - NewIntY;
				if((NewIntX >= 0) && (NewIntX < pInfo->ImageWidth) && (NewIntY >= 0) && (NewIntY < pInfo->ImageHeight)){
					//定位源图像坐标，读取相应坐标的像素值
					pData = pInfo->pImageData + ColorBytes * NewIntX + BytesPerLine * NewIntY;	//像素F(x,y)
					b = *(pData + 0);
					b = (int)((float)b * (1 - PointFloatX)*(1 - PointFloatY));
					g = *(pData + 1);
					g = (int)((float)g * (1 - PointFloatX)*(1 - PointFloatY));
					r = *(pData + 2);
					r = (int)((float)r * (1 - PointFloatX)*(1 - PointFloatY));
					a = *(pData + 3);
					a = (int)((float)a * (1 - PointFloatX)*(1 - PointFloatY));
					A = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);

					pData = pInfo->pImageData + ColorBytes * NewIntX + BytesPerLine * (NewIntY + 1);	//像素F(x,y+1)
					b = *(pData + 0);
					b = (int)((float)b * (1 - PointFloatX)*PointFloatY);
					g = *(pData + 1);
					g = (int)((float)g * (1 - PointFloatX)*PointFloatY);
					r = *(pData + 2);
					r = (int)((float)r * (1 - PointFloatX)*PointFloatY);
					a = *(pData + 3);
					a = (int)((float)a * (1 - PointFloatX)*PointFloatY);
					B = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);

					pData = pInfo->pImageData + ColorBytes * (NewIntX + 1) + BytesPerLine * NewIntY;	//像素F(x+1,y)
					b = *(pData + 0);
					b = (int)((float)b * PointFloatX*(1 - PointFloatY));
					g = *(pData + 1);
					g = (int)((float)g * PointFloatX*(1 - PointFloatY));
					r = *(pData + 2);
					r = (int)((float)r * PointFloatX*(1 - PointFloatY));
					a = *(pData + 3);
					a = (int)((float)a * PointFloatX*(1 - PointFloatY));
					C = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);

					pData = pInfo->pImageData + ColorBytes * (NewIntX + 1) + BytesPerLine * (NewIntY + 1);	//像素F(x+1,y+1)
					b = *(pData + 0);
					b = (int)((float)b * PointFloatX*PointFloatY);
					g = *(pData + 1);
					g = (int)((float)g * PointFloatX*PointFloatY);
					r = *(pData + 2);
					r = (int)((float)r * PointFloatX*PointFloatY);
					a = *(pData + 3);
					a = (int)((float)a * PointFloatX*PointFloatY);
					D = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);
					//计算灰度值
					Finally_Color = A + B + C + D;
					Alpha = (Finally_Color >> 24) & 0xff;
					if(Alpha > 0x14){
						LCD_SetPixelIndex(PosX + j + OffestX, PosY + i + OffestY, LCD_Color2Index(Finally_Color), Alpha);
					}

				}
			}
		}
		/*for(x = SrcX1; x < pInfo->ImageWidth + SrcX1; x++){
			j = (int)((PosCosValue * x + PosSinValue * SrcY1) + 0.5);
			i = (int)((NegSinValue * x + PosCosValue * SrcY1) + 0.5);
			LCD_SetPixelIndex(PosX + j, PosY + i, LCD_Color2Index(GUI_RED), 0xff);
		}*/
	}

}
#else

static I32 maxI32(I32 a, I32 b)
{
	if(a > b)
		return a;
	else
		return b;
}
static I32 minI32(I32 a,I32 b)
{
	if(a < b)
		return a;
	else
		return b;
}
static I32 absI32(I32 a)
{
	if(a < 0)
		return -a;
	else
		return a;
}
/*
 * 反映射最近邻插值和双线性插值算法
 * */
void GUI_ImageDrawRotate(U32 PosX, U32 PosY, ImageRotateInfo *pInfo)
{
	U8 		ColorBytes = 0;
	U8  	a = 0, r = 0, g = 0, b = 0;
	U32 	A = 0, B = 0, C = 0, D = 0;
	U32 	Finally_Color = 0;
	I32   	x = 0, y = 0;
	I32	  	BytesPerLine = 0;
	I32   	NewSizeX = 0, NewSizeY = 0;
	I32   	OldMidX = 0, OldMidY = 0;
	I32   	RotatMinX = 0, RotatMinY = 0;
	I32		OffestX = 0, OffestY = 0;
	I32 	MagPosSinValue = 0, MagPosCosValue = 0;
	I32 	MagNegSinValue = 0, MagNegCosValue = 0;
	float 	Rad = 0.0f;
	float 	PosSinValue = 0.0f, PosCosValue = 0.0f;
	float 	NegSinValue = 0.0f, NegCosValue = 0.0f;
	const 	U8 *pColor;
	const 	U8 *pData;
	U16 	ColorRGB565;

	//原图四个点的坐标
	I32 SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	//旋转后四个点的坐标
	I32 DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;

	pData = pInfo->pImageData;
	//角度转化成弧度
	Rad = pInfo->RotatAngle*3.14159f/180;
	PosSinValue = sin(Rad);
	PosCosValue = cos(Rad);
	NegSinValue = -PosSinValue;
	NegCosValue = PosCosValue;
	MagPosSinValue = (I32)(PosSinValue * GUI_FIX_DIV);
	MagPosCosValue = (I32)(PosCosValue * GUI_FIX_DIV);
	MagNegSinValue = (I32)(NegSinValue * GUI_FIX_DIV);
	MagNegCosValue = (I32)(NegCosValue * GUI_FIX_DIV);
	//计算旋转的中心点
	if((pInfo->RotatX == 0) && (pInfo->RotatY == 0)){
		OldMidX = pInfo->ImageWidth/2;
		OldMidY = pInfo->ImageHeight/2;
	}else{
		OldMidX = pInfo->RotatX;
		OldMidY = pInfo->RotatY;
	}
	//计算原图四个点的坐标
	SrcX1 = 0;
	SrcY1 = pInfo->ImageHeight;

	SrcX2 = pInfo->ImageWidth;
	SrcY2 = pInfo->ImageHeight;

	SrcX3 = 0;
	SrcY3 = 0;

	SrcX4 = pInfo->ImageWidth;
	SrcY4 = 0;

	//计算旋转后四个点的坐标
	DstX1 = (((SrcX1 - OldMidX) * MagPosCosValue - (SrcY1 - OldMidY) * MagPosSinValue) >> GUI_FIX_DIV_BIT) + OldMidX;
	DstY1 = (((SrcX1 - OldMidX) * MagPosSinValue + (SrcY1 - OldMidY) * MagPosCosValue) >> GUI_FIX_DIV_BIT) + OldMidY;

	DstX2 = (((SrcX2 - OldMidX) * MagPosCosValue - (SrcY2 - OldMidY) * MagPosSinValue) >> GUI_FIX_DIV_BIT) + OldMidX;
	DstY2 = (((SrcX2 - OldMidX) * MagPosSinValue + (SrcY2 - OldMidY) * MagPosCosValue) >> GUI_FIX_DIV_BIT) + OldMidY;

	DstX3 = (((SrcX3 - OldMidX) * MagPosCosValue - (SrcY3 - OldMidY) * MagPosSinValue) >> GUI_FIX_DIV_BIT) + OldMidX;
	DstY3 = (((SrcX3 - OldMidX) * MagPosSinValue + (SrcY3 - OldMidY) * MagPosCosValue) >> GUI_FIX_DIV_BIT) + OldMidY;

	DstX4 = (((SrcX4 - OldMidX) * MagPosCosValue - (SrcY4 - OldMidY) * MagPosSinValue) >> GUI_FIX_DIV_BIT) + OldMidX;
	DstY4 = (((SrcX4 - OldMidX) * MagPosSinValue + (SrcY4 - OldMidY) * MagPosCosValue) >> GUI_FIX_DIV_BIT) + OldMidY;

	//计算旋转后外接矩形的高度和宽度
	NewSizeX = maxI32(absI32(DstX4 - DstX1), absI32(DstX3 - DstX2));
	NewSizeY = maxI32(absI32(DstY4 - DstY1), absI32(DstY3 - DstY2));
	if(pInfo->DstWidth > NewSizeX){
		OffestX = (pInfo->DstWidth - NewSizeX)/2;
	}
	if(pInfo->DstHeight > NewSizeY){
		OffestY = (pInfo->DstHeight - NewSizeY)/2;
	}
	//计算旋转后x,y的最小值
	RotatMinX = minI32(minI32(DstX1, DstX2),minI32(DstX3, DstX4));
	RotatMinY = minI32(minI32(DstY1, DstY2),minI32(DstY3, DstY4));
//	GUI_Debug("NewSizeX:%d, NewSizeY:%d, OffestX:%d, OffestY:%d, RotatMinX:%d, RotatMinY:%d\n",
//			NewSizeX, NewSizeY, OffestX, OffestY, RotatMinX, RotatMinY);
	ColorBytes = pInfo->ImageColorDepth >> 3;
	BytesPerLine = ColorBytes * pInfo->ImageWidth;
	if(pInfo->RotatAngle == 0){
		for (y = 0; y < pInfo->ImageHeight; y++){
			for (x = 0; x < pInfo->ImageWidth; x++){
				pColor = pData + ColorBytes * x;
				if(ROTATE_PIXEL_FORMAT_RGB565 == pInfo->PixelFormat){
					ColorRGB565 = (*pColor << 8) | *(pColor + 1);
					r = ((ColorRGB565 >> 11) & 0x1f) << 3;
					g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
					b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
					a = 0xff;
				}else if(ROTATE_PIXEL_FORMAT_ARGB8565 == pInfo->PixelFormat){
					a = *pColor++;
					ColorRGB565 = (*pColor << 8) | *(pColor + 1);
					r = ((ColorRGB565 >> 11) & 0x1f) << 3;
					g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
					b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
				}else if(ROTATE_PIXEL_FORMAT_RGB888 == pInfo->PixelFormat){
					b = *(pColor + 0);
					g = *(pColor + 1);
					r = *(pColor + 2);
					a = 0xff;
				}else{
					b = *(pColor + 0);
					g = *(pColor + 1);
					r = *(pColor + 2);
					a = *(pColor + 3);
				}
#if (24 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Finally_Color = (a << 24) | ((U32)r << 16) | (g << 8) | b;
#elif (16 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
				Finally_Color = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3);
				//Color = LCD_L0_Color2Index(((U32)Red << 16) | (Green << 8) | Blue);
#endif
				LCD_SetPixelIndex(PosX + x, PosY + y, Finally_Color, a);
			}
			pData += BytesPerLine;
		}
	}else if(pInfo->RotatAngle%90 == 0)
	{
		I32 Int_y_temp1 = 0, Int_y_temp2 = 0;
		I32 Int_x_temp1 = 0, Int_y_temp3 = 0;
		for (y = 0; y < pInfo->ImageHeight; y++){
			Int_y_temp1 = (y - OldMidY) * MagPosSinValue;
			Int_y_temp2 = (y - OldMidY) * MagPosCosValue;
			for (x = 0; x < pInfo->ImageWidth; x++){
				pColor = pData + ColorBytes * x;
				Int_x_temp1 = (((x - OldMidX) * MagPosCosValue - Int_y_temp1) >> GUI_FIX_DIV_BIT) + OldMidX + PosX - 1;
				Int_y_temp3 = (((x - OldMidX) * MagPosSinValue + Int_y_temp2) >> GUI_FIX_DIV_BIT) + OldMidY + PosY - 1;
				if((Int_x_temp1 >= 0) && (Int_y_temp3 >= 0)){
					if(ROTATE_PIXEL_FORMAT_RGB565 == pInfo->PixelFormat){
						ColorRGB565 = (*pColor << 8) | *(pColor + 1);
						r = ((ColorRGB565 >> 11) & 0x1f) << 3;
						g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
						b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
						a = 0xff;
					}else if(ROTATE_PIXEL_FORMAT_ARGB8565 == pInfo->PixelFormat){
						a = *pColor++;
						ColorRGB565 = (*pColor << 8) | *(pColor + 1);
						r = ((ColorRGB565 >> 11) & 0x1f) << 3;
						g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
						b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
					}else if(ROTATE_PIXEL_FORMAT_RGB888 == pInfo->PixelFormat){
						b = *(pColor + 0);
						g = *(pColor + 1);
						r = *(pColor + 2);
						a = 0xff;
					}else{
						b = *(pColor + 0);
						g = *(pColor + 1);
						r = *(pColor + 2);
						a = *(pColor + 3);
					}
#if (24 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
					Finally_Color = (a << 24) | ((U32)r << 16) | (g << 8) | b;
#elif (16 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
					Finally_Color = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3);
#endif
					LCD_SetPixelIndex(Int_x_temp1 - RotatMinX + OffestX, Int_y_temp3 + OffestY - RotatMinY, Finally_Color, a);
				}
			}
			pData += BytesPerLine;
		}
	}else{
	//	eDbug("angle%90 != 0!\r\n");
		I32 	NewTemp1Y = 0, NewTemp2Y = 0;
		I32 	NewFloatX = 0, NewFloatY = 0;
		I32	  	MagFloatX = 0, MagFloatY;
		I32   	NewIntX = 0, NewIntY = 0;
		I32 	Value1 = 0, Value2 = 0, Value3 = 0, Value4 = 0;
		for(y = RotatMinY; y < NewSizeY + RotatMinY; y++){
			NewTemp1Y = (y - OldMidY) * MagNegSinValue;
			NewTemp2Y = (y - OldMidY) * MagNegCosValue;
			for(x = RotatMinX; x < NewSizeX + RotatMinX; x++){
				//计算反旋转后的坐标
				NewFloatX = ((x - OldMidX) * MagNegCosValue - NewTemp1Y) + (OldMidX << GUI_FIX_DIV_BIT);
				NewFloatY = ((x - OldMidX) * MagNegSinValue + NewTemp2Y) + (OldMidY << GUI_FIX_DIV_BIT);

				if(NewFloatX >= 0 && NewFloatY >= 0){
					//得出反旋转后的坐标整数部分
					NewIntX = NewFloatX >> GUI_FIX_DIV_BIT;
					NewIntY = NewFloatY >> GUI_FIX_DIV_BIT;
					//得出反旋转后坐标的小数部分
					MagFloatX = NewFloatX & GUI_FIX_DIV_1;
					MagFloatY = NewFloatY & GUI_FIX_DIV_1;
					if((NewIntX >= 0) && (NewIntX < pInfo->ImageWidth) && (NewIntY >= 0) && (NewIntY < pInfo->ImageHeight)){
						//(1 - x_float) * (1 - y_float)
						Value1 = (GUI_FIX_DIV - MagFloatX) * (GUI_FIX_DIV - MagFloatY);
						//(1 - x_float) * y_float)
						Value2 = (GUI_FIX_DIV - MagFloatX) * MagFloatY;
						// x_float * (1 - y_float)
						Value3 = MagFloatX * (GUI_FIX_DIV - MagFloatY);
						// x_float * y_float)
						Value4 = MagFloatX * MagFloatY;
						//定位源图像坐标，读取相应坐标的像素值
						//像素F(x,y)
						pColor = pData + ColorBytes * NewIntX + BytesPerLine * NewIntY;
						if(ROTATE_PIXEL_FORMAT_RGB565 == pInfo->PixelFormat){
							ColorRGB565 = (*pColor << 8) | *(pColor + 1);
							r = ((ColorRGB565 >> 11) & 0x1f) << 3;
							g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
							b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
							a = 0xff;
						}else if(ROTATE_PIXEL_FORMAT_ARGB8565 == pInfo->PixelFormat){
							a = *pColor++;
							ColorRGB565 = (*pColor << 8) | *(pColor + 1);
							r = ((ColorRGB565 >> 11) & 0x1f) << 3;
							g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
							b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
						}else if(ROTATE_PIXEL_FORMAT_RGB888 == pInfo->PixelFormat){
							b = *(pColor + 0);
							g = *(pColor + 1);
							r = *(pColor + 2);
							a = 0xff;
						}else{
							b = *(pColor + 0);
							g = *(pColor + 1);
							r = *(pColor + 2);
							a = *(pColor + 3);
						}
						b = (b * Value1) >> (GUI_FIX_DIV_BIT << 1);
						g = (g * Value1) >> (GUI_FIX_DIV_BIT << 1);
						r = (r * Value1) >> (GUI_FIX_DIV_BIT << 1);
						a = (a * Value1) >> (GUI_FIX_DIV_BIT << 1);
						A = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);
						//像素F(x,y+1)
						if(NewIntY + 1 < pInfo->ImageHeight){
							pColor = pData + ColorBytes * NewIntX + BytesPerLine * (NewIntY + 1);
							if(ROTATE_PIXEL_FORMAT_RGB565 == pInfo->PixelFormat){
								ColorRGB565 = (*pColor << 8) | *(pColor + 1);
								r = ((ColorRGB565 >> 11) & 0x1f) << 3;
								g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
								b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
								a = 0xff;
							}else if(ROTATE_PIXEL_FORMAT_ARGB8565 == pInfo->PixelFormat){
								a = *pColor++;
								ColorRGB565 = (*pColor << 8) | *(pColor + 1);
								r = ((ColorRGB565 >> 11) & 0x1f) << 3;
								g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
								b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
							}else if(ROTATE_PIXEL_FORMAT_RGB888 == pInfo->PixelFormat){
								b = *(pColor + 0);
								g = *(pColor + 1);
								r = *(pColor + 2);
								a = 0xff;
							}else{
								b = *(pColor + 0);
								g = *(pColor + 1);
								r = *(pColor + 2);
								a = *(pColor + 3);
							}
							b = (b * Value2) >> (GUI_FIX_DIV_BIT << 1);
							g = (g * Value2) >> (GUI_FIX_DIV_BIT << 1);
							r = (r * Value2) >> (GUI_FIX_DIV_BIT << 1);
							a = (a * Value2) >> (GUI_FIX_DIV_BIT << 1);
							B = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);
						}else{
							B = 0;
						}

						//像素F(x+1,y)
						if(NewIntX + 1 < pInfo->ImageWidth){
							pColor = pData + ColorBytes * (NewIntX + 1) + BytesPerLine * NewIntY;
							if(ROTATE_PIXEL_FORMAT_RGB565 == pInfo->PixelFormat){
								ColorRGB565 = (*pColor << 8) | *(pColor + 1);
								r = ((ColorRGB565 >> 11) & 0x1f) << 3;
								g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
								b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
								a = 0xff;
							}else if(ROTATE_PIXEL_FORMAT_ARGB8565 == pInfo->PixelFormat){
								a = *pColor++;
								ColorRGB565 = (*pColor << 8) | *(pColor + 1);
								r = ((ColorRGB565 >> 11) & 0x1f) << 3;
								g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
								b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
							}else if(ROTATE_PIXEL_FORMAT_RGB888 == pInfo->PixelFormat){
								b = *(pColor + 0);
								g = *(pColor + 1);
								r = *(pColor + 2);
								a = 0xff;
							}else{
								b = *(pColor + 0);
								g = *(pColor + 1);
								r = *(pColor + 2);
								a = *(pColor + 3);
							}
							b = (b * Value3) >> (GUI_FIX_DIV_BIT << 1);
							g = (g * Value3) >> (GUI_FIX_DIV_BIT << 1);
							r = (r * Value3) >> (GUI_FIX_DIV_BIT << 1);
							a = (a * Value3) >> (GUI_FIX_DIV_BIT << 1);
							C = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);
						}else{
							C = 0;
						}

						//像素F(x+1,y+1)
						if((NewIntX + 1 < pInfo->ImageWidth) && (NewIntY + 1 < pInfo->ImageHeight)){
							pColor = pData + ColorBytes * (NewIntX + 1) + BytesPerLine * (NewIntY + 1);
							if(ROTATE_PIXEL_FORMAT_RGB565 == pInfo->PixelFormat){
								ColorRGB565 = (*pColor << 8) | *(pColor + 1);
								r = ((ColorRGB565 >> 11) & 0x1f) << 3;
								g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
								b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
								a = 0xff;
							}else if(ROTATE_PIXEL_FORMAT_ARGB8565 == pInfo->PixelFormat){
								a = *pColor++;
								ColorRGB565 = (*pColor << 8) | *(pColor + 1);
								r = ((ColorRGB565 >> 11) & 0x1f) << 3;
								g = ((ColorRGB565 >> 5 ) & 0x3f) << 2;
								b = ((ColorRGB565 >> 0 ) & 0x1f) << 3;
							}else if(ROTATE_PIXEL_FORMAT_RGB888 == pInfo->PixelFormat){
								b = *(pColor + 0);
								g = *(pColor + 1);
								r = *(pColor + 2);
								a = 0xff;
							}else{
								b = *(pColor + 0);
								g = *(pColor + 1);
								r = *(pColor + 2);
								a = *(pColor + 3);
							}
							b = (b * Value4) >> (GUI_FIX_DIV_BIT << 1);
							g = (g * Value4) >> (GUI_FIX_DIV_BIT << 1);
							r = (r * Value4) >> (GUI_FIX_DIV_BIT << 1);
							a = (a * Value4) >> (GUI_FIX_DIV_BIT << 1);
							D = (((U32)a << 24) |((U32)r << 16) | (g << 8) | b);
						}else{
							D = 0;
						}

						//计算灰度值
						Finally_Color = A + B + C + D;
						b = (Finally_Color >> 0 ) & 0xff;
						g = (Finally_Color >> 8 ) & 0xff;
						r = (Finally_Color >> 16) & 0xff;
						a = (Finally_Color >> 24) & 0xff;
#if (24 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
						Finally_Color = (a << 24) | ((U32)r << 16) | (g << 8) | b;
#elif (16 == LCD_BITSPERPIXEL) && (LCD_SWAP_RB)
						Finally_Color = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3);
						//Color = LCD_L0_Color2Index(((U32)Red << 16) | (Green << 8) | Blue);
#endif
						LCD_SetPixelIndex(PosX + x + OffestX - RotatMinX, PosY + y + OffestY - RotatMinY, Finally_Color, a);
						//LCD_SetPixelIndex(PosX + x + OffestX - RotatMinX, PosY + y + OffestY - RotatMinY, LCD_Color2Index(Finally_Color), (Finally_Color >> 24) & 0xff);
					}
				}
			}
		}
	}
}
#endif
