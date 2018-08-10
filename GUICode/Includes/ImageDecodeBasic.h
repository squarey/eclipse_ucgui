/*
 * LV_ImageDecodeBasic.h
 *
 *  Created on: 2018年3月26日
 *      Author: Administrator
 */

#ifndef IMAGEDECODEBASIC_H_
#define IMAGEDECODEBASIC_H_
#include "GUI.h"
#include "GUI_PictureMemory.h"

typedef enum
{
	IMAGEVIEW_COLOR_TYPE_NONE,
	IMAGEVIEW_COLOR_TYPE_RGB,
	IMAGEVIEW_COLOR_TYPE_ARGB,
	IMAGEVIEW_COLOR_TYPE_BITMAP,
}ImageViewColorType_em;
typedef enum
{
	IMAGEVIEW_FORMAT_ERROR,
	IMAGEVIEW_FORMAT_PNG,
	IMAGEVIEW_FORMAT_JPG,
	IMAGEVIEW_FORMAT_BMP,
}ImageViewFormat_em;
typedef struct
{
	char* pFile;               	/* full image path. E.g. "U:/my_image.png" */
	I16 Width;                  	/* Width of the image (doubled when upscaled) (Handled by the library) */
	I16 Height;                 	/* Height of the image (doubled when upscaled) (Handled by the library) */
	GUI_COLOR Color;			  	/* Only use by ischange_clolor is 1 */
	ImageViewColorType_em ColorType;
	//ImageViewFormat_em Format;
	U8 ColorDepth;
	U8 *pBuffer;
	U8 IsChangeColor :1;       		/*1: change image color */
	void *pExt;
}ImageViewInfo_t;

typedef U8 (*GUI_ImageDecode)(ImageViewInfo_t *pInfo);
typedef U8 (*GUI_ImageResourceRelease)(ImageViewInfo_t *pInfo);


typedef struct
{
	GUI_ImageDecode			PNGDecode;
	GUI_ImageDecode			JPGDecode;
	GUI_ImageDecode			BMPDecode;
	GUI_ImageResourceRelease	ImageResRelease;
}GUI_ImageDecode_t;


void GUI_ImageDecodeMethodInit(GUI_ImageDecode_t *pMethod);
void GUI_ImageDecodeMehtodRegister(GUI_ImageDecode_t *pMethod);
U8 GUI_ImageDecodeIsSupportPNG(void);
U8 GUI_ImageDecodeIsSupportJPG(void);
U8 GUI_ImageDecodeIsSupportBMP(void);
U8 GUI_ImageDecodePNG(ImageViewInfo_t *pInfo);
U8 GUI_ImageDecodeJPG(ImageViewInfo_t *pInfo);
U8 GUI_ImageDecodeBMP(ImageViewInfo_t *pInfo);
U8 GUI_ImageResRelease(ImageViewInfo_t *pInfo);

ImageViewFormat_em GUI_ImageGetFormat(const char *pPath);

#endif /* LV_IMAGEDECODEBASIC_H_ */
