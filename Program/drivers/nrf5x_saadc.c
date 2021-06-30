/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_saadc.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_saadc.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

static int16_t saadc_buffer[DEFAULT_SAADC_BUFFER_SIZE] = {0};

/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

/**
 *  @brief  SAADC_BaseInit
 */
void SAADC_BaseInit( SAADC_BaseInitTypeDef *hsaadc )
{
    hsaadc->Instance->RESOLUTION = hsaadc->Resolution;
    hsaadc->Instance->OVERSAMPLE = hsaadc->Oversample;
    if (hsaadc->EventCallback != NULL)
    {
        SAADC_InterruptCmd(hsaadc, NRF_SAADC_INT_ALL, DISABLE);
    }
    SAADC_EVENTS_END(hsaadc->Instance) = RESET;
    SAADC_EVENTS_STARTED(hsaadc->Instance) = RESET;
    SAADC_EVENTS_STOPPED(hsaadc->Instance) = RESET;

    if (hsaadc->BufferSize != 0)
    {
        hsaadc->Instance->RESULT.MAXCNT = hsaadc->BufferSize;
        hsaadc->Instance->RESULT.PTR = (uint32_t)&hsaadc->Buffer;
    }
    else
    {
        hsaadc->Instance->RESULT.MAXCNT = DEFAULT_SAADC_BUFFER_SIZE;
        hsaadc->Instance->RESULT.PTR = (uint32_t)&saadc_buffer;
    }
}

/**
 *  @brief  SAADC_ChannelInit
 */
void SAADC_ChannelInit( SAADC_BaseInitTypeDef *hsaadc, SAADC_ChannelInitTypeDef *hsaadcch )
{
    hsaadc->Instance->CH[hsaadcch->Channel].CONFIG =
        ((hsaadcch->ResistorP << SAADC_CH_CONFIG_RESP_Pos)   & SAADC_CH_CONFIG_RESP_Msk)   | 
        ((hsaadcch->ResistorN << SAADC_CH_CONFIG_RESN_Pos)   & SAADC_CH_CONFIG_RESN_Msk)   | 
        ((hsaadcch->Gain      << SAADC_CH_CONFIG_GAIN_Pos)   & SAADC_CH_CONFIG_GAIN_Msk)   | 
        ((hsaadcch->Reference << SAADC_CH_CONFIG_REFSEL_Pos) & SAADC_CH_CONFIG_REFSEL_Msk) | 
        ((hsaadcch->AcqTime   << SAADC_CH_CONFIG_TACQ_Pos)   & SAADC_CH_CONFIG_TACQ_Msk)   | 
        ((hsaadcch->Mode      << SAADC_CH_CONFIG_MODE_Pos)   & SAADC_CH_CONFIG_MODE_Msk)   | 
        ((hsaadcch->Burst     << SAADC_CH_CONFIG_BURST_Pos)  & SAADC_CH_CONFIG_BURST_Msk);
    hsaadc->Instance->CH[hsaadcch->Channel].PSELN = hsaadcch->InputN;
    hsaadc->Instance->CH[hsaadcch->Channel].PSELP = hsaadcch->InputP;
}

/**
 *  @brief  SAADC_Cmd
 */
void SAADC_Cmd( SAADC_BaseInitTypeDef *hsaadc, uint32_t state )
{
    if (state != ENABLE)
    {
        hsaadc->Instance->ENABLE = SAADC_ENABLE_ENABLE_Disabled;
    }
    else
    {
        hsaadc->Instance->ENABLE = SAADC_ENABLE_ENABLE_Enabled;
    }
}

/**
 *  @brief  SAADC_InterruptCmd
 */
void SAADC_InterruptCmd( SAADC_BaseInitTypeDef *saadc, uint32_t mode, uint32_t state )
{
    if (state == ENABLE)
    {
        saadc->Instance->INTENSET = mode;
    }
    else
    {
        saadc->Instance->INTENCLR = mode;
    }
}

/**
 *  @brief  SAADC_SingleRead
 */
int16_t SAADC_SingleRead( SAADC_BaseInitTypeDef *hsaadc )
{
    hsaadc->Instance->RESULT.MAXCNT = 1;
    hsaadc->Instance->RESULT.PTR = (uint32_t)&saadc_buffer;

    SAADC_TASKS_START(hsaadc->Instance) = SET;
    while (SAADC_EVENTS_STARTED(hsaadc->Instance) != SET);
    SAADC_TASKS_SAMPLE(hsaadc->Instance) = SET;
    while (SAADC_EVENTS_END(hsaadc->Instance) != SET);

    return saadc_buffer[0];
}
//int16_t SAADC_SingleRead( SAADC_BaseInitTypeDef *hsaadc )
//{
//    int16_t result[2];

//    hsaadc->Instance->RESULT.MAXCNT = 1;
//    hsaadc->Instance->RESULT.PTR = (uint32_t)result;
//    SAADC_TASKS_START(hsaadc->Instance) = SET;
//    while (SAADC_EVENTS_STARTED(hsaadc->Instance) != SET);
//    SAADC_TASKS_SAMPLE(hsaadc->Instance) = SET;
//    while (SAADC_EVENTS_END(hsaadc->Instance) != SET);

//    return result[0];
//}

/*************************************** END OF FILE ****************************************/

///**
// *  @brief  ADC_InterruptCmd
// */
//void ADC_InterruptCmd( ADC_InitTypeDef *hadc, uint32_t state )
//{
//    if (state != ENABLE)
//    {
//        hadc->Instance->INTENCLR = ADC_INTENCLR_END_Enabled;
//    }
//    else
//    {
//        hadc->Instance->INTENSET = ADC_INTENSET_END_Enabled;
//    }
//}

///**
// *  @brief  ADC_Start
// */
//void ADC_Start( ADC_InitTypeDef *hadc )
//{
//    ADC_TASKS_START(hadc->Instance) = SET;
//}

///**
// *  @brief  ADC_Stop
// */
//void ADC_Stop( ADC_InitTypeDef *hadc )
//{
//    ADC_TASKS_STOP(hadc->Instance) = SET;
//}

///**
// *  @brief  ADC_Read
// */
//uint16_t ADC_Read( ADC_InitTypeDef *hadc )
//{
//    ADC_EVENTS_END(hadc->Instance) = RESET;
//    return ADC_RESULT(hadc->Instance);
//}



