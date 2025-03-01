/**
*******************************************************************************
* @file           : gpio_expander.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 28/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __GPIO_EXPANDER_H__
#define __GPIO_EXPANDER_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdint.h>
#include <vector>

#include "gpio_expander_drv_factory.h"
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/
typedef struct
{
	uint8_t port;
	uint8_t gpio;
} port_t;
 /******************************************************************************
        Public class
 ******************************************************************************/
class gpio_expander
{
	public:
		gpio_expander(gpio_expander_chips chip);
		gpio_expander(gpio_expander_chips chip, uint8_t address);
		~gpio_expander();
		
		void set_address(uint8_t address);
		uint8_t get_address();
		
		std::vector<port_t> get_available_ports();
		
		void set_all_output(void);
		void set_all_input(void);
		void set_gpio_output(uint8_t port, uint8_t gpio);
		void set_gpio_input(uint8_t port, uint8_t gpio);
		
		std::vector<port_t> read_all_ports();
		void write_all_ports(std::vector<port_t> p);
		
		bool gpio_read(uint8_t port, uint8_t gpio);
		void gpio_write(uint8_t port, uint8_t gpio, bool value);
		
	private:
		uint8_t chip_address;
		std::vector<port_t> ports;
};

#endif // EOF __GPIO_EXPANDER_H__

