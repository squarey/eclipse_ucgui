/*
 * GUI_StyleDraw.c
 *
 *  Created on: 2018年4月28日
 *      Author: Administrator
 */
#include "GUI_StyleDraw.h"
#include "GUI_Circle.h"
#include "GUI_Protected.h"

static U16 __DrawContRadiusCorrect(U16 Radius, U16 Width, U16 Height)
{
	if(Radius >= (Width >> 1)){
		Radius = (Width >> 1);
		if(Radius != 0){
			Radius--;
		}
	}
	if(Radius >= (Height >> 1)) {
		Radius = (Height >> 1);
		if(Radius != 0){
			Radius--;
		}
	}

	return Radius;
}
static void __RectSet(GUI_RECT * pRect, I16 x0, I16 y0, I16 x1, I16 y1)
{
    pRect->x0 = x0;
    pRect->y0 = y0;
    pRect->x1 = x1;
    pRect->y1 = y1;
}
static I16 __RectGetWidth(const GUI_RECT * pRect)
{
    return pRect->x1 - pRect->x0 + 1;
}
static I16 __RectGetHeight(const GUI_RECT * pRect)
{
    return pRect->y1 - pRect->y0 + 1;
}
GUI_COLOR GUI_ColorMix(GUI_COLOR Color1, GUI_COLOR Color2, U8 Mix)
{
	GUI_COLOR ResultColor;
	U16 Red1 = 0, Red2 = 0, Red = 0;
	U16 Green1 = 0, Green2 = 0, Green = 0;
	U16 Blue1 = 0, Blue2 = 0, Blue = 0;

	Red1 = Color1 & 0xff;
	Green1 = (Color1 >> 8) & 0xff;
	Blue1 = (Color1 >> 16) & 0xff;

	Red2 = Color2 & 0xff;
	Green2 = (Color2 >> 8) & 0xff;
	Blue2 = (Color2 >> 16) & 0xff;

	Red = (Red1 * Mix + Red2 * (255 - Mix)) >> 8;
	Green = (Green1 * Mix + Green2 * (255 - Mix)) >> 8;
	Blue = (Blue1 * Mix + Blue2 * (255 - Mix)) >> 8;

	ResultColor = (Blue << 16) | (Green << 8) | Red;
    return ResultColor;
}

static void _DrawRectMainMiddle(const GUI_RECT * pRect, const GUI_FullRectStyle *pStyle)
{
	U8 Mix;
	GUI_RECT WorkRect;
    U16 Radius = pStyle->Radius;

    GUI_COLOR mColor = pStyle->MainColor;
    GUI_COLOR gColor = pStyle->GradColor;
    U8 Opa = pStyle->Opacity;
    I16 Height = GUI_RectGetHeight(pRect);
    I16 Width = GUI_RectGetWidth(pRect);

    Radius = __DrawContRadiusCorrect(Radius, Width, Height);

    /*If the Radius is too big then there is no body*/
    if(Radius > Height / 2){
    	return;
    }

	WorkRect.x0 = pRect->x0;
	WorkRect.x1 = pRect->x1;
    if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)) {
    	WorkRect.y0 = pRect->y0 + Radius;
    	WorkRect.y1 = pRect->y1 - Radius;
    	mColor &= 0x00ffffff;
    	mColor |= (Opa << 24);
    	GUI_SetColor(mColor);
    	GUI_FillRectEx(&WorkRect);
    } else {
    	I16 Row = 0;
    	I16 RowStart = pRect->y0 + Radius;
    	I16 RowEnd = pRect->y1 - Radius;
    	GUI_COLOR ActColor;
        if(RowStart < 0){
        	RowStart = 0;
        }
		for(Row = RowStart; Row <= RowEnd; Row++){
			WorkRect.y0 = Row;
			WorkRect.y1 = Row;
			Mix = (U32)((U32)(pRect->y1 - WorkRect.y0) << 8) / Height;
			ActColor = GUI_ColorMix(mColor, gColor, Mix);
			ActColor |= (Opa << 24);
			GUI_SetColor(ActColor);
			//GUI_FillRectEx(&WorkRect);
			GUI_DrawHLine(Row, WorkRect.x0, WorkRect.x1);
        }
    }
}

