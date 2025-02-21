/**
*******************************************************************************
* @file           : scale_drv_factory.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 20/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __SCALE_DRV_FACTORY_H__
#define __SCALE_DRV_FACTORY_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <memory>
#include <stdint.h>
#include "adc_interface.h"
#include "hx710a.h"
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/
 
 /******************************************************************************
        Public class
 ******************************************************************************/
enum class adc_chip 
{
    HX710A = 0,
    ADS1232
};

class scale_drv_factory 
{
	public:
    	
    	static std::unique_ptr<adc_interface> create(adc_chip type, hx710a_t *hx710a_config) 
    	{	
        	switch (type) 
        	{
            	case adc_chip::HX710A:
                case adc_chip::ADS1232:
                	return std::make_unique<hx710a>(hx710a_config);
            	
            	default:
                	return nullptr;
        	}
    	}
};

#endif // EOF __SCALE_DRV_FACTORY_H__
