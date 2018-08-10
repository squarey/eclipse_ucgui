

#include "GUI_ReDefine.h"
#include "string.h"
#include "stdarg.h"

/* �ڴ濽�� */
void GUI_memcpy(void * pdest, const void * psrc, unsigned int size)
{
	//eLIBs_memcpy(pdest, psrc, size);
	memcpy(pdest, psrc, size);
}
/* �ַ������� */
void GUI_strcpy(char * pdest, const char * psrc)
{
	//eLIBs_strcpy(pdest, psrc);
	strcpy(pdest, psrc);
}
int GUI_strcmp(const char *p1_str, const char *p2_str)
{
	//return eLIBs_strcmp(p1_str, p2_str);
	return strcmp(p1_str, p2_str);
}
unsigned int GUI_strlen(const char *str)
{
	return strlen(str);
}
char *GUI_strstr(const char *pSrc,const char *pDes)
{
	return strstr(pSrc, pDes);
}
/* �ڴ�Ƚ� */
unsigned char GUI_memcmp(const void *p1_mem, const void *p2_mem, unsigned int size)
{
	return memcmp(p1_mem, p2_mem, size);
}
/* �ڴ����data_val��ֵ */
void GUI_memset(void *pmem, unsigned char data_val, unsigned int size)
{
	memset(pmem, data_val, size);
}

void *GUI_memmove(void *dest, const void *src, unsigned int count)
{
	return memmove(dest,src,count);
}
/* ����ָ�����ȵ��ַ��� */
void GUI_strncpy(char *pdest, const char *psrc, unsigned int len_max)
{
	strncpy(pdest, psrc, len_max);
}

UC_FILE *GUI_fopen(const char * filename, const char * mode)
{
	return (UC_FILE *)fopen(filename, mode);
}

int GUI_fseek(UC_FILE * stream, int offset, int whence)
{
	return fseek((FILE *)stream, offset, whence);
}

unsigned int GUI_fread(void * ptr, unsigned int size, unsigned int nmemb, UC_FILE * stream)
{
	return fread(ptr, size, nmemb, (FILE *)stream);
}


int GUI_fclose(UC_FILE * stream)
{
	return fclose((FILE *)stream);
}

int GUI_sprintf(char *buffer, const char *format, ...)
{
	va_list args;
	int rv = 0;
	va_start(args, format);
	rv = _vsnprintf(buffer, 1000, format, args);
	va_end(args);

	return rv;
}

void IntegerToString(int ivalue, char *str)
{
	GUI_sprintf(str,"%02d",ivalue);
}
void IntegerToTime(int hours, int minutes, char *str)
{
	GUI_sprintf(str,"%02d:%02d",hours,minutes);
}



