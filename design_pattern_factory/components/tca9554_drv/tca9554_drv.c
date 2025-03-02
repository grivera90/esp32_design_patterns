/**
*******************************************************************************
* @file           : tca9554_drv.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : 25/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
/******************************************************************************
    Includes
******************************************************************************/
#include <stdint.h>
#include <stddef.h>

#include "include/tca9554_drv.h"
/******************************************************************************
    Defines and constants
******************************************************************************/

/******************************************************************************
    Data types
******************************************************************************/

/******************************************************************************
    Local variables
******************************************************************************/

/******************************************************************************
    Local function prototypes
******************************************************************************/

/******************************************************************************
    Local function definitions
******************************************************************************/

/******************************************************************************
    Public function definitions
******************************************************************************/
tca9554_ret_t tca9554_init(tca9554_t *tca9554, tca9554_address_t chip_address)
{
	if (NULL == tca9554->i2c_read_byte || NULL == tca9554->i2c_write_byte)
	{
		return TCA9554_ERROR;
	}
	
	tca9554->config_register.set.all = 0xFF;
	tca9554->output_register.set.all = 0xFF;
	tca9554->polarity_register.set.all = 0x00;
	tca9554->slave_address = chip_address;
	
	tca9554->i2c_write_byte(tca9554->slave_address, TCA9554_CONFIG_REG, tca9554->config_register.set.all);
	tca9554->i2c_write_byte(tca9554->slave_address, TCA9554_POLARITY_REG, tca9554->polarity_register.set.all);
	tca9554->i2c_write_byte(tca9554->slave_address, TCA9554_OUTPUT_REG, tca9554->output_register.set.all);
	
	/* check if the registers have been written correctly  */
	uint8_t temp = 0; 
	if (0xFF != tca9554->i2c_read_byte(tca9554->slave_address, TCA9554_CONFIG_REG, &temp))
	{
		return TCA9554_ERROR;
	}
	
	if (0xFF != tca9554->i2c_read_byte(tca9554->slave_address, TCA9554_POLARITY_REG, &temp))
	{
		return TCA9554_ERROR;
	}
	
	if (0x00 != tca9554->i2c_read_byte(tca9554->slave_address, TCA9554_OUTPUT_REG, &temp))
	{
		return TCA9554_ERROR;
	}
	
		
	return TCA9554_OK;
}

tca9554_ret_t tca9554_write_reg(tca9554_t *tca9554, tca9554_reg_address_t reg_address, uint8_t reg_value)
{
	return (0 == tca9554->i2c_write_byte(tca9554->slave_address, reg_address, reg_value)) ? TCA9554_OK : TCA9554_ERROR;
}

tca9554_ret_t tca9554_read_reg(tca9554_t *tca9554, tca9554_reg_address_t reg_address, uint8_t *reg_value)
{
	
	return (0 == tca9554->i2c_read_byte(tca9554->slave_address, reg_address, reg_value)) ? TCA9554_OK : TCA9554_ERROR;	
}

tca9554_ret_t tca9554_write_bit(tca9554_t *tca9554, tca9554_gpio_t gpio, uint8_t gpio_value)
{
	return TCA9554_OK;	
}

tca9554_ret_t tca9554_read_bit(tca9554_t *tca9554, tca9554_gpio_t gpio, uint8_t *gpio_value)
{
	return TCA9554_OK;	
}



