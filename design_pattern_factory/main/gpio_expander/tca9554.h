/**
*******************************************************************************
* @file           : tca9554.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 20/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> Systel S.A. All rights reserved.
*
*/
#ifndef __TCA9554_H__
#define __TCA9554_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdint.h>

#include "tca9554_drv.h"
#include "../gpio_expander_interface/gpio_expander_interface.h"
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/
 
 /******************************************************************************
        Public class
 ******************************************************************************/
class tca9554 : public gpio_expander_interface
{
	private:
		tca9554_t tca9554_conf;
	
	public: 
		tca9554(tca9554_t *config)
		{
			tca9554_conf = *config;
			tca9554_init(&tca9554_conf, tca9554_conf.slave_address);
		}
		
		void write_port(uint8_t port, uint8_t gpio) override
		{
			
		}
		
		uint8_t read_port(uint8_t port) override
		{
			return 0;
		}
		
		void gpio_write(uint8_t port, uint8_t gpio, uint8_t value) override
		{
			
		}
		
		uint8_t gpio_read(uint8_t port, uint8_t gpio) override
		{
			return 0;
		}
};

#endif // EOF __HX710A_H__
