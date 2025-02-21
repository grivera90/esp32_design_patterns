/**
*******************************************************************************
* @file           : scale.cpp
* @brief          : Description of implementation module
* @author         : Gonzalo Rivera
* @date           : 20/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> Systel S.A. All rights reserved.
*
*/
/******************************************************************************
    Includes
******************************************************************************/
#include <memory>
#include <stdio.h>

#include "scale.h"
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
static void mock_gpio_write(uint8_t value);
static uint8_t mock_gpio_read(void);
static void mock_delay_us(uint32_t us);
/******************************************************************************
    Local function definitions
******************************************************************************/
static void mock_gpio_write(uint8_t value)
{
	
}

static uint8_t mock_gpio_read(void)
{
	return 1;	
}

static void mock_delay_us(uint32_t us)
{
	
}
/******************************************************************************
    Class implementation
******************************************************************************/
scale::scale(adc_chip chip)
{
	// scale_drv_factory scale_factory;
	
	switch(chip)
	{
		case adc_chip::HX710A:
		case adc_chip::ADS1232:
			hx710a_t hx710a_config = 
			{
				.pd_sck_write = mock_gpio_write,
				.dout_read = mock_gpio_read,
				.delay_us = mock_delay_us,
				.gain = 128
			};
			
		 	// adc_driver = scale_factory.create(chip, &hx710a_config);
		 	adc_driver = scale_drv_factory::create(chip, &hx710a_config);
	}
}

void scale::set_zero()
{
	scale_zero = 0; // set zero from some method.
}
bool scale::is_stable()
{
	return scale_stable = false;
}
double scale::get_weight()
{
	uint32_t c = adc_driver->get_count();
	return scale_weight = (double) c;
}

void scale::set_filter(scale_filter_t filter)
{
	scale_filter = filter;
}
scale_filter_t scale::get_filter()
{
	return FILTER_NONE;
}

