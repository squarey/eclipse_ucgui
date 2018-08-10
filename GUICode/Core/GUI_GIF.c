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
File        : GUI_GIF.c
Purpose     : Implementation of rendering GIF images
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_ReDefine.h"


#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GIF_INTRO_TERMINATOR ';'
#define GIF_INTRO_EXTENSION  '!'
#define GIF_INTRO_IMAGE      ','

#define GIF_COMMENT     0xFE
#define GIF_APPLICATION 0xFF
#define GIF_PLAINTEXT   0x01
#define GIF_GRAPHICCTL  0xF9

#define MAX_NUM_LWZ_BITS 12

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct
{
	const U8 * pSrc; /* Pointer used for reading the data */
	I32 RemBytes;    /* Number of remaining bytes */
} SOURCE;

typedef struct
{
	I32 XPos;
	I32 YPos;
	I32 XSize;
	I32 YSize;
	I32 Flags;
	I32 NumColors;
} IMAGE_DESCRIPTOR;

typedef struct
{
	U8    aBuffer[258];                     /* Input buffer for data block */
	short aCode  [(1 << MAX_NUM_LWZ_BITS)]; /* This array stores the LZW codes for the compressed strings */
	U8    aPrefix[(1 << MAX_NUM_LWZ_BITS)]; /* Prefix character of the LZW code. */
	U8    aDecompBuffer[3000];              /* Decompression buffer. The higher the compression, the more bytes are needed in the buffer. */
	U8 *  sp;                               /* Pointer into the decompression buffer */
	I32   CurBit;
	I32   LastBit;
	I32   GetDone;
	I32   LastByte;
	I32   ReturnClear;
	I32   CodeSize;
	I32   SetCodeSize;
	I32   MaxCode;
	I32   MaxCodeSize;
	I32   ClearCode;
	I32   EndCode;
	I32   FirstCode;
	I32   OldCode;
} LZW_CONTEXT;

/*********************************************************************
*
*       Static const
*
**********************************************************************
*/
static const I32 _aMaskTbl[16] =
{
	0x0000, 0x0001, 0x0003, 0x0007,
	0x000f, 0x001f, 0x003f, 0x007f,
	0x00ff, 0x01ff, 0x03ff, 0x07ff,
	0x0fff, 0x1fff, 0x3fff, 0x7fff,
};

static const I32 _aInterlaceOffset[] = {  8, 8, 4, 2 };
static const I32 _aInterlaceYPos[]   = {  0, 4, 2, 1 };

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
LZW_CONTEXT _LZWContext;
GUI_COLOR   _aColorTable[256];
SOURCE      _Source;
static U8   _aBuffer[256];

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _ReadU8
*
* Purpose:
*   Reads one byte from the given pointer if possible and increments the pointer
*/
static U8 _ReadU8(void)
{
	U8 Value;
	_Source.RemBytes -= 1;
	if (_Source.RemBytes < 0) {
		return 0;
	}
	Value = *(_Source.pSrc++);
	return Value;
}

/*********************************************************************
*
*       _ReadU16
*
* Purpose:
*   Reads a word from the given pointer if possible and increments the pointer
*/
static U16 _ReadU16(void)
{
	U16 Value;
	U8 Byte0, Byte1;
	Byte0 = _ReadU8();
	Byte1 = _ReadU8();
	Value = (Byte1 << 8) | Byte0;
	return Value;
}

/*********************************************************************
*
*       _ReadBytes
*
* Purpose:
*   Reads a string from the given pointer if possible and increments the pointer
*/
static void _ReadBytes(U8 * pBuffer, I32 Len)
{
	if (_Source.RemBytes < 0) {
		return;
	}
	if (_Source.RemBytes < Len) {
		Len = _Source.RemBytes;
		return;
	}
	_Source.RemBytes -= Len;
	GUI_memcpy(pBuffer, _Source.pSrc, Len);
	_Source.pSrc += Len;
}

/*********************************************************************
*
*       _SkipBytes
*
* Purpose:
*   Skips the number of given bytes and increments the pointer
*/
static void _SkipBytes(I32 Len)
{
	if (_Source.RemBytes < 0) {
		return;
	}
	if (_Source.RemBytes < Len) {
		Len = _Source.RemBytes;
		return;
	}
	_Source.RemBytes -= Len;
	_Source.pSrc += Len;
}

