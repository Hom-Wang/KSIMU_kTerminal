/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    lps22hb.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __LPS22HB_H
#define __LPS22HB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include <stdint.h>

/* Define ----------------------------------------------------------------------------------*/

#define LPS22HB_I2C_ADDR                                ((uint8_t)0x5C)     // SA0 = 0
#define LPS22HB_DEVICD_ID                               ((uint8_t)0xB1)

#define LPS22HB_INTERRUPT_CFG                           ((uint8_t)0x0B)
#define LPS22HB_THS_P_L                                 ((uint8_t)0x0C)
#define LPS22HB_THS_P_H                                 ((uint8_t)0x0D)
#define LPS22HB_WHO_AM_I                                ((uint8_t)0x0F)     // Who am I
#define LPS22HB_CTRL_REG1                               ((uint8_t)0x10)
#define LPS22HB_CTRL_REG2                               ((uint8_t)0x11)
#define LPS22HB_CTRL_REG3                               ((uint8_t)0x12)     // Interrupt control
#define LPS22HB_FIFO_CTRL                               ((uint8_t)0x14)
#define LPS22HB_REF_P_XL                                ((uint8_t)0x15)
#define LPS22HB_REF_P_L                                 ((uint8_t)0x16)
#define LPS22HB_REF_P_H                                 ((uint8_t)0x17)
#define LPS22HB_RPDS_L                                  ((uint8_t)0x18)
#define LPS22HB_RPDS_H                                  ((uint8_t)0x19)
#define LPS22HB_RES_CONF                                ((uint8_t)0x1A)
#define LPS22HB_INT_SOURCE                              ((uint8_t)0x25)
#define LPS22HB_FIFO_STATUS                             ((uint8_t)0x26)
#define LPS22HB_STATUS                                  ((uint8_t)0x27)
#define LPS22HB_PRESS_OUT_XL                            ((uint8_t)0x28)
#define LPS22HB_PRESS_OUT_L                             ((uint8_t)0x29)
#define LPS22HB_PRESS_OUT_H                             ((uint8_t)0x2A)
#define LPS22HB_TEMP_OUT_L                              ((uint8_t)0x2B)
#define LPS22HB_TEMP_OUT_H                              ((uint8_t)0x2C)
#define LPS22HB_LPFP_RES                                ((uint8_t)0x33)

//#define LPS22HB_SENS_500UT_LSB                          (6.6)               // ±500 uT, LSB/uT
//#define LPS22HB_SENS_200UT_LSB                          (13.2)              // ±200 uT, LSB/uT

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

void        LPS22HB_WriteReg( uint8_t writeAddr, uint8_t writeData );
void        LPS22HB_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens );
uint8_t     LPS22HB_ReadReg( uint8_t readAddr );
void        LPS22HB_ReadRegs( uint8_t readAddr, uint8_t *readData, uint8_t lens );

void        LPS22HB_Config( void );
uint32_t    LPS22HB_Init( void );

uint32_t    LPS22HB_DeviceCheck( uint8_t deviceid );
double      LPS22HB_GetBaroSensitivity( void );
double      LPS22HB_GetTempSensitivity( void );
uint32_t    LPS22HB_GetLsbData( int32_t *lsb );
uint32_t    LPS22HB_GetRawData( float *raw );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
