﻿


#include <stdlib.h>
#include "GUI.h"
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


extern GUI_CONST_STORAGE GUI_BITMAP bmcooker_right;

static GUI_CONST_STORAGE unsigned char _accooker_right[] = {
  /* RLE: 012 Pixels @ 000,000 */ 0x8C, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 012,000 */ 0x06, 0x0B, 0x65, 0xFD, 0x53, 0x04, 0x7B, 0x9D, 0x04, 0xBB, 0xD0, 0x04, 0xBB, 0xED, 0x04, 0xBB, 0xFD, 0x04, 0xBB, 
  /* RLE: 038 Pixels @ 018,000 */ 0xA6, 0xFF, 0x04, 0xBB, 
  /* RLE: 039 Pixels @ 056,000 */ 0xA7, 0xFF, 0x04, 0xDB, 
  /* ABS: 008 Pixels @ 095,000 */ 0x08, 0xFA, 0x04, 0xDB, 0xE9, 0x04, 0xDB, 0xC8, 0x04, 0xDB, 0x92, 0x04, 0xDB, 0x41, 0x04, 0xDB, 0x04, 0x04, 0xDB, 0x00, 0x04, 0xBB, 0x00, 0x2D, 0x7C, 
  /* RLE: 017 Pixels @ 103,000 */ 0x91, 0x00, 0xFF, 0xFF, 
  /* ABS: 010 Pixels @ 008,001 */ 0x0A, 0x00, 0xEF, 0xDF, 0x05, 0xD7, 0x7F, 0x2E, 0x2D, 0x5C, 0x87, 0x35, 0x9C, 0xCD, 0x35, 0x7C, 0xE3, 0x55, 0xDD, 0xEE, 0x8E, 0x9E, 0xF7, 0xAF, 0x1E, 0xFC, 0xC7, 0x5F, 0xFF, 0xCF, 0x7F, 
  /* RLE: 037 Pixels @ 018,001 */ 0xA5, 0xFF, 0xD7, 0x7F, 
  /* ABS: 003 Pixels @ 055,001 */ 0x03, 0xFF, 0xE7, 0xBF, 0xFF, 0x55, 0xDD, 0xFF, 0x04, 0xBB, 
  /* RLE: 037 Pixels @ 058,001 */ 0xA5, 0xFF, 0x04, 0xDB, 
  /* ABS: 010 Pixels @ 095,001 */ 0x0A, 0xFE, 0x04, 0xDB, 0xFB, 0x04, 0xDB, 0xF5, 0x04, 0xDB, 0xEC, 0x04, 0xDB, 0xE1, 0x04, 0xDB, 0xC2, 0x04, 0xDB, 0x75, 0x04, 0xDB, 0x22, 0x2D, 0x5C, 0x03, 0xEF, 0xBF, 0x00, 0xF7, 0xDF, 
  /* RLE: 014 Pixels @ 105,001 */ 0x8E, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 007,002 */ 0x06, 0x00, 0xEF, 0xBF, 0x3A, 0x35, 0x5C, 0xAC, 0x04, 0xDB, 0xFE, 0x55, 0xFD, 0xFF, 0xAE, 0xFE, 0xFF, 0xF7, 0xDF, 
  /* RLE: 043 Pixels @ 013,002 */ 0xAB, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,002 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 044 Pixels @ 058,002 */ 0xAC, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 102,002 */ 0x03, 0xF7, 0x04, 0xDB, 0x94, 0x04, 0x9B, 0x26, 0x5D, 0xFD, 
  /* RLE: 013 Pixels @ 105,002 */ 0x8D, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 006,003 */ 0x04, 0x0A, 0x66, 0x1D, 0x89, 0x2D, 0x5C, 0xF2, 0x3D, 0x9C, 0xFF, 0xC7, 0x5F, 
  /* RLE: 046 Pixels @ 010,003 */ 0xAE, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,003 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 045 Pixels @ 058,003 */ 0xAD, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 103,003 */ 0x04, 0xFF, 0x04, 0xFB, 0xE3, 0x04, 0xBB, 0x6A, 0x45, 0xBD, 0x00, 0x7E, 0x7D, 
  /* RLE: 009 Pixels @ 107,003 */ 0x89, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 004,004 */ 0x04, 0x00, 0xF7, 0xDF, 0x1E, 0x3D, 0x9C, 0xBD, 0x04, 0xBB, 0xFF, 0x86, 0x7D, 
  /* RLE: 048 Pixels @ 008,004 */ 0xB0, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,004 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 047 Pixels @ 058,004 */ 0xAF, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 105,004 */ 0x03, 0xFF, 0x04, 0xBB, 0x9E, 0x04, 0x9B, 0x0E, 0x6E, 0x3D, 
  /* RLE: 007 Pixels @ 108,004 */ 0x87, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 003,005 */ 0x04, 0x00, 0xEF, 0xBF, 0x2A, 0x35, 0x7C, 0xD2, 0x04, 0xFB, 0xFF, 0xB7, 0x1E, 
  /* RLE: 049 Pixels @ 007,005 */ 0xB1, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,005 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 049 Pixels @ 058,005 */ 0xB1, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 107,005 */ 0x02, 0xB3, 0x04, 0x9B, 0x13, 0x5D, 0xFD, 
  /* RLE: 006 Pixels @ 109,005 */ 0x86, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 003,006 */ 0x03, 0x18, 0x9E, 0x9E, 0xC6, 0x04, 0xBB, 0xFF, 0xBF, 0x3E, 
  /* RLE: 050 Pixels @ 006,006 */ 0xB2, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,006 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 049 Pixels @ 058,006 */ 0xB1, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 107,006 */ 0x03, 0xFF, 0x04, 0xFB, 0xA3, 0x04, 0x9B, 0x08, 0xD7, 0x5F, 
  /* RLE: 004 Pixels @ 110,006 */ 0x84, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 002,007 */ 0x03, 0x05, 0xBF, 0x3E, 0x9D, 0x04, 0xFB, 0xFF, 0x9E, 0xDE, 
  /* RLE: 051 Pixels @ 005,007 */ 0xB3, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,007 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 051 Pixels @ 058,007 */ 0xB3, 0xFF, 0x04, 0xDB, 
  /* ABS: 007 Pixels @ 109,007 */ 0x07, 0x76, 0x1D, 0x5C, 0x00, 0xE7, 0x9F, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xF7, 0xDF, 0x54, 0x04, 0xBB, 0xFF, 0x5E, 0x1D, 
  /* RLE: 015 Pixels @ 004,008 */ 0x8F, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 019,008 */ 0x02, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xDF, 
  /* RLE: 022 Pixels @ 021,008 */ 0x96, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,008 */ 0x02, 0xFF, 0xF7, 0x9E, 0xFF, 0xF7, 0x9E, 
  /* RLE: 011 Pixels @ 045,008 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,008 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 016 Pixels @ 058,008 */ 0x90, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 074,008 */ 0x03, 0xFF, 0x04, 0xFB, 0xFF, 0x25, 0x3C, 0xFF, 0x15, 0x1C, 
  /* RLE: 013 Pixels @ 077,008 */ 0x8D, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 090,008 */ 0x03, 0xFF, 0x04, 0x9B, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xFB, 
  /* RLE: 005 Pixels @ 093,008 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,008 */ 0x03, 0xFF, 0x1D, 0x1C, 0xFF, 0x2D, 0x3C, 0xFF, 0x04, 0xFB, 
  /* RLE: 008 Pixels @ 101,008 */ 0x88, 0xFF, 0x04, 0xDB, 
  /* ABS: 007 Pixels @ 109,008 */ 0x07, 0xF4, 0x04, 0xBB, 0x2F, 0x2D, 0x5C, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x09, 0x7E, 0x7D, 0xD4, 0x1D, 0x3C, 0xFF, 0xDF, 0x9F, 
  /* RLE: 014 Pixels @ 004,009 */ 0x8E, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 018,009 */ 0x03, 0xFF, 0xFF, 0xDF, 0xFF, 0x94, 0x92, 0xFF, 0xA5, 0x34, 
  /* RLE: 013 Pixels @ 021,009 */ 0x8D, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 034,009 */ 0x03, 0xFF, 0xE7, 0x3C, 0xFF, 0x84, 0x10, 0xFF, 0xE7, 0x1C, 
  /* RLE: 006 Pixels @ 037,009 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,009 */ 0x02, 0xFF, 0x9C, 0xF3, 0xFF, 0x9C, 0xF3, 
  /* RLE: 011 Pixels @ 045,009 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,009 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 016 Pixels @ 058,009 */ 0x90, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 074,009 */ 0x03, 0xFF, 0x1D, 0x1C, 0xFF, 0xD7, 0x3E, 0xFF, 0x8E, 0x5D, 
  /* RLE: 012 Pixels @ 077,009 */ 0x8C, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 089,009 */ 0x04, 0xFF, 0x04, 0xFC, 0xFF, 0xA6, 0xDE, 0xFF, 0x55, 0xDD, 0xFF, 0x04, 0xBB, 
  /* RLE: 005 Pixels @ 093,009 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,009 */ 0x03, 0xFF, 0x7E, 0x1D, 0xFF, 0xC6, 0xFE, 0xFF, 0x1C, 0xFC, 
  /* RLE: 009 Pixels @ 101,009 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 110,009 */ 0x05, 0xAE, 0x04, 0xFC, 0x00, 0xAE, 0xFE, 0x00, 0xFF, 0xFF, 0x59, 0x3D, 0x7C, 0xFE, 0x6E, 0x3D, 
  /* RLE: 015 Pixels @ 003,010 */ 0x8F, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 018,010 */ 0x03, 0xFF, 0xEF, 0x7D, 0xFF, 0x4A, 0x49, 0xFF, 0xA5, 0x34, 
  /* RLE: 013 Pixels @ 021,010 */ 0x8D, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 034,010 */ 0x03, 0xFF, 0xD6, 0x9A, 0xFF, 0x29, 0x45, 0xFF, 0xCE, 0x79, 
  /* RLE: 006 Pixels @ 037,010 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,010 */ 0x02, 0xFF, 0x84, 0x10, 0xFF, 0x84, 0x10, 
  /* RLE: 011 Pixels @ 045,010 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,010 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 010 Pixels @ 058,010 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* RLE: 005 Pixels @ 068,010 */ 0x85, 0xFF, 0x04, 0xBB, 
  /* ABS: 005 Pixels @ 073,010 */ 0x05, 0xFF, 0x04, 0x9B, 0xFF, 0x2D, 0x5C, 0xFF, 0xFF, 0xFF, 0xFF, 0x65, 0xFD, 0xFF, 0x04, 0x7B, 
  /* RLE: 007 Pixels @ 078,010 */ 0x87, 0xFF, 0x04, 0xBB, 
  /* RLE: 004 Pixels @ 085,010 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 089,010 */ 0x05, 0xFF, 0x0C, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x7D, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xBB, 
  /* RLE: 004 Pixels @ 094,010 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,010 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1D, 0x1C, 
  /* RLE: 009 Pixels @ 101,010 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 110,010 */ 0x05, 0xEC, 0x04, 0x9B, 0x37, 0x76, 0x1D, 0x00, 0xAE, 0xFE, 0xB1, 0x35, 0x7C, 0xFF, 0xD7, 0x7F, 
  /* RLE: 009 Pixels @ 003,011 */ 0x89, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 012,011 */ 0x02, 0xFF, 0xFF, 0xDF, 0xFF, 0xBD, 0xD7, 
  /* RLE: 003 Pixels @ 014,011 */ 0x83, 0xFF, 0xAD, 0x75, 
  /* ABS: 005 Pixels @ 017,011 */ 0x05, 0xFF, 0xB5, 0x96, 0xFF, 0x9C, 0xF3, 0xFF, 0x31, 0xA6, 0xFF, 0x84, 0x10, 0xFF, 0xBD, 0xD7, 
  /* RLE: 007 Pixels @ 022,011 */ 0x87, 0xFF, 0xAD, 0x75, 
  /* ABS: 001 Pixels @ 029,011 */ 0x01, 0xFF, 0xCE, 0x59, 
  /* RLE: 004 Pixels @ 030,011 */ 0x84, 0xFF, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 034,011 */ 0x06, 0xFF, 0xD6, 0xBA, 0xFF, 0x39, 0xC7, 0xFF, 0xD6, 0x9A, 0xFF, 0xFF, 0xFF, 0xFF, 0xD6, 0xBA, 0xFF, 0xFF, 0xDF, 
  /* RLE: 003 Pixels @ 040,011 */ 0x83, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,011 */ 0x02, 0xFF, 0x84, 0x30, 0xFF, 0x84, 0x30, 
  /* RLE: 011 Pixels @ 045,011 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,011 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 009 Pixels @ 058,011 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 067,011 */ 0x03, 0xFF, 0x0C, 0xFB, 0xFF, 0x4D, 0xDD, 0xFF, 0x66, 0x3D, 
  /* RLE: 003 Pixels @ 070,011 */ 0x83, 0xFF, 0x66, 0x1D, 
  /* ABS: 005 Pixels @ 073,011 */ 0x05, 0xFF, 0x5E, 0x1D, 0xFF, 0x9E, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x9E, 0xFF, 0x55, 0xFD, 
  /* RLE: 006 Pixels @ 078,011 */ 0x86, 0xFF, 0x66, 0x1D, 
  /* ABS: 011 Pixels @ 084,011 */ 0x0B, 0xFF, 0x5D, 0xFD, 0xFF, 0x0D, 0x1C, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xBB, 0xFF, 0x0C, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x86, 0x5D, 0xFF, 0x04, 0x7B, 0xFF, 0x45, 0x9C, 0xFF, 0x25, 0x3C, 
  /* RLE: 003 Pixels @ 095,011 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,011 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1D, 0x1C, 
  /* RLE: 009 Pixels @ 101,011 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 110,011 */ 0x04, 0xFF, 0x04, 0xBB, 0x83, 0x45, 0xBD, 0x3C, 0x04, 0x7B, 0xD4, 0x3D, 0x7C, 
  /* RLE: 010 Pixels @ 002,012 */ 0x8A, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 012,012 */ 0x03, 0xFF, 0xF7, 0x9E, 0xFF, 0x63, 0x2C, 0xFF, 0x42, 0x28, 
  /* RLE: 003 Pixels @ 015,012 */ 0x83, 0xFF, 0x4A, 0x69, 
  /* ABS: 003 Pixels @ 018,012 */ 0x03, 0xFF, 0x39, 0xC7, 0xFF, 0x39, 0xE7, 0xFF, 0x52, 0x8A, 
  /* RLE: 007 Pixels @ 021,012 */ 0x87, 0xFF, 0x4A, 0x69, 
  /* ABS: 012 Pixels @ 028,012 */ 0x0C, 0xFF, 0x4A, 0x49, 0xFF, 0x7B, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x5D, 0xFF, 0xE7, 0x1C, 0xFF, 0xD6, 0x9A, 0xFF, 0x39, 0xC7, 0xFF, 0xD6, 0xBA, 0xFF, 0xCE, 0x59, 0xFF, 0x4A, 0x69, 0xFF, 0xE7, 0x1C, 
  /* RLE: 003 Pixels @ 040,012 */ 0x83, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,012 */ 0x02, 0xFF, 0x8C, 0x51, 0xFF, 0x8C, 0x51, 
  /* RLE: 011 Pixels @ 045,012 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,012 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 009 Pixels @ 058,012 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 067,012 */ 0x03, 0xFF, 0x1C, 0xFC, 0xFF, 0xCF, 0x1E, 0xFF, 0xFF, 0xFF, 
  /* RLE: 004 Pixels @ 070,012 */ 0x84, 0xFF, 0xFF, 0xDF, 
  /* ABS: 003 Pixels @ 074,012 */ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xDF, 0xFF, 0xF7, 0xBF, 
  /* RLE: 006 Pixels @ 077,012 */ 0x86, 0xFF, 0xFF, 0xDF, 
  /* ABS: 012 Pixels @ 083,012 */ 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x9F, 0xFF, 0x25, 0x3C, 0xFF, 0x04, 0xBB, 0xFF, 0x25, 0x3C, 0xFF, 0x5D, 0xBD, 0xFF, 0x1D, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0x76, 0x3D, 0xFF, 0x35, 0x5C, 0xFF, 0xF7, 0xBF, 0xFF, 0x75, 0xFD, 
  /* RLE: 003 Pixels @ 095,012 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,012 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1C, 0xFC, 
  /* RLE: 009 Pixels @ 101,012 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 110,012 */ 0x04, 0xFF, 0x04, 0xFB, 0xB1, 0x04, 0xDB, 0x93, 0x04, 0xBB, 0xE7, 0x76, 0x5D, 
  /* RLE: 011 Pixels @ 002,013 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 001 Pixels @ 013,013 */ 0x01, 0xFF, 0xF7, 0xBE, 
  /* RLE: 003 Pixels @ 014,013 */ 0x83, 0xFF, 0xF7, 0x9E, 
  /* ABS: 005 Pixels @ 017,013 */ 0x05, 0xFF, 0xF7, 0xBE, 0xFF, 0x73, 0x8E, 0xFF, 0x6B, 0x6D, 0xFF, 0xFF, 0xDF, 0xFF, 0xF7, 0xBE, 
  /* RLE: 007 Pixels @ 022,013 */ 0x87, 0xFF, 0xF7, 0x9E, 
  /* ABS: 010 Pixels @ 029,013 */ 0x0A, 0xFF, 0xF7, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x84, 0x30, 0xFF, 0x8C, 0x71, 0xFF, 0xD6, 0xBA, 0xFF, 0x39, 0xE7, 0xFF, 0x8C, 0x51, 0xFF, 0x52, 0xAA, 0xFF, 0xBD, 0xD7, 
  /* RLE: 004 Pixels @ 039,013 */ 0x84, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,013 */ 0x02, 0xFF, 0x8C, 0x51, 0xFF, 0x8C, 0x51, 
  /* RLE: 011 Pixels @ 045,013 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,013 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 010 Pixels @ 058,013 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 068,013 */ 0x01, 0xFF, 0x15, 0x1C, 
  /* RLE: 003 Pixels @ 069,013 */ 0x83, 0xFF, 0x1D, 0x1C, 
  /* ABS: 005 Pixels @ 072,013 */ 0x05, 0xFF, 0x0D, 0x1C, 0xFF, 0x65, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0x86, 0x5D, 0xFF, 0x0C, 0xFB, 
  /* RLE: 007 Pixels @ 077,013 */ 0x87, 0xFF, 0x1D, 0x1C, 
  /* ABS: 018 Pixels @ 084,013 */ 0x12, 0xFF, 0x15, 0x1C, 0xFF, 0x04, 0xFB, 0xFF, 0x04, 0x9B, 0xFF, 0x66, 0x1D, 0xFF, 0xEF, 0x9F, 0xFF, 0x25, 0x5C, 0xFF, 0xEF, 0xBF, 0xFF, 0xC7, 0x1E, 0xFF, 0xE7, 0x9F, 0xFF, 0x9E, 0x9E, 0xFF, 0x0C, 0xFC, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 
        0xFF, 0x04, 0xBB, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1C, 0xFB, 0xFF, 0x04, 0xBB, 
  /* RLE: 009 Pixels @ 102,013 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,013 */ 0x03, 0xD4, 0x04, 0xDB, 0xCC, 0x04, 0xBB, 0xF4, 0x9E, 0xDE, 
  /* RLE: 015 Pixels @ 002,014 */ 0x8F, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 017,014 */ 0x03, 0xFF, 0xF7, 0x9E, 0xFF, 0x4A, 0x69, 0xFF, 0xAD, 0x55, 
  /* RLE: 012 Pixels @ 020,014 */ 0x8C, 0xFF, 0xFF, 0xFF, 
  /* ABS: 017 Pixels @ 032,014 */ 0x11, 0xFF, 0x73, 0xAE, 0xFF, 0x94, 0x92, 0xFF, 0xDE, 0xDB, 0xFF, 0x21, 0x24, 0xFF, 0x4A, 0x49, 0xFF, 0xCE, 0x59, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0x38, 0xFF, 0x84, 0x30, 0xFF, 0x8C, 0x71, 0xFF, 0x8C, 0x71, 0xFF, 0x5A, 0xCB, 0xFF, 0x5A, 0xCB, 
        0xFF, 0x8C, 0x71, 0xFF, 0x8C, 0x71, 0xFF, 0x84, 0x30, 0xFF, 0xC6, 0x38, 
  /* RLE: 007 Pixels @ 049,014 */ 0x87, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,014 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 014 Pixels @ 058,014 */ 0x8E, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 072,014 */ 0x05, 0xFF, 0x04, 0xBB, 0xFF, 0xB6, 0xFE, 0xFF, 0xE7, 0x9F, 0xFF, 0x1D, 0x1C, 0xFF, 0x04, 0xBB, 
  /* RLE: 009 Pixels @ 077,014 */ 0x89, 0xFF, 0x04, 0xDB, 
  /* ABS: 019 Pixels @ 086,014 */ 0x13, 0xFF, 0x04, 0xBB, 0xFF, 0x7E, 0x5D, 0xFF, 0xE7, 0x7F, 0xFF, 0x25, 0x3C, 0xFF, 0xF7, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x5D, 0xFF, 0x04, 0xDB, 0xFF, 0x4D, 0x9C, 0xFF, 0xB6, 0xDE, 0xFF, 0xAE, 0xDE, 0xFF, 0xAE, 0xBE, 0xFF, 0xD7, 0x5F, 
        0xFF, 0xEF, 0xBF, 0xFF, 0xB6, 0xDE, 0xFF, 0xAE, 0xBE, 0xFF, 0xB6, 0xDE, 0xFF, 0x8E, 0x5D, 0xFF, 0x14, 0xFC, 
  /* RLE: 006 Pixels @ 105,014 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,014 */ 0x03, 0xEB, 0x04, 0xDB, 0xED, 0x04, 0x9B, 0xFB, 0xB7, 0x1E, 
  /* RLE: 015 Pixels @ 002,015 */ 0x8F, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 017,015 */ 0x03, 0xFF, 0xAD, 0x75, 0xFF, 0x4A, 0x49, 0xFF, 0xEF, 0x7D, 
  /* RLE: 012 Pixels @ 020,015 */ 0x8C, 0xFF, 0xFF, 0xFF, 
  /* ABS: 017 Pixels @ 032,015 */ 0x11, 0xFF, 0x6B, 0x4D, 0xFF, 0xAD, 0x75, 0xFF, 0xDE, 0xDB, 0xFF, 0x31, 0x86, 0xFF, 0xC6, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0x38, 0xFF, 0x84, 0x30, 0xFF, 0x8C, 0x71, 0xFF, 0x8C, 0x71, 0xFF, 0x5A, 0xCB, 0xFF, 0x5A, 0xCB, 
        0xFF, 0x8C, 0x71, 0xFF, 0x8C, 0x71, 0xFF, 0x84, 0x30, 0xFF, 0xC6, 0x38, 
  /* RLE: 007 Pixels @ 049,015 */ 0x87, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,015 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 013 Pixels @ 058,015 */ 0x8D, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 071,015 */ 0x05, 0xFF, 0x04, 0xBB, 0xFF, 0x5D, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x5D, 0xFF, 0x04, 0x9B, 
  /* RLE: 011 Pixels @ 076,015 */ 0x8B, 0xFF, 0x04, 0xDB, 
  /* ABS: 018 Pixels @ 087,015 */ 0x12, 0xFF, 0xAE, 0xBE, 0xFF, 0xC7, 0x1E, 0xFF, 0x15, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0x9E, 0x9E, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x55, 0xBC, 0xFF, 0xB6, 0xDE, 0xFF, 0xAE, 0xDE, 0xFF, 0xAE, 0xBE, 0xFF, 0xD7, 0x5F, 0xFF, 0xEF, 0xBF, 
        0xFF, 0xB6, 0xDE, 0xFF, 0xAE, 0xBE, 0xFF, 0xB6, 0xDE, 0xFF, 0x8E, 0x5D, 0xFF, 0x14, 0xFC, 
  /* RLE: 006 Pixels @ 105,015 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,015 */ 0x03, 0xF8, 0x04, 0xDB, 0xFF, 0x04, 0x9B, 0xFF, 0xC7, 0x3E, 
  /* RLE: 015 Pixels @ 002,016 */ 0x8F, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 017,016 */ 0x03, 0xFF, 0x52, 0xAA, 0xFF, 0x7B, 0xCF, 0xFF, 0xFF, 0xFF, 
  /* RLE: 008 Pixels @ 020,016 */ 0x88, 0xFF, 0xF7, 0x9E, 
  /* RLE: 003 Pixels @ 028,016 */ 0x83, 0xFF, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 031,016 */ 0x06, 0xFF, 0xE7, 0x3C, 0xFF, 0x4A, 0x49, 0xFF, 0xD6, 0x9A, 0xFF, 0xDE, 0xDB, 0xFF, 0x39, 0xC7, 0xFF, 0xD6, 0x9A, 
  /* RLE: 006 Pixels @ 037,016 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,016 */ 0x02, 0xFF, 0x8C, 0x51, 0xFF, 0x8C, 0x51, 
  /* RLE: 011 Pixels @ 045,016 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,016 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 012 Pixels @ 058,016 */ 0x8C, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 070,016 */ 0x05, 0xFF, 0x04, 0xBB, 0xFF, 0x2D, 0x3C, 0xFF, 0xDF, 0x7F, 0xFF, 0xEF, 0x9F, 0xFF, 0x35, 0x7C, 
  /* RLE: 007 Pixels @ 075,016 */ 0x87, 0xFF, 0x25, 0x5C, 
  /* ABS: 011 Pixels @ 082,016 */ 0x0B, 0xFF, 0x25, 0x3C, 0xFF, 0x0C, 0xFC, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x1D, 0x1C, 0xFF, 0xEF, 0x9F, 0xFF, 0x86, 0x5D, 0xFF, 0x04, 0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0x86, 0x5D, 0xFF, 0x04, 0x9B, 
  /* RLE: 004 Pixels @ 093,016 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 097,016 */ 0x05, 0xFF, 0x04, 0xBB, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1C, 0xFB, 0xFF, 0x04, 0xBB, 
  /* RLE: 010 Pixels @ 102,016 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 000,017 */ 0x02, 0xFB, 0x04, 0x9B, 0xFE, 0xBF, 0x3E, 
  /* RLE: 014 Pixels @ 002,017 */ 0x8E, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 016,017 */ 0x03, 0xFF, 0xBD, 0xD7, 0xFF, 0x29, 0x65, 0xFF, 0x39, 0xE7, 
  /* RLE: 003 Pixels @ 019,017 */ 0x83, 0xFF, 0x4A, 0x69, 
  /* ABS: 015 Pixels @ 022,017 */ 0x0F, 0xFF, 0x5A, 0xCB, 0xFF, 0x52, 0xAA, 0xFF, 0x4A, 0x49, 0xFF, 0x4A, 0x69, 0xFF, 0x4A, 0x49, 0xFF, 0x5A, 0xCB, 0xFF, 0xD6, 0xBA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xDB, 0xFF, 0x84, 0x30, 0xFF, 0xF7, 0x9E, 0xFF, 0xD6, 0xBA, 
        0xFF, 0x39, 0xE7, 0xFF, 0xDE, 0xDB, 
  /* RLE: 006 Pixels @ 037,017 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,017 */ 0x02, 0xFF, 0x8C, 0x51, 0xFF, 0x8C, 0x51, 
  /* RLE: 011 Pixels @ 045,017 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,017 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 012 Pixels @ 058,017 */ 0x8C, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 070,017 */ 0x02, 0xFF, 0x14, 0xFB, 0xFF, 0xBE, 0xFE, 
  /* RLE: 010 Pixels @ 072,017 */ 0x8A, 0xFF, 0xFF, 0xFF, 
  /* ABS: 011 Pixels @ 082,017 */ 0x0B, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x25, 0x3C, 0xFF, 0xCF, 0x1E, 0xFF, 0x4D, 0xBC, 0xFF, 0x04, 0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3D, 0xFF, 0x04, 0xBB, 
  /* RLE: 005 Pixels @ 093,017 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,017 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1C, 0xFC, 
  /* RLE: 010 Pixels @ 101,017 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,017 */ 0x03, 0xFE, 0x04, 0xDB, 0xE7, 0x04, 0x9B, 0xFA, 0xB7, 0x1E, 
  /* RLE: 013 Pixels @ 002,018 */ 0x8D, 0xFF, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 015,018 */ 0x04, 0xFF, 0xEF, 0x5D, 0xFF, 0x52, 0x8A, 0xFF, 0x73, 0x8E, 0xFF, 0xB5, 0x96, 
  /* RLE: 003 Pixels @ 019,018 */ 0x83, 0xFF, 0xAD, 0x75, 
  /* ABS: 007 Pixels @ 022,018 */ 0x07, 0xFF, 0x4A, 0x49, 0xFF, 0x5A, 0xEB, 0xFF, 0xBD, 0xD7, 0xFF, 0xAD, 0x75, 0xFF, 0xAD, 0x75, 0xFF, 0xB5, 0xB6, 0xFF, 0xEF, 0x7D, 
  /* RLE: 003 Pixels @ 029,018 */ 0x83, 0xFF, 0xFF, 0xFF, 
  /* ABS: 005 Pixels @ 032,018 */ 0x05, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBD, 0xF7, 0xFF, 0x4A, 0x69, 0xFF, 0xE7, 0x3C, 
  /* RLE: 006 Pixels @ 037,018 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,018 */ 0x02, 0xFF, 0x84, 0x30, 0xFF, 0x84, 0x30, 
  /* RLE: 011 Pixels @ 045,018 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,018 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 011 Pixels @ 058,018 */ 0x8B, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 069,018 */ 0x05, 0xFF, 0x0C, 0xFC, 0xFF, 0xAE, 0xDE, 0xFF, 0xF7, 0xDF, 0xFF, 0xF7, 0xBF, 0xFF, 0xE7, 0x9F, 
  /* RLE: 006 Pixels @ 074,018 */ 0x86, 0xFF, 0x4D, 0xBC, 
  /* ABS: 013 Pixels @ 080,018 */ 0x0D, 0xFF, 0x45, 0xBC, 0xFF, 0x8E, 0x5D, 0xFF, 0xFF, 0xDF, 0xFF, 0x5D, 0xDD, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x1D, 0x1C, 0xFF, 0x04, 0xFB, 0xFF, 0x3D, 0x7C, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 
  /* RLE: 005 Pixels @ 093,018 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,018 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1D, 0x1C, 
  /* RLE: 010 Pixels @ 101,018 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,018 */ 0x03, 0xF6, 0x04, 0xDB, 0xC1, 0x04, 0xBB, 0xF1, 0x96, 0xBE, 
  /* RLE: 013 Pixels @ 002,019 */ 0x8D, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 015,019 */ 0x03, 0xFF, 0x84, 0x10, 0xFF, 0x4A, 0x49, 0xFF, 0xEF, 0x7D, 
  /* RLE: 004 Pixels @ 018,019 */ 0x84, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 022,019 */ 0x02, 0xFF, 0x63, 0x2C, 0xFF, 0x7B, 0xEF, 
  /* RLE: 010 Pixels @ 024,019 */ 0x8A, 0xFF, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 034,019 */ 0x04, 0xFF, 0xAD, 0x55, 0xFF, 0x21, 0x24, 0xFF, 0x84, 0x30, 0xFF, 0xFF, 0xDF, 
  /* RLE: 005 Pixels @ 038,019 */ 0x85, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,019 */ 0x02, 0xFF, 0x84, 0x30, 0xFF, 0x84, 0x30, 
  /* RLE: 011 Pixels @ 045,019 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,019 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 010 Pixels @ 058,019 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 007 Pixels @ 068,019 */ 0x07, 0xFF, 0x35, 0x5C, 0xFF, 0xCF, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF, 0x5D, 0xDD, 0xFF, 0x9E, 0xBE, 0xFF, 0xE7, 0x9F, 0xFF, 0x04, 0xDB, 
  /* RLE: 006 Pixels @ 075,019 */ 0x86, 0xFF, 0x04, 0xBB, 
  /* ABS: 004 Pixels @ 081,019 */ 0x04, 0xFF, 0x55, 0x9C, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 
  /* RLE: 004 Pixels @ 085,019 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 089,019 */ 0x05, 0xFF, 0x75, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x7F, 0xFF, 0x2D, 0x3C, 0xFF, 0x04, 0xBB, 
  /* RLE: 004 Pixels @ 094,019 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,019 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1D, 0x1C, 
  /* RLE: 010 Pixels @ 101,019 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,019 */ 0x03, 0xE7, 0x04, 0xDB, 0x82, 0x04, 0xBB, 0xE3, 0x6E, 0x3D, 
  /* RLE: 012 Pixels @ 002,020 */ 0x8C, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 014,020 */ 0x03, 0xFF, 0xA5, 0x34, 0xFF, 0x29, 0x65, 0xFF, 0xBD, 0xD7, 
  /* RLE: 005 Pixels @ 017,020 */ 0x85, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 022,020 */ 0x02, 0xFF, 0x63, 0x0C, 0xFF, 0x7B, 0xEF, 
  /* RLE: 010 Pixels @ 024,020 */ 0x8A, 0xFF, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 034,020 */ 0x04, 0xFF, 0x73, 0xAE, 0xFF, 0x73, 0x8E, 0xFF, 0x6B, 0x6D, 0xFF, 0x8C, 0x71, 
  /* RLE: 005 Pixels @ 038,020 */ 0x85, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,020 */ 0x02, 0xFF, 0x84, 0x30, 0xFF, 0x84, 0x30, 
  /* RLE: 011 Pixels @ 045,020 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,020 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 008 Pixels @ 058,020 */ 0x88, 0xFF, 0x04, 0xDB, 
  /* ABS: 009 Pixels @ 066,020 */ 0x09, 0xFF, 0x04, 0xBB, 0xFF, 0x45, 0x9C, 0xFF, 0xF7, 0xDF, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xFD, 0xFF, 0x04, 0x7B, 0xFF, 0xA6, 0xDE, 0xFF, 0xEF, 0x9F, 0xFF, 0x04, 0xFC, 
  /* RLE: 006 Pixels @ 075,020 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 081,020 */ 0x04, 0xFF, 0x5D, 0xBC, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 
  /* RLE: 003 Pixels @ 085,020 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 006 Pixels @ 088,020 */ 0x06, 0xFF, 0x04, 0xBB, 0xFF, 0xAE, 0xBE, 0xFF, 0xE7, 0x9F, 0xFF, 0xB7, 0x1E, 0xFF, 0xCF, 0x3E, 0xFF, 0x1D, 0x1C, 
  /* RLE: 004 Pixels @ 094,020 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,020 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1D, 0x1C, 
  /* RLE: 010 Pixels @ 101,020 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 111,020 */ 0x03, 0xCE, 0x04, 0xDB, 0x29, 0x04, 0xBB, 0xCF, 0x2D, 0x5C, 
  /* RLE: 011 Pixels @ 002,021 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 013,021 */ 0x03, 0xFF, 0xAD, 0x55, 0xFF, 0x39, 0xC7, 0xFF, 0xA5, 0x14, 
  /* RLE: 006 Pixels @ 016,021 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 022,021 */ 0x02, 0xFF, 0x63, 0x0C, 0xFF, 0x7B, 0xEF, 
  /* RLE: 009 Pixels @ 024,021 */ 0x89, 0xFF, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 033,021 */ 0x06, 0xFF, 0xE7, 0x3C, 0xFF, 0x42, 0x28, 0xFF, 0xC6, 0x18, 0xFF, 0xE7, 0x3C, 0xFF, 0x39, 0xE7, 0xFF, 0xA5, 0x14, 
  /* RLE: 004 Pixels @ 039,021 */ 0x84, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,021 */ 0x02, 0xFF, 0x84, 0x30, 0xFF, 0x84, 0x30, 
  /* RLE: 011 Pixels @ 045,021 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,021 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 008 Pixels @ 058,021 */ 0x88, 0xFF, 0x04, 0xDB, 
  /* ABS: 009 Pixels @ 066,021 */ 0x09, 0xFF, 0x04, 0xBB, 0xFF, 0x3D, 0x9C, 0xFF, 0xB6, 0xDE, 0xFF, 0x45, 0x9C, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0x9B, 0xFF, 0xA6, 0xDE, 0xFF, 0xEF, 0x9F, 0xFF, 0x04, 0xFC, 
  /* RLE: 006 Pixels @ 075,021 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 081,021 */ 0x04, 0xFF, 0x5D, 0xBC, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 
  /* RLE: 003 Pixels @ 085,021 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 007 Pixels @ 088,021 */ 0x07, 0xFF, 0x1D, 0x1C, 0xFF, 0xE7, 0x9F, 0xFF, 0xA6, 0xBE, 0xFF, 0x1C, 0xFC, 0xFF, 0xE7, 0x9F, 0xFF, 0xBF, 0x1E, 0xFF, 0x04, 0xFB, 
  /* RLE: 003 Pixels @ 095,021 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 098,021 */ 0x03, 0xFF, 0x8E, 0x5D, 0xFF, 0xD7, 0x5F, 0xFF, 0x1D, 0x1C, 
  /* RLE: 010 Pixels @ 101,021 */ 0x8A, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 111,021 */ 0x04, 0xA9, 0x04, 0xDB, 0x00, 0xF7, 0xDF, 0x9F, 0x3D, 0x9C, 0xFF, 0xBF, 0x3E, 
  /* RLE: 009 Pixels @ 003,022 */ 0x89, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 012,022 */ 0x03, 0xFF, 0xC6, 0x38, 0xFF, 0x42, 0x08, 0xFF, 0x9C, 0xF3, 
  /* RLE: 007 Pixels @ 015,022 */ 0x87, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 022,022 */ 0x02, 0xFF, 0x63, 0x2C, 0xFF, 0x7B, 0xEF, 
  /* RLE: 009 Pixels @ 024,022 */ 0x89, 0xFF, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 033,022 */ 0x06, 0xFF, 0x94, 0x92, 0xFF, 0x52, 0x8A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAD, 0x75, 0xFF, 0x73, 0x8E, 
  /* RLE: 004 Pixels @ 039,022 */ 0x84, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 043,022 */ 0x02, 0xFF, 0x8C, 0x71, 0xFF, 0x8C, 0x71, 
  /* RLE: 011 Pixels @ 045,022 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,022 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 011 Pixels @ 058,022 */ 0x8B, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 069,022 */ 0x05, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0x9B, 0xFF, 0xA6, 0xDE, 0xFF, 0xE7, 0x9F, 
  /* RLE: 006 Pixels @ 074,022 */ 0x86, 0xFF, 0x04, 0xDB, 
  /* ABS: 026 Pixels @ 080,022 */ 0x1A, 0xFF, 0x04, 0xBB, 0xFF, 0x5D, 0xBC, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xBB, 0xFF, 0x7E, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0x3D, 0x7C, 0xFF, 0x04, 0xBB, 0xFF, 0x5D, 0xDD, 
        0xFF, 0xE7, 0x9F, 0xFF, 0x14, 0xFB, 0xFF, 0x04, 0x9B, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0x9B, 0xFF, 0x86, 0x3D, 0xFF, 0xD7, 0x5E, 0xFF, 0x14, 0xDB, 0xFF, 0x04, 0x9B, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0x9B, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xFB, 
  /* RLE: 004 Pixels @ 106,022 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 005 Pixels @ 110,022 */ 0x05, 0xFF, 0x04, 0xBB, 0x73, 0x66, 0x1D, 0x00, 0xFF, 0xFF, 0x3F, 0x3D, 0x5C, 0xFC, 0x55, 0xDD, 
  /* RLE: 009 Pixels @ 003,023 */ 0x89, 0xFF, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 012,023 */ 0x06, 0xFF, 0xEF, 0x7D, 0xFF, 0xC6, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xBE, 0xFF, 0xD6, 0xBA, 0xFF, 0xD6, 0x9A, 
  /* RLE: 003 Pixels @ 018,023 */ 0x83, 0xFF, 0xD6, 0xBA, 
  /* ABS: 004 Pixels @ 021,023 */ 0x04, 0xFF, 0xD6, 0x9A, 0xFF, 0x52, 0xAA, 0xFF, 0x6B, 0x6D, 0xFF, 0xE7, 0x1C, 
  /* RLE: 003 Pixels @ 025,023 */ 0x83, 0xFF, 0xD6, 0xBA, 
  /* ABS: 007 Pixels @ 028,023 */ 0x07, 0xFF, 0xD6, 0x9A, 0xFF, 0xDE, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCE, 0x79, 0xFF, 0x39, 0xE7, 0xFF, 0xB5, 0xB6, 
  /* RLE: 003 Pixels @ 035,023 */ 0x83, 0xFF, 0xFF, 0xFF, 
  /* ABS: 012 Pixels @ 038,023 */ 0x0C, 0xFF, 0xDE, 0xFB, 0xFF, 0xAD, 0x75, 0xFF, 0xAD, 0x75, 0xFF, 0xB5, 0x96, 0xFF, 0xB5, 0x96, 0xFF, 0x63, 0x0C, 0xFF, 0x63, 0x0C, 0xFF, 0xB5, 0x96, 0xFF, 0xB5, 0x96, 0xFF, 0xAD, 0x75, 0xFF, 0xAD, 0x55, 0xFF, 0xF7, 0x9E, 
  /* RLE: 006 Pixels @ 050,023 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,023 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 013 Pixels @ 058,023 */ 0x8D, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 071,023 */ 0x03, 0xFF, 0x04, 0x9B, 0xFF, 0x9E, 0xDE, 0xFF, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 074,023 */ 0x86, 0xFF, 0xAE, 0xDE, 
  /* ABS: 010 Pixels @ 080,023 */ 0x0A, 0xFF, 0xAE, 0xBE, 0xFF, 0xC7, 0x3E, 0xFF, 0xFF, 0xDF, 0xFF, 0x5D, 0xDD, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xBB, 0xFF, 0x35, 0x5C, 0xFF, 0xEF, 0xBF, 0xFF, 0xAE, 0xDE, 
  /* RLE: 003 Pixels @ 090,023 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 093,023 */ 0x01, 0xFF, 0x35, 0x5C, 
  /* RLE: 004 Pixels @ 094,023 */ 0x84, 0xFF, 0x66, 0x1D, 
  /* ABS: 007 Pixels @ 098,023 */ 0x07, 0xFF, 0xBE, 0xFE, 0xFF, 0xE7, 0x9F, 0xFF, 0x76, 0x3D, 0xFF, 0x5E, 0x1D, 0xFF, 0x66, 0x1D, 0xFF, 0x6E, 0x3D, 0xFF, 0x25, 0x5C, 
  /* RLE: 005 Pixels @ 105,023 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 006 Pixels @ 110,023 */ 0x06, 0xE3, 0x04, 0x9B, 0x21, 0x76, 0x1D, 0x00, 0xFF, 0xFF, 0x03, 0xAE, 0xFE, 0xB8, 0x14, 0xFC, 0xFF, 0xC7, 0x5E, 
  /* RLE: 011 Pixels @ 004,024 */ 0x8B, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 015,024 */ 0x03, 0xFF, 0xD6, 0x9A, 0xFF, 0x4A, 0x49, 0xFF, 0x39, 0xC7, 
  /* RLE: 004 Pixels @ 018,024 */ 0x84, 0xFF, 0x39, 0xE7, 
  /* ABS: 002 Pixels @ 022,024 */ 0x02, 0xFF, 0x31, 0x86, 0xFF, 0x31, 0xA6, 
  /* RLE: 004 Pixels @ 024,024 */ 0x84, 0xFF, 0x39, 0xE7, 
  /* ABS: 006 Pixels @ 028,024 */ 0x06, 0xFF, 0x39, 0xC7, 0xFF, 0x73, 0xAE, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xBE, 0xFF, 0x5A, 0xCB, 0xFF, 0x7B, 0xCF, 
  /* RLE: 004 Pixels @ 034,024 */ 0x84, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 038,024 */ 0x02, 0xFF, 0xDE, 0xFB, 0xFF, 0x42, 0x08, 
  /* RLE: 003 Pixels @ 040,024 */ 0x83, 0xFF, 0x4A, 0x69, 
  /* ABS: 002 Pixels @ 043,024 */ 0x02, 0xFF, 0x52, 0xAA, 0xFF, 0x52, 0xAA, 
  /* RLE: 003 Pixels @ 045,024 */ 0x83, 0xFF, 0x4A, 0x69, 
  /* ABS: 002 Pixels @ 048,024 */ 0x02, 0xFF, 0x42, 0x08, 0xFF, 0xDE, 0xFB, 
  /* RLE: 006 Pixels @ 050,024 */ 0x86, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,024 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 013 Pixels @ 058,024 */ 0x8D, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 071,024 */ 0x03, 0xFF, 0x04, 0x9B, 0xFF, 0x9E, 0xDE, 0xFF, 0xFF, 0xFF, 
  /* RLE: 006 Pixels @ 074,024 */ 0x86, 0xFF, 0xAE, 0xDE, 
  /* ABS: 010 Pixels @ 080,024 */ 0x0A, 0xFF, 0xAE, 0xBE, 0xFF, 0xCF, 0x3E, 0xFF, 0xFF, 0xDF, 0xFF, 0x65, 0xDD, 0xFF, 0x04, 0xBB, 0xFF, 0x04, 0xDB, 0xFF, 0x0C, 0xFC, 0xFF, 0xBE, 0xFE, 0xFF, 0xE7, 0x9F, 0xFF, 0x25, 0x3C, 
  /* RLE: 003 Pixels @ 090,024 */ 0x83, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 093,024 */ 0x02, 0xFF, 0x0C, 0xFB, 0xFF, 0xF7, 0xBF, 
  /* RLE: 003 Pixels @ 095,024 */ 0x83, 0xFF, 0xFF, 0xDF, 
  /* ABS: 002 Pixels @ 098,024 */ 0x02, 0xFF, 0xF7, 0xBF, 0xFF, 0xEF, 0xBF, 
  /* RLE: 003 Pixels @ 100,024 */ 0x83, 0xFF, 0xFF, 0xDF, 
  /* ABS: 003 Pixels @ 103,024 */ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 004 Pixels @ 106,024 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 007 Pixels @ 110,024 */ 0x07, 0x91, 0x15, 0x1C, 0x00, 0xD7, 0x7F, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x37, 0x15, 0x1C, 0xF7, 0x3D, 0x7C, 0xFF, 0xF7, 0xDF, 
  /* RLE: 010 Pixels @ 005,025 */ 0x8A, 0xFF, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 015,025 */ 0x03, 0xFF, 0xFF, 0xDF, 0xFF, 0xE7, 0x1C, 0xFF, 0xDE, 0xFB, 
  /* RLE: 004 Pixels @ 018,025 */ 0x84, 0xFF, 0xE7, 0x1C, 
  /* ABS: 001 Pixels @ 022,025 */ 0x01, 0xFF, 0xE7, 0x3C, 
  /* RLE: 005 Pixels @ 023,025 */ 0x85, 0xFF, 0xE7, 0x1C, 
  /* ABS: 006 Pixels @ 028,025 */ 0x06, 0xFF, 0xDE, 0xFB, 0xFF, 0xEF, 0x5D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xFB, 0xFF, 0xF7, 0xBE, 
  /* RLE: 005 Pixels @ 034,025 */ 0x85, 0xFF, 0xFF, 0xFF, 
  /* RLE: 010 Pixels @ 039,025 */ 0x8A, 0xFF, 0xF7, 0x9E, 
  /* RLE: 007 Pixels @ 049,025 */ 0x87, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,025 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 013 Pixels @ 058,025 */ 0x8D, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 071,025 */ 0x03, 0xFF, 0x04, 0xBB, 0xFF, 0x7E, 0x3D, 0xFF, 0xAE, 0xBE, 
  /* RLE: 007 Pixels @ 074,025 */ 0x87, 0xFF, 0x04, 0xDB, 
  /* ABS: 008 Pixels @ 081,025 */ 0x08, 0xFF, 0x45, 0x7C, 0xFF, 0xBE, 0xFE, 0xFF, 0x4D, 0x9C, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xDB, 0xFF, 0x04, 0xFB, 0xFF, 0x3D, 0x7C, 0xFF, 0x2D, 0x3C, 
  /* RLE: 005 Pixels @ 089,025 */ 0x85, 0xFF, 0x04, 0xDB, 
  /* ABS: 001 Pixels @ 094,025 */ 0x01, 0xFF, 0x15, 0x1C, 
  /* RLE: 008 Pixels @ 095,025 */ 0x88, 0xFF, 0x1D, 0x1C, 
  /* ABS: 002 Pixels @ 103,025 */ 0x02, 0xFF, 0x1D, 0x3C, 0xFF, 0x0C, 0xFC, 
  /* RLE: 004 Pixels @ 105,025 */ 0x84, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 109,025 */ 0x02, 0xDF, 0x04, 0x9B, 0x16, 0x4D, 0xBD, 
  /* RLE: 003 Pixels @ 111,025 */ 0x83, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 002,026 */ 0x03, 0x00, 0xE7, 0xBF, 0x77, 0x25, 0x5C, 0xFF, 0x76, 0x5D, 
  /* RLE: 051 Pixels @ 005,026 */ 0xB3, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,026 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 050 Pixels @ 058,026 */ 0xB2, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 108,026 */ 0x02, 0xFA, 0x04, 0xDB, 0x4F, 0x55, 0xDD, 
  /* RLE: 005 Pixels @ 110,026 */ 0x85, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 003,027 */ 0x03, 0x06, 0x9E, 0xBE, 0xA2, 0x04, 0x9B, 0xFF, 0x8E, 0x9E, 
  /* RLE: 050 Pixels @ 006,027 */ 0xB2, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,027 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 050 Pixels @ 058,027 */ 0xB2, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 108,027 */ 0x02, 0x7A, 0x04, 0x9B, 0x00, 0xD7, 0x7F, 
  /* RLE: 006 Pixels @ 110,027 */ 0x86, 0x00, 0xFF, 0xFF, 
  /* ABS: 003 Pixels @ 004,028 */ 0x03, 0x0D, 0x66, 0x1D, 0xA7, 0x04, 0x9B, 0xFF, 0x86, 0x7E, 
  /* RLE: 049 Pixels @ 007,028 */ 0xB1, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,028 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 049 Pixels @ 058,028 */ 0xB1, 0xFF, 0x04, 0xDB, 
  /* ABS: 002 Pixels @ 107,028 */ 0x02, 0x83, 0x04, 0xBB, 0x00, 0x96, 0xBE, 
  /* RLE: 008 Pixels @ 109,028 */ 0x88, 0x00, 0xFF, 0xFF, 
  /* ABS: 004 Pixels @ 005,029 */ 0x04, 0x04, 0x76, 0x5D, 0x8C, 0x04, 0x7B, 0xF7, 0x4D, 0xDD, 0xFF, 0xE7, 0xBF, 
  /* RLE: 047 Pixels @ 009,029 */ 0xAF, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,029 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 047 Pixels @ 058,029 */ 0xAF, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 105,029 */ 0x03, 0xEC, 0x04, 0x9B, 0x6A, 0x04, 0xBB, 0x00, 0xA6, 0xDE, 
  /* RLE: 010 Pixels @ 108,029 */ 0x8A, 0x00, 0xFF, 0xFF, 
  /* ABS: 005 Pixels @ 006,030 */ 0x05, 0x02, 0xAF, 0x1E, 0x53, 0x5D, 0xFD, 0xD8, 0x15, 0x1C, 0xFF, 0x8E, 0x9E, 0xFF, 0xF7, 0xDF, 
  /* RLE: 045 Pixels @ 011,030 */ 0xAD, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,030 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 046 Pixels @ 058,030 */ 0xAE, 0xFF, 0x04, 0xDB, 
  /* ABS: 003 Pixels @ 104,030 */ 0x03, 0xBF, 0x04, 0xBB, 0x3A, 0x86, 0x7D, 0x00, 0xBF, 0x1E, 
  /* RLE: 013 Pixels @ 107,030 */ 0x8D, 0x00, 0xFF, 0xFF, 
  /* ABS: 006 Pixels @ 008,031 */ 0x06, 0x11, 0x5D, 0xFD, 0x77, 0x0D, 0x1C, 0xDD, 0x15, 0x3C, 0xFB, 0x6E, 0x3D, 0xFF, 0xCF, 0x5F, 0xFF, 0xF7, 0xDF, 
  /* RLE: 042 Pixels @ 014,031 */ 0xAA, 0xFF, 0xFF, 0xFF, 
  /* ABS: 002 Pixels @ 056,031 */ 0x02, 0xFF, 0x66, 0x1D, 0xFF, 0x04, 0xBB, 
  /* RLE: 043 Pixels @ 058,031 */ 0xAB, 0xFF, 0x04, 0xDB, 
  /* ABS: 004 Pixels @ 101,031 */ 0x04, 0xF9, 0x04, 0xDB, 0xD0, 0x04, 0xFC, 0x5E, 0x15, 0x1C, 0x06, 0x96, 0xBE, 
  /* RLE: 017 Pixels @ 105,031 */ 0x91, 0x00, 0xFF, 0xFF, 
  /* ABS: 008 Pixels @ 010,032 */ 0x08, 0x0A, 0x6E, 0x3D, 0x55, 0x6E, 0x3D, 0x97, 0x2D, 0x5C, 0xBD, 0x25, 0x5C, 0xD8, 0x5D, 0xFD, 0xED, 0x7E, 0x5D, 0xF8, 0x8E, 0x9E, 0xFE, 0x96, 0xBE, 
  /* RLE: 037 Pixels @ 018,032 */ 0xA5, 0xFF, 0x96, 0xBE, 
  /* ABS: 003 Pixels @ 055,032 */ 0x03, 0xFF, 0xA6, 0xDE, 0xFF, 0x3D, 0x9C, 0xFF, 0x04, 0xBB, 
  /* RLE: 037 Pixels @ 058,032 */ 0xA5, 0xFF, 0x04, 0xDB, 
  /* ABS: 008 Pixels @ 095,032 */ 0x08, 0xFD, 0x04, 0xDB, 0xF6, 0x04, 0xDB, 0xE9, 0x04, 0xDB, 0xD5, 0x04, 0xDB, 0xB7, 0x04, 0xDB, 0x8B, 0x04, 0xDB, 0x45, 0x04, 0xBB, 0x03, 0x2D, 0x7C, 
  /* RLE: 009 Pixels @ 103,032 */ 0x89, 0x00, 0xFF, 0xFF, 
};  //3696 pixels compress to 3733 bytes


GUI_CONST_STORAGE GUI_BITMAP bmcooker_right = {
  112,  //xSize
  33,  //ySize
  336,  //ByteBytesPerLine
  24,  //BitsPerPixel
  (unsigned char *)_accooker_right,  //Pointer to picture data
  NULL,  //Pointer to palette
  GUI_DRAW_AlphaRLEM16M
};  

