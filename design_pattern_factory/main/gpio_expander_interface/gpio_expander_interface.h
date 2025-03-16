/**
*******************************************************************************
* @file           : gpio_expander_interface.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 28/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __GPIO_EXPANDER_INTERFACE_H__
#define __GPIO_EXPANDER_INTERFACE_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdint.h>
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/

 /******************************************************************************
        Public class
 ******************************************************************************/
class gpio_expander_interface
{
	public:
		virtual ~gpio_expander_interface() = default;
		
		virtual void write_port(uint8_t port, uint8_t gpio) = 0;
		virtual uint8_t read_port(uint8_t port) = 0;
		virtual void gpio_write(uint8_t port, uint8_t gpio, uint8_t value) = 0;
		virtual uint8_t gpio_read(uint8_t port, uint8_t gpio) = 0;
};

#endif // EOF __GPIO_EXPANDER_INTERFACE_H__

