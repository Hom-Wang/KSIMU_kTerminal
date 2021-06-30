/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    st7735s.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __ST7735S_H
#define __ST7735S_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include <stdint.h>

/* Define ----------------------------------------------------------------------------------*/

#define TFT_VIEWING_ROTATE_0                            0
#define TFT_VIEWING_ROTATE_90                           90
#define TFT_VIEWING_ROTATE_180                          180
#define TFT_VIEWING_ROTATE_270                          270
#define TFT_VIEWING_DIRECTION                           TFT_VIEWING_ROTATE_0

#if ((TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_0) || \
     (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_180))
#define ST7735S_WIDTH                                   80
#define ST7735S_HIGHT                                   160
#elif ((TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_90) || \
       (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_270))
#define ST7735S_WIDTH                                   160
#define ST7735S_HIGHT                                   80
#endif

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Extern ----------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

void        ST7735S_WriteCmd( uint8_t command );
void        ST7735S_WriteData( uint8_t data );
void        ST7735S_WriteData16( uint16_t data16 );
void        ST7735S_WriteColor( uint16_t color );

void        ST7735S_Config( void );
void        ST7735S_Init( void );

void        ST7735S_Display( uint8_t cmd );
void        ST7735S_Clear( uint16_t color );
void        ST7735S_SetWindow( int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2 );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
