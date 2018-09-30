﻿


#include <stdlib.h>
#include "GUI.h"
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


extern GUI_CONST_STORAGE GUI_BITMAP bmwifi_level3_open_w;

static GUI_CONST_STORAGE unsigned char _acwifi_level3_open_w[] = {
  /* RLE: 498 Pixels @ 000,000 */ 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xF5, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 018,010 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 021,010 */ 0x86, 0x01, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 027,010 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 032 Pixels @ 030,010 */ 0xA0, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 014,011 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 001 Pixels @ 017,011 */ 0x01, 0x01, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 018,011 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 021,011 */ 0x86, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 027,011 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 001 Pixels @ 030,011 */ 0x01, 0x01, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 031,011 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 025 Pixels @ 034,011 */ 0x99, 0x00, 0x00, 0x00, 
  /* ABS: 004 Pixels @ 011,012 */ 0x04, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 015,012 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 010 Pixels @ 019,012 */ 0x0A, 0x01, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x0D, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x14, 0xFF, 0xFF, 0x14, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x0D, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 029,012 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 033,012 */ 0x04, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 020 Pixels @ 037,012 */ 0x94, 0x00, 0x00, 0x00, 
  /* ABS: 030 Pixels @ 009,013 */ 0x1E, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x0E, 0xFF, 0xFF, 0x23, 0xFF, 0xFF, 0x32, 0xFF, 0xFF, 0x40, 0xFF, 0xFF, 0x49, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 
        0x4D, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x49, 0xFF, 0xFF, 0x40, 0xFF, 0xFF, 0x32, 0xFF, 0xFF, 0x23, 0xFF, 0xFF, 0x0E, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
        0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 016 Pixels @ 039,013 */ 0x90, 0x00, 0x00, 0x00, 
  /* ABS: 015 Pixels @ 007,014 */ 0x0F, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF, 0x25, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 
        0x4E, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 022,014 */ 0x84, 0x4D, 0xFF, 0xFF, 
  /* ABS: 015 Pixels @ 026,014 */ 0x0F, 0x4E, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x25, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 
        0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 013 Pixels @ 041,014 */ 0x8D, 0x00, 0x00, 0x00, 
  /* RLE: 005 Pixels @ 006,015 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 011,015 */ 0x06, 0x0D, 0xFF, 0xFF, 0x31, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 
  /* RLE: 014 Pixels @ 017,015 */ 0x8E, 0x4C, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 031,015 */ 0x06, 0x4D, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x31, 0xFF, 0xFF, 0x0D, 0xFF, 0xFF, 
  /* RLE: 005 Pixels @ 037,015 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* RLE: 013 Pixels @ 042,015 */ 0x8D, 0x00, 0x00, 0x00, 
  /* ABS: 034 Pixels @ 007,016 */ 0x22, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0x2B, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 
        0x4E, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 
        0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x2B, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 012 Pixels @ 041,016 */ 0x8C, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 005,017 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 032 Pixels @ 008,017 */ 0x20, 0x14, 0xFF, 0xFF, 0x44, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 
        0x42, 0xFF, 0xFF, 0x3B, 0xFF, 0xFF, 0x37, 0xFF, 0xFF, 0x39, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 0x42, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 
        0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x44, 0xFF, 0xFF, 0x14, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 040,017 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 010 Pixels @ 043,017 */ 0x8A, 0x00, 0x00, 0x00, 
  /* ABS: 038 Pixels @ 005,018 */ 0x26, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x12, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x3A, 0xFF, 0xFF, 
        0x22, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x22, 0xFF, 0xFF, 0x3A, 0xFF, 0xFF, 
        0x4D, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x12, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 
  /* RLE: 010 Pixels @ 043,018 */ 0x8A, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 005,019 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 035 Pixels @ 008,019 */ 0x23, 0x32, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 0x27, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0x35, 0xFF, 0xFF, 
        0x40, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0x40, 0xFF, 0xFF, 0x35, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x27, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 
        0x53, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x32, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 011 Pixels @ 043,019 */ 0x8B, 0x00, 0x00, 0x00, 
  /* ABS: 016 Pixels @ 006,020 */ 0x10, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x28, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x29, 0xFF, 0xFF, 0x45, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 
        0x53, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 022,020 */ 0x84, 0x4E, 0xFF, 0xFF, 
  /* ABS: 016 Pixels @ 026,020 */ 0x10, 0x50, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x45, 0xFF, 0xFF, 0x29, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x28, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 
        0x03, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 011 Pixels @ 042,020 */ 0x8B, 0x00, 0x00, 0x00, 
  /* ABS: 013 Pixels @ 005,021 */ 0x0D, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x45, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0x2F, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 
  /* RLE: 012 Pixels @ 018,021 */ 0x8C, 0x4C, 0xFF, 0xFF, 
  /* ABS: 013 Pixels @ 030,021 */ 0x0D, 0x4F, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x2F, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x45, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 011 Pixels @ 043,021 */ 0x8B, 0x00, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 006,022 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 028 Pixels @ 010,022 */ 0x1C, 0x0B, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0x1B, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 
        0x4F, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x1B, 0xFF, 0xFF, 
        0x05, 0xFF, 0xFF, 0x0B, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 038,022 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* RLE: 013 Pixels @ 042,022 */ 0x8D, 0x00, 0x00, 0x00, 
  /* ABS: 034 Pixels @ 007,023 */ 0x22, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 
        0x55, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x50, 0xFF, 0xFF, 0x55, 0xFF, 0xFF, 0x53, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 0x4D, 0xFF, 0xFF, 
        0x4B, 0xFF, 0xFF, 0x4F, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x11, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 015 Pixels @ 041,023 */ 0x8F, 0x00, 0x00, 0x00, 
  /* ABS: 013 Pixels @ 008,024 */ 0x0D, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x25, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x54, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x30, 0xFF, 0xFF, 0x13, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 021,024 */ 0x86, 0x06, 0xFF, 0xFF, 
  /* ABS: 013 Pixels @ 027,024 */ 0x0D, 0x13, 0xFF, 0xFF, 0x30, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x54, 0xFF, 0xFF, 0x4E, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x4C, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x25, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 018 Pixels @ 040,024 */ 0x92, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 010,025 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 022 Pixels @ 013,025 */ 0x16, 0x31, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x1E, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x14, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0x70, 0xFF, 0xFF, 0x90, 0xFF, 0xFF, 0x9E, 0xFF, 0xFF, 0x9E, 0xFF, 0xFF, 0x90, 0xFF, 0xFF, 
        0x70, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0x14, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x1E, 0xFF, 0xFF, 0x4A, 0xFF, 0xFF, 0x51, 0xFF, 0xFF, 0x52, 0xFF, 0xFF, 0x30, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 035,025 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 019 Pixels @ 038,025 */ 0x93, 0x00, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 009,026 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 022 Pixels @ 013,026 */ 0x16, 0x02, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 0x33, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0x82, 0xFF, 0xFF, 0xC1, 0xFF, 0xFF, 0xD5, 0xFF, 0xFF, 0xD9, 0xFF, 0xFF, 0xD4, 0xFF, 0xFF, 0xD2, 0xFF, 0xFF, 0xD2, 0xFF, 0xFF, 0xD4, 0xFF, 0xFF, 
        0xD9, 0xFF, 0xFF, 0xD5, 0xFF, 0xFF, 0xC1, 0xFF, 0xFF, 0x82, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x33, 0xFF, 0xFF, 0x3C, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 035,026 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* RLE: 019 Pixels @ 039,026 */ 0x93, 0x00, 0x00, 0x00, 
  /* RLE: 004 Pixels @ 010,027 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 014,027 */ 0x08, 0x03, 0xFF, 0xFF, 0x0C, 0xFF, 0xFF, 0x6E, 0xFF, 0xFF, 0xCB, 0xFF, 0xFF, 0xD7, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0xC8, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 022,027 */ 0x84, 0xC8, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 026,027 */ 0x08, 0xC6, 0xFF, 0xFF, 0xC8, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0xD7, 0xFF, 0xFF, 0xCB, 0xFF, 0xFF, 0x6E, 0xFF, 0xFF, 0x0C, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 034,027 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* RLE: 021 Pixels @ 038,027 */ 0x95, 0x00, 0x00, 0x00, 
  /* ABS: 026 Pixels @ 011,028 */ 0x1A, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x28, 0xFF, 0xFF, 0xD0, 0xFF, 0xFF, 0xCE, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xCA, 0xFF, 0xFF, 0xC8, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xC8, 0xFF, 0xFF, 
        0xC8, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xC8, 0xFF, 0xFF, 0xCA, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 0xCE, 0xFF, 0xFF, 0xD0, 0xFF, 0xFF, 0x28, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 024 Pixels @ 037,028 */ 0x98, 0x00, 0x00, 0x00, 
  /* ABS: 022 Pixels @ 013,029 */ 0x16, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x46, 0xFF, 0xFF, 0xD1, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xD2, 0xFF, 0xFF, 0xDB, 0xFF, 0xFF, 0xD9, 0xFF, 0xFF, 0xD9, 0xFF, 0xFF, 0xDB, 0xFF, 0xFF, 
        0xD2, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xD1, 0xFF, 0xFF, 0x46, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 026 Pixels @ 035,029 */ 0x9A, 0x00, 0x00, 0x00, 
  /* ABS: 022 Pixels @ 013,030 */ 0x16, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x67, 0xFF, 0xFF, 0xD6, 0xFF, 0xFF, 0xD0, 0xFF, 0xFF, 0xD2, 0xFF, 0xFF, 0xA1, 0xFF, 0xFF, 0x62, 0xFF, 0xFF, 0x45, 0xFF, 0xFF, 0x45, 0xFF, 0xFF, 0x62, 0xFF, 0xFF, 
        0xA0, 0xFF, 0xFF, 0xD2, 0xFF, 0xFF, 0xD0, 0xFF, 0xFF, 0xD6, 0xFF, 0xFF, 0x67, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 026 Pixels @ 035,030 */ 0x9A, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 013,031 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 016 Pixels @ 016,031 */ 0x10, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x85, 0xFF, 0xFF, 0xAE, 0xFF, 0xFF, 0x29, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0x30, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x4B, 0xFF, 0xFF, 0x30, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0x29, 0xFF, 0xFF, 0xAE, 0xFF, 0xFF, 
        0x85, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 032,031 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 027 Pixels @ 035,031 */ 0x9B, 0x00, 0x00, 0x00, 
  /* ABS: 020 Pixels @ 014,032 */ 0x14, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x0C, 0xFF, 0xFF, 0x0D, 0xFF, 0xFF, 0x46, 0xFF, 0xFF, 0xB2, 0xFF, 0xFF, 0xD3, 0xFF, 0xFF, 0xDA, 0xFF, 0xFF, 0xDA, 0xFF, 0xFF, 0xD3, 0xFF, 0xFF, 0xB0, 0xFF, 0xFF, 
        0x47, 0xFF, 0xFF, 0x0D, 0xFF, 0xFF, 0x0C, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 029 Pixels @ 034,032 */ 0x9D, 0x00, 0x00, 0x00, 
  /* ABS: 018 Pixels @ 015,033 */ 0x12, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x0E, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0xD8, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xC6, 0xFF, 0xFF, 0xD9, 0xFF, 0xFF, 0xBC, 0xFF, 0xFF, 
        0x0F, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 031 Pixels @ 033,033 */ 0x9F, 0x00, 0x00, 0x00, 
  /* ABS: 016 Pixels @ 016,034 */ 0x10, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x2A, 0xFF, 0xFF, 0xC4, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xCC, 0xFF, 0xFF, 0xC5, 0xFF, 0xFF, 0x2A, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
        0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 033 Pixels @ 032,034 */ 0xA1, 0x00, 0x00, 0x00, 
  /* ABS: 014 Pixels @ 017,035 */ 0x0E, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0xD1, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xD1, 0xFF, 0xFF, 0x47, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
        0x00, 0xFF, 0xFF, 
  /* RLE: 035 Pixels @ 031,035 */ 0xA3, 0x00, 0x00, 0x00, 
  /* ABS: 012 Pixels @ 018,036 */ 0x0C, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x64, 0xFF, 0xFF, 0xD5, 0xFF, 0xFF, 0xD5, 0xFF, 0xFF, 0x64, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 036 Pixels @ 030,036 */ 0xA4, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 018,037 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 021,037 */ 0x06, 0x02, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x87, 0xFF, 0xFF, 0x87, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 027,037 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 037 Pixels @ 030,037 */ 0xA5, 0x00, 0x00, 0x00, 
  /* ABS: 010 Pixels @ 019,038 */ 0x0A, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 039 Pixels @ 029,038 */ 0xA7, 0x00, 0x00, 0x00, 
  /* RLE: 003 Pixels @ 020,039 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 023,039 */ 0x02, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 025,039 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* RLE: 041 Pixels @ 028,039 */ 0xA9, 0x00, 0x00, 0x00, 
  /* ABS: 006 Pixels @ 021,040 */ 0x06, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 357 Pixels @ 027,040 */ 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xE7, 0x00, 0x00, 0x00, 
};  //2304 pixels compress to 2208 bytes


GUI_CONST_STORAGE GUI_BITMAP bmwifi_level3_open_w = {
  48,  //xSize
  48,  //ySize
  144,  //ByteBytesPerLine
  24,  //BitsPerPixel
  (unsigned char *)_acwifi_level3_open_w,  //Pointer to picture data
  NULL,  //Pointer to palette
  GUI_DRAW_AlphaRLEM16M
};  