/*********************************************************************
*
*       _InitLWZ
*
* Purpose:
*   Initializes the given LZW with the input code size
*/
static void _InitLZW(I32 InputCodeSize)
{
	GUI__memset((U8 *)&_LZWContext, 0, sizeof(LZW_CONTEXT));
	_LZWContext.SetCodeSize  = InputCodeSize;
	_LZWContext.CodeSize     = InputCodeSize + 1;
	_LZWContext.ClearCode    = (1 << InputCodeSize);
	_LZWContext.EndCode      = (1 << InputCodeSize) + 1;
	_LZWContext.MaxCode      = (1 << InputCodeSize) + 2;
	_LZWContext.MaxCodeSize  = (1 << InputCodeSize) << 1;
	_LZWContext.ReturnClear  = 1;
	_LZWContext.LastByte     = 2;
	_LZWContext.sp           = _LZWContext.aDecompBuffer;
}

/*********************************************************************
*
*       _GetDataBlock
*
* Purpose:
*   Reads a LZW data block. The first byte contains the length of the block,
*   so the maximum length is 256 byte
*
* Return value:
*   Length of the data block
*/
static I32 _GetDataBlock(U8 * pBuffer)
{
	U8 Count;
	Count = _ReadU8(); /* Read the length of the data block */
	if (Count) {
		if (pBuffer) {
			_ReadBytes(pBuffer, Count);
		} else {
			_Source.pSrc += Count;
		}
	}
	return((I32)Count);
}

/*********************************************************************
*
*       _GetNextCode
*
* Purpose:
*   Returns the next LZW code from the LZW stack. One LZW code contains up to 12 bits.
*
* Return value:
*   >= 0 if succeed
*   <  0 if not succeed
*/
static I32 _GetNextCode(void)
{
	I32 i, j, End;
	long Result;
	if (_LZWContext.ReturnClear) {
		/* The first code should be a clear code. */
		_LZWContext.ReturnClear = 0;
		return _LZWContext.ClearCode;
	}
	End = _LZWContext.CurBit + _LZWContext.CodeSize;
	if (End >= _LZWContext.LastBit) {
		I32 Count;
		if (_LZWContext.GetDone) {
			return -1; /* Error */
		}
		_LZWContext.aBuffer[0] = _LZWContext.aBuffer[_LZWContext.LastByte - 2];
		_LZWContext.aBuffer[1] = _LZWContext.aBuffer[_LZWContext.LastByte - 1];
		if ((Count = _GetDataBlock(&_LZWContext.aBuffer[2])) == 0) {
			_LZWContext.GetDone = 1;
		}
		if (Count < 0) {
			return -1; /* Error */
		}
		_LZWContext.LastByte = 2 + Count;
		_LZWContext.CurBit   = (_LZWContext.CurBit - _LZWContext.LastBit) + 16;
		_LZWContext.LastBit  = (2 + Count) * 8 ;
		End                  = _LZWContext.CurBit + _LZWContext.CodeSize;
	}
	j = End >> 3;
	i = _LZWContext.CurBit >> 3;
	if (i == j) {
		Result = (long)_LZWContext.aBuffer[i];
	} else if (i + 1 == j) {
		Result = (long)_LZWContext.aBuffer[i] | ((long)_LZWContext.aBuffer[i + 1] << 8);
	}  else {
		Result = (long)_LZWContext.aBuffer[i] | ((long)_LZWContext.aBuffer[i + 1] << 8) | ((long)_LZWContext.aBuffer[i + 2] << 16);
	}
	Result = (Result >> (_LZWContext.CurBit & 0x7)) & _aMaskTbl[_LZWContext.CodeSize];
	_LZWContext.CurBit += _LZWContext.CodeSize;
	return (I32)Result;
}

