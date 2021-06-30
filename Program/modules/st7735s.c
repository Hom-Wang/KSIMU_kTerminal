/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    st7735s.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "modules\st7735s.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

/**
 *  @brief  ST7735S_WriteByte
 */
void ST7735S_WriteByte( uint8_t byte )
{
    for (uint32_t i = 0; i < 8; i++)
    {
        TFT_SCK_L();
        if (byte & 0x80)
        {
            TFT_SDI_H();
        }
        else
        {
            TFT_SDI_L();
        }
        TFT_SCK_H();
        byte <<= 1;
    }
}

/**
 *  @brief  ST7735S_WriteCmd
 */
void ST7735S_WriteCmd( uint8_t command )
{
    TFT_CS_L();
    TFT_DC_L();
    ST7735S_WriteByte(command);
    TFT_DC_H();
    TFT_CS_H();
}

/**
 *  @brief  ST7735S_WriteData
 */
void ST7735S_WriteData( uint8_t data )
{
    TFT_CS_L();
    TFT_DC_H();
    ST7735S_WriteByte(data);
    TFT_CS_H();
}

/**
 *  @brief  ST7735S_WriteData16
 */
void ST7735S_WriteData16( uint16_t data16 )
{
    TFT_CS_L();
    TFT_DC_H();
    ST7735S_WriteByte(data16 >> 8);
    ST7735S_WriteByte(data16);
    TFT_CS_H();
}

/**
 *  @brief  ST7735S_WriteColor
 */
void ST7735S_WriteColor( uint16_t color )
{
    TFT_CS_L();
    TFT_DC_H();
    ST7735S_WriteByte(color >> 8);
    ST7735S_WriteByte(color);
    TFT_CS_H();
}

/**
 *  @brief  ST7735S_Config
 */
void ST7735S_Config( void )
{
    TFT_CS_H();
    TFT_DC_H();
    TFT_RST_H();
    TFT_BLK_L();
    TFT_SCK_H();
    TFT_SDI_H();
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(TFT_CS_PORT, TFT_CS_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(TFT_DC_PORT, TFT_DC_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(TFT_RST_PORT, TFT_RST_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(TFT_BLK_PORT, TFT_BLK_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(TFT_SCK_PORT, TFT_SCK_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(TFT_SDI_PORT, TFT_SDI_PIN));
    delay_ms(20);
}

/**
 *  @brief  ST7735S_Init
 */
void ST7735S_Init( void )
{
    // Hardware Reset
    TFT_RST_L();
    delay_ms(10);
    TFT_RST_H();
    delay_ms(150);

    klogd("  st7735s software reset\n");
    ST7735S_WriteCmd(0x01);     // Software Reset
    delay_ms(150);
    ST7735S_WriteCmd(0x11);     // Sleep Out
    delay_ms(500);

    ST7735S_WriteCmd(0xB1);     // Frame Rate Control, Normal Mode
    ST7735S_WriteData(0x01);
    ST7735S_WriteData(0x2C);
    ST7735S_WriteData(0x2D);
    ST7735S_WriteCmd(0xB2);     // Idle mode
    ST7735S_WriteData(0x01);
    ST7735S_WriteData(0x2C);
    ST7735S_WriteData(0x2D);
    ST7735S_WriteCmd(0xB3);     // Partial mode
    ST7735S_WriteData(0x01);
    ST7735S_WriteData(0x2C);
    ST7735S_WriteData(0x2D);
    ST7735S_WriteData(0x01);
    ST7735S_WriteData(0x2C);
    ST7735S_WriteData(0x2D);
    ST7735S_WriteCmd(0xB4);     // Column Inversion
    ST7735S_WriteData(0x07);
    ST7735S_WriteCmd(0xC0);     // AVDD GVDD
    ST7735S_WriteData(0xA2);
    ST7735S_WriteData(0x02);
    ST7735S_WriteData(0x84);
    ST7735S_WriteCmd(0xC1);     // VGH VGL
    ST7735S_WriteData(0xC5);    // C0
    ST7735S_WriteCmd(0xC2);     // Normal mode
    ST7735S_WriteData(0x0A);
    ST7735S_WriteData(0x00);
    ST7735S_WriteCmd(0xC3);     // Idle
    ST7735S_WriteData(0x8A);
    ST7735S_WriteData(0x2A);
    ST7735S_WriteCmd(0xC4);     // Partial mode
    ST7735S_WriteData(0x8D);
    ST7735S_WriteData(0xEE);
    ST7735S_WriteCmd(0xC5);     // VCOM
    ST7735S_WriteData(0x0E);
    ST7735S_WriteCmd(0xE0);     // Positive gamma
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x0E);
    ST7735S_WriteData(0x08);
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x10);
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x02);
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x09);
    ST7735S_WriteData(0x0F);
    ST7735S_WriteData(0x25);
    ST7735S_WriteData(0x36);
    ST7735S_WriteData(0x00);
    ST7735S_WriteData(0x08);
    ST7735S_WriteData(0x04);
    ST7735S_WriteData(0x10);
    ST7735S_WriteCmd(0xE1);     // Negative gamma
    ST7735S_WriteData(0x0A);
    ST7735S_WriteData(0x0D);
    ST7735S_WriteData(0x08);
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x0F);
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x02);
    ST7735S_WriteData(0x07);
    ST7735S_WriteData(0x09);
    ST7735S_WriteData(0x0F);
    ST7735S_WriteData(0x25);
    ST7735S_WriteData(0x35);
    ST7735S_WriteData(0x00);
    ST7735S_WriteData(0x09);
    ST7735S_WriteData(0x04);
    ST7735S_WriteData(0x10);

    ST7735S_WriteCmd(0xFC);
    ST7735S_WriteData(0x80);

    ST7735S_WriteCmd(0x20);
    ST7735S_WriteCmd(0x36);
