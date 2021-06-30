/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_saadc.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5x_SAADC_H
#define __NRF5x_SAADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "nrf_saadc.h"

/* Define ----------------------------------------------------------------------------------*/

#define DEFAULT_SAADC_BUFFER_SIZE                       16

/* Macro -----------------------------------------------------------------------------------*/

//#define UART_TASKS_STARTRX(__INS)                       __INS->TASKS_STARTRX    // Start UART receiver
//#define UART_TASKS_STOPRX(__INS)                        __INS->TASKS_STOPRX     // Stop UART receiver
//#define UART_TASKS_STARTTX(__INS)                       __INS->TASKS_STARTTX    // Start UART transmitter
//#define UART_TASKS_STOPTX(__INS)                        __INS->TASKS_STOPTX     // Stop UART transmitter
//#define UART_TASKS_SUSPEND(__INS)                       __INS->TASKS_SUSPEND    // Suspend UART

//#define UART_EVENTS_CTS(__INS)                          __INS->EVENTS_CTS       // CTS is activated (set low). Clear To Send.
//#define UART_EVENTS_NCTS(__INS)                         __INS->EVENTS_NCTS      // CTS is deactivated (set high). Not Clear To Send.
//#define UART_EVENTS_RXDRDY(__INS)                       __INS->EVENTS_RXDRDY    // Data received in RXD.
//#define UART_EVENTS_TXDRDY(__INS)                       __INS->EVENTS_TXDRDY    // Data sent from TXD
//#define UART_EVENTS_ERROR(__INS)                        __INS->EVENTS_ERROR     // Error detected
//#define UART_EVENTS_RXTO(__INS)                         __INS->EVENTS_RXTO      // Receiver timeout

#define SAADC_TASKS_START(__INS)                        __INS->TASKS_START              // Starts the SAADC and prepares the result buffer in RAM
#define SAADC_TASKS_SAMPLE(__INS)                       __INS->TASKS_SAMPLE             // Takes one SAADC sample
#define SAADC_TASKS_STOP(__INS)                         __INS->TASKS_STOP               // Stops the SAADC and terminates all on-going conversions
#define SAADC_TASKS_CALIBRATEOFFSET(__INS)              __INS->TASKS_CALIBRATEOFFSET    // Starts offset auto-calibration

#define SAADC_EVENTS_STARTED(__INS)                     __INS->EVENTS_STARTED           // The SAADC has started
#define SAADC_EVENTS_END(__INS)                         __INS->EVENTS_END               // The SAADC has filled up the result buffer
#define SAADC_EVENTS_DONE(__INS)                        __INS->EVENTS_DONE              // A conversion task has been completed. Depending on the configuration, multiple conversions might be needed for a result to be transferred to RAM.
#define SAADC_EVENTS_RESULTDONE(__INS)                  __INS->EVENTS_RESULTDONE        // Result ready for transfer to RAM
#define SAADC_EVENTS_CALIBRATEDONE(__INS)               __INS->EVENTS_CALIBRATEDONE     // Calibration is complete
#define SAADC_EVENTS_STOPPED(__INS)                     __INS->EVENTS_STOPPED           // The SAADC has stopped

//#define SAADC_EVENTS_END(__INS)                         __INS->EVENTS_END   // An ADC conversion is completed

//#define SAADC_RESULT(__INS)                             __INS->RESULT

/* Typedef ---------------------------------------------------------------------------------*/

typedef struct
{
    NRF_SAADC_Type *Instance;

    uint32_t Resolution;
    // NRF_SAADC_RESOLUTION_8BIT        -  8 bit resolution
    // NRF_SAADC_RESOLUTION_10BIT       - 10 bit resolution
    // NRF_SAADC_RESOLUTION_12BIT       - 12 bit resolution
    // NRF_SAADC_RESOLUTION_14BIT       - 14 bit resolution
    uint32_t Oversample;
    // NRF_SAADC_OVERSAMPLE_DISABLED    - No oversampling
    // NRF_SAADC_OVERSAMPLE_2X          - Oversample 2x
    // NRF_SAADC_OVERSAMPLE_4X          - Oversample 4x
    // NRF_SAADC_OVERSAMPLE_8X          - Oversample 8x
    // NRF_SAADC_OVERSAMPLE_16X         - Oversample 16x
    // NRF_SAADC_OVERSAMPLE_32X         - Oversample 32x
    // NRF_SAADC_OVERSAMPLE_64X         - Oversample 64x
    // NRF_SAADC_OVERSAMPLE_128X        - Oversample 128x
    // NRF_SAADC_OVERSAMPLE_256X        - Oversample 256x
    uint32_t BufferSize;
    int16_t Buffer;

    pFunc EventCallback;
    // SAADC EVENT CALLBACK

} SAADC_BaseInitTypeDef;