/*********************************************************************
*
*       _GetNextByte
*
* Purpose:
*   Reads the next LZW code from the LZW stack and returns the first byte from the LZW code.
*
* Return value:
*   >= 0 if succeed
*   -1   if not succeed
*   -2   if end code has been read
*/
static I32 _GetNextByte(void)
{
	I32 i, Code, Incode;
	while ((Code = _GetNextCode()) >= 0) {
		if (Code == _LZWContext.ClearCode) {
			/* Corrupt GIFs can make this happen */
			if (_LZWContext.ClearCode >= (1 << MAX_NUM_LWZ_BITS)) {
				return -1; /* Error */
			}
			/* Clear the tables */
			GUI__memset((U8 *)_LZWContext.aCode, 0, sizeof(_LZWContext.aCode));
			for (i = 0; i < _LZWContext.ClearCode; ++i) {
				_LZWContext.aPrefix[i] = i;
			}
			/* Calculate the 'special codes' in dependence of the initial code size
				and initialize the stack pointer */
			_LZWContext.CodeSize    = _LZWContext.SetCodeSize + 1;
			_LZWContext.MaxCodeSize = _LZWContext.ClearCode << 1;
			_LZWContext.MaxCode     = _LZWContext.ClearCode + 2;
			_LZWContext.sp          = _LZWContext.aDecompBuffer;
			/* Read the first code from the stack after clearing and initializing */
			do {
				_LZWContext.FirstCode = _GetNextCode();
			} while (_LZWContext.FirstCode == _LZWContext.ClearCode);
			_LZWContext.OldCode = _LZWContext.FirstCode;
			return _LZWContext.FirstCode;
		}
		if (Code == _LZWContext.EndCode) {
			return -2; /* End code */
		}
		Incode = Code;
		if (Code >= _LZWContext.MaxCode) {
			*(_LZWContext.sp)++ = _LZWContext.FirstCode;
			Code = _LZWContext.OldCode;
		}
		while (Code >= _LZWContext.ClearCode) {
			*(_LZWContext.sp)++ = _LZWContext.aPrefix[Code];
			if (Code == _LZWContext.aCode[Code]) {
				return Code;
			}
			if ((_LZWContext.sp - _LZWContext.aDecompBuffer) >= sizeof(_LZWContext.aDecompBuffer)) {
				return Code;
			}
			Code = _LZWContext.aCode[Code];
		}
		*(_LZWContext.sp)++ = _LZWContext.FirstCode = _LZWContext.aPrefix[Code];
		if ((Code = _LZWContext.MaxCode) < (1 << MAX_NUM_LWZ_BITS)) {
			_LZWContext.aCode  [Code] = _LZWContext.OldCode;
			_LZWContext.aPrefix[Code] = _LZWContext.FirstCode;
			++_LZWContext.MaxCode;
			if ((_LZWContext.MaxCode >= _LZWContext.MaxCodeSize) && (_LZWContext.MaxCodeSize < (1 << MAX_NUM_LWZ_BITS))) {
				_LZWContext.MaxCodeSize <<= 1;
				++_LZWContext.CodeSize;
			}
		}
		_LZWContext.OldCode = Incode;
		if (_LZWContext.sp > _LZWContext.aDecompBuffer) {
			return *--(_LZWContext.sp);
		}
	}
	return Code;
}

/*********************************************************************
*
*       _ReadExtension
*
* Purpose:
*   Reads an extension block. One extension block can consist of several data blocks.
*   If an unknown extension block occures, the routine failes.
*/
static I32 _ReadExtension(I32 * pTransIndex, GUI_GIF_IMAGE_INFO * pInfo, U8 * pDisposal)
{
	U8 Label;
	Label = _ReadU8();
	switch (Label) {
		case GIF_PLAINTEXT:
		case GIF_APPLICATION:
		case GIF_COMMENT:
			while (_GetDataBlock(_aBuffer) > 0);
			return 0;
		case GIF_GRAPHICCTL:
			if (_GetDataBlock(_aBuffer) != 4) { /* Length of a graphic control block must be 4 */
				return 1;
			}
			if (pInfo) {
				pInfo->Delay    = (_aBuffer[2] << 8) | _aBuffer[1];
			}
			if (pDisposal) {
				*pDisposal = (_aBuffer[0] >> 2) & 0x7;
			}
			if (pTransIndex) {
				if ((_aBuffer[0] & 0x1) != 0) {
					*pTransIndex = _aBuffer[3];
				}
			}
			if (_ReadU8() != 0) { /* Read block terminator */
				return 1;
			}
			return 0;
	}
	return 1; /* Error */
}

/*********************************************************************
*
*       _ReadComment
*
* Purpose:
*   Reads a comment from the extension block if available and returns the number
*   of comment bytes.
*/
static I32 _ReadComment(U8 * pBuffer, I32 MaxSize, I32 * pSize)
{
	U8 Label;
	I32 Size;
	Label = _ReadU8();
	switch (Label) {
		case GIF_PLAINTEXT:
		case GIF_APPLICATION:
			while (_GetDataBlock(_aBuffer) > 0);
			return 0;
		case GIF_COMMENT:
			Size = _GetDataBlock(_aBuffer);
			if (Size > MaxSize) {
				Size = MaxSize;
			}
			if (pBuffer) {
				*pSize = Size;
				GUI_memcpy(pBuffer, _aBuffer, Size);
			}
			return 0;
		case GIF_GRAPHICCTL:
			if (_GetDataBlock(_aBuffer) != 4) { /* Length of a graphic control block must be 4 */
				return 1;
			}
			if (_ReadU8() != 0) { /* Read block terminator, must be 0 */
				return 1;
			}
			return 0;
	}
	return 1; /* Error */
}

