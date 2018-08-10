

#ifndef _GUI_PICTURE_MEM_H
#define _GUI_PICTURE_MEM_H

#include "GUI.h"


typedef struct
{
    U32 TotalSize;				/* Picture total buffer size */
    U32 FreeCount;				
    U32 FreeSize;					/* free  */
    U32 FreeBiggestSize;			/* biggest free */
    U32 UsedCount;				/* used */
    U8  UsedPercent;
    U8  FragPercent;
}PicMemoryMonitor_t;

void GUI_PicMemoryInit(void *pBufferStart, U32 Size);
void *GUI_PicMemoryAlloc(U32 Size);
void GUI_PicMemoryFree(const void * pData);
void GUI_PicMemoryGetMonitor(PicMemoryMonitor_t * pMonitor);

#endif