typedef struct
{
    uint32_t Channel;
    // 0 ~ NRF_SAADC_CHANNEL_COUNT - 1
    // Oversampling can be used only with one channel.
    uint32_t InputP;
    uint32_t InputN;
    // NRF_SAADC_INPUT_DISABLED     - Not connected
    // NRF_SAADC_INPUT_AIN0         - Analog input 0 (AIN0)
    // NRF_SAADC_INPUT_AIN1         - Analog input 1 (AIN1)
    // NRF_SAADC_INPUT_AIN2         - Analog input 2 (AIN2)
    // NRF_SAADC_INPUT_AIN3         - Analog input 3 (AIN3)
    // NRF_SAADC_INPUT_AIN4         - Analog input 4 (AIN4)
    // NRF_SAADC_INPUT_AIN5         - Analog input 5 (AIN5)
    // NRF_SAADC_INPUT_AIN6         - Analog input 6 (AIN6)
    // NRF_SAADC_INPUT_AIN7         - Analog input 7 (AIN7)
    // NRF_SAADC_INPUT_VDD          - VDD as input
    // NRF_SAADC_INPUT_VDDHDIV5     - VDDH/5 as input
    uint32_t ResistorP;
    uint32_t ResistorN;
    // NRF_SAADC_RESISTOR_DISABLED  - Bypass resistor ladder
    // NRF_SAADC_RESISTOR_PULLDOWN  - Pull-down to GND
    // NRF_SAADC_RESISTOR_PULLUP    - Pull-up to VDD
    // NRF_SAADC_RESISTOR_VDD1_2    - Set input at VDD/2
    uint32_t Gain;
    // NRF_SAADC_GAIN1_6            - Gain factor 1/6
    // NRF_SAADC_GAIN1_5            - Gain factor 1/5
    // NRF_SAADC_GAIN1_4            - Gain factor 1/4
    // NRF_SAADC_GAIN1_3            - Gain factor 1/3
    // NRF_SAADC_GAIN1_2            - Gain factor 1/2
    // NRF_SAADC_GAIN1              - Gain factor 1
    // NRF_SAADC_GAIN2              - Gain factor 2
    // NRF_SAADC_GAIN4              - Gain factor 4
    uint32_t Reference;
    // NRF_SAADC_REFERENCE_INTERNAL - Internal reference (0.6 V)
    // NRF_SAADC_REFERENCE_VDD4     - VDD/4 as reference
    uint32_t AcqTime;
    // NRF_SAADC_ACQTIME_3US        - 3 us
    // NRF_SAADC_ACQTIME_5US        - 5 us
    // NRF_SAADC_ACQTIME_10US       - 10 us
    // NRF_SAADC_ACQTIME_15US       - 15 us
    // NRF_SAADC_ACQTIME_20US       - 20 us
    // NRF_SAADC_ACQTIME_40US       - 40 us
    uint32_t Mode;
    // NRF_SAADC_MODE_SINGLE_ENDED  - Single-ended mode. PSELN will be ignored, negative input to ADC shorted to GND
    // NRF_SAADC_MODE_DIFFERENTIAL  - Differential mode.
    uint32_t Burst;
    // NRF_SAADC_BURST_DISABLED     - Burst mode is disabled (normal operation)
    // NRF_SAADC_BURST_ENABLED      - Burst mode is enabled. SAADC takes 2^OVERSAMPLE number of samples as fast as it can, and sends the average to Data RAM

} SAADC_ChannelInitTypeDef;

/* Extern ----------------------------------------------------------------------------------*/

//extern const uint32_t BAUDRATE_REGVAL[18][2];

/* Functions -------------------------------------------------------------------------------*/

void        SAADC_BaseInit( SAADC_BaseInitTypeDef *hssadc );
void        SAADC_ChannelInit( SAADC_BaseInitTypeDef *hssadc, SAADC_ChannelInitTypeDef *hsaadcch );
void        SAADC_Cmd( SAADC_BaseInitTypeDef *hssadc, uint32_t state );
void        SAADC_InterruptCmd( SAADC_BaseInitTypeDef *saadc, uint32_t mode, uint32_t state );

int16_t SAADC_SingleRead( SAADC_BaseInitTypeDef *hsaadc );

//void        ADC_Init( ADC_InitTypeDef *hadc );
//void        ADC_Cmd( ADC_InitTypeDef *hadc, uint32_t state );
//void        ADC_InterruptCmd( ADC_InitTypeDef *hadc, uint32_t state );
//void        ADC_Start( ADC_InitTypeDef *hadc );
//void        ADC_Stop( ADC_InitTypeDef *hadc );
//uint16_t    ADC_Read( ADC_InitTypeDef *hadc );
//uint16_t    ADC_ReadData( ADC_InitTypeDef *hadc );


#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
