/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    boardConfig.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __BOARDCONFIG_H
#define __BOARDCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
/* Define ----------------------------------------------------------------------------------*/

#define KS_HW_BOARD_NAME                                "KSIMU"
#define KS_HW_MCU_NAME                                  "NRF52833"

#define KS_HW_USE_CLOCK_SOUCE_INT                       (0U)
#define KS_HW_USE_CLOCK_SOUCE_EXT                       (1U)
#define KS_HW_HCLOCK_SOUCE                              KS_HW_USE_CLOCK_SOUCE_INT
#define KS_HW_LCLOCK_SOUCE                              KS_HW_USE_CLOCK_SOUCE_INT

/* -------- LED and KEY */

#define LED_R_PIN                                       15
#define LED_R_PORT                                      0
#define LED_R_Set()                                     __GPIO_SET(LED_R_PORT, LED_R_PIN)
#define LED_R_Reset()                                   __GPIO_RST(LED_R_PORT, LED_R_PIN)
#define LED_R_Toggle()                                  __GPIO_TOG(LED_R_PORT, LED_R_PIN)
#define LED_R_On()                                      LED_R_Reset()
#define LED_R_Off()                                     LED_R_Set()

#define LED_G_PIN                                       17
#define LED_G_PORT                                      0
#define LED_G_Set()                                     __GPIO_SET(LED_G_PORT, LED_G_PIN)
#define LED_G_Reset()                                   __GPIO_RST(LED_G_PORT, LED_G_PIN)
#define LED_G_Toggle()                                  __GPIO_TOG(LED_G_PORT, LED_G_PIN)
#define LED_G_On()                                      LED_G_Reset()
#define LED_G_Off()                                     LED_G_Set()

#define LED_B_PIN                                       20
#define LED_B_PORT                                      0
#define LED_B_Set()                                     __GPIO_SET(LED_B_PORT, LED_B_PIN)
#define LED_B_Reset()                                   __GPIO_RST(LED_B_PORT, LED_B_PIN)
#define LED_B_Toggle()                                  __GPIO_TOG(LED_B_PORT, LED_B_PIN)
#define LED_B_On()                                      LED_B_Reset()
#define LED_B_Off()                                     LED_B_Set()

#define KEY_PIN                                         18
#define KEY_PORT                                        0
#define KEY_Read()                                      (__GPIO_READ(KEY_PORT, KEY_PIN) == RESET)


/* -------- Timer */

#define TICK_TIMERx                                     NRF_TIMER0
#define TICK_TIMERx_IRQn                                TIMER0_IRQn
#define TICK_TIMERx_IRQHANDLER                          TIMER0_IRQHandler
#define TICK_TIMERx_IRQn_PRIORITY                       1
#define TICK_TIMERx_MODE                                NRF_TIMER_MODE_TIMER
#define TICK_TIMERx_PRESCALER                           NRF_TIMER_FREQ_1MHz
#define TICK_TIMERx_BIT_MODE                            NRF_TIMER_BIT_WIDTH_32

#define TICK_TIMERx_CHANNEL                             NRF_TIMER_CC_CHANNEL0
#define TICK_TIMERx_CHANNEL_PERIOD                      1000
#define TICK_TIMERx_TICKFREQ                            1000


/* -------- Serial */

//#define CONFIG_NFCT_PINS_AS_GPIOS                       // Disable NFC, PIN9, PIN10
#define SERIAL_UARTx                                    NRF_UART0
#define SERIAL_UARTx_IRQn                               UARTE0_UART0_IRQn
#define SERIAL_UARTx_IRQHANDLER                         UARTE0_UART0_IRQHandler
#define SERIAL_UARTx_IRQn_PRIORITY                      1
#define SERIAL_TXD_PIN                                  10
#define SERIAL_RXD_PIN                                  9
#define SERIAL_RTS_PIN                                  2
#define SERIAL_CTS_PIN                                  3

#define SERIAL_BAUDRATE                                 NRF_UART_BAUDRATE_115200
//#define SERIAL_BAUDRATE                                 NRF_UART_BAUDRATE_230400
//#define SERIAL_BAUDRATE                                 NRF_UART_BAUDRATE_250000
//#define SERIAL_BAUDRATE                                 NRF_UART_BAUDRATE_460800
//#define SERIAL_BAUDRATE                                 NRF_UART_BAUDRATE_921600
//#define SERIAL_BAUDRATE                                 NRF_UART_BAUDRATE_1000000
#define SERIAL_PARITY                                   NRF_UART_PARITY_EXCLUDED
#define SERIAL_HARDWARECTRL                             NRF_UART_HWFC_DISABLED
#define SERIAL_INTERRUPT_MODE                           NRF_UART_INT_MASK_RXDRDY


/* -------- Inertial Sensor */

#define IMU_SCL_PIN                                     11
#define IMU_SCL_PORT                                    0

#define IMU_SDA_PIN                                     5
#define IMU_SDA_PORT                                    0

#define IMU_INT_PIN                                     9
#define IMU_INT_PORT                                    1
#define IMU_INT_PULL_MODE                               NRF_GPIO_PIN_NOPULL


/* -------- TFT */

#define TFT_CS_PIN                                      3
#define TFT_CS_PORT                                     0
#define TFT_CS_H()                                      __GPIO_SET(TFT_CS_PORT, TFT_CS_PIN)
#define TFT_CS_L()                                      __GPIO_RST(TFT_CS_PORT, TFT_CS_PIN)

#define TFT_SCK_PIN                                     30
#define TFT_SCK_PORT                                    0
#define TFT_SCK_H()                                     __GPIO_SET(TFT_SCK_PORT, TFT_SCK_PIN)
#define TFT_SCK_L()                                     __GPIO_RST(TFT_SCK_PORT, TFT_SCK_PIN)
 
#define TFT_SDI_PIN                                     31
#define TFT_SDI_PORT                                    0
#define TFT_SDI_H()                                     __GPIO_SET(TFT_SDI_PORT, TFT_SDI_PIN)
#define TFT_SDI_L()                                     __GPIO_RST(TFT_SDI_PORT, TFT_SDI_PIN)

#define TFT_DC_PIN                                      29
#define TFT_DC_PORT                                     0
#define TFT_DC_H()                                      __GPIO_SET(TFT_DC_PORT, TFT_DC_PIN)
#define TFT_DC_L()                                      __GPIO_RST(TFT_DC_PORT, TFT_DC_PIN)

#define TFT_RST_PIN                                     28
#define TFT_RST_PORT                                    0
#define TFT_RST_H()                                     __GPIO_SET(TFT_RST_PORT, TFT_RST_PIN)
#define TFT_RST_L()                                     __GPIO_RST(TFT_RST_PORT, TFT_RST_PIN)

#define TFT_BLK_PIN                                     4
#define TFT_BLK_PORT                                    0
#define TFT_BLK_H()                                     __GPIO_SET(TFT_BLK_PORT, TFT_BLK_PIN)
#define TFT_BLK_L()                                     __GPIO_RST(TFT_BLK_PORT, TFT_BLK_PIN)
#define TFT_BLK_On()                                    TFT_BLK_H()
#define TFT_BLK_Off()                                   TFT_BLK_L()


/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Extern ----------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
