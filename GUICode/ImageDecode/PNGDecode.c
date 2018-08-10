/*
 * LV_PNGDecode.c
 *
 *  Created on: 2018��3��25��
 *      Author: Administrator
 */
#include "PNGDecode.h"
#if USE_UC_LIBPNG_DECODE != 0
#include <stdlib.h>
#include "png.h"


#define PNG_BYTES_TO_CHECK 4

U8 ImageDecodeForPNG(ImageViewInfo_t *pInfo)
{
	if((NULL == pInfo) || (NULL == pInfo->pFile)){
		GUI_Debug("pFile is null\n");
		return 0;
	}else{
		FILE 		*pic_fp;
		png_structp png_ptr;
		png_infop  	info_ptr;
		I8     	buf[PNG_BYTES_TO_CHECK];
		I32    	temp;
		U32 	buffer_size;
		U32 	rows_bytes;
		U8		Type = 0;
		//I32 ColorType,channels;
		//U8 bit_depth;
		//GUI_Debug("ext->FilePath:%s\n",ext->PNGInfo.FilePath);
		/*if(false == LV_PNGIsSymbol(pInfo->FilePath)){
			//GUI_Debug("png path is error, please check!\n");
			return LV_RES_INV;
		}*/
		pic_fp = fopen(pInfo->pFile, "rb");
		if(pic_fp == NULL)
		{
			 GUI_Debug("open %s fail\n",pInfo->pFile);
			 return 0;
		}
		GUI_Debug("Decoude file %s\n", pInfo->pFile);
		 png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		 info_ptr = png_create_info_struct(png_ptr);
		 setjmp(png_jmpbuf(png_ptr));
		 temp = fread(buf,1,PNG_BYTES_TO_CHECK,pic_fp);
		 //GUI_Debug("temp:%d\n",temp);
		 temp = png_sig_cmp((void*)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
		 if(temp != 0)
		 {
			 //GUI_Debug("The file is not png pic,temp = %d\n",temp);
			 fclose(pic_fp);
			 png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			 return 0;
		 }
		 rewind(pic_fp);
		 png_init_io(png_ptr, pic_fp);
		 //
		 //GUI_Debug("png_read_png\n");

		 png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0 );
		 //png_read_info(png_ptr, info_ptr);
		// png_set_sig_bytes(png_ptr, 8);
		 pInfo->Width 		= png_get_image_width(png_ptr, info_ptr);
		 pInfo->Height 		= png_get_image_height(png_ptr, info_ptr);
		 //pInfo->ColorDepth	= png_get_bit_depth(png_ptr, info_ptr); /* ��ȡλ�� */
		 Type 				= png_get_color_type(png_ptr, info_ptr); /*��ɫ����*/
		 rows_bytes 		= png_get_rowbytes(png_ptr, info_ptr);
		 buffer_size 		= rows_bytes * pInfo->Height;
		 //pInfo->pBuffer 		= (U8 *)malloc(buffer_size);
		 pInfo->pBuffer 		= (U8 *)GUI_PicMemoryAlloc(buffer_size);
		 if(PNG_COLOR_TYPE_RGB_ALPHA == Type){
			 pInfo->ColorDepth = 32;
			 pInfo->ColorType = IMAGEVIEW_COLOR_TYPE_ARGB;
		 }else if(PNG_COLOR_TYPE_RGB == Type){
			 pInfo->ColorDepth = 24;
			 pInfo->ColorType = IMAGEVIEW_COLOR_TYPE_RGB;
		 }
		 if(NULL == pInfo->pBuffer){
			 GUI_Debug("malloc for png decode fail\n");
		 }else{
			 U32 i = 0;
			 png_bytep* row_pointers;
			 row_pointers = png_get_rows( png_ptr, info_ptr );
			 for(i = 0; i < pInfo->Height; i++){
				 GUI_memcpy( pInfo->pBuffer + i * rows_bytes, row_pointers[i], rows_bytes);
				 //png_read_rows(png_ptr, &ext->Buffer[i], NULL, 1);
			 }
			 //png_read_end(png_ptr, info_ptr);
		 }
		 png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		 fclose(pic_fp);
		 {
			PicMemoryMonitor_t Monitor;
			GUI_PicMemoryGetMonitor(&Monitor);
			GUI_Debug("----------------------------------------------\n");
			GUI_Debug("TotalSize:%d, FreeCount:%d, FreeSize:%d, FreeBiggestSize:%d\n", Monitor.TotalSize, Monitor.FreeCount, Monitor.FreeSize, Monitor.FreeBiggestSize);
			GUI_Debug("UsedCount:%d, UsedPercent:%d, FragPercent:%d\n", Monitor.UsedCount, Monitor.UsedPercent, Monitor.FragPercent);
			GUI_Debug("----------------------------------------------\n");
		}
		 return 0;
	}
}
#endif

