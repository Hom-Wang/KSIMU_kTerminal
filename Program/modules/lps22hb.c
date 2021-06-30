/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 *  
 *  @file    lps22hb.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "drivers\simui2c\nrf5x_i2cSimu.h"
#include "modules\lps22hb.h"

/* Define ----------------------------------------------------------------------------------*/

#define LPS22HB_Delay(__MS)     delay_ms(__MS)

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

static SimuI2C_InitTypeDef hi2c;

/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

/**
 *  @brief  LPS22HB_WriteReg
 */
void LPS22HB_WriteReg( uint8_t writeAddr, uint8_t writeData )
{
    SimuI2C_WriteReg(&hi2c, LPS22HB_I2C_ADDR, writeAddr, writeData);
}

/**
 *  @brief  LPS22HB_WriteRegs
 */
void LPS22HB_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
    SimuI2C_WriteRegs(&hi2c, LPS22HB_I2C_ADDR, writeAddr, writeData, lens);
}

/**
 *  @brief  LPS22HB_ReadReg
 */
uint8_t LPS22HB_ReadReg( uint8_t readAddr )
{
    uint8_t readData;
    SimuI2C_ReadReg(&hi2c, LPS22HB_I2C_ADDR, readAddr, &readData);
    return readData;
}

/**
 *  @brief  LPS22HB_ReadRegs
 */
void LPS22HB_ReadRegs( uint8_t readAddr, uint8_t *readData, uint8_t lens )
{
    SimuI2C_ReadRegs(&hi2c, LPS22HB_I2C_ADDR, readAddr, readData, lens);
}

/**
 *  @brief  LPS22HB_Config
 */
void LPS22HB_Config( void )
{
    hi2c.PinSCL    = IMU_SCL_PIN;
    hi2c.PortSCL   = IMU_SCL_PORT;
    hi2c.PinSDA    = IMU_SDA_PIN;
    hi2c.PortSDA   = IMU_SDA_PORT;
    hi2c.Frequency = 5;
    SimuI2C_Config(&hi2c);
}

/**
 *  @brief  LPS22HB_Init
 */
uint32_t LPS22HB_Init( void )
{
    uint8_t deviceid;

    klogd("\n");
    klogd("  >> lps22hb initial (address %02X)\n", LPS22HB_I2C_ADDR);
    klogd("  lps22hb device id check            ... ");
    deviceid = LPS22HB_ReadReg(LPS22HB_WHO_AM_I);
    klogd("0x%02X", deviceid);
    if (LPS22HB_DeviceCheck(deviceid) != KS_OK)
    {
        klogd(" ... error\n");
        return KS_ERROR;
    }
    else
    {
        klogd(" ... ok\n");
    }

    klogd("  lps22hb software reset\n");
    LPS22HB_Delay(10);
    LPS22HB_WriteReg(LPS22HB_CTRL_REG2, 0x14);
    LPS22HB_Delay(50);

    uint8_t reg[2][2] =
    {
        {LPS22HB_RES_CONF, 0x00},   // Normal Mode
//        {LPS22HB_RES_CONF, 0x01},   // Low Current mode

//        {LPS22HB_CTRL_REG1, 0x00},  // LPF disabled, one-shot mode enabled
//        {LPS22HB_CTRL_REG1, 0x10},  // LPF disabled, ODR 1 Hz
//        {LPS22HB_CTRL_REG1, 0x20},  // LPF disabled, ODR 10 Hz
//        {LPS22HB_CTRL_REG1, 0x30},  // LPF disabled, ODR 25 Hz
//        {LPS22HB_CTRL_REG1, 0x40},  // LPF disabled, ODR 50 Hz
        {LPS22HB_CTRL_REG1, 0x50},  // LPF disabled, ODR 75 Hz
    };

    klogd("  lps22hb normal mode                ... %02Xh = 0x%02X\n", reg[0][0], reg[0][1]);
    LPS22HB_WriteReg(reg[0][0], reg[0][1]);
    klogd("  lps22hb output data rate setting   ... %02Xh = 0x%02X\n", reg[1][0], reg[1][1]);
    LPS22HB_WriteReg(reg[1][0], reg[1][1]);

    return KS_OK;
}

/**
 *  @brief  LPS22HB_DeviceCheck
 */
uint32_t LPS22HB_DeviceCheck( uint8_t deviceid )
{
#if 0
    printf(" ... 0x%02X (%02X) ... ", deviceid, LPS22HB_I2C_ADDR);
//    return KS_ERROR;
#endif

    if (deviceid != LPS22HB_DEVICD_ID)
    {
        return KS_ERROR;
    }

    return KS_OK;
}

/**
 *  @brief  LPS22HB_GetBaroSensitivity
 */
double LPS22HB_GetBaroSensitivity( void )
{
    return 1.0 / 4096.0;
}

/**
 *  @brief  LPS22HB_GetTempSensitivity
 */
double LPS22HB_GetTempSensitivity( void )
{
    return 1.0 / 100.0;
}

/**
 *  @brief  LPS22HB_GetLsbData
 */
uint32_t LPS22HB_GetLsbData( int32_t *lsb )
{
    uint8_t res[5] = {0};
    LPS22HB_ReadRegs(LPS22HB_PRESS_OUT_XL, res, 5);
    lsb[0] = (int32_t)(res[2] << 16) | (res[1] << 8) | res[0];
    lsb[1] = (int16_t)(res[4] << 8) | res[3];
    if (lsb[0] & 0x00800000)
    {
        lsb[0] |= 0xFF000000;
    }
#if 0
    klogd("lsb[0] = %8d, lsb[1] = %8d\n", lsb[0], lsb[1]);
#endif
    return KS_OK;
}

/**
 *  @brief  LPS22HB_GetRawData
 */
uint32_t LPS22HB_GetRawData( float *raw )
{
    uint32_t status;
    int32_t res[2] = {0};
    status = LPS22HB_GetLsbData(res);
    if (status == KS_OK)
    {
        raw[0] = res[0] / 4096.0;
        raw[1] = res[1] / 100.0;
    }
    return status;
}

/*************************************** END OF FILE ****************************************/