static void _DrawRectMainCorner(const GUI_RECT * pRect, const GUI_FullRectStyle * pStyle)
{
	U8 Mix;
	GUI_RECT EdgeTopArea;
	GUI_RECT MidTopArea;
	GUI_RECT MidBottonArea;
	GUI_RECT EdgeBottonArea;

	GUI_POINT Circle;
	I16 CircleTemp = 0;
	U16 Radius = pStyle->Radius;
	GUI_COLOR mColor = pStyle->MainColor;
	GUI_COLOR gColor = pStyle->GradColor;
	GUI_COLOR ActColor;
	U8 Opa = pStyle->Opacity;
    I16 Height = GUI_RectGetHeight(pRect);
    I16 Width = GUI_RectGetWidth(pRect);

    GUI_POINT LeftTopOrigo;   	/*Left  Top    origo*/
    GUI_POINT LeftBottonOrigo;   	/*Left  Bottom origo*/
    GUI_POINT RightTopOrigo;   	/*Right Top    origo*/
    GUI_POINT RightBottonOrigo;   /*Left  Bottom origo*/

    Radius = __DrawContRadiusCorrect(Radius, Width, Height);
    LeftTopOrigo.x = pRect->x0 + Radius;
    LeftTopOrigo.y = pRect->y0 + Radius;

    LeftBottonOrigo.x = pRect->x0 + Radius;
    LeftBottonOrigo.y = pRect->y1 - Radius;

    RightTopOrigo.x = pRect->x1 - Radius;
    RightTopOrigo.y = pRect->y0 + Radius;

    RightBottonOrigo.x = pRect->x1 - Radius;
    RightBottonOrigo.y = pRect->y1 - Radius;
    GUI_CircleInit(&Circle, &CircleTemp, Radius);
    /*Init the areas*/
    __RectSet(&MidBottonArea,  LeftBottonOrigo.x + GUI_CIRC_OCT4_X(Circle),
    							LeftBottonOrigo.y + GUI_CIRC_OCT4_Y(Circle),
								RightBottonOrigo.x + GUI_CIRC_OCT1_X(Circle),
								RightBottonOrigo.y + GUI_CIRC_OCT1_Y(Circle));

    __RectSet(&EdgeBottonArea, LeftBottonOrigo.x + GUI_CIRC_OCT3_X(Circle),
    							LeftBottonOrigo.y + GUI_CIRC_OCT3_Y(Circle),
								RightBottonOrigo.x + GUI_CIRC_OCT2_X(Circle),
								RightBottonOrigo.y + GUI_CIRC_OCT2_Y(Circle));

    __RectSet(&MidTopArea,  LeftTopOrigo.x + GUI_CIRC_OCT5_X(Circle),
    						LeftTopOrigo.y + GUI_CIRC_OCT5_Y(Circle),
							RightTopOrigo.x + GUI_CIRC_OCT8_X(Circle),
							RightTopOrigo.y + GUI_CIRC_OCT8_Y(Circle));

    __RectSet(&EdgeTopArea, LeftTopOrigo.x + GUI_CIRC_OCT6_X(Circle),
    						LeftTopOrigo.y + GUI_CIRC_OCT6_Y(Circle),
							RightTopOrigo.x + GUI_CIRC_OCT7_X(Circle),
							RightTopOrigo.y + GUI_CIRC_OCT7_Y(Circle));

    while(GUI_CircleCont(&Circle)) {
        U8 EdgeTopRefresh = 0;
        U8 MidTopRefresh = 0;
        U8 MidBottonRefresh = 0;
        U8 EdgeBottonRefresh = 0;
        /*If a new row coming draw the previous
         * The x coordinate can grow on the same y so wait for the last x*/
        if(MidBottonArea.y0 != GUI_CIRC_OCT4_Y(Circle) + LeftBottonOrigo.y ) {
        	MidBottonRefresh = 1;
        }

        if(EdgeBottonArea.y0 != GUI_CIRC_OCT2_Y(Circle) + LeftBottonOrigo.y) {
        	EdgeBottonRefresh = 1;
        }

        if(MidTopArea.y0 != GUI_CIRC_OCT8_Y(Circle) + LeftTopOrigo.y) {
        	MidTopRefresh = 1;
        }

        if(EdgeTopArea.y0 != GUI_CIRC_OCT7_Y(Circle) + LeftTopOrigo.y) {
        	EdgeTopRefresh = 1;
        }

        /* Do not refresh the first row in the middle
         * because the body drawer makes it*/
        if(MidBottonArea.y0 == pRect->y1 - Radius){
        	MidBottonRefresh = 0;
        }

        if(MidTopArea.y0 == pRect->y0 + Radius){
        	MidTopRefresh = 0;
        }
        /*Draw the areas which are not disabled*/
        if(EdgeTopRefresh != 0){
            if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
            	ActColor = mColor & 0x00ffffff;
            }else {
                Mix = (U32)((U32)(pRect->y1 - EdgeTopArea.y0) << 8) / Height;
                ActColor = GUI_ColorMix(mColor, gColor, Mix);
            }
            ActColor |= (Opa << 24);
            GUI_SetColor(ActColor);
            GUI_FillRectEx(&EdgeTopArea);
        }

        if(MidTopRefresh != 0) {
            if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
            	ActColor = mColor & 0x00ffffff;
            }else {
                Mix = (U32)((U32)(pRect->y1 - MidTopArea.y0) << 8) / Height;
                ActColor = GUI_ColorMix(mColor, gColor, Mix);
            }
            ActColor |= (Opa << 24);
            GUI_SetColor(ActColor);
			GUI_FillRectEx(&MidTopArea);
        }

        if(MidBottonRefresh != 0) {
            if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
            	ActColor = mColor & 0x00ffffff;
            }else {
            	Mix = (U32)((U32)(pRect->y1 - MidBottonArea.y0) << 8) / Height;
            	ActColor = GUI_ColorMix(mColor, gColor, Mix);
            }
            ActColor |= (Opa << 24);
            GUI_SetColor(ActColor);
			GUI_FillRectEx(&MidBottonArea);
        }

        if(EdgeBottonRefresh != 0) {

        	if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
				ActColor = mColor & 0x00ffffff;
			}else {
				Mix = (U32)((U32)(pRect->y1 - EdgeBottonArea.y0) << 8) / Height;
				ActColor = GUI_ColorMix(mColor, gColor, Mix);
            }
        	ActColor |= (Opa << 24);
        	GUI_SetColor(ActColor);
			GUI_FillRectEx(&EdgeBottonArea);
        }
         /*Save the current coordinates*/
        __RectSet(&MidBottonArea,  LeftBottonOrigo.x + GUI_CIRC_OCT4_X(Circle),
                                 LeftBottonOrigo.y + GUI_CIRC_OCT4_Y(Circle),
                                 RightBottonOrigo.x + GUI_CIRC_OCT1_X(Circle),
                                 RightBottonOrigo.y + GUI_CIRC_OCT1_Y(Circle));

        __RectSet(&EdgeBottonArea, LeftBottonOrigo.x + GUI_CIRC_OCT3_X(Circle),
                                 LeftBottonOrigo.y + GUI_CIRC_OCT3_Y(Circle),
                                 RightBottonOrigo.x + GUI_CIRC_OCT2_X(Circle),
                                 RightBottonOrigo.y + GUI_CIRC_OCT2_Y(Circle));

        __RectSet(&MidTopArea,  LeftTopOrigo.x + GUI_CIRC_OCT5_X(Circle),
                                 LeftTopOrigo.y + GUI_CIRC_OCT5_Y(Circle),
                                 RightTopOrigo.x + GUI_CIRC_OCT8_X(Circle),
                                 RightTopOrigo.y + GUI_CIRC_OCT8_Y(Circle));

        __RectSet(&EdgeTopArea, LeftTopOrigo.x + GUI_CIRC_OCT6_X(Circle),
                                 LeftTopOrigo.y + GUI_CIRC_OCT6_Y(Circle),
                                 RightTopOrigo.x + GUI_CIRC_OCT7_X(Circle),
                                 RightTopOrigo.y + GUI_CIRC_OCT7_Y(Circle));

        GUI_CircleGetNext(&Circle, &CircleTemp);
    }

    if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
    	ActColor = mColor & 0x00ffffff;
    }else {
        Mix = (U32)((U32)(pRect->y1 - EdgeTopArea.y0) << 8) / Height;
        ActColor = GUI_ColorMix(mColor, gColor, Mix);
    }
    ActColor |= (Opa << 24);
    GUI_SetColor(ActColor);
    GUI_FillRectEx(&EdgeTopArea);

	if(EdgeTopArea.y0 != MidTopArea.y0) {
		if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
			ActColor = mColor & 0x00ffffff;
        }else {
        	Mix = (U32)((U32)(pRect->y1 - MidTopArea.y0) << 8) / Height;
        	ActColor = GUI_ColorMix(mColor, gColor, Mix);
	    }
		ActColor |= (Opa << 24);
		GUI_SetColor(ActColor);
		GUI_FillRectEx(&MidTopArea);
	}

	if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
	    ActColor = mColor & 0x00ffffff;
	}else {
		Mix = (U32)((U32)(pRect->y1 - MidBottonArea.y0) << 8) / Height;
		ActColor = GUI_ColorMix(mColor, gColor, Mix);
	}
	ActColor |= (Opa << 24);
	GUI_SetColor(ActColor);
	GUI_FillRectEx(&MidBottonArea);

	if(EdgeBottonArea.y0 != MidBottonArea.y0) {
		if((mColor & 0x00ffffff) == (gColor & 0x00ffffff)){
			ActColor = mColor & 0x00ffffff;
		}else {
			Mix = (U32)((U32)(pRect->y1 - EdgeBottonArea.y0) << 8) / Height;
			ActColor = GUI_ColorMix(mColor, gColor, Mix);
		}
		ActColor |= (Opa << 24);
		GUI_SetColor(ActColor);
		GUI_FillRectEx(&EdgeBottonArea);
	}
}

