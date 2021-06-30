/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    tft.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __TFT_H
#define __TFT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "modules\st7735s.h"
#include "fonts\fontlib.h"

/* Define ----------------------------------------------------------------------------------*/

#define TFT_W                                           ST7735S_WIDTH   // 80
#define TFT_H                                           ST7735S_HIGHT   // 160

#define FONT5                                           Font5x4     // max line = 32 (TFT_H/5)
#define FONT8                                           Font8x6     // max line = 20 (TFT_H/8)
#define FONT16                                          Font16x8    // max line = 10 (TFT_H/16)

#define RGB_TO_GARY(C_R, C_G, C_B)                      ((uint8_t)(0.299f * C_R + 0.587f * C_G + 0.114f * C_B))
#define ToRGB565(RGB888)                                ((uint16_t)((RGB888&0xF80000>>8)|(RGB888&0x00FC00>>5)|(RGB888&0x0000F8>>3)))
#define ToRGB888(RGB565)                                ((uint16_t)((RGB565&0xF800<<8)|(RGB565&0x07E0<<5)|(RGB565&0x001F<<3)))

#define RGB565_R(RGB565)                                ((uint8_t)((RGB565 >> 11) & 0x1F))
#define RGB565_G(RGB565)                                ((uint8_t)((RGB565 >>  4) & 0x3F))
#define RGB565_B(RGB565)                                ((uint8_t)((RGB565      ) & 0x1F))

// INPUT R G B，OUTPUT RGB565
#define RGB(C_R, C_G, C_B)                              ((uint32_t)(((C_R<<8)&0xF800)|((C_G<<3)&0x07E0)|((C_B>>3)&0x001F)))

#define LINE(__FONT, __INDEX)                           (__FONT.height * __INDEX)
#define CENTER(__FONT, __STR)                           ((TFT_W - __FONT.width * lenOfStr(__STR)) >> 1)

#define RED                                             ((uint16_t)0xF800)  /* 紅色 */
#define GREEN                                           ((uint16_t)0x07E0)  /* 綠色 */
#define BLUE                                            ((uint16_t)0x001F)  /* 藍色 */
#define MAGENTA                                         ((uint16_t)0xF81F)  /* 紅紫色，洋紅色 */
#define GRED                                            ((uint16_t)0xFFE0)
#define GBLUE                                           ((uint16_t)0x07FF) 
#define BRED                                            ((uint16_t)0XF81F)
#define BROWN                                           ((uint16_t)0xBC40)  /* 棕色 */
#define BRRED                                           ((uint16_t)0xFC07)  /* 棕紅色 */
#define CYAN                                            ((uint16_t)0x7FFF)  /* 藍綠色，青色 */
#define BLACK                                           ((uint16_t)0x0000)  /* 黑色 */
#define GRAY                                            ((uint16_t)0X8430)  /* 灰色 */
#define WHITE                                           ((uint16_t)0xFFFF)  /* 白色 */
#define YELLOW                                          ((uint16_t)0xFFE0)  /* 黃色 */
#define DARKBLUE                                        ((uint16_t)0x01CF)  /* 深藍色 */
#define LIGHTBLUE                                       ((uint16_t)0x7D7C)  /* 淺藍色 */
#define GRAYBLUE                                        ((uint16_t)0x5458)  /* 灰藍色 */
#define LIGHTGREEN                                      ((uint16_t)0X841F)  /* 淺綠色 */
#define LGRAY                                           ((uint16_t)0XC618)  /* 淺灰色 */
#define LGRAYBLUE                                       ((uint16_t)0XA651)  /* 淺灰藍色 */
#define LBBLUE                                          ((uint16_t)0X2B12)  /* 淺棕藍色 */

/* Macro -----------------------------------------------------------------------------------*/

#define TFT_Config()                                    ST7735S_Config()
#define TFT_Init()                                      ST7735S_Init()
#define TFT_WriteColor(__COLOR)                         ST7735S_WriteColor(__COLOR)
#define TFT_Display(__CMD)                              ST7735S_Display(__CMD)
#define TFT_Clear(__COLOR)                              ST7735S_Clear(__COLOR)
#define TFT_SetWindow(__X1, __Y1, __X2, __Y2)           ST7735S_SetWindow(__X1, __Y1, __X2, __Y2)

/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

void        TFT_DrawPixel( int16_t posX, int16_t posY, uint16_t color );
void        TFT_DrawLineX( int16_t posX, int16_t posY, int16_t length, uint16_t color );
void        TFT_DrawLineY( int16_t posX, int16_t posY, int16_t length, uint16_t color );
//void        TFT_DrawLine( int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, uint16_t color );
//void        TFT_FillLine( int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, int16_t rectX1, int16_t rectY1, int16_t rectX2, int16_t rectY2, uint16_t color1, uint16_t color2 );
void        TFT_DrawRect( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t color );
void        TFT_DrawRoundRect( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t radius, uint16_t color );
void        TFT_FillRect( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t color );
void        TFT_DrawCircle( int16_t posX, int16_t posY, uint16_t radius, uint16_t color );
void        TFT_DrawCircleHelper( int16_t posX, int16_t posY, uint16_t radius, uint8_t corner, uint16_t color );
void        TFT_FillCircle( int16_t posX, int16_t posY, uint16_t radius, uint16_t color );
//void        TFT_DrawVect( vector_t *vect, uint16_t *color, uint8_t lens );
void        TFT_DrawDotPic( int16_t posX, int16_t posY, uint16_t width, uint16_t height, uint16_t *dotPic, uint16_t fontColor, uint16_t backColor );
void        TFT_DrawPic( int16_t posX, int16_t posY, uint16_t width, uint16_t height, const uint16_t *pic );
void        TFT_PutChar( int16_t posX, int16_t posY, sFONT *pFont, uint8_t word, uint16_t fontColor, uint16_t backColor );
void        TFT_PutStr( int16_t posX, int16_t posY, sFONT *pFont, char *pString, uint16_t fontColor, uint16_t backColor );
//void        TFT_PutNum( int16_t posX, int16_t posY, sFONT *pFont, StringType_t type, uint8_t lens, int32_t number, uint16_t fontColor, uint16_t backColor );
void        TFT_TestColoBar( void );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
