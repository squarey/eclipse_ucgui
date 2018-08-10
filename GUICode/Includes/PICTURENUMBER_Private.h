


#ifndef PICTURENUMBER_PRIVATE_H
#define PICTURENUMBER_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "PICTURENUMBER.h"

#if GUI_WINSUPPORT && PICTURENUMBER_SUPPORT

typedef struct 
{
	WIDGET Widget;
	U32 DispNumber;
	U32 OldNumberLen;
	void *NumberBuffer[12];
	
}PICTURENUMBER_Obj;

#define PICTURENUMBER_H2P(h) (PICTURENUMBER_Obj *)GUI_ALLOC_h2p(h)
#define PICTURENUMBER_INIT_ID(p)

#endif 


#endif