static void _DrawRectBorderStraight(const GUI_RECT * pRect, const GUI_BorderStyle * pStyle)
{
	I16 Radius = pStyle->Radius;

	I16 Width = __RectGetWidth(pRect);
	I16 Height = __RectGetHeight(pRect);
	U16 bWidth = pStyle->Width;
	//U8 opa = pStyle->Body.Border.Opacity;
	GUI_BorderPart Part = pStyle->Part;
	GUI_COLOR Color = pStyle->Color;
	GUI_RECT WorkRect;
	I16 LengthCorr = 0;
	I16 CornerSize = 0;

	/*the 0 px border width drawn as 1 px, so decrement the b_width*/
	bWidth--;

	Radius = __DrawContRadiusCorrect(Radius, Width, Height);

	if(Radius < bWidth) {
		LengthCorr = bWidth - Radius;
		CornerSize = bWidth;
	} else {
		CornerSize = Radius;
	}

	/* Modify the corner_size if corner is drawn */
	CornerSize ++;

	/*Depending one which Part's are drawn modify the rect lengths */
	if(Part & GUI_BORDER_TOP){
		WorkRect.y0 = pRect->y0 + CornerSize;
	}else{
		WorkRect.y0 = pRect->y0 + Radius;
	}
	if(Part & GUI_BORDER_BOTTOM){
		WorkRect.y1 = pRect->y1 - CornerSize;
	}else{
		WorkRect.y1 = pRect->y1 - Radius;
	}
	GUI_SetColor(Color);
	/*Left border*/
	if(Part & GUI_BORDER_LEFT) {
		WorkRect.x0 = pRect->x0;
		WorkRect.x1 = WorkRect.x0 + bWidth;
		GUI_FillRectEx(&WorkRect);
	}

	/*Right border*/
	if(Part & GUI_BORDER_RIGHT) {
		WorkRect.x1 = pRect->x1;
		WorkRect.x0 = WorkRect.x1 - bWidth;
		GUI_FillRectEx(&WorkRect);
	}

	WorkRect.x0 = pRect->x0 + CornerSize - LengthCorr;
	WorkRect.x1 = pRect->x1 - CornerSize + LengthCorr;

	/*Upper border*/
	if(Part & GUI_BORDER_TOP) {
		WorkRect.y0 = pRect->y0;
		WorkRect.y1 = pRect->y0 + bWidth;
		GUI_FillRectEx(&WorkRect);
	}

	/*Lower border*/
	if(Part & GUI_BORDER_BOTTOM) {
		WorkRect.y1 = pRect->y1;
		WorkRect.y0 = WorkRect.y1 - bWidth;
		GUI_FillRectEx(&WorkRect);
	}

	/*Draw the a remaining rectangles if the Radius is smaller then b_width */
	if(LengthCorr != 0) {
		/*Left top correction*/
		if((Part & GUI_BORDER_TOP) && (Part & GUI_BORDER_LEFT)) {
			WorkRect.x0 = pRect->x0;
			WorkRect.x1 = pRect->x0 + Radius;
			WorkRect.y0 = pRect->y0 + Radius + 1;
			WorkRect.y1 = pRect->y0 + bWidth;
			GUI_FillRectEx(&WorkRect);
		}

		/*Right top correction*/
		if((Part & GUI_BORDER_TOP) && (Part & GUI_BORDER_RIGHT)) {
			WorkRect.x0 = pRect->x1 - Radius;
			WorkRect.x1 = pRect->x1;
			WorkRect.y0 = pRect->y0 + Radius + 1;
			WorkRect.y1 = pRect->y0 + bWidth;
			GUI_FillRectEx(&WorkRect);
		}

		/*Left bottom correction*/
		if((Part & GUI_BORDER_BOTTOM) && (Part & GUI_BORDER_LEFT)) {
			WorkRect.x0 = pRect->x0;
			WorkRect.x1 = pRect->x0 + Radius;
			WorkRect.y0 = pRect->y1 - bWidth;
			WorkRect.y1 = pRect->y1 - Radius - 1;
			GUI_FillRectEx(&WorkRect);
		}

		/*Right bottom correction*/
		if((Part & GUI_BORDER_BOTTOM) && (Part & GUI_BORDER_RIGHT)) {
			WorkRect.x0 = pRect->x1 - Radius;
			WorkRect.x1 = pRect->x1;
			WorkRect.y0 = pRect->y1 - bWidth;
			WorkRect.y1 = pRect->y1 - Radius - 1;
			GUI_FillRectEx(&WorkRect);
		}
	}

	/*If Radius == 0 one px on the corners are not drawn*/
	if(0 == Radius) {

		/*Left top corner*/
		if(Part & (GUI_BORDER_TOP | GUI_BORDER_LEFT)) {
			GUI_DrawPixel(pRect->x0, pRect->y0);
		}

		/*Right top corner*/
		if(Part & (GUI_BORDER_TOP | GUI_BORDER_RIGHT)) {
			GUI_DrawPixel(pRect->x1, pRect->y0);
		}

		/*Left bottom corner*/
		if(Part & (GUI_BORDER_BOTTOM | GUI_BORDER_LEFT)) {
			GUI_DrawPixel(pRect->x0, pRect->y1);
		}

		/*Right bottom corner*/
		if(Part & (GUI_BORDER_BOTTOM | GUI_BORDER_RIGHT)) {
			GUI_DrawPixel(pRect->x1, pRect->y1);
		}
	}
}

