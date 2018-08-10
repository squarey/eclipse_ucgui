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
File        : EDITFloat.c
Purpose     : Edit decimal values
---------------------------END-OF-HEADER------------------------------
*/

#include <math.h>

#include "EDIT_Private.h"
#include "GUIDebug.h"

#if GUI_WINSUPPORT && EDIT_SUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_SetFloatMode
*/
void EDIT_SetFloatMode(EDIT_Handle hEdit, float Value, float Min, float Max, I32 Shift, U8 Flags)
{
	I32 _Value, _Min, _Max;
	float Scale;
	if (hEdit) {
		Scale  =(float)GUI_Pow10[Shift];
		_Value = floor(Scale * Value + 0.5);
		_Min   = floor(Scale * Min + 0.5);
		_Max   = floor(Scale * Max + 0.5);
		EDIT_SetDecMode(hEdit, _Value, _Min, _Max, Shift, Flags);
	}
}

/*********************************************************************
*
*       EDIT_GetFloatValue
*/
float EDIT_GetFloatValue(EDIT_Handle hObj)
{
	float Value = 0;
	if (hObj) {
		float Scale;
		EDIT_Obj * pObj;
		pObj  = EDIT_H2P(hObj);
		Scale = (float)GUI_Pow10[pObj->NumDecs];
		Value = (float)(I32)pObj->CurrentValue / Scale;
	}
	return Value;
}

/*********************************************************************
*
*       EDIT_SetFloatValue
*/
void EDIT_SetFloatValue(EDIT_Handle hObj, float Value)
{
	if (hObj) {
		float Scale;
		EDIT_Obj * pObj;
		pObj  = EDIT_H2P(hObj);
		Scale = (float)GUI_Pow10[pObj->NumDecs];
		Value *= Scale;
		EDIT_SetValue(hObj, (I32)(Value + (Value >= 0 ? 0.5 : -0.5)));
	}
}

#else  /* avoid empty object files */

void EditFloat_C(void);
void EditFloat_C(void){}

#endif /* GUI_WINSUPPORT */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
