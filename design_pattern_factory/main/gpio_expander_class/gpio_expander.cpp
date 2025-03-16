/**
*******************************************************************************
* @file           : gpio_expander.cpp
* @brief          : Description of implementation module
* @author         : Gonzalo Rivera
* @date           : 28/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
/******************************************************************************
    Includes
******************************************************************************/
#include <memory>
#include <stdio.h>

#include "gpio_expander.h"
#include "gpio_expander_drv_factory.h"
#include "tca9554_drv.h"
/*
	TODO: include BSP y/o HAL.
*/
/******************************************************************************
    Defines and constants
******************************************************************************/

/******************************************************************************
    Data types
******************************************************************************/

/******************************************************************************
    Local function prototypes
******************************************************************************/
static int mock_i2c_write_byte(uint8_t slave_addr, uint8_t reg_addr, uint8_t reg_value);
static int mock_i2c_read_byte(uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_value);
/******************************************************************************
    Local function definitions
******************************************************************************/
/**
 * @brief This configuration is to TCA9554 gpio expander.
 *
 * @note M = Master S = Slave 
 * _______________________________________________________________________________________________
 * | start | slave_addr + wr_bit + | ack | register_addr + | ack  | register_value  | ack  | stop |
 * ----M---|------------M----------|--S--|--------M--------|--S---|--------M--------|--S---|--M---|
 *
 */
static int mock_i2c_write_byte(uint8_t dev_address, uint8_t reg_address, uint8_t reg_value)
{
	return 0;
}

/**
 * @brief This configuration is to TCA9554 gpio expander.
 *
 * @note M = Master S = Slave 
 * ________________________________________________________________________________________________________________________________
 * | start | slave_addr + wr_bit | ack | register_addr | ack  | re_start | slave_addr + rd_bit| ack | register_value | nack | stop |
 * ----M---|------------M--------|--S--|--------M------|--S---|----M-----|----------M---------|--S--|--------S-------|---M--|--M---|
 *
 */
static int mock_i2c_read_byte(uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_value)
{
	return 0;
}

/******************************************************************************
    Class implementation
******************************************************************************/
gpio_expander::gpio_expander(gpio_expander_chip chip, uint8_t address)
{
	chip_address = address;
	
	switch(chip)
	{
		case gpio_expander_chip::TCA9554:
		case gpio_expander_chip::TCA9554A:
			
			tca9554_t tca9554_config = 
			{
				.slave_address = (tca9554_address_t)chip_address,
				
				// Nested designators are a C99 extension.
				.input_register{ .set {.all = 0x00}},
				.output_register{ .set {.all = 0x00}},
				.polarity_register{ .set {.all = 0x00}},
				.config_register{ .set {.all = 0x00}},
				
				.i2c_master_xmit = mock_i2c_write_byte,
				.i2c_master_recv = mock_i2c_read_byte
			};
			
		 	gpio_expander_driver = gpio_expander_drv_factory::create(chip, &tca9554_config);
	}	
}

void gpio_expander::set_address(uint8_t address)
{
	chip_address = address; // its secure that???
}

uint8_t gpio_expander::get_address()
{
	return chip_address;
}


