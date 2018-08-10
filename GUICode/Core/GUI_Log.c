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
File        : GUI_Log.C
Purpose     : Logging (used only at higher debug levels)
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
//#include <string.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*      defines
*
**********************************************************************
*/

#define MAXLEN 50

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _CopyString
*/
static void _CopyString(char* d, const char* s, I32 MaxLen)
{
	while ((MaxLen > 0) && *s) {
		*d++ = *s++;
		MaxLen--;
	}
	*d = 0;
}

/*********************************************************************
*
*       Public code
*
*  Note: These routines are needed only in higher debug levels.
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_Log
*/
void GUI_Log(const char *s) 
{
	GUI_LOG_OUT(s);
}

/*********************************************************************
*
*       GUI_Log1
*/
void GUI_Log1(const char *s, I32 p0) 
{
	char ac[MAXLEN + 10];
	char* sOut = ac;
	_CopyString(ac, s, MAXLEN);
	sOut += GUI_strlen(sOut);
	GUI__AddSpaceHex(p0, 8, &sOut);
	GUI_Log(ac);
}

/*********************************************************************
*
*       GUI_Log2
*/
void GUI_Log2(const char *s, I32 p0, I32 p1) 
{
	char ac[MAXLEN + 20];
	char* sOut = ac;
	_CopyString(ac, s, MAXLEN);
	sOut += GUI_strlen(sOut);
	GUI__AddSpaceHex(p0, 8, &sOut);
	GUI__AddSpaceHex(p1, 8, &sOut);
	GUI_Log(ac);
}

/*********************************************************************
*
*       GUI_Log3
*/
void GUI_Log3(const char *s, I32 p0, I32 p1, I32 p2) 
{
	char ac[MAXLEN + 30];
	char* sOut = ac;
	_CopyString(ac, s, MAXLEN);
	sOut += GUI_strlen(sOut);
	GUI__AddSpaceHex(p0, 8, &sOut);
	GUI__AddSpaceHex(p1, 8, &sOut);
	GUI__AddSpaceHex(p2, 8, &sOut);
	GUI_Log(ac);
}

/*********************************************************************
*
*       GUI_Log4
*/
void GUI_Log4(const char *s, I32 p0, I32 p1, I32 p2, I32 p3) 
{
	char ac[MAXLEN + 40];
	char* sOut = ac;
	_CopyString(ac, s, MAXLEN);
	sOut += GUI_strlen(sOut);
	GUI__AddSpaceHex(p0, 8, &sOut);
	GUI__AddSpaceHex(p1, 8, &sOut);
	GUI__AddSpaceHex(p2, 8, &sOut);
	GUI__AddSpaceHex(p3, 8, &sOut);
	GUI_Log(ac);
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
