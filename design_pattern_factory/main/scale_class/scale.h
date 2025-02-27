/**
*******************************************************************************
* @file           : scale.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 20/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __SCALE_H__
#define __SCALE_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdint.h>
#include "scale_drv_factory.h"
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/
 typedef enum
 {
	FILTER_NONE = 0,
	FILTER_FIR,
	FILTER_IIR,
	FILTER_BESSEL,
	FILTER_MAX
	
 } scale_filter_t;
 
 typedef struct 
 {
	scale_filter_t filter;
	uint8_t gain;
	uint8_t prom;
	
 } scale_config_t;
 /******************************************************************************
        Public class
 ******************************************************************************/
class scale
{
	public:
		scale(adc_chip chip);
		~scale();
		
		void set_zero();
		bool is_stable();
		double get_weight();
		void set_filter(scale_filter_t filter);
		scale_filter_t get_filter();
	
	private:
		std::unique_ptr<adc_interface> adc_driver;
		bool scale_stable = false;
		double scale_weight;
		double scale_zero;
		scale_filter_t scale_filter = FILTER_NONE;
};

#endif // EOF __SCALE_H__

