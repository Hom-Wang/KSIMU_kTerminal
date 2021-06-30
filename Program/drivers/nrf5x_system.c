/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_system.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_uart.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

#ifndef NRF_P1
NRF_GPIO_Type* const NRFX_PORT[2] = { NRF_P0, NRF_P0 };
#else
NRF_GPIO_Type* const NRFX_PORT[2] = { NRF_P0, NRF_P1 };
#endif
device_info_t dv = {0};

/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

void bsp_system_information( device_info_t *pdv )
{
    pdv->id         = KS_UUID32();
    pdv->mode       = 0;
    pdv->baudrate   = UART_RegValue2Baudrate(SERIAL_BAUDRATE);
    pdv->updaterate = DEFAULT_UPDATE_FREQ;

    klogd("Board Name: %s\n", KS_HW_BOARD_NAME);
    klogd("Controller: %s\n", KS_HW_MCU_NAME);
    klogd("\n");
    klogd("UUID: %04X%04X\n", (uint32_t)(KS_UUID64() >> 32), KS_UUID32());
    klogd("Mode: %d\n", pdv->mode);
    klogd("Baudrate: %d bps\n", pdv->baudrate);
    klogd("Updaterate: %d Hz\n", pdv->updaterate);
    klogd("\n");
}

/*************************************** END OF FILE ****************************************/
