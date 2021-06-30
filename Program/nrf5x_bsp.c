/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_bsp.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_clock.h"
#include "drivers\nrf5x_timer.h"
#include "modules\serial.h"
#include "modules\icm42605.h"
#include "modules\ist8308.h"
#include "modules\lps22hb.h"
#include "modules\tft.h"
#include "nrf5x_bsp.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

TIMER_BaseInitTypeDef htimer;
TIMER_ChannelInitTypeDef htimer_cc;

static uint32_t accEnable = 0, magEnable = 0, baroEnable = 0;
static float gyrSensitivity = 0, accSensitivity = 0, magSensitivity = 0;
static float baroSensitivity = 0, tempSensitivity = 0;

/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

void bsp_gpio_init( void )
{
    nrf5x_clock_config();

    LED_R_Off();
    LED_G_Off();
    LED_B_Off();
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(LED_R_PORT, LED_R_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(LED_G_PORT, LED_G_PIN));
    nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(LED_B_PORT, LED_B_PIN));
    nrf_gpio_cfg_input(NRF_GPIO_PIN_MAP(KEY_PORT, KEY_PIN), NRF_GPIO_PIN_PULLUP);
}

void bsp_timer_init( pFunc event, uint32_t freq )
{
    htimer.Instance  = TICK_TIMERx;
    htimer.Mode      = TICK_TIMERx_MODE;
    htimer.BitMode   = TICK_TIMERx_BIT_MODE;
    htimer.Prescaler = TICK_TIMERx_PRESCALER;
    TIMER_BaseInit(&htimer);

    htimer_cc.Channel = TICK_TIMERx_CHANNEL;
    htimer_cc.Period  = (uint32_t)((16000000U >> NRF_TIMER_FREQ_1MHz) / freq);
    htimer_cc.EventCallback = event;
    TIMER_ChannelInit(&htimer, &htimer_cc);
    TIMER_InterruptCmd(&htimer, htimer_cc.Channel, ENABLE);

    NVIC_SetPriority(TICK_TIMERx_IRQn, TICK_TIMERx_IRQn_PRIORITY);
    NVIC_EnableIRQ(TICK_TIMERx_IRQn);
}

void bsp_timer_enable( uint32_t state )
{
    TIMER_Cmd(&htimer, state);
}

void bsp_uart_serial_init( pFunc event )
{
    hserial.RxEventCallback = event;

    Serial_Config();
    Serial_Cmd(ENABLE);
    printf("\r\n\f\r\n");
}

void bsp_sensor_init( void )
{
    uint32_t status;
    uint32_t error = 0;

    klogd("bsp sensor init ...\n");

    // icm42605 init
    ICM42605_Config();
    delay_ms(50);
    status = ICM42605_Init();
    if (status != KS_OK)
    {
        accEnable = KS_FALSE;
        error++;
    }
    else
    {
        accEnable = KS_TRUE;
    }

    // ist8308 init
    IST8308_Config();
    delay_ms(50);
    status = IST8308_Init();
    if (status != KS_OK)
    {
        magEnable = KS_FALSE;
        error++;
    }
    else
    {
        magEnable = KS_TRUE;
    }

    // lps22hb init
    LPS22HB_Config();
    delay_ms(50);
    status = LPS22HB_Init();
    if (status != KS_OK)
    {
        baroEnable = KS_FALSE;
        error++;
    }
    else
    {
        baroEnable = KS_TRUE;
    }
    klogd("\n");
# if 0
    gyrSensitivity = ICM42688_GetGyrSensitivity();
    accSensitivity = ICM42688_GetAccSensitivity();
    magSensitivity = IST8308_GetMagSensitivity();
    klogd("sensor resulation %.6f dps, %.6f mg, %.6f uT\n",
        gyrSensitivity, accSensitivity, magSensitivity);
#else
    gyrSensitivity = ICM42605_GetGyrSensitivity() * 3.14159 / 180;  // rad/s
    accSensitivity = ICM42605_GetAccSensitivity() * 0.00981;        // m/s^2
    magSensitivity = IST8308_GetMagSensitivity();                   // uT
    baroSensitivity = LPS22HB_GetBaroSensitivity();     // bar
    tempSensitivity = LPS22HB_GetTempSensitivity();     // degc
    klogd("  sensor resulation %.6f rad/s, %.6f m/s^2, %.6f uT\n",
        gyrSensitivity, accSensitivity, magSensitivity);
    klogd("  baro resulation %.6f bar, %.4f degc\n",
        baroSensitivity, tempSensitivity);
#endif

    // check init status
    if (error != KS_OK)
    {
#if 1
        LED_R_On();
        return;
#else
        while (1)
        {
            LED_R_Toggle();
            delay_ms(100);
        }
#endif
    }
    klogd("\n");
}