/*********************************************************************
*
*       _DispGIFImage
*
* Purpose:
*   This routine draws a GIF image from the current pointer which should point to a
*   valid GIF data block. The size of the desired image is given in the image descriptor.
*
* Return value:
*   0 if succeed
*   1 if not succeed
*
* Parameters:
*   pDescriptor  - Points to a IMAGE_DESCRIPTOR structure, which contains infos about size, colors and interlacing.
*   x0, y0       - Obvious.
*   Transparency - Color index which should be treated as transparent.
*   Disposal     - Contains the disposal method of the previous image. If Disposal == 2, the transparent pixels
*                  of the image are rendered with the background color.
*/
static I32 _DispGIFImage(IMAGE_DESCRIPTOR * pDescriptor, I32 x0, I32 y0, I32 Transparency, I32 Disposal)
{
	I32 Codesize, Index, OldIndex, XPos, YPos, YCnt, Pass, Interlace, XEnd;
	I32 Width, Height, NumColors, Cnt, BkColorIndex, ColorIndex;
	LCD_LOGPALETTE LogPalette;
	const LCD_PIXELINDEX * pTrans;
	Width     = pDescriptor->XSize;
	Height    = pDescriptor->YSize;
	NumColors = pDescriptor->NumColors;
	XEnd      = Width + x0 - 1;
	BkColorIndex = LCD_GetBkColorIndex();
	/* Get color translation table  */
	LogPalette.NumEntries  = NumColors;
	LogPalette.HasTrans    = 0;
	LogPalette.pPalEntries = _aColorTable;
	if ((pTrans = LCD_GetpPalConvTable((const LCD_LOGPALETTE *)&LogPalette)) == NULL) {
		return 1; /* Error */
	}
	Codesize  = _ReadU8();                 /* Read the LZW codesize */
	_InitLZW(Codesize);                    /* Initialize the LZW stack with the LZW codesize */
	Interlace = pDescriptor->Flags & 0x40; /* Evaluate if image is interlaced */
	for (YCnt = 0, YPos = y0, Pass = 0; YCnt < Height; YCnt++) {
		Cnt      = 0;
		OldIndex = -1;
		for (XPos = x0; XPos <= XEnd; XPos++) {
			if (_LZWContext.sp > _LZWContext.aDecompBuffer) {
				Index = *--(_LZWContext.sp);
			} else {
				Index = _GetNextByte();
			}
			if (Index == -2) {
				return 0; /* End code */
			}
			if ((Index < 0) || (Index >= NumColors)) {
				/* If Index out of legal range stop decompressing */
				return 1; /* Error */
			}
				/* If current index equals old index increment counter */
			if ((Index == OldIndex) && (XPos <= XEnd)) {
				Cnt++;
			} else {
				if (Cnt) {
					if (OldIndex != Transparency) {
						LCD_SetColorIndex(*(pTrans + OldIndex));
						LCD_DrawHLine(XPos - Cnt - 1, YPos, XPos - 1);
					} else if (Disposal == 2) {
						LCD_SetColorIndex(BkColorIndex);
						LCD_DrawHLine(XPos - Cnt - 1, YPos, XPos - 1);
					}
					Cnt = 0;
				} else {
					if (OldIndex >= 0) {
						if (OldIndex != Transparency) {
							LCD_SetPixelIndex(XPos - 1, YPos, *(pTrans + OldIndex), 0xff);
						} else if (Disposal == 2) {
							LCD_SetPixelIndex(XPos - 1, YPos, BkColorIndex, 0xff);
						}
					}
				}
			}
			OldIndex = Index;
		}
		if ((OldIndex != Transparency) || (Disposal == 2)) {
			if (OldIndex != Transparency) {
				ColorIndex = *(pTrans + OldIndex);
			} else {
				ColorIndex = BkColorIndex;
			}
			if (Cnt) {
				LCD_SetColorIndex(ColorIndex);
				LCD_DrawHLine(XPos - Cnt - 1, YPos, XPos - 1);
			} else {
				LCD_SetPixelIndex(XEnd, YPos, ColorIndex, 0xff);
			}
		}
		/* Adjust YPos if image is interlaced */
		if (Interlace) {
			YPos += _aInterlaceOffset[Pass];
			if ((YPos - y0) >= Height) {
				++Pass;
				YPos = _aInterlaceYPos[Pass] + y0;
			}
		} else {
			YPos++;
		}
	}
	return 0;
}

