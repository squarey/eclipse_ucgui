/*
 * LV_PNGDecode.h
 *
 *  Created on: 2018��3��25��
 *      Author: Administrator
 */

#ifndef UC_PNGDECODE_H_
#define UC_PNGDECODE_H_

#define USE_UC_LIBPNG_DECODE 1
#if USE_UC_LIBPNG_DECODE != 0

#include "GUI.h"
#include "ImageDecodeBasic.h"

U8 ImageDecodeForPNG(ImageViewInfo_t *pInfo);

#endif
#endif /* UC_PNGDECODE_H_ */