#if (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_0)
    ST7735S_WriteData(0xC8);
#elif (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_90)
    ST7735S_WriteData(0x78);
#elif (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_180)
    ST7735S_WriteData(0x08);
#elif (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_270)
    ST7735S_WriteData(0xA8);
#endif

    ST7735S_WriteCmd(0x3A);     // 16-bit Color Format
    ST7735S_WriteData(0x05);

    ST7735S_Clear(0x0000);
    ST7735S_WriteCmd(0x21);     // display inversion
    ST7735S_WriteCmd(0x29);     // display on

    ST7735S_WriteCmd(0x13);
    delay_ms(10);

    TFT_BLK_On();
    ST7735S_Display(ENABLE);
    delay_ms(50);
}

/**
 *  @brief  ST7735S_Display
 */
void ST7735S_Display( uint8_t cmd )
{
    if (cmd != ENABLE)
    {
        ST7735S_WriteCmd(0x28);
    }
    else
    {
        ST7735S_WriteCmd(0x29);
    }
    delay_ms(100);
}

/**
 *  @brief  ST7735S_Clear
 */
void ST7735S_Clear( uint16_t color )
{
    uint32_t point = ST7735S_WIDTH * ST7735S_HIGHT;
    ST7735S_SetWindow(0, 0, ST7735S_WIDTH - 1, ST7735S_HIGHT - 1);
    while (point--)
    {
        ST7735S_WriteColor(color);
    }
}

/**
 *  @brief  ST7735S_SetWindow
 */
void ST7735S_SetWindow( int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2 )
{
#if ((TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_0) || \
     (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_180))
    posX1 += 26;
    posX2 += 26;
    posY1 += 1;
    posY2 += 1;
#elif ((TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_90) || \
       (TFT_VIEWING_DIRECTION == TFT_VIEWING_ROTATE_270))
    posX1 += 1;
    posX2 += 1;
    posY1 += 26;
    posY2 += 26;
#endif
    ST7735S_WriteCmd(0x2A);
    ST7735S_WriteData16(posX1);
    ST7735S_WriteData16(posX2);
    ST7735S_WriteCmd(0x2B);
    ST7735S_WriteData16(posY1);
    ST7735S_WriteData16(posY2);
    ST7735S_WriteCmd(0x2C);
}

/*************************************** END OF FILE ****************************************/
