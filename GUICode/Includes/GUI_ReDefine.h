

#ifndef _GUI_REDEFINE_H
#define _GUI_REDEFINE_H

#include "stdio.h"

#ifndef NULL
#define NULL	(char *)0
#endif

/*typedef struct __UCFILE
{
    unsigned int   tmp;
}UC_FILE;
*/

#define UC_FILE FILE

void GUI_memcpy(void * pdest, const void * psrc, unsigned int size);
void GUI_strcpy(char * pdest, const char * psrc);
int GUI_strcmp(const char *p1_str, const char *p2_str);
unsigned int GUI_strlen(const char *str);
char *GUI_strstr(const char *pSrc,const char *pDes);
unsigned char GUI_memcmp(const void *p1_mem, const void *p2_mem, unsigned int size);
void GUI_memset(void *pmem, unsigned char data_val, unsigned int size);
void *GUI_memmove(void *dest, const void *src, unsigned int count);
void GUI_strncpy(char *pdest, const char *psrc, unsigned int len_max);
UC_FILE *GUI_fopen(const char * filename, const char * mode);
int GUI_fseek(UC_FILE * stream, int offset, int whence);
unsigned int GUI_fread(void * ptr, unsigned int size, unsigned int nmemb, UC_FILE * stream);
int GUI_fclose(UC_FILE * stream);
int GUI_sprintf(char *buffer, const char *format, ...);
void IntegerToString(int ivalue, char *str);
void IntegerToTime(int hours, int minutes, char *str);

#endif

