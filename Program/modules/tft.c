/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 *  
 *  @file    tft.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "modules\tft.h"
//#include <stdio.h>
//#include <string.h>

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

/**
 *  @brief  TFT_DrawPixel
 */
void TFT_DrawPixel( int16_t posX, int16_t posY, uint16_t color )
{
    if ((posX < 0) || (posY < 0) || (posX >= TFT_W) || (posY >= TFT_H))
    {
        return;
    }
    TFT_SetWindow(posX, posY, posX, posY);
    TFT_WriteColor(color);
}

/**
 *  @brief  TFT_DrawLineX
 */
void TFT_DrawLineX( int16_t posX, int16_t posY, int16_t length, uint16_t color )
{
    int16_t posX2;

    if (length < 0)
    {
        posX2 = posX;
        posX  = posX + length - 1;
    }
    else
    {
        posX2 = posX + length - 1;
    }
    if ((length <= 0) || ((posX < 0) && (posX2 < 0)) || ((posX >= TFT_W) && (posX2 >= TFT_W)))
    {
        return;
    }
    if (posX < 0)
    {
        posX = 0;
    }
    if (posX2 >= TFT_W)
    {
        posX2 = TFT_W - 1;
    }
    TFT_SetWindow(posX, posY, posX2, posY);
    while (length--)
    {
        TFT_WriteColor(color);
    }
}

/**
 *  @brief  TFT_DrawLineY
 */
void TFT_DrawLineY( int16_t posX, int16_t posY, int16_t length, uint16_t color )
{
    int16_t posY2;

    if (length < 0)
    {
        posY2 = posY;
        posY  = posY + length + 1;
    }
    else
    {
        posY2 = posY + length - 1;
    }
    if ((length <= 0) || ((posY < 0) && (posY2 < 0)) || ((posY >= TFT_H) && (posY2 >= TFT_H)))
    {
        return;
    }

    if (posY < 0)
    {
        posY = 0;
    }

    if (posY2 >= TFT_H)
    {
        posY2 = TFT_H - 1;
    }
    TFT_SetWindow(posX, posY, posX, posY2);
    while (length--)
    {
        TFT_WriteColor(color);
    }
}

/**
 *  @brief  TFT_DrawLine
 */
//void TFT_DrawLine( int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, uint16_t color )
//{
//    int16_t dx = (posX2 - posX1), dy = (posY2 - posY1);
//    int16_t err, step;
//    uint8_t steep = absInt(dy) > absInt(dx);

//    if (steep)
//    {
//        swapS16(&posX1, &posY1);
//        swapS16(&posX2, &posY2);
//    }
//    if (posX1 > posX2)
//    {
//        swapS16(&posX1, &posX2);
//        swapS16(&posY1, &posY2);
//    }

//    dx = posX2 - posX1;
//    dy = posY2 - posY1;
//    err = dx / 2;
//    step = (dy > 0) ? (1) : (-1);
//    dx = absInt(dx);
//    dy = absInt(dy);

//    while (posX1 <= posX2)
//    {
//        if (steep)
//        {
//            TFT_DrawPixel(posY1, posX1, color);
//        }
//        else
//        {
//            TFT_DrawPixel(posX1, posY1, color);
//        }
//        posX1++;
//        err -= dy;
//        if (err < 0)
//        {
//            posY1 += step;
//            err += dx;
//        }
//    }
//}

/**
 *  @brief  TFT_FillLine
 */
//void TFT_FillLine( int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, int16_t rectX1, int16_t rectY1, int16_t rectX2, int16_t rectY2, uint16_t color1, uint16_t color2 )
//{
//    int16_t dx = (posX2 - posX1), dy = (posY2 - posY1);
//    int16_t err, step;
//    uint16_t steep = absInt(dy) > absInt(dx);

//    if (steep)
//    {
//        swapS16(&posX1, &posY1);
//        swapS16(&posX2, &posY2);
//        swapS16(&rectX1, &rectY1);
//        swapS16(&rectX2, &rectY2);
//    }
//    if (posX1 > posX2)
//    {
//        swapS16(&posX1, &posX2);
//        swapS16(&posY1, &posY2);
//    }

