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
		virtual uint32_t get_count() = 0;
};

#endif // EOF __GPIO_EXPANDER_INTERFACE_H__

