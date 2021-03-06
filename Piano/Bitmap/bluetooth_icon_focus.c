﻿


#include <stdlib.h>
#include "GUI.h"
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


extern GUI_CONST_STORAGE GUI_BITMAP bmbluetooth_icon_focus;

static GUI_CONST_STORAGE unsigned char _acbluetooth_icon_focus[] = {
  /* RLE: 009 Pixels @ 000,000 */ 0x89, 0x00, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 009,000 */ 0x02, 0x56, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 
  /* RLE: 019 Pixels @ 011,000 */ 0x93, 0x00, 0xFF, 0xFF, 
  /* ABS: 005 Pixels @ 008,001 */ 0x05, 0x0E, 0xFF, 0xFF, 0xDA, 0xFF, 0xFF, 0xD9, 0xFF, 0xFF, 0x6F, 0xFF, 0xFF, 0x10, 0xFF, 0xFF, 
  /* RLE: 017 Pixels @ 013,001 */ 0x91, 0x00, 0xFF, 0xFF, 
  /* ABS: 007 Pixels @ 008,002 */ 0x07, 0x19, 0xFF, 0xFF, 0xF4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCE, 0xFF, 0xFF, 0x59, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 
  /* RLE: 015 Pixels @ 015,002 */ 0x8F, 0x00, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 008,003 */ 0x08, 0x16, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xCB, 0xFF, 0xFF, 0x7C, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB1, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 016,003 */ 0x86, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 000,004 */ 0x03, 0x27, 0xFF, 0xFF, 0x5C, 0xFF, 0xFF, 0x2E, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 003,004 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 010 Pixels @ 008,004 */ 0x0A, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x26, 0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0x92, 0xFF, 0xFF, 0x1D, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 018,004 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 000,005 */ 0x04, 0x9B, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 004,005 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 026 Pixels @ 008,005 */ 0x1A, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x5E, 0xFF, 0xFF, 0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0x70, 0xFF, 0xFF, 0x0D, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
        0x00, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x74, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0xFF, 0xFF, 0x7A, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x16, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 012,006 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 015,006 */ 0x06, 0x20, 0xFF, 0xFF, 0x8C, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCD, 0xFF, 0xFF, 0x57, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 021,006 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 010 Pixels @ 002,007 */ 0x0A, 0x50, 0xFF, 0xFF, 0xEC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA1, 0xFF, 0xFF, 0x0B, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 012,007 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 005 Pixels @ 017,007 */ 0x05, 0x25, 0xFF, 0xFF, 0xAC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAC, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 000,008 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 009 Pixels @ 003,008 */ 0x09, 0x2B, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0x26, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 012,008 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 005 Pixels @ 017,008 */ 0x05, 0x06, 0xFF, 0xFF, 0x7D, 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 000,009 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 004,009 */ 0x08, 0x19, 0xFF, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDA, 0xFF, 0xFF, 0x57, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 012,009 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 016,009 */ 0x06, 0x55, 0xFF, 0xFF, 0xD1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAC, 0xFF, 0xFF, 0x2F, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 000,010 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 016 Pixels @ 005,010 */ 0x10, 0x04, 0xFF, 0xFF, 0x7E, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x38, 0xFF, 0xFF, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xC2, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 
  /* RLE: 008 Pixels @ 021,010 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* ABS: 012 Pixels @ 007,011 */ 0x0C, 0x54, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB9, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0x98, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD1, 0xFF, 0xFF, 0x63, 0xFF, 0xFF, 0x0B, 0xFF, 0xFF, 
  /* RLE: 011 Pixels @ 019,011 */ 0x8B, 0x00, 0xFF, 0xFF, 
  /* ABS: 009 Pixels @ 008,012 */ 0x09, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x77, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE9, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0x14, 0xFF, 0xFF, 
  /* RLE: 013 Pixels @ 017,012 */ 0x8D, 0x00, 0xFF, 0xFF, 
  /* ABS: 007 Pixels @ 008,013 */ 0x07, 0x09, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0x78, 0xFF, 0xFF, 0x17, 0xFF, 0xFF, 
  /* RLE: 015 Pixels @ 015,013 */ 0x8F, 0x00, 0xFF, 0xFF, 
  /* ABS: 007 Pixels @ 008,014 */ 0x07, 0x08, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0x36, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 
  /* RLE: 015 Pixels @ 015,014 */ 0x8F, 0x00, 0xFF, 0xFF, 
  /* ABS: 009 Pixels @ 008,015 */ 0x09, 0x3A, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xE2, 0xFF, 0xFF, 0xCD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0xFF, 0xFF, 0xB2, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 
  /* RLE: 012 Pixels @ 017,015 */ 0x8C, 0x00, 0xFF, 0xFF, 
  /* ABS: 012 Pixels @ 007,016 */ 0x0C, 0x5B, 0xFF, 0xFF, 0xF2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB4, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF, 0x5F, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBD, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 
  /* RLE: 008 Pixels @ 019,016 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* ABS: 016 Pixels @ 005,017 */ 0x10, 0x0B, 0xFF, 0xFF, 0x8C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC4, 0xFF, 0xFF, 0x10, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0x66, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xC6, 0xFF, 0xFF, 0x56, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 021,017 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 004,018 */ 0x08, 0x2B, 0xFF, 0xFF, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 0xF1, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 012,018 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 007 Pixels @ 015,018 */ 0x07, 0x15, 0xFF, 0xFF, 0x60, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0x59, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 000,019 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 009 Pixels @ 003,019 */ 0x09, 0x44, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBD, 0xFF, 0xFF, 0x1D, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 012,019 */ 0x86, 0x00, 0xFF, 0xFF, 
  /* ABS: 016 Pixels @ 018,019 */ 0x10, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xED, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x7E, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x18, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 012,020 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 011 Pixels @ 016,020 */ 0x0B, 0x06, 0xFF, 0xFF, 0x5C, 0xFF, 0xFF, 0xCE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0x72, 0xFF, 0xFF, 0x2C, 0xFF, 0xFF, 0xA0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0x57, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 005,021 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 008,021 */ 0x04, 0x16, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 012,021 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 011 Pixels @ 015,021 */ 0x0B, 0x3C, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0xFF, 0xFF, 0x9F, 0xFF, 0xFF, 0x2F, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x9F, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xD0, 0xFF, 0xFF, 0x27, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 004,022 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 011 Pixels @ 008,022 */ 0x0B, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x17, 0xFF, 0xFF, 0x93, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCE, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 019,022 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 000,023 */ 0x03, 0x08, 0xFF, 0xFF, 0x37, 0xFF, 0xFF, 0x13, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 003,023 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 010 Pixels @ 008,023 */ 0x0A, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB6, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x57, 0xFF, 0xFF, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD8, 0xFF, 0xFF, 0x65, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 
  /* RLE: 012 Pixels @ 018,023 */ 0x8C, 0x00, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 008,024 */ 0x08, 0x16, 0xFF, 0xFF, 0xFA, 0xFF, 0xFF, 0xD8, 0xFF, 0xFF, 0xAB, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xF4, 0xFF, 0xFF, 0x81, 0xFF, 0xFF, 0x17, 0xFF, 0xFF, 
  /* RLE: 014 Pixels @ 016,024 */ 0x8E, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 008,025 */ 0x06, 0x19, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA9, 0xFF, 0xFF, 0x2D, 0xFF, 0xFF, 
  /* RLE: 016 Pixels @ 014,025 */ 0x90, 0x00, 0xFF, 0xFF, 
  /* ABS: 005 Pixels @ 008,026 */ 0x05, 0x0A, 0xFF, 0xFF, 0xB7, 0xFF, 0xFF, 0xB3, 0xFF, 0xFF, 0x49, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 
  /* RLE: 009 Pixels @ 013,026 */ 0x89, 0x00, 0xFF, 0xFF, 
};  //594 pixels compress to 1117 bytes


GUI_CONST_STORAGE GUI_BITMAP bmbluetooth_icon_focus = {
  22,  //xSize
  27,  //ySize
  66,  //ByteBytesPerLine
  24,  //BitsPerPixel
  (unsigned char *)_acbluetooth_icon_focus,  //Pointer to picture data
  NULL,  //Pointer to palette
  GUI_DRAW_AlphaRLEM16M
};  