//    dx = posX2 - posX1;
//    dy = posY2 - posY1;
//    err = dx / 2;
//    step = (dy > 0) ? (1) : (-1);
//    dx = absInt(dx);
//    dy = absInt(dy);

//    while (posX1 < rectX2)
//    {
//        if (posX1 > rectX1)
//        {
//            if (steep)
//            {
//                if ((posY1 + 1) <= rectY2)
//                {
//                    TFT_DrawLineX(rectY1 + 1, posX1, posY1 - rectY1 - 1, color1);
//                }
//                else
//                {
//                    TFT_DrawLineX(rectY1 + 1, posX1, rectY2 - rectY1 - 1, color1);
//                }
//                if ((posY1 + 1) > rectY1)
//                {
//                    TFT_DrawLineX(posY1 + 1, posX1, rectY2 - posY1 - 1, color2);
//                }
//                else
//                {
//                    TFT_DrawLineX(rectY1 + 1, posX1, rectY2 - rectY1 - 1, color2);
//                }
//            }
//            else
//            {
//                if ((posY1 + 1) <= rectY2)
//                {
//                    TFT_DrawLineY(posX1, rectY1 + 1, posY1 - rectY1 - 1, color1);
//                }
//                else
//                {
//                    TFT_DrawLineY(posX1, rectY1 + 1, rectY2 - rectY1 - 1, color1);
//                }
//                if ((posY1 + 1) > rectY1)
//                {
//                    TFT_DrawLineY(posX1, posY1 + 1, rectY2 - posY1 - 1, color2);
//                }
//                else
//                {
//                    TFT_DrawLineY(posX1, rectY1 + 1, rectY2 - rectY1 - 1, color2);
//                }
//            }
//        }
//        posX1++;
//        err -= dy;
//        if (err < 0)
//        {
//            posY1 += step;
//            err += dx;
//        }
//    }
//}

/**
 *  @brief  TFT_DrawRect
 */
void TFT_DrawRect( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t color )
{
    if ((width > TFT_W) || (height > TFT_H))
    {
        return;
    }
    if (((posX + width) > TFT_W) || ((posY + height) > TFT_H))
    {
        return;
    }
    TFT_DrawLineX(posX,             posY,              width,      color);
    TFT_DrawLineX(posX,             posY + height - 1, width,      color);
    TFT_DrawLineY(posX,             posY + 1,          height - 2, color);
    TFT_DrawLineY(posX + width - 1, posY + 1,          height - 2, color);
}

/**
 *  @brief  TFT_DrawRoundRect
 */
void TFT_DrawRoundRect( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t radius, uint16_t color )
{
    if ((width > TFT_W) || (height > TFT_H))
    {
        return;
    }
    if (((posX + width) > TFT_W) || ((posY + height) > TFT_H))
    {
        return;
    }
    if ((radius > (width << 1)) || (radius > (height << 1)))
    {
        return;
    }
    TFT_DrawLineX(posX + radius,    posY,              width - (radius << 1),  color);
    TFT_DrawLineX(posX + radius,    posY + height - 1, width - (radius << 1),  color);
    TFT_DrawLineY(posX,             posY + radius + 1, height - (radius << 1), color);
    TFT_DrawLineY(posX + width - 1, posY + radius + 1, height - (radius << 1), color);
    TFT_DrawCircleHelper(posX - radius + width - 1, posY + radius,              radius, 0x03, color);
    TFT_DrawCircleHelper(posX - radius + width - 1, posY - radius + height - 1, radius, 0x0C, color);
    TFT_DrawCircleHelper(posX + radius,             posY - radius + height - 1, radius, 0x30, color);
    TFT_DrawCircleHelper(posX + radius,             posY + radius,              radius, 0xC0, color);
}

/**
 *  @brief  TFT_FillRect
 */
void TFT_FillRect( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t color )
{
    uint32_t point = width * height;

    if ((width > TFT_W) || (height > TFT_H))
    {
        return;
    }
    TFT_SetWindow(posX, posY, posX + width - 1, posY + height - 1);
    while (point--)
    {
        TFT_WriteColor(color);
    }
}

/**
 *  @brief  TFT_DrawCircle
 */
