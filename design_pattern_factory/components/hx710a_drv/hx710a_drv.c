/**
*******************************************************************************
* @file           : hx710a_drv.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : 20/02/2025
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
#include <stdio.h>
#include <stdbool.h>

#include "include/hx710a_drv.h"
/******************************************************************************
    Defines and constants
******************************************************************************/
const char *MODULE_NAME = "[HX710A]";
/******************************************************************************
    Data types
******************************************************************************/

/******************************************************************************
    Local variables
******************************************************************************/

/******************************************************************************
    Local function prototypes
******************************************************************************/
static uint32_t bit_banding_read(hx710a_t *hx710a);
static void set_channel(hx710a_t *hx710a, hx710x_ch_t ch);
static bool wait_to_ready(hx710a_t *hx710a, uint32_t timeout_ms);
/******************************************************************************
    Local function definitions
******************************************************************************/
static uint32_t bit_banding_read(hx710a_t *hx710a)
{
	uint8_t i = 0; 
	uint32_t adc_raw_value = 0; 
	
	for (i = 0; i < 24; i++)
	{
		hx710a->pd_sck_write(1);
		hx710a->delay_us(1);
		
		adc_raw_value |= hx710a->dout_read() << (23 - i);
		
		hx710a->pd_sck_write(0);
		hx710a->delay_us(1);
	}
	
	return adc_raw_value;
}

static void set_channel(hx710a_t *hx710a, hx710x_ch_t ch)
{
	uint8_t i = 0; 
	
	for (i = 0; i < (ch - 24); i++)
	{
		hx710a->pd_sck_write(1);
		hx710a->delay_us(1);
		
		hx710a->pd_sck_write(0);
		hx710a->delay_us(1);		
	}
}

static bool wait_to_ready(hx710a_t *hx710a, uint32_t timeout_ms)
{
	uint32_t ms = 0; 
	
	while(ms < timeout_ms)
	{
		if (hx710a->dout_read() != 1)
		{
			return true;
		}
		
		hx710a->delay_us(1000);
		ms++;
	}
	
	return false; 
}
/******************************************************************************
    Public function definitions
******************************************************************************/
hx710a_ret_t hx710a_init(hx710a_t *hx710a)
{
	if (NULL == hx710a->dout_read || NULL == hx710a->pd_sck_write || NULL == hx710a->delay_us)
	{
		return HX710A_ERROR;
	}

	hx710a->pd_sck_write(0);
	hx710a->delay_us(1000);
	
	return (wait_to_ready(hx710a, 200) == true) ? HX710A_OK : HX710A_ERROR;
}

uint32_t hx710_read(hx710a_t *hx710a)
{
	uint32_t adc_counts = bit_banding_read(hx710a);
	set_channel(hx710a, DIFF_CH_10_HZ);
	
	return adc_counts;
}



