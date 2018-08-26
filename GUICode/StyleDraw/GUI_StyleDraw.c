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

void GUI_DrawRectMainMiddle(const GUI_RECT * pRect, const GUI_FullRectStyle *pStyle)
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
			GUI_FillRectEx(&WorkRect);
        }
    }
}

void GUI_DrawRectMainCorner(const GUI_RECT * pRect, const GUI_FullRectStyle * pStyle)
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
void GUI_DrawRectBorderStraight(const GUI_RECT * pRect, const GUI_BorderStyle * pStyle)
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

void GUI_DrawRectBorderCorner(const GUI_RECT* pRect, const GUI_BorderStyle * pStyle)
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
