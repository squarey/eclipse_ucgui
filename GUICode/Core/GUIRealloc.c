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
File        : GUIRealloc.C
Purpose     : Dynamic memory management
----------------------------------------------------------------------
*/

//#include <stddef.h>           /* needed for definition of NULL */

#include "GUI_Protected.h"
#include "GUIDebug.h"
#include "GUI_ReDefine.h"


/*********************************************************************
*
*       Public routines: Using internal memory management
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ALLOC_Realloc
*
* Purpose:
*   Reallocate a memory block. This is typically used to grow memory
*   blocks. The contents of the old memory block are copied into the
*   new block (or as much as fits in case of shrinkage).
*   In case of error the old memory block (and its handle) remain
*   unchanged.
*
*  Parameters
*    hOld       Current handle of the memory block. 0 (Invalid handle) is permitted.
*    NewSize    Number of bytes required
*
* Return value:
*   On success:    Handle of newly allocated memory block
*   On error:      0
*/
GUI_HMEM GUI_ALLOC_Realloc(GUI_HMEM hOld, I32 NewSize)
{
	GUI_HMEM hNew;
	hNew = GUI_ALLOC_AllocNoInit(NewSize);
	if (hNew && hOld) {
		void *pNew, *pOld;
		I32 Size, OldSize;
		OldSize = GUI_ALLOC_GetSize(hOld);
		Size = (OldSize < NewSize) ? OldSize : NewSize;
		pNew = GUI_ALLOC_h2p(hNew);
		pOld = GUI_ALLOC_h2p(hOld);
		GUI_memcpy(pNew, pOld, Size);
		GUI_ALLOC_Free(hOld);
	}
	return hNew;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