/*********************************************************************
*
*       _ReadColorMap
*/
static I32 _ReadColorMap(I32 NumColors)
{
	I32 i;
	for (i = 0; i < NumColors; i++) {
		U8 r, g, b;
		r = _ReadU8 ();
		g = _ReadU8 ();
		b = _ReadU8 ();
		if (_Source.RemBytes < 0) {
			return 1; /* Error */
		}
			_aColorTable[i] = r | ((U16)g << 8) | ((U32)b << 16);
	}
	return 0;
}

/*********************************************************************
*
*       _InitGIFDecoding
*
* Purpose:
*   The routine initializes the static SOURCE structure and checks
*   if the file is a legal GIF file.
*
* Return value:
*   0 on success, 1 on error
*/
static I32 _InitGIFDecoding(const U8 * pData, U32 NumBytes)
{
	U8 acVersion[7] = {0};
	_Source.pSrc     = pData;
	_Source.RemBytes = NumBytes;
	/* Check if the file is a legal GIF file by checking the 6 byte file header */
	_ReadBytes(acVersion, 6); if (!_Source.RemBytes) { return 0; }
	if ( (acVersion[0] != 'G') ||
			(acVersion[1] != 'I') ||
			(acVersion[2] != 'F') ||
			(acVersion[3] != '8') ||
			((acVersion[4] != '7') && (acVersion[4] != '9')) ||
			(acVersion[5] != 'a')) {
		return 1;
	}
	return 0;
}

/*********************************************************************
*
*       _GetImageDimension
*
* Purpose:
*   Reads the image dimension from the logical screen descriptor
*
* Return value:
*   0 on success, 1 on error
*/
static I32 _GetImageDimension(I32 * pxSize, I32 * pySize)
{
	I32 XSize, YSize;
	/* Read image size */
	XSize = _ReadU16();
	YSize = _ReadU16();
	if ((XSize > 2000) || (YSize > 2000)) {
		return 1; /* Error if image is too large */
	}
	if (pxSize) {
		*pxSize = XSize;
	}
	if (pySize) {
		*pySize = YSize;
	}
	return 0;
}

/*********************************************************************
*
*       _GetGlobalColorTable
*
* Purpose:
*   Reads the global color table if there is one. Returns the number of
*   available colors over the pointer pNumColors (can be NULL).
*
* Return value:
*   0 on success, 1 on error
*/
static I32 _GetGlobalColorTable(I32 * pNumColors)
{
	U8 Flags;
	I32 NumColors;
	/* Read flags from logical screen descriptor */
	Flags = _ReadU8 ();
	_ReadU8 ();
	_ReadU8 ();
	if (_Source.RemBytes < 0) {
		return 1; /* Error */
	}
	NumColors = 2 << (Flags & 0x7);
	if (Flags & 0x80) {
		/* Read global color table */
		if (_ReadColorMap(NumColors)) {
			return 1; /* Error */
		}
	}
	if (pNumColors) {
		*pNumColors = NumColors;
	}
	return 0;
}

/*********************************************************************
*
*       _GetSizeAndColorTable
*/
static I32 _GetSizeAndColorTable(const U8 * pData, U32 NumBytes, I32 * pxSize, I32 * pySize, I32 * pNumColors)
{
	/* Initialize decoding */
	if (_InitGIFDecoding(pData, NumBytes)) {
		return 1; /* Error */
	}
	/* Get image size */
	if (_GetImageDimension(pxSize, pySize)) {
		return 1; /* Error */
	}
	/* Get global color table (if available) */
	if (_GetGlobalColorTable(pNumColors)) {
		return 1; /* Error */
	}
	return 0;
}

