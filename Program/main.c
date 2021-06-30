/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    main.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "modules\serial.h"
#include "modules\i2cmaster.h"
#include "kitsprout\kTerminal.h"
#include "nrf5x_bsp.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

static uint32_t sec = 0;
static uint32_t msc = 0;
static uint32_t tick = 0;

/* Prototypes ------------------------------------------------------------------------------*/

void event_timer_tick( void );
void event_uart_serial_recv( void );

/* Functions -------------------------------------------------------------------------------*/

void bsp_init( void )
{
    bsp_system_information(&dv);
    bsp_gpio_init();
    bsp_timer_init(event_timer_tick, TICK_TIMERx_TICKFREQ);
    bsp_uart_serial_init(event_uart_serial_recv);
    bsp_sensor_init();
//    bsp_tft_init();
    klogd("\n");
    bsp_timer_enable(ENABLE);
    
    i2c_config(IMU_SCL_PORT, IMU_SCL_PIN, IMU_SDA_PORT, IMU_SDA_PIN, 5);    // 400kHz
}

int main( void )
{
    bsp_init();

    while (1)
    {
        if (tick >= (TICK_TIMERx_TICKFREQ / dv.updaterate))
        {
            tick = 0;
            switch (dv.mode)
            {
                case 1:
                {
                    LED_G_Toggle();
                    int16_t lsb[12] = {0};
                    lsb[0] = sec;
                    lsb[1] = msc * (1000.0f / TICK_TIMERx_TICKFREQ);
                    bsp_sensor_get_lsb(&lsb[2]);
                    kSerial_SendPacket(NULL, lsb, 12, KS_I16);
                }
                case 2:
                {
                    LED_G_Off();
                    float raw[12] = {0};
                    bsp_sensor_get_raw(raw, 12);
                    printf("[G] %7.3f %7.3f %7.3f [A] %7.3f %7.3f %7.3f [M] %7.2f %7.2f %7.2f [T] %6.2f [B] %7.2f [T] %6.2f\n",
                        raw[0], raw[1], raw[2],
                        raw[3], raw[4], raw[5],
                        raw[6], raw[7], raw[8],
                        raw[9], raw[10], raw[11]);
                }
                default:
                {
                    LED_G_Off();
                    float raw[12] = {0};
                    bsp_sensor_get_raw(raw, 12);
                    klogd("[G] %7.3f %7.3f %7.3f [A] %7.3f %7.3f %7.3f [M] %7.2f %7.2f %7.2f [T] %6.2f [B] %7.2f [T] %6.2f\n",
                        raw[0], raw[1], raw[2],
                        raw[3], raw[4], raw[5],
                        raw[6], raw[7], raw[8],
                        raw[9], raw[10], raw[11]);
                }
            }
        }
    }
}

void event_timer_tick( void )
{
    tick++;
    if (++msc >= TICK_TIMERx_TICKFREQ)
    {
        msc = 0;
        sec++;
    }
}

void event_uart_serial_recv( void )
{
    LED_B_Toggle();
    uint8_t input = Serial_RecvByte();
#if 1
    kTerminal(input);
#else
    Serial_SendByte(input);
#endif
}

/*************************************** END OF FILE ****************************************/