static void _DrawRectBorderCorner(const GUI_RECT* pRect, const GUI_BorderStyle * pStyle)
{
	U16 Radius = pStyle->Radius;
    U16 bWidth = pStyle->Width;
    I16 ActWidth1 = 0;
	I16 ActWidth2 = 0;
	I16 TempIn = 0;
	I16 RadiusIn = 0;
	I16 TempOut = 0;
	I16 Width = 0;
	I16 Height = 0;
    GUI_COLOR Color = pStyle->Color;
    GUI_BorderPart Part = pStyle->Part;
    GUI_RECT CircleRect;
    GUI_POINT LeftTopOrigo;   	/*Left  Top    origo*/
	GUI_POINT LeftBottonOrigo;   	/*Left  Bottom origo*/
	GUI_POINT RightTopOrigo;   	/*Right Top    origo*/
	GUI_POINT RightBottonOrigo;   /*Left  Bottom origo*/
	GUI_POINT CircleOut;
	GUI_POINT CircleIn;

    Width = __RectGetWidth(pRect);
    Height = __RectGetHeight(pRect);

    Radius = __DrawContRadiusCorrect(Radius, Width, Height);
    /*0 px border width drawn as 1 px, so decrement the bWidth*/
    bWidth--;
    LeftTopOrigo.x = pRect->x0 + Radius;
    LeftTopOrigo.y = pRect->y0 + Radius;

    LeftBottonOrigo.x = pRect->x0 + Radius;
    LeftBottonOrigo.y = pRect->y1 - Radius;

    RightTopOrigo.x = pRect->x1 - Radius;
    RightTopOrigo.y = pRect->y0 + Radius;

    RightBottonOrigo.x = pRect->x1 - Radius;
    RightBottonOrigo.y = pRect->y1 - Radius;

    GUI_CircleInit(&CircleOut, &TempOut, Radius);

    RadiusIn = Radius - bWidth;

    if(RadiusIn < 0){
        RadiusIn = 0;
    }

    GUI_CircleInit(&CircleIn, &TempIn, RadiusIn);
    GUI_SetColor(Color);
    while( CircleOut.y <= CircleOut.x) {
        /*Calculate the actual width to avoid overwriting pixels*/
        if(CircleIn.y < CircleIn.x) {
            ActWidth1 = CircleOut.x - CircleIn.x;
            ActWidth2 = ActWidth1;
        } else {
            ActWidth1 = CircleOut.x - CircleOut.y;
            ActWidth2 = ActWidth1 - 1;
        }

        /*Draw the octets to the right bottom corner*/
        if((Part & GUI_BORDER_BOTTOM) && (Part & GUI_BORDER_RIGHT)) {
            CircleRect.x0 = RightBottonOrigo.x + GUI_CIRC_OCT1_X(CircleOut) - ActWidth2;
            CircleRect.x1 = RightBottonOrigo.x + GUI_CIRC_OCT1_X(CircleOut);
            CircleRect.y0 = RightBottonOrigo.y + GUI_CIRC_OCT1_Y(CircleOut);
            CircleRect.y1 = RightBottonOrigo.y + GUI_CIRC_OCT1_Y(CircleOut);
            GUI_FillRectEx(&CircleRect);

            CircleRect.x0 = RightBottonOrigo.x + GUI_CIRC_OCT2_X(CircleOut);
            CircleRect.x1 = RightBottonOrigo.x + GUI_CIRC_OCT2_X(CircleOut);
            CircleRect.y0 = RightBottonOrigo.y + GUI_CIRC_OCT2_Y(CircleOut)- ActWidth1;
            CircleRect.y1 = RightBottonOrigo.y + GUI_CIRC_OCT2_Y(CircleOut);
            GUI_FillRectEx(&CircleRect);
        }

        /*Draw the octets to the left bottom corner*/
        if((Part & GUI_BORDER_BOTTOM) && (Part & GUI_BORDER_LEFT)) {
            CircleRect.x0 = LeftBottonOrigo.x + GUI_CIRC_OCT3_X(CircleOut);
            CircleRect.x1 = LeftBottonOrigo.x + GUI_CIRC_OCT3_X(CircleOut);
            CircleRect.y0 = LeftBottonOrigo.y + GUI_CIRC_OCT3_Y(CircleOut) - ActWidth2;
            CircleRect.y1 = LeftBottonOrigo.y + GUI_CIRC_OCT3_Y(CircleOut);
            GUI_FillRectEx(&CircleRect);

            CircleRect.x0 = LeftBottonOrigo.x + GUI_CIRC_OCT4_X(CircleOut);
            CircleRect.x1 = LeftBottonOrigo.x + GUI_CIRC_OCT4_X(CircleOut) + ActWidth1;
            CircleRect.y0 = LeftBottonOrigo.y + GUI_CIRC_OCT4_Y(CircleOut);
            CircleRect.y1 = LeftBottonOrigo.y + GUI_CIRC_OCT4_Y(CircleOut);
            GUI_FillRectEx(&CircleRect);
        }

        /*Draw the octets to the left top corner*/
        if((Part & GUI_BORDER_TOP) && (Part & GUI_BORDER_LEFT)) {
            if(LeftBottonOrigo.y + GUI_CIRC_OCT4_Y(CircleOut) > LeftTopOrigo.y + GUI_CIRC_OCT5_Y(CircleOut)) {
                /*Don't draw if the lines are common in the middle*/
                CircleRect.x0 = LeftTopOrigo.x + GUI_CIRC_OCT5_X(CircleOut);
                CircleRect.x1 = LeftTopOrigo.x + GUI_CIRC_OCT5_X(CircleOut) + ActWidth2;
                CircleRect.y0 = LeftTopOrigo.y + GUI_CIRC_OCT5_Y(CircleOut);
                CircleRect.y1 = LeftTopOrigo.y + GUI_CIRC_OCT5_Y(CircleOut);
                GUI_FillRectEx(&CircleRect);
            }

            CircleRect.x0 = LeftTopOrigo.x + GUI_CIRC_OCT6_X(CircleOut);
            CircleRect.x1 = LeftTopOrigo.x + GUI_CIRC_OCT6_X(CircleOut);
            CircleRect.y0 = LeftTopOrigo.y + GUI_CIRC_OCT6_Y(CircleOut);
            CircleRect.y1 = LeftTopOrigo.y + GUI_CIRC_OCT6_Y(CircleOut) + ActWidth1;
            GUI_FillRectEx(&CircleRect);
        }

        /*Draw the octets to the right top corner*/
        if((Part & GUI_BORDER_TOP) && (Part & GUI_BORDER_RIGHT)) {
            CircleRect.x0 = RightTopOrigo.x + GUI_CIRC_OCT7_X(CircleOut);
            CircleRect.x1 = RightTopOrigo.x + GUI_CIRC_OCT7_X(CircleOut);
            CircleRect.y0 = RightTopOrigo.y + GUI_CIRC_OCT7_Y(CircleOut);
            CircleRect.y1 = RightTopOrigo.y + GUI_CIRC_OCT7_Y(CircleOut) + ActWidth2;
            GUI_FillRectEx(&CircleRect);

            /*Don't draw if the lines are common in the middle*/
            if(RightBottonOrigo.y + GUI_CIRC_OCT1_Y(CircleOut) > RightTopOrigo.y + GUI_CIRC_OCT8_Y(CircleOut)) {
                CircleRect.x0 = RightTopOrigo.x + GUI_CIRC_OCT8_X(CircleOut) - ActWidth1;
                CircleRect.x1 = RightTopOrigo.x + GUI_CIRC_OCT8_X(CircleOut);
                CircleRect.y0 = RightTopOrigo.y + GUI_CIRC_OCT8_Y(CircleOut);
                CircleRect.y1 = RightTopOrigo.y + GUI_CIRC_OCT8_Y(CircleOut);
                GUI_FillRectEx(&CircleRect);
            }
        }
        GUI_CircleGetNext(&CircleOut, &TempOut);

        /*The internal circle will be ready faster
         * so check it! */
        if(CircleIn.y < CircleIn.x) {
        	GUI_CircleGetNext(&CircleIn, &TempIn);
        }
    }
}
static void _DrawContShadowFullStraight(const GUI_RECT *pRect, const GUI_ShadowStyle * pStyle, const U8 *map)
{

    I16 radius = pStyle->Radius;
    I16 swidth = pStyle->Width;
    I16 width = WM_RectGetWidth(pRect);
    I16 height = WM_RectGetHeight(pRect);

    radius = __DrawContRadiusCorrect(radius, width, height);

    GUI_RECT sider_area;
    sider_area.x0 = pRect->x1;
    sider_area.y0 = pRect->y0 + radius + 1;
    sider_area.x1 = sider_area.x0;
    sider_area.y1 = pRect->y1 -  radius - 1;

    GUI_RECT sidel_area;
    sidel_area.x0 = pRect->x0;
    sidel_area.y0 = pRect->y0 + radius + 1;
    sidel_area.x1 = sidel_area.x0;
    sidel_area.y1 = pRect->y1 - radius - 1;

    GUI_RECT sidet_area;
    sidet_area.x0 = pRect->x0 + radius + 1;
    sidet_area.y0 = pRect->y0;
    sidet_area.x1 = pRect->x1 - radius - 1;
    sidet_area.y1 = sidet_area.y0;

    GUI_RECT sideb_area;
    sideb_area.x0 = pRect->x0 + radius + 1;
    sideb_area.y0 = pRect->y1;
    sideb_area.x1 = pRect->x1 - radius - 1;
    sideb_area.y1 = sideb_area.y0;

    I16 d;
    for(d = 0; d < swidth; d++) {
    	GUI_SetColor((map[d] << 24) | (pStyle->Color & 0x00ffffff));
    	GUI_FillRectEx(&sider_area);
        sider_area.x0++;
        sider_area.x1++;

        GUI_FillRectEx(&sidel_area);
        sidel_area.x0--;
        sidel_area.x1--;

        GUI_FillRectEx(&sidet_area);
        sidet_area.y0--;
        sidet_area.y1--;

        GUI_FillRectEx(&sideb_area);
        sideb_area.y0++;
        sideb_area.y1++;
    }

}
static void _DrawContShadowFull(const GUI_RECT *pRect, const GUI_ShadowStyle *pStyle)
{
	I16 radius = pStyle->Radius;
	I16 swidth = pStyle->Width;

	I16 width = WM_RectGetWidth(pRect);
	I16 height = WM_RectGetHeight(pRect);

	radius = __DrawContRadiusCorrect(radius, width, height);

	I16 cruve_x[radius + swidth];     /*Stores the 'x' coordinates of a quarter circle.*/
	GUI_memset(cruve_x, 0, sizeof(cruve_x));
	GUI_POINT circ;
	I16 circ_tmp;
	GUI_CircleInit(&circ, &circ_tmp, radius);
	while(GUI_CircleCont(&circ)) {
		cruve_x[GUI_CIRC_OCT1_Y(circ)] = GUI_CIRC_OCT1_X(circ);
		cruve_x[GUI_CIRC_OCT2_Y(circ)] = GUI_CIRC_OCT2_X(circ);
		GUI_CircleGetNext(&circ, &circ_tmp);
	}
	I16 row;

	I16 filter_size = 2 * swidth + 1;
	U16 opa_h_result[filter_size];

	for(row = 0; row < filter_size; row++) {
		opa_h_result[row] = (U32)((U32)(filter_size - row) * pStyle->Opacity * 2) / (filter_size);
	}

	U16 p;
	U8 opa_v_result[radius + swidth];

	GUI_POINT point_rt;
	GUI_POINT point_rb;
	GUI_POINT point_lt;
	GUI_POINT point_lb;
	GUI_POINT ofs_rb;
	GUI_POINT ofs_rt;
	GUI_POINT ofs_lb;
	GUI_POINT ofs_lt;
	ofs_rb.x = pRect->x1 - radius;
	ofs_rb.y = pRect->y1 - radius;

	ofs_rt.x = pRect->x1 - radius;
	ofs_rt.y = pRect->y0 + radius;

	ofs_lb.x = pRect->x0 + radius;
	ofs_lb.y = pRect->y1 - radius;

	ofs_lt.x = pRect->x0 + radius;
	ofs_lt.y = pRect->y0 + radius;

	for(row = 0; row < radius + swidth; row++) {
		for(p = 0; p < radius + swidth; p++) {
		   I16 v;
		   U32 opa_tmp = 0;
		   I16 row_v;
		   bool swidth_out = false;
		   for(v = -swidth; v < swidth; v++) {
			   row_v = row + v;
			   if(row_v < 0) row_v = 0; /*Rows above the corner*/

			   /*Rows below the bottom are empty so they won't modify the filter*/
			   if(row_v > radius) {
				   break;
			   }
			   else
			   {
				   I16 p_tmp = p - (cruve_x[row_v] - cruve_x[row]);
				   if(p_tmp < -swidth) { /*Cols before the filtered shadow (still not blurred)*/
					   opa_tmp += pStyle->Opacity * 2;
				   }
				   /*Cols after the filtered shadow (already no effect) */
				   else if (p_tmp > swidth) {
					   /* If on the current point the  filter top point is already out of swidth then
						* the remaining part will not do not anything on this point*/
					   if(v == -swidth) { /*Is the first point?*/
						   swidth_out = true;
					   }
					   break;
				   } else {
					   opa_tmp += opa_h_result[p_tmp + swidth];
				   }
			   }
		   }
		   if(swidth_out == false) {
			   opa_tmp = opa_tmp / (filter_size);
			   opa_v_result[p] = opa_tmp > 255 ? 255 : opa_tmp;
		   }
		   else {
			   break;
		   }
		}

		point_rt.x = cruve_x[row] + ofs_rt.x;
		point_rt.y = ofs_rt.y - row;

		point_rb.x = cruve_x[row] + ofs_rb.x;
		point_rb.y = ofs_rb.y + row;

		point_lt.x = ofs_lt.x -  cruve_x[row];
		point_lt.y = ofs_lt.y - row;

		point_lb.x = ofs_lb.x - cruve_x[row];
		point_lb.y = ofs_lb.y + row;

		U16 d;
		for(d = 0; d < p; d++) {
			GUI_SetColor((opa_v_result[d] << 24) | (pStyle->Color & 0x00ffffff));
			if(point_rt.x != point_lt.x) {
				GUI_DrawPoint(point_lt.x,point_lt.y);
			}

			if(point_rb.x != point_lb.x && point_lt.y != point_lb.y) {
				GUI_DrawPoint(point_lb.x,point_lb.y);
			}

			if(point_lt.y != point_lb.y) {
				GUI_DrawPoint(point_rb.x,point_rb.y);
			}


			GUI_DrawPoint(point_rt.x,point_rt.y);


			point_rb.x++;
			point_lb.x--;

			point_rt.x++;
			point_lt.x--;
		}

		/*When the first row is known draw the straight pars with same opa. map*/
		if(row == 0) {
			_DrawContShadowFullStraight(pRect, pStyle, opa_v_result);
		}
	}
}
static void _DrawContShadowBottom(const GUI_RECT *pRect, const GUI_ShadowStyle *pStyle)
{
    I16 radius = pStyle->Radius;
    I16 swidth = pStyle->Width;
    I16 width = WM_RectGetWidth(pRect);
    I16 height = WM_RectGetHeight(pRect);

    radius = __DrawContRadiusCorrect(radius, width, height);

    I16 cruve_x[radius + swidth];     /*Stores the 'x' coordinates of a quarter circle.*/
    GUI_memset(cruve_x, 0, sizeof(cruve_x));
    GUI_POINT circ;
    I16 circ_tmp;
    GUI_CircleInit(&circ, &circ_tmp, radius);
    while(GUI_CircleCont(&circ)) {
        cruve_x[GUI_CIRC_OCT1_Y(circ)] = GUI_CIRC_OCT1_X(circ);
        cruve_x[GUI_CIRC_OCT2_Y(circ)] = GUI_CIRC_OCT2_X(circ);
        GUI_CircleGetNext(&circ, &circ_tmp);
    }
    I16 row;

    I16 filter_size = 2 * swidth + 1;
    U8 opa_h_result[filter_size];

    for(row = 0; row < filter_size; row++) {
        opa_h_result[row] = (U32)((U32)(filter_size - row) * pStyle->Opacity) / (filter_size);
    }

    GUI_POINT point_l;
    GUI_POINT point_r;
    GUI_RECT area_mid;
    GUI_POINT ofs1;
    GUI_POINT ofs2;

    ofs1.x = pRect->x0 + radius;
    ofs1.y = pRect->y1 - radius;

    ofs2.x = pRect->x1 - radius;
    ofs2.y = pRect->y1 - radius;

    for(row = 0; row < radius; row++) {
        point_l.x = ofs1.x + radius - row - radius;
        point_l.y = ofs1.y + cruve_x[row];

        point_r.x = ofs2.x + row;
        point_r.y = ofs2.y + cruve_x[row];

        U16 d;
        for(d = swidth; d < filter_size; d++) {
        	GUI_SetColor((opa_h_result[d] << 24) | (pStyle->Color & 0x00ffffff));
        	GUI_DrawPoint(point_l.x, point_l.y);
            point_l.y ++;

            GUI_DrawPoint(point_r.x, point_r.y);
            point_r.y ++;
        }

    }

    area_mid.x0 = ofs1.x + 1;
    area_mid.y0 = ofs1.y + radius;
    area_mid.x1 = ofs2.x - 1;
    area_mid.y1 = area_mid.y0;

    U16 d;
    for(d = swidth; d < filter_size; d++) {
    	GUI_SetColor((opa_h_result[d] << 24) | (pStyle->Color & 0x00ffffff));
        GUI_FillRectEx(&area_mid);
        area_mid.y0 ++;
        area_mid.y1 ++;
    }
}
 void GUI_DrawRectShadow(const GUI_RECT *pRect, const GUI_ShadowStyle *pStyle)
{
    /* If mask is in the middle of cords do not draw shadow*/
    I16 radius = pStyle->Radius;
    I16 width = WM_RectGetWidth(pRect);
    I16 height = WM_RectGetHeight(pRect);
    radius = __DrawContRadiusCorrect(radius, width, height);
 //   GUI_RECT area_tmp;

    /*Check horizontally without radius*/
//    lv_area_copy(&area_tmp, coords);
//    area_tmp.x1 += radius;
//    area_tmp.x2 -= radius;
//    if(lv_area_is_in(mask, &area_tmp) != false) return;
//
//    /*Check vertically without radius*/
//    lv_area_copy(&area_tmp, coords);
//    area_tmp.y1 += radius;
//    area_tmp.y2 -= radius;
//    if(lv_area_is_in(mask, &area_tmp) != false) return;

    if(pStyle->Type == GUI_SHADOW_FULL) {
        _DrawContShadowFull(pRect, pStyle);
    } else if(pStyle->Type == GUI_SHADOW_BOTTOM) {
    	_DrawContShadowBottom(pRect, pStyle);
    }
}
/*
 * 填充圆角矩形
 * pRect: 所需填充的区域
 * pStyle: 填充的风格
 * pStyle->Radius: 圆角的半径
 * pStyle->Opacity: 填充颜色的透明度
 * pStyle->MainColor: 主色调
 * pStyle->GradColor: 渐变色调
 * */
void GUI_FillRoundRect(const GUI_RECT *pRect, const GUI_FullRectStyle *pStyle)
{
	_DrawRectMainMiddle(pRect, pStyle);
	_DrawRectMainCorner(pRect, pStyle);
}
/*
 * 绘制圆角矩形(不填充)
 * pRect: 所需绘制的区域
 * pStyle: 绘制的风格
 * pStyle->Radius: 圆角的半径
 * pStyle->Width: 圆角矩形的线宽
 * pStyle->Part: 绘制的部分
 * pStyle->Color: 绘制的颜色
 * */
void GUI_DrawRoundRect(const GUI_RECT* pRect, const GUI_BorderStyle * pStyle)
{
	_DrawRectBorderStraight(pRect, pStyle);
	_DrawRectBorderCorner(pRect, pStyle);
}