/*********************************************************************
*
*       _GetGIFInfo
*/
static I32 _GetGIFInfo(const U8 * pData, U32 NumBytes, GUI_GIF_INFO * pInfo)
{
	U8 Flags, Introducer;
	I32 NumColors, ImageCnt;
	/* Initialize decoding and get size and global color table */
	if (_GetSizeAndColorTable(pData, NumBytes, &pInfo->xSize, &pInfo->ySize, &NumColors)) {
		return 1; /* Error */
	}
	ImageCnt = 0;
	/* Iterate over the blocks */
	do {
		Introducer = _ReadU8();
		switch (Introducer) {
			case GIF_INTRO_IMAGE:
				_SkipBytes(8);                /* Skip the first 8 bytes of the image descriptor */
				Flags = _ReadU8();            /* Only 'Flags' are intresting */
				if (Flags & 0x80) {
					_SkipBytes(NumColors * 3);  /* Skip local color table */
				}
				_SkipBytes(1);                /* Skip codesize */
				while (_GetDataBlock(0) > 0); /* Skip data blocks */
				ImageCnt++;
				break;
			case GIF_INTRO_TERMINATOR:
				break;
			case GIF_INTRO_EXTENSION:
				if (_ReadExtension(NULL, NULL, NULL)) { /* Skip image extension */
					return 1;
				}
				break;
			default:
				return 1;
		}
	} while (Introducer != GIF_INTRO_TERMINATOR); /* We do not support more than one image, so stop when the first terminator has been read */
	pInfo->NumImages = ImageCnt;
	return 0;
}

/*********************************************************************
*
*       _GetImageInfo
*/
static I32 _GetImageInfo(const U8 * pData, U32 NumBytes, GUI_GIF_IMAGE_INFO * pInfo, I32 Index)
{
	U8 Flags, Introducer;
	I32 NumColors, ImageCnt;
	/* Initialize decoding and get size and global color table */
	if (_GetSizeAndColorTable(pData, NumBytes, NULL, NULL, &NumColors)) {
		return 1; /* Error */
	}
	ImageCnt = 0;
	/* Iterate over the blocks */
	do {
		Introducer = _ReadU8();
		switch (Introducer) {
			case GIF_INTRO_IMAGE:
				if (Index == ImageCnt) {
					pInfo->xPos  = _ReadU16();
					pInfo->xPos  = _ReadU16();
					pInfo->xSize = _ReadU16();
					pInfo->ySize = _ReadU16();
					return 0;
				}
				_SkipBytes(8);                /* Skip the first 8 bytes of the image descriptor */
				Flags = _ReadU8();            /* Only 'Flags' are intresting */
				if (Flags & 0x80) {
					_SkipBytes(NumColors * 3);  /* Skip local color table */
				}
				_SkipBytes(1);                /* Skip codesize */
				while (_GetDataBlock(0) > 0); /* Skip data blocks */
				ImageCnt++;
				break;
			case GIF_INTRO_TERMINATOR:
				break;
			case GIF_INTRO_EXTENSION:
				if (_ReadExtension(NULL, (Index == ImageCnt) ? pInfo : NULL, NULL)) {
					return 1;
				}
				break;
			default:
				return 1;
		}
	} while (Introducer != GIF_INTRO_TERMINATOR); /* We do not support more than one image, so stop when the first terminator has been read */
	return 0;
}

/*********************************************************************
*
*       _GetGIFComment
*
* Purpose:
*   Returns the given comment of the GIF image.
*
* Parameters:
*   pData            - Pointer to start of the GIF file
*   NumBytes         - Number of bytes in the file
*   pBuffer          - Pointer to buffer to be filled by the routine
*   MaxSize          - Number of bytes in buffer
*   Index            - Index of the comment to be returned
*
* Return value:
*   0 on success, 1 on error
*/
static I32 _GetGIFComment(const U8 * pData, U32 NumBytes, U8 * pBuffer, I32 MaxSize, I32 Index)
{
	U8 Flags, Introducer;
	I32 NumColors, CommentCnt, Size;
	/* Initialize decoding and skip size and global color table */
	if (_GetSizeAndColorTable(pData, NumBytes, NULL, NULL, &NumColors)) {
		return 1; /* Error */
	}
	CommentCnt = Size = 0;
	/* Iterate over the blocks */
	do {
		Introducer = _ReadU8();
		switch (Introducer) {
			case GIF_INTRO_IMAGE:
				_SkipBytes(8);                /* Skip the first 8 bytes of the image descriptor */
				Flags = _ReadU8();            /* Only 'Flags' are intresting */
				if (Flags & 0x80) {
					_SkipBytes(NumColors * 3);  /* Skip local color table */
				}
				_SkipBytes(1);                /* Skip codesize */
				while (_GetDataBlock(0) > 0); /* Skip data blocks */
				break;
			case GIF_INTRO_TERMINATOR:
				break;
			case GIF_INTRO_EXTENSION:
				_ReadComment((Index == CommentCnt) ? pBuffer : NULL, MaxSize, &Size);
				if ((Size) && (Index == CommentCnt)) {
					return 0;
				}
				break;
			default:
				return 1;
		}
	} while (Introducer != GIF_INTRO_TERMINATOR); /* We do not support more than one image, so stop when the first terminator has been read */
	return 1;
}

