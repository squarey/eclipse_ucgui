﻿


#include <stdlib.h>
#include "GUI.h"
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


extern GUI_CONST_STORAGE GUI_BITMAP bmselect_icon;

static GUI_CONST_STORAGE unsigned char _acselect_icon[] = {
  /* RLE: 028 Pixels @ 000,000 */ 0x9C, 0x00, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 028,000 */ 0x04, 0x25, 0x04, 0xDB, 0x9D, 0x04, 0xDB, 0x97, 0x04, 0xDB, 0x19, 0x04, 0xDB, 
  /* RLE: 027 Pixels @ 000,001 */ 0x9B, 0x00, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 027,001 */ 0x05, 0x3E, 0x04, 0xDB, 0xFD, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xE0, 0x04, 0xDB, 
  /* RLE: 026 Pixels @ 000,002 */ 0x9A, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 026,002 */ 0x01, 0x45, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 027,002 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* RLE: 025 Pixels @ 000,003 */ 0x99, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 025,003 */ 0x01, 0x49, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 026,003 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* RLE: 024 Pixels @ 000,004 */ 0x98, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 024,004 */ 0x01, 0x45, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 025,004 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 031,004 */ 0x01, 0xDD, 0x04, 0xDB, 
  /* RLE: 023 Pixels @ 000,005 */ 0x97, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 023,005 */ 0x01, 0x39, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 024,005 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 030,005 */ 0x02, 0xEC, 0x04, 0xDB, 0x21, 0x04, 0xDB, 
  /* RLE: 022 Pixels @ 000,006 */ 0x96, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 022,006 */ 0x01, 0x3F, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 023,006 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 029,006 */ 0x02, 0xEF, 0x04, 0xDB, 0x1D, 0x04, 0xDB, 
  /* RLE: 022 Pixels @ 031,006 */ 0x96, 0x00, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 021,007 */ 0x02, 0x4D, 0x04, 0xDB, 0xF8, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 023,007 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 028,007 */ 0x02, 0xEB, 0x04, 0xDB, 0x21, 0x04, 0xDB, 
  /* RLE: 022 Pixels @ 030,007 */ 0x96, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 020,008 */ 0x01, 0x3C, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 021,008 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 027,008 */ 0x02, 0xF3, 0x04, 0xDB, 0x1C, 0x04, 0xDB, 
  /* RLE: 022 Pixels @ 029,008 */ 0x96, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 019,009 */ 0x01, 0x3D, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 020,009 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 026,009 */ 0x02, 0xEA, 0x04, 0xDB, 0x1E, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 028,009 */ 0x85, 0x00, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 001,010 */ 0x03, 0x16, 0x04, 0xDB, 0x6B, 0x04, 0xDB, 0x47, 0x04, 0xDB, 
  /* RLE: 014 Pixels @ 004,010 */ 0x8E, 0x00, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 018,010 */ 0x02, 0x44, 0x04, 0xDB, 0xFE, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 020,010 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 025,010 */ 0x02, 0xE4, 0x04, 0xDB, 0x1F, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 027,010 */ 0x85, 0x00, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 000,011 */ 0x05, 0x39, 0x04, 0xDB, 0xF2, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0x82, 0x04, 0xDB, 
  /* RLE: 012 Pixels @ 005,011 */ 0x8C, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 017,011 */ 0x01, 0x3E, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 018,011 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 024,011 */ 0x02, 0xF0, 0x04, 0xDB, 0x1C, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 026,011 */ 0x86, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 000,012 */ 0x01, 0xDE, 0x04, 0xDB, 
  /* RLE: 004 Pixels @ 001,012 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 005,012 */ 0x01, 0x92, 0x04, 0xDB, 
  /* RLE: 010 Pixels @ 006,012 */ 0x8A, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 016,012 */ 0x01, 0x40, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 017,012 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 023,012 */ 0x02, 0xF7, 0x04, 0xDB, 0x18, 0x04, 0xDB, 
  /* RLE: 007 Pixels @ 025,012 */ 0x87, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 000,013 */ 0x01, 0xF1, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 001,013 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 006,013 */ 0x01, 0x9C, 0x04, 0xDB, 
  /* RLE: 008 Pixels @ 007,013 */ 0x88, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 015,013 */ 0x01, 0x47, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 016,013 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 022,013 */ 0x02, 0xEA, 0x04, 0xDB, 0x27, 0x04, 0xDB, 
  /* RLE: 008 Pixels @ 024,013 */ 0x88, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 000,014 */ 0x01, 0x8D, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 001,014 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 007,014 */ 0x01, 0x91, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 008,014 */ 0x86, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 014,014 */ 0x01, 0x43, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 015,014 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 021,014 */ 0x02, 0xE9, 0x04, 0xDB, 0x2A, 0x04, 0xDB, 
  /* RLE: 010 Pixels @ 023,014 */ 0x8A, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 001,015 */ 0x01, 0x9C, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 002,015 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 008,015 */ 0x01, 0x96, 0x04, 0xDB, 
  /* RLE: 004 Pixels @ 009,015 */ 0x84, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 013,015 */ 0x01, 0x43, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 014,015 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 020,015 */ 0x02, 0xF5, 0x04, 0xDB, 0x16, 0x04, 0xDB, 
  /* RLE: 012 Pixels @ 022,015 */ 0x8C, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 002,016 */ 0x01, 0x97, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 003,016 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 009,016 */ 0x04, 0x96, 0x04, 0xDB, 0x00, 0x04, 0xDB, 0x00, 0x04, 0xDB, 0x4A, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 013,016 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 019,016 */ 0x02, 0xED, 0x04, 0xDB, 0x1F, 0x04, 0xDB, 
  /* RLE: 014 Pixels @ 021,016 */ 0x8E, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 003,017 */ 0x01, 0xA6, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 004,017 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 010,017 */ 0x02, 0x7B, 0x04, 0xDB, 0x38, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 012,017 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 018,017 */ 0x02, 0xEE, 0x04, 0xDB, 0x27, 0x04, 0xDB, 
  /* RLE: 016 Pixels @ 020,017 */ 0x90, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 004,018 */ 0x01, 0xAA, 0x04, 0xDB, 
  /* RLE: 012 Pixels @ 005,018 */ 0x8C, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 017,018 */ 0x02, 0xF2, 0x04, 0xDB, 0x22, 0x04, 0xDB, 
  /* RLE: 018 Pixels @ 019,018 */ 0x92, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 005,019 */ 0x01, 0xA3, 0x04, 0xDB, 
  /* RLE: 010 Pixels @ 006,019 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 016,019 */ 0x02, 0xEE, 0x04, 0xDB, 0x24, 0x04, 0xDB, 
  /* RLE: 020 Pixels @ 018,019 */ 0x94, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 006,020 */ 0x01, 0x9F, 0x04, 0xDB, 
  /* RLE: 008 Pixels @ 007,020 */ 0x88, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 015,020 */ 0x02, 0xEC, 0x04, 0xDB, 0x1F, 0x04, 0xDB, 
  /* RLE: 022 Pixels @ 017,020 */ 0x96, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 007,021 */ 0x01, 0xA5, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 008,021 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 014,021 */ 0x02, 0xF1, 0x04, 0xDB, 0x1B, 0x04, 0xDB, 
  /* RLE: 024 Pixels @ 016,021 */ 0x98, 0x00, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 008,022 */ 0x01, 0x9E, 0x04, 0xDB, 
  /* RLE: 004 Pixels @ 009,022 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 013,022 */ 0x02, 0xE9, 0x04, 0xDB, 0x20, 0x04, 0xDB, 
  /* RLE: 026 Pixels @ 015,022 */ 0x9A, 0x00, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 009,023 */ 0x05, 0x76, 0x04, 0xDB, 0xAE, 0x04, 0xDB, 0xB7, 0x04, 0xDB, 0x9A, 0x04, 0xDB, 0x1D, 0x04, 0xDB, 
  /* RLE: 018 Pixels @ 014,023 */ 0x92, 0x00, 0x04, 0xDB, 
};  //768 pixels compress to 575 bytes


GUI_CONST_STORAGE GUI_BITMAP bmselect_icon = {
  32,  //xSize
  24,  //ySize
  96,  //ByteBytesPerLine
  24,  //BitsPerPixel
  (unsigned char *)_acselect_icon,  //Pointer to picture data
  NULL,  //Pointer to palette
  GUI_DRAW_AlphaRLEM16M
};  

