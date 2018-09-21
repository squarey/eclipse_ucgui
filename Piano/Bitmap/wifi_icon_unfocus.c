﻿


#include <stdlib.h>
#include "GUI.h"
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


extern GUI_CONST_STORAGE GUI_BITMAP bmwifi_icon_unfocus;

static GUI_CONST_STORAGE unsigned char _acwifi_icon_unfocus[] = {
  /* RLE: 013 Pixels @ 000,000 */ 0x8D, 0x00, 0xBD, 0xD7, 
  /* ABS: 014 Pixels @ 013,000 */ 0x0E, 0x1D, 0xBD, 0xD7, 0x3E, 0xBD, 0xD7, 0x69, 0xBD, 0xD7, 0x94, 0xBD, 0xD7, 0xBC, 0xBD, 0xD7, 0xC6, 0xBD, 0xD7, 0xD9, 0xBD, 0xD7, 0xDB, 0xBD, 0xD7, 0xC9, 0xBD, 0xD7, 0xBC, 0xBD, 0xD7, 0x9C, 0xBD, 0xD7, 0x70, 0xBD, 0xD7, 0x44, 0xBD, 0xD7, 
        0x23, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 027,000 */ 0x85, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,000 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 010 Pixels @ 000,001 */ 0x8A, 0x00, 0xBD, 0xD7, 
  /* ABS: 004 Pixels @ 010,001 */ 0x04, 0x2C, 0xBD, 0xD7, 0x7B, 0xBD, 0xD7, 0xD1, 0xBD, 0xD7, 0xFE, 0xBD, 0xD7, 
  /* RLE: 013 Pixels @ 014,001 */ 0x8D, 0xFF, 0xBD, 0xD7, 
  /* ABS: 005 Pixels @ 027,001 */ 0x05, 0xD9, 0xBD, 0xD7, 0x8B, 0xBD, 0xD7, 0x34, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,001 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 007 Pixels @ 000,002 */ 0x87, 0x00, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 007,002 */ 0x03, 0x03, 0xBD, 0xD7, 0x56, 0xBD, 0xD7, 0xCD, 0xBD, 0xD7, 
  /* RLE: 020 Pixels @ 010,002 */ 0x94, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 030,002 */ 0x03, 0xDC, 0xBD, 0xD7, 0x69, 0xBD, 0xD7, 0x0F, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 033,002 */ 0x87, 0x00, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 000,003 */ 0x86, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 006,003 */ 0x02, 0x5D, 0xBD, 0xD7, 0xE0, 0xBD, 0xD7, 
  /* RLE: 024 Pixels @ 008,003 */ 0x98, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 032,003 */ 0x03, 0xEE, 0xBD, 0xD7, 0x72, 0xBD, 0xD7, 0x02, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 035,003 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 000,004 */ 0x84, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 004,004 */ 0x02, 0x35, 0xBD, 0xD7, 0xC8, 0xBD, 0xD7, 
  /* RLE: 011 Pixels @ 006,004 */ 0x8B, 0xFF, 0xBD, 0xD7, 
  /* ABS: 006 Pixels @ 017,004 */ 0x06, 0xEF, 0xBD, 0xD7, 0xE5, 0xBD, 0xD7, 0xDC, 0xBD, 0xD7, 0xDB, 0xBD, 0xD7, 0xE3, 0xBD, 0xD7, 0xED, 0xBD, 0xD7, 
  /* RLE: 011 Pixels @ 023,004 */ 0x8B, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 034,004 */ 0x02, 0xDA, 0xBD, 0xD7, 0x44, 0xBD, 0xD7, 
  /* RLE: 004 Pixels @ 036,004 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* RLE: 003 Pixels @ 000,005 */ 0x83, 0x00, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 003,005 */ 0x01, 0x75, 0xBD, 0xD7, 
  /* RLE: 009 Pixels @ 004,005 */ 0x89, 0xFF, 0xBD, 0xD7, 
  /* ABS: 015 Pixels @ 013,005 */ 0x0F, 0xD2, 0xBD, 0xD7, 0xA1, 0xBD, 0xD7, 0x5C, 0xBD, 0xD7, 0x2F, 0xBD, 0xD7, 0x0B, 0xBD, 0xD7, 0x03, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 0x02, 0xBD, 0xD7, 0x0A, 0xBD, 0xD7, 0x28, 0xBD, 0xD7, 0x55, 0xBD, 0xD7, 0x98, 0xBD, 0xD7, 
        0xCC, 0xBD, 0xD7, 0xFB, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 028,005 */ 0x88, 0xFF, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 036,005 */ 0x01, 0x93, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 037,005 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 000,006 */ 0x03, 0x00, 0xBD, 0xD7, 0x06, 0xBD, 0xD7, 0xB6, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 003,006 */ 0x87, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 010,006 */ 0x03, 0xE3, 0xBD, 0xD7, 0x91, 0xBD, 0xD7, 0x28, 0xBD, 0xD7, 
  /* RLE: 014 Pixels @ 013,006 */ 0x8E, 0x00, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 027,006 */ 0x03, 0x1C, 0xBD, 0xD7, 0x80, 0xBD, 0xD7, 0xD7, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 030,006 */ 0x87, 0xFF, 0xBD, 0xD7, 
  /* ABS: 005 Pixels @ 037,006 */ 0x05, 0xCF, 0xBD, 0xD7, 0x1A, 0xBD, 0xD7, 0x00, 0xFF, 0xFF, 0x33, 0xBD, 0xD7, 0xD7, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 002,007 */ 0x86, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 008,007 */ 0x03, 0xE6, 0xBD, 0xD7, 0x74, 0xBD, 0xD7, 0x03, 0xBD, 0xD7, 
  /* RLE: 019 Pixels @ 011,007 */ 0x93, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 030,007 */ 0x02, 0x5D, 0xBD, 0xD7, 0xD7, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 032,007 */ 0x86, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 038,007 */ 0x03, 0xEE, 0xBD, 0xD7, 0x41, 0xBD, 0xD7, 0xB6, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 001,008 */ 0x86, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 007,008 */ 0x02, 0x98, 0xBD, 0xD7, 0x08, 0xBD, 0xD7, 
  /* RLE: 023 Pixels @ 009,008 */ 0x97, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 032,008 */ 0x02, 0x7D, 0xBD, 0xD7, 0xFC, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 034,008 */ 0x85, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 039,008 */ 0x03, 0xDF, 0xBD, 0xD7, 0x13, 0xBD, 0xD7, 0xC8, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 002,009 */ 0x83, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 005,009 */ 0x02, 0xE7, 0xBD, 0xD7, 0x42, 0xBD, 0xD7, 
  /* RLE: 009 Pixels @ 007,009 */ 0x89, 0x00, 0xBD, 0xD7, 
  /* ABS: 008 Pixels @ 016,009 */ 0x08, 0x16, 0xBD, 0xD7, 0x2C, 0xBD, 0xD7, 0x3C, 0xBD, 0xD7, 0x46, 0xBD, 0xD7, 0x46, 0xBD, 0xD7, 0x3E, 0xBD, 0xD7, 0x2E, 0xBD, 0xD7, 0x1A, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 024,009 */ 0x88, 0x00, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 032,009 */ 0x03, 0x00, 0xFF, 0xFF, 0x26, 0xBD, 0xD7, 0xD3, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 035,009 */ 0x83, 0xFF, 0xBD, 0xD7, 
  /* ABS: 008 Pixels @ 038,009 */ 0x08, 0xE1, 0xBD, 0xD7, 0x21, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 0xCD, 0xBD, 0xD7, 0xFF, 0xBD, 0xD7, 0xCB, 0xBD, 0xD7, 0x0D, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 006,010 */ 0x87, 0x00, 0xBD, 0xD7, 
  /* ABS: 004 Pixels @ 013,010 */ 0x04, 0x28, 0xBD, 0xD7, 0x70, 0xBD, 0xD7, 0xC3, 0xBD, 0xD7, 0xF8, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 017,010 */ 0x86, 0xFF, 0xBD, 0xD7, 
  /* ABS: 004 Pixels @ 023,010 */ 0x04, 0xFB, 0xBD, 0xD7, 0xD0, 0xBD, 0xD7, 0x7F, 0xBD, 0xD7, 0x2F, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 027,010 */ 0x85, 0x00, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 032,010 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 010 Pixels @ 035,010 */ 0x0A, 0xAE, 0xBD, 0xD7, 0xFF, 0xBD, 0xD7, 0xE8, 0xBD, 0xD7, 0x11, 0xBD, 0xD7, 0x00, 0xFF, 0xFF, 0x00, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 0x0E, 0xBD, 0xD7, 0x92, 0xBD, 0xD7, 0x02, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 005,011 */ 0x86, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 011,011 */ 0x02, 0x3D, 0xBD, 0xD7, 0xB7, 0xBD, 0xD7, 
  /* RLE: 014 Pixels @ 013,011 */ 0x8E, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 027,011 */ 0x02, 0xCA, 0xBD, 0xD7, 0x4A, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 029,011 */ 0x83, 0x00, 0xBD, 0xD7, 
  /* RLE: 004 Pixels @ 032,011 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 036,011 */ 0x04, 0x85, 0xBD, 0xD7, 0x29, 0xBD, 0xD7, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
  /* RLE: 009 Pixels @ 000,012 */ 0x89, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 009,012 */ 0x02, 0x1B, 0xBD, 0xD7, 0xAA, 0xBD, 0xD7, 
  /* RLE: 018 Pixels @ 011,012 */ 0x92, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 029,012 */ 0x03, 0xC4, 0xBD, 0xD7, 0x2D, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,012 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 008 Pixels @ 000,013 */ 0x88, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 008,013 */ 0x02, 0x4F, 0xBD, 0xD7, 0xF7, 0xBD, 0xD7, 
  /* RLE: 021 Pixels @ 010,013 */ 0x95, 0xFF, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 031,013 */ 0x01, 0x6A, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,013 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 000,014 */ 0x86, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 006,014 */ 0x02, 0x0A, 0xBD, 0xD7, 0x8E, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 008,014 */ 0x87, 0xFF, 0xBD, 0xD7, 
  /* ABS: 010 Pixels @ 015,014 */ 0x0A, 0xF2, 0xBD, 0xD7, 0xC8, 0xBD, 0xD7, 0x8F, 0xBD, 0xD7, 0x64, 0xBD, 0xD7, 0x45, 0xBD, 0xD7, 0x43, 0xBD, 0xD7, 0x5E, 0xBD, 0xD7, 0x86, 0xBD, 0xD7, 0xC0, 0xBD, 0xD7, 0xEA, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 025,014 */ 0x87, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 032,014 */ 0x02, 0xAE, 0xBD, 0xD7, 0x0F, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 034,014 */ 0x86, 0x00, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 000,015 */ 0x86, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 006,015 */ 0x02, 0x0E, 0xBD, 0xD7, 0xE6, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 008,015 */ 0x85, 0xFF, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 013,015 */ 0x03, 0xDE, 0xBD, 0xD7, 0x77, 0xBD, 0xD7, 0x12, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 016,015 */ 0x88, 0x00, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 024,015 */ 0x03, 0x0A, 0xBD, 0xD7, 0x64, 0xBD, 0xD7, 0xD1, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 027,015 */ 0x86, 0xFF, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 033,015 */ 0x01, 0x15, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 034,015 */ 0x86, 0x00, 0xFF, 0xFF, 
  /* RLE: 007 Pixels @ 000,016 */ 0x87, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 007,016 */ 0x02, 0x03, 0xBD, 0xD7, 0xD3, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 009,016 */ 0x83, 0xFF, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 012,016 */ 0x01, 0x83, 0xBD, 0xD7, 
  /* RLE: 014 Pixels @ 013,016 */ 0x8E, 0x00, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 027,016 */ 0x01, 0x69, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 028,016 */ 0x83, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 031,016 */ 0x02, 0xEC, 0xBD, 0xD7, 0x14, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 033,016 */ 0x87, 0x00, 0xFF, 0xFF, 
  /* RLE: 008 Pixels @ 000,017 */ 0x88, 0x00, 0xBD, 0xD7, 
  /* ABS: 004 Pixels @ 008,017 */ 0x04, 0x07, 0xBD, 0xD7, 0xDF, 0xBD, 0xD7, 0xF8, 0xBD, 0xD7, 0x3D, 0xBD, 0xD7, 
  /* RLE: 016 Pixels @ 012,017 */ 0x90, 0x00, 0xBD, 0xD7, 
  /* ABS: 004 Pixels @ 028,017 */ 0x04, 0x2B, 0xBD, 0xD7, 0xE8, 0xBD, 0xD7, 0xF2, 0xBD, 0xD7, 0x1C, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,017 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 009 Pixels @ 000,018 */ 0x89, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 009,018 */ 0x02, 0x0E, 0xBD, 0xD7, 0x1E, 0xBD, 0xD7, 
  /* RLE: 018 Pixels @ 011,018 */ 0x92, 0x00, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 029,018 */ 0x03, 0x10, 0xBD, 0xD7, 0x18, 0xBD, 0xD7, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,018 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 016 Pixels @ 000,019 */ 0x90, 0x00, 0xBD, 0xD7, 
  /* ABS: 008 Pixels @ 016,019 */ 0x08, 0x27, 0xBD, 0xD7, 0x6C, 0xBD, 0xD7, 0xB3, 0xBD, 0xD7, 0xD8, 0xBD, 0xD7, 0xDB, 0xBD, 0xD7, 0xB8, 0xBD, 0xD7, 0x75, 0xBD, 0xD7, 0x2B, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 024,019 */ 0x88, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,019 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 014 Pixels @ 000,020 */ 0x8E, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 014,020 */ 0x02, 0x0B, 0xBD, 0xD7, 0x99, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 016,020 */ 0x88, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 024,020 */ 0x02, 0xA3, 0xBD, 0xD7, 0x11, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 026,020 */ 0x86, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,020 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 013 Pixels @ 000,021 */ 0x8D, 0x00, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 013,021 */ 0x01, 0x21, 0xBD, 0xD7, 
  /* RLE: 012 Pixels @ 014,021 */ 0x8C, 0xFF, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 026,021 */ 0x01, 0x33, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 027,021 */ 0x85, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,021 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 013 Pixels @ 000,022 */ 0x8D, 0x00, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 013,022 */ 0x02, 0x1B, 0xBD, 0xD7, 0xE0, 0xBD, 0xD7, 
  /* RLE: 010 Pixels @ 015,022 */ 0x8A, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 025,022 */ 0x02, 0xF8, 0xBD, 0xD7, 0x2D, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 027,022 */ 0x85, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,022 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 015 Pixels @ 000,023 */ 0x8F, 0x00, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 015,023 */ 0x01, 0xC8, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 016,023 */ 0x88, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 024,023 */ 0x02, 0xE2, 0xBD, 0xD7, 0x11, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 026,023 */ 0x86, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,023 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 016 Pixels @ 000,024 */ 0x90, 0x00, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 016,024 */ 0x01, 0xC8, 0xBD, 0xD7, 
  /* RLE: 006 Pixels @ 017,024 */ 0x86, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 023,024 */ 0x02, 0xE4, 0xBD, 0xD7, 0x11, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 025,024 */ 0x87, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,024 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 017 Pixels @ 000,025 */ 0x91, 0x00, 0xBD, 0xD7, 
  /* ABS: 001 Pixels @ 017,025 */ 0x01, 0xC8, 0xBD, 0xD7, 
  /* RLE: 004 Pixels @ 018,025 */ 0x84, 0xFF, 0xBD, 0xD7, 
  /* ABS: 002 Pixels @ 022,025 */ 0x02, 0xE9, 0xBD, 0xD7, 0x1A, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 024,025 */ 0x88, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,025 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 018 Pixels @ 000,026 */ 0x92, 0x00, 0xBD, 0xD7, 
  /* ABS: 005 Pixels @ 018,026 */ 0x05, 0xC8, 0xBD, 0xD7, 0xFF, 0xBD, 0xD7, 0xFF, 0xBD, 0xD7, 0xE2, 0xBD, 0xD7, 0x14, 0xBD, 0xD7, 
  /* RLE: 009 Pixels @ 023,026 */ 0x89, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,026 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* RLE: 019 Pixels @ 000,027 */ 0x93, 0x00, 0xBD, 0xD7, 
  /* ABS: 003 Pixels @ 019,027 */ 0x03, 0xD3, 0xBD, 0xD7, 0xE5, 0xBD, 0xD7, 0x11, 0xBD, 0xD7, 
  /* RLE: 010 Pixels @ 022,027 */ 0x8A, 0x00, 0xBD, 0xD7, 
  /* RLE: 008 Pixels @ 032,027 */ 0x88, 0x00, 0xFF, 0xFF, 
};  //1120 pixels compress to 1133 bytes


GUI_CONST_STORAGE GUI_BITMAP bmwifi_icon_unfocus = {
  40,  //xSize
  28,  //ySize
  120,  //ByteBytesPerLine
  24,  //BitsPerPixel
  (unsigned char *)_acwifi_icon_unfocus,  //Pointer to picture data
  NULL,  //Pointer to palette
  GUI_DRAW_AlphaRLEM16M
};  