void TFT_DrawCircle( int16_t posX, int16_t posY, uint16_t radius, uint16_t color )
{
    int16_t di = 3 - (radius * 2);
    int16_t cX = 0, cY = radius;

    while (cX <= cY)
    {
        TFT_DrawPixel(posX + cX, posY - cY, color);
        TFT_DrawPixel(posX - cX, posY - cY, color);
        TFT_DrawPixel(posX + cY, posY - cX, color);
        TFT_DrawPixel(posX - cY, posY - cX, color);
        TFT_DrawPixel(posX + cX, posY + cY, color);
        TFT_DrawPixel(posX - cX, posY + cY, color);
        TFT_DrawPixel(posX + cY, posY + cX, color);
        TFT_DrawPixel(posX - cY, posY + cX, color);
        if (di < 0)
        {
            di += (cX << 2) + 6;
        }
        else
        {
            di += ((cX - cY) << 2) + 10;
            cY--;
        }
        cX++;
    }
}

/**
 *  @brief  TFT_DrawCircleHelper
 */
void TFT_DrawCircleHelper( int16_t posX, int16_t posY, uint16_t radius, uint8_t corner, uint16_t color )
{
    int16_t di = 3 - (radius * 2);
    int16_t cX = 0, cY = radius;

    while (cX <= cY)
    {
        if (corner & 0x01)
        {
            TFT_DrawPixel(posX + cX, posY - cY, color);
        }
        if (corner & 0x02)
        {
            TFT_DrawPixel(posX + cY, posY - cX, color);
        }
        if (corner & 0x04)
        {
            TFT_DrawPixel(posX + cY, posY + cX, color);
        }
        if (corner & 0x08)
        {
            TFT_DrawPixel(posX + cX, posY + cY, color);
        }
        if (corner & 0x10)
        {
            TFT_DrawPixel(posX - cX, posY + cY, color);
        }
        if (corner & 0x20)
        {
            TFT_DrawPixel(posX - cY, posY + cX, color);
        }
        if (corner & 0x40)
        {
            TFT_DrawPixel(posX - cY, posY - cX, color);
        }
        if (corner & 0x80)
        {
            TFT_DrawPixel(posX - cX, posY - cY, color);
        }
        if (di < 0)
        {
            di += (cX << 2) + 6;
        }
        else
        {
            di += ((cX - cY) << 2) + 10;
            cY--;
        }
        cX++;
    }
}

/**
 *  @brief  TFT_FillCircle
 */
void TFT_FillCircle( int16_t posX, int16_t posY, uint16_t radius, uint16_t color )
{
    int16_t di = 3 - (radius * 2);
    int16_t cX = 0, cY = radius;

    while (cX <= cY)
    {
        TFT_DrawLineX(posX - cX, posY - cY, (cX << 1) + 1, color);
        TFT_DrawLineX(posX - cX, posY + cY, (cX << 1) + 1, color);
        TFT_DrawLineX(posX - cY, posY - cX, (cY << 1) + 1, color);
        TFT_DrawLineX(posX - cY, posY + cX, (cY << 1) + 1, color);
        if (di < 0)
        {
            di += (cX << 2) + 6;
        }
        else
        {
            di += ((cX - cY) << 2) + 10;
            cY--;
        }
        cX++;
    }
}

/**
 *  @brief  TFT_DrawVect
 */
//void TFT_DrawVect( vector_t *vect, uint16_t *color, uint8_t lens )
//{
//    for (uint8_t i = 0;  i < (lens - 1); i++)
//    {
//        TFT_DrawLine(vect[i].x, vect[i].y, vect[i+1].x, vect[i+1].y, color[i]);
//    }
//    TFT_DrawLine(vect[lens - 1].x, vect[lens - 1].y, vect[0].x, vect[0].y, color[lens - 1]);
//}

/**
 *  @brief  TFT_DrawDotPic
 */