/*********************************************************************
*
*       _ClearUnusedPixels
*
* Purpose:
*   Clears the pixels between the border of the previous drawn image and
*   the current image.
*/
static void _ClearUnusedPixels(I32 x0, I32 y0, IMAGE_DESCRIPTOR * pDescriptor, GUI_GIF_IMAGE_INFO * pInfo)
{
	LCD_SetColorIndex(LCD_GetBkColorIndex());
	if (pDescriptor->YPos > pInfo->yPos) {
		LCD_FillRect(x0 + pInfo->xPos,
						y0 + pInfo->yPos,
						x0 + pInfo->xPos + pInfo->xSize - 1,
						y0 + pDescriptor->YPos - 1);
	}
	if (pDescriptor->XPos > pInfo->xPos) {
		LCD_FillRect(x0 + pInfo->xPos,
						y0 + pInfo->yPos,
						x0 + pDescriptor->XPos - 1,
						y0 + pInfo->yPos + pInfo->ySize - 1);
	}
	if ((pDescriptor->YPos + pDescriptor->YSize) < (pInfo->yPos + pInfo->ySize)) {
		LCD_FillRect(x0 + pInfo->xPos,
						y0 + pDescriptor->YPos + pDescriptor->YSize - 1,
						x0 + pInfo->xPos + pInfo->xSize - 1,
						y0 + pInfo->yPos + pInfo->ySize - 1);
	}
	if ((pDescriptor->XPos + pDescriptor->XSize) < (pInfo->xPos + pInfo->xSize)) {
		LCD_FillRect(x0 + pDescriptor->XPos + pDescriptor->XSize - 1,
						y0 + pInfo->yPos,
						x0 + pInfo->xPos + pInfo->xSize - 1,
						y0 + pInfo->yPos + pInfo->ySize - 1);
	}
}

