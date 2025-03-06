/**
*******************************************************************************
* @file           : gpio_expander_drv_factory.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 28/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __GPIO_EXPANDER_DRV_FACTORY_H__
#define __GPIO_EXPANDER_DRV_FACTORY_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <memory>
#include <stdint.h>

#include "../gpio_expander_class/tca9554.h"
#include "../gpio_expander_interface/gpio_expander_interface.h"
#include "tca9554_drv.h"
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/
 
 /******************************************************************************
        Public class
 ******************************************************************************/
enum class gpio_expander_chip 
{
    TCA9554 = 0,
    TCA9554A,
};

class gpio_expander_drv_factory 
{
	public:
    	
    	static std::unique_ptr<gpio_expander_interface> create(gpio_expander_chip chip, tca9554_t *tca9554_conf) 
    	{	
        	switch (chip) 
        	{
            	case gpio_expander_chip::TCA9554:
            	case gpio_expander_chip::TCA9554A:
                	return std::make_unique<tca9554>(tca9554_conf);
            	
            	default:
                	return nullptr;
        	}
    	}
};

#endif // EOF __GPIO_EXPANDER_DRV_FACTORY_H__
