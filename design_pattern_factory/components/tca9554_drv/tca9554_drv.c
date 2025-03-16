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
tca9554_ret_t tca9554_init(tca9554_t *tca9554, tca9554_address_t chip_address, bool default_conf)
{
	if (NULL == tca9554->i2c_master_xmit || NULL == tca9554->i2c_master_recv)
	{
		return TCA9554_ERROR;
	}
	
	if (true == default_conf)
	{
		/* Default config. */
		tca9554->config_register.set.all = 0xFF;
		tca9554->output_register.set.all = 0xFF;
		tca9554->polarity_register.set.all = 0x00;	
	}
	
	tca9554->slave_address = chip_address;	

	if (0 != tca9554->i2c_master_xmit(tca9554->slave_address, TCA9554_CONFIG_REG, tca9554->config_register.set.all))
	{
		return TCA9554_ERROR;
	}
	
	if (0 != tca9554->i2c_master_xmit(tca9554->slave_address, TCA9554_POLARITY_REG, tca9554->polarity_register.set.all))
	{
		return TCA9554_ERROR;
	}
	
	if (0 != tca9554->i2c_master_xmit(tca9554->slave_address, TCA9554_OUTPUT_REG, tca9554->output_register.set.all))
	{
		return TCA9554_ERROR;
	}
	
	/* Check if the registers have been written correctly.  */
	uint8_t temp = 0; 
	if (0 != tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_CONFIG_REG, &temp) || temp != 0xFF)
	{
		return TCA9554_ERROR;
	}
	
	if (0 != tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_OUTPUT_REG, &temp) || temp != 0xFF)
	{
		return TCA9554_ERROR;
	}
	
	if (0 != tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_POLARITY_REG, &temp) || temp != 0x00)
	{
		return TCA9554_ERROR;
	}
	
	return TCA9554_OK;
}

tca9554_ret_t tca9554_write_reg(tca9554_t *tca9554, tca9554_reg_address_t reg_address, uint8_t reg_value)
{
	return (0 == tca9554->i2c_master_xmit(tca9554->slave_address, reg_address, reg_value)) ? TCA9554_OK : TCA9554_ERROR;
}

tca9554_ret_t tca9554_read_reg(tca9554_t *tca9554, tca9554_reg_address_t reg_address, uint8_t *reg_value)
{
	
	return (0 == tca9554->i2c_master_recv(tca9554->slave_address, reg_address, reg_value)) ? TCA9554_OK : TCA9554_ERROR;	
}

tca9554_ret_t tca9554_port_write(tca9554_t *tca9554, uint8_t port_value)
{
	return (0 == tca9554->i2c_master_xmit(tca9554->slave_address, TCA9554_OUTPUT_REG, port_value)) ? TCA9554_OK : TCA9554_ERROR;
}

tca9554_ret_t tca9554_port_read(tca9554_t *tca9554, uint8_t *port_value)
{
	return (0 == tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_INPUT_REG, port_value)) ? TCA9554_OK : TCA9554_ERROR;
}

tca9554_ret_t tca9554_port_write_polarity(tca9554_t *tca9554, uint8_t pol_value)
{
	return (0 == tca9554->i2c_master_xmit(tca9554->slave_address, TCA9554_POLARITY_REG, pol_value)) ? TCA9554_OK : TCA9554_ERROR;
}

tca9554_ret_t tca9554_port_read_polarity(tca9554_t *tca9554, uint8_t *pol_value)
{
	return (0 == tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_POLARITY_REG, pol_value)) ? TCA9554_OK : TCA9554_ERROR;
}

tca9554_ret_t tca9554_pin_write(tca9554_t *tca9554, tca9554_gpio_t gpio, bool gpio_value)
{
	uint8_t temp = 0; 
	
	if (0 != tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_OUTPUT_REG, &temp))
	{
		return TCA9554_ERROR;
	}
	
	/* MASK */
	if (true == gpio_value)
	{
		temp |= (1 << gpio);
	}
	else
	{
		temp &= ~(1 << gpio);
	}

	if (0 != tca9554->i2c_master_xmit(tca9554->slave_address, TCA9554_OUTPUT_REG, temp))
	{
		return TCA9554_ERROR;
	}
	
	return TCA9554_OK;
}

tca9554_ret_t tca9554_pin_read(tca9554_t *tca9554, tca9554_gpio_t gpio, bool *gpio_value)
{
	uint8_t temp = 0;
	if (0 != tca9554->i2c_master_recv(tca9554->slave_address, TCA9554_INPUT_REG, &temp))
	{
		return TCA9554_ERROR;
	}
	
	*gpio_value = (bool) (temp >> gpio);
	
	return TCA9554_OK;
}