void TFT_DrawDotPic( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t *dotPic, uint16_t fontColor, uint16_t backColor )
{
    uint16_t tmp;

    if ((width > TFT_W) || (height > TFT_H))
    {
        return;
    }

    TFT_SetWindow(posX, posY, posX + width - 1, posY + height - 1);

    for (int16_t i = 0; i < height; i++)
    {
        tmp = dotPic[i];
        for (int16_t j = 0; j < width; j++)
        {
            if ((tmp >> j) & 0x01)
            {
                TFT_DrawPixel(posX + j, posY + i, fontColor);
            }
            else
            {
                TFT_DrawPixel(posX + j, posY + i, backColor);
            }
        }
    }
}

/**
 *  @brief  TFT_Config
 */
void TFT_DrawPic( int16_t posX, int16_t posY, uint16_t width, uint16_t height, const uint16_t *pic )
{
    uint32_t point = height * width;

    if ((width > TFT_W) || (height > TFT_H))
    {
        return;
    }

    TFT_SetWindow(posX, posY, posX + width - 1, posY + height - 1);

    for (uint32_t i = 0; i < point; i++)
    {
        TFT_WriteColor(pic[i]);
    }
}

/**
 *  @brief  TFT_PutChar
 */
void TFT_PutChar( int16_t posX, int16_t posY, sFONT *pFont, uint8_t word, uint16_t fontColor, uint16_t backColor )
{
    uint8_t tmp;
    uint8_t font_h = pFont->height;
    uint8_t font_w = pFont->width;
    uint16_t point;

    if (pFont->type == dirH)
    {
        point = (word - ' ') * font_h;
        for (uint8_t i = 0; i < font_h; i++)
        {
            tmp = pFont->table[point + i];
            for (uint8_t j = 0; j < font_w; j++)
            {
                if ((tmp << j) & 0x80)
                {
                    TFT_DrawPixel(posX + j, posY + i, fontColor);
                }
                else
                {
                    TFT_DrawPixel(posX + j, posY + i, backColor);
                }
            }
        }
    }
    else
    {
        point = (word - ' ') * font_w;
        for (uint8_t i = 0; i < font_w; i++)
        {
            tmp = pFont->table[point + i];
            for (uint8_t j = 0; j < font_h; j++)
            {
                if ((tmp >> j) & 0x01)
                {
                    TFT_DrawPixel(posX + i, posY + j, fontColor);
                }
                else
                {
                    TFT_DrawPixel(posX + i, posY + j, backColor);
                }
            }
        }
    }
}

/**
 *  @brief  TFT_PutStr
 */
void TFT_PutStr( int16_t posX, int16_t posY, sFONT *pFont, char *pString, uint16_t fontColor, uint16_t backColor )
{
    uint16_t offsetX = 0;

    while (*pString)
    {
        TFT_PutChar(posX + offsetX, posY, pFont, *pString, fontColor, backColor);
        pString++;
        offsetX += pFont->width;
    }
}

/**
 *  @brief  TFT_PutNum
 */
//void TFT_PutNum( int16_t posX, int16_t posY, sFONT *pFont, StringType_t type, uint8_t lens, int32_t number, uint16_t fontColor, uint16_t backColor )
//{
//    char strBuf[16] = {0};
//    num2Str(type, lens, strBuf, number);
//    TFT_PutStr(posX, posY, pFont, strBuf, fontColor, backColor);
//}

/**
 *  @brief  TFT_TestColoBar
 */
#define COLOR_NUMBER      (16)
#define COLOR_BAR_HEIGHT  (TFT_W / COLOR_NUMBER)  // 128/16 = 6
void TFT_TestColoBar( void )
{
    const uint16_t drawColor[COLOR_NUMBER] =
    {
        WHITE,
        RED,
        GREEN,
        BLUE,
        MAGENTA,
        GRED,
        GBLUE,
        BRED,
        BROWN,
        BRRED,
        CYAN,
        GRAY,
        YELLOW,
        DARKBLUE,
        LIGHTBLUE,
        GRAYBLUE
    };

    TFT_SetWindow(0, 0, TFT_W - 1, TFT_H - 1);

    for (uint8_t i = 0; i < COLOR_NUMBER; i++)
    {
        uint32_t j = (TFT_H / COLOR_NUMBER) * TFT_W;
        while (j--)
        {
            TFT_WriteColor(drawColor[i]);
        }
    }
}

/*************************************** END OF FILE ****************************************/