/*********************************************************************
*
*       _DrawGIFImage
*
* Purpose:
*   Draws the given sub image of a GIF file.
*
* Parameters:
*   pData    - Pointer to start of the GIF file
*   NumBytes - Number of bytes in the file
*   x0       - Drawing position x
*   y0       - Drawing position y
*   Index    - Index of sub image to be drawn
*
* Return value:
*   0 on success, 1 on error
*/
static I32 _DrawGIFImage(const U8 * pData, U32 NumBytes, I32 x0, I32 y0, I32 Index)
{
	U8 Disposal;
	I32 XSize, YSize, TransIndex, ImageCnt;
	IMAGE_DESCRIPTOR Descriptor = {0};
	GUI_GIF_IMAGE_INFO Info = {0};
	U8 Introducer;
	ImageCnt   =  0;
	TransIndex = -1;
	/* Initialize decoding and get size and global color table */
	if (_GetSizeAndColorTable(pData, NumBytes, &XSize, &YSize, &Descriptor.NumColors)) {
		return 1; /* Error */
	}
	/* Iterate over the blocks */
	do {
		Introducer = _ReadU8();
		switch (Introducer) {
			case GIF_INTRO_IMAGE:
				/* Read image descriptor */
				Descriptor.XPos  = _ReadU16();
				Descriptor.YPos  = _ReadU16();
				Descriptor.XSize = _ReadU16();
				Descriptor.YSize = _ReadU16();
				Descriptor.Flags = _ReadU8 ();
				if (_Source.RemBytes < 0) {
					return 1; /* Error */
				}
				if (Descriptor.Flags & 0x80) {
					/* Read local color table */
					if (_ReadColorMap(Descriptor.NumColors)) {
						return 1; /* Error */
					}
				}
				if (ImageCnt == Index - 1) {
					Info.xPos  = Descriptor.XPos;
					Info.yPos  = Descriptor.YPos;
					Info.xSize = Descriptor.XSize;
					Info.ySize = Descriptor.YSize;
				}
				if (Index == ImageCnt) {
					if (Disposal == 2) {
						_ClearUnusedPixels(x0, y0, &Descriptor, &Info);
					}
					if (_DispGIFImage(&Descriptor, x0 + Descriptor.XPos, y0 + Descriptor.YPos, TransIndex, Disposal)) {
						return 1; /* Error */
					}
					if (_ReadU8() != 0) {
						return 1; /* Error */
					}
					return 0;
				} else {
					_ReadU8();                    /* Skip codesize */
					while (_GetDataBlock(0) > 0); /* Skip data blocks */
				}
				ImageCnt++;
				break;
			case GIF_INTRO_TERMINATOR:
				break;
			case GIF_INTRO_EXTENSION:
				/* Read image extension */
				if (_ReadExtension(&TransIndex, (Index == ImageCnt) ? &Info : NULL, (Index == ImageCnt) ? &Disposal : NULL)) {
					return 1;
				}
				break;
			default:
				return 1;
		}
	} while (Introducer != GIF_INTRO_TERMINATOR); /* We do not support more than one image, so stop when the first terminator has been read */
	return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GIF_GetXSize
*
* Purpose:
*   Returns the XSize of the given GIF image without further tests.
*/
I32 GUI_GIF_GetXSize(const void * pGIF)
{
	const U8 * pSrc;
	if (!pGIF) {
		return 0;
	}
	pSrc = (const U8 *)pGIF + 6;
	return GUI__Read16(&pSrc);
}

/*********************************************************************
*
*       GUI_GIF_GetYSize
*
* Purpose:
*   Returns the YSize of the given GIF image without further tests.
*/
I32 GUI_GIF_GetYSize(const void * pGIF)
{
	const U8 * pSrc;
	if (!pGIF) {
		return 0;
	}
	pSrc = (const U8 *)pGIF + 8;
	return GUI__Read16(&pSrc);
}

/*********************************************************************
*
*       GUI_GIF_DrawEx
*/
I32 GUI_GIF_DrawEx(const void * pGIF, U32 NumBytes, I32 x0, I32 y0, I32 Index)
{
	const U8 * pSrc;
	I32 Result, OldColorIndex;
#if (GUI_WINSUPPORT)
	I32 Width, Height;
	GUI_RECT r;
	Width  = GUI_GIF_GetXSize(pGIF);
	Height = GUI_GIF_GetYSize(pGIF);
#endif
	OldColorIndex = LCD_GetColorIndex();
	pSrc          = (const U8 *)pGIF;
#if (GUI_WINSUPPORT)
	WM_ADDORG(x0,y0);
	r.x1 = (r.x0 = x0) + Width - 1;
	r.y1 = (r.y0 = y0) + Height - 1;
#endif
	Result = _DrawGIFImage(pSrc, NumBytes, x0, y0, Index);
	LCD_SetColorIndex(OldColorIndex);
	return Result;
}

/*********************************************************************
*
*       GUI_GIF_Draw
*/
I32 GUI_GIF_Draw(const void * pGIF, U32 NumBytes, I32 x0, I32 y0)
{
	return GUI_GIF_DrawEx(pGIF, NumBytes, x0, y0, 0);
}

/*********************************************************************
*
*       GUI_GIF_GetInfo
*/
I32 GUI_GIF_GetInfo(const void * pGIF, U32 NumBytes, GUI_GIF_INFO * pInfo)
{
	const U8 * pSrc;
	pSrc = (const U8 *)pGIF;
	if (_GetGIFInfo(pSrc, NumBytes, pInfo)) {
		return 1;
	}
	return 0;
}

/*********************************************************************
*
*       GUI_GIF_GetImageInfo
*/
I32 GUI_GIF_GetImageInfo(const void * pGIF, U32 NumBytes, GUI_GIF_IMAGE_INFO * pInfo, I32 Index)
{
	const U8 * pSrc;
	pSrc = (const U8 *)pGIF;
	if (_GetImageInfo(pSrc, NumBytes, pInfo, Index)) {
		return 1;
	}
	return 0;
}

/*********************************************************************
*
*       GUI_GIF_GetComment
*/
I32 GUI_GIF_GetComment(const void * pGIF, U32 NumBytes, U8 * pBuffer, I32 MaxSize, I32 Index)
{
	const U8 * pSrc;
	pSrc = (const U8 *)pGIF;
	if (_GetGIFComment(pSrc, NumBytes, pBuffer, MaxSize, Index)) {
		return 1;
	}
	return 0;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
