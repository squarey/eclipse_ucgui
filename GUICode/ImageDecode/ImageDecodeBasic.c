/*
 * GUI_ImageDecodeBasic.c
 *
 *  Created on: 2018年3月26日
 *      Author: Administrator
 */

#include "ImageDecodeBasic.h"

static GUI_ImageDecode_t ImageDecodeMethod;


void GUI_ImageDecodeMethodInit(GUI_ImageDecode_t *pMethod)
{
	pMethod->ImageResRelease = NULL;
	pMethod->PNGDecode = NULL;
	pMethod->JPGDecode = NULL;
	pMethod->BMPDecode = NULL;
}

void GUI_ImageDecodeMehtodRegister(GUI_ImageDecode_t *pMethod)
{
	ImageDecodeMethod.ImageResRelease = pMethod->ImageResRelease;
	ImageDecodeMethod.JPGDecode = pMethod->JPGDecode;
	ImageDecodeMethod.PNGDecode = pMethod->PNGDecode;
	ImageDecodeMethod.BMPDecode = pMethod->BMPDecode;
}

U8 GUI_ImageDecodeIsSupportPNG(void)
{
	if(ImageDecodeMethod.PNGDecode){
		return 1;
	}else{
		return 0;
	}
}

U8 GUI_ImageDecodeIsSupportJPG(void)
{
	if(ImageDecodeMethod.JPGDecode){
		return 1;
	}else{
		return 0;
	}
}
U8 GUI_ImageDecodeIsSupportBMP(void)
{
	if(ImageDecodeMethod.BMPDecode){
		return 1;
	}else{
		return 0;
	}
}

U8 GUI_ImageDecodePNG(ImageViewInfo_t *pInfo)
{
	if(ImageDecodeMethod.PNGDecode){
		return ImageDecodeMethod.PNGDecode(pInfo);
	}else{
		GUI_Debug("Not support png decode\n");
		return 0;
	}

}

U8 GUI_ImageDecodeJPG(ImageViewInfo_t *pInfo)
{
	if(ImageDecodeMethod.JPGDecode){
		return ImageDecodeMethod.JPGDecode(pInfo);
	}
	return 0;
}
U8 GUI_ImageDecodeBMP(ImageViewInfo_t *pInfo)
{
	if(ImageDecodeMethod.BMPDecode){
		return ImageDecodeMethod.BMPDecode(pInfo);
	}
	return 0;
}

U8 GUI_ImageResRelease(ImageViewInfo_t *pInfo)
{
	if(ImageDecodeMethod.ImageResRelease){
		return ImageDecodeMethod.ImageResRelease(pInfo);
	}
	return 0;
}
ImageViewFormat_em GUI_ImageGetFormat(const char *pPath)
{
	if(NULL == pPath){
		return IMAGEVIEW_FORMAT_ERROR;
	}
	if(GUI_strstr(pPath, ".png")){
		return IMAGEVIEW_FORMAT_PNG;
	}else if(GUI_strstr(pPath, ".bmp")){
		return IMAGEVIEW_FORMAT_BMP;
	}else if((GUI_strstr(pPath, ".jpg")) || (GUI_strstr(pPath, ".jpge"))){
		return IMAGEVIEW_FORMAT_JPG;
	}else{
		return IMAGEVIEW_FORMAT_ERROR;
	}
}