// ENU Coordinate System
void bsp_sensor_get_lsb( int16_t *lsb )
{
    int16_t res[10] = {0};
    if (accEnable)
    {
        ICM42605_GetLsbData(&res[0]);
        lsb[0] = -res[4];   // gyr.x
        lsb[1] =  res[5];   // gyr.y
        lsb[2] = -res[6];   // gyr.z
        lsb[3] =  res[1];   // acc.x
        lsb[4] = -res[2];   // acc.y
        lsb[5] =  res[3];   // acc.z
        lsb[9] =  res[0];   // temp
    }
    if (magEnable)
    {
        IST8308_GetLsbData(&res[7]);
        lsb[6] =  res[8];   // mag.x
        lsb[7] = -res[7];   // mag.y
        lsb[8] = -res[9];   // mag.z
    }
}

void bsp_sensor_get_raw( float *raw, uint32_t dim )
{
    int16_t lsb[10] = {0};
    int32_t lsb32[2] = {0};
    bsp_sensor_get_lsb(lsb);
    raw[0] = lsb[0] * gyrSensitivity;   // gyr.x
    raw[1] = lsb[1] * gyrSensitivity;   // gyr.y
    raw[2] = lsb[2] * gyrSensitivity;   // gyr.z
    raw[3] = lsb[3] * accSensitivity;   // acc.x
    raw[4] = lsb[4] * accSensitivity;   // acc.y
    raw[5] = lsb[5] * accSensitivity;   // acc.z
    raw[6] = lsb[6] * magSensitivity;   // mag.x
    raw[7] = lsb[7] * magSensitivity;   // mag.y
    raw[8] = lsb[8] * magSensitivity;   // mag.z
    raw[9] = lsb[9] / 132.48f + 25;     // temp
    if ((dim > 9) && baroEnable)
    {
        LPS22HB_GetLsbData(lsb32);
        raw[10] = lsb32[0] * baroSensitivity;
        raw[11] = lsb32[1] * tempSensitivity;
    }
#if 0
    klogd("[G] %6d %6d %6d [A] %6d %6d %6d [M] %6d %6d %6d [T] %6d [B] %8d [T] %6d\n",
        lsb[0], lsb[1], lsb[2],
        lsb[3], lsb[4], lsb[5],
        lsb[6], lsb[7], lsb[8],
        lsb[9], lsb32[0], lsb32[1]);
#endif
#if 0
    klogd("[G] %7.3f %7.3f %7.3f [A] %7.3f %7.3f %7.3f [M] %7.2f %7.2f %7.2f [T] %6.2f [B] %7.2f [T] %6.2f\n",
        raw[0], raw[1], raw[2],
        raw[3], raw[4], raw[5],
        raw[6], raw[7], raw[8],
        raw[9], raw[10], raw[11]);
#endif
}

void bsp_sensor_get_baro_lsb( int32_t *lsb )
{
    LPS22HB_GetLsbData(lsb);
}

void bsp_tft_init( void )
{
    TFT_Config();
    TFT_Init();
#if 1
    TFT_TestColoBar();
#endif
}

/*************************************** END OF FILE ****************************************/
