/**
*******************************************************************************
* @file           : hx710a_drv.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 20/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __HX710A_DRV_H__
#define __HX710A_DRV_H__
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
typedef enum
{
	DIFF_CH_10_HZ = 25,
	TEMP_CH = 26,
	DVDD_AVDD_CH = 26,
	DIFF_CH_40_HZ = 27
	
} hx710x_ch_t;

typedef enum
{
	HX710A_OK = 0,
	HX710A_ERROR
	
} hx710a_ret_t;

typedef void (*pd_sck_write_func_t)(uint8_t value);
typedef uint8_t (*dout_read_func_t)(void);
typedef void (*delay_us_t)(uint32_t us);

typedef struct
{
	pd_sck_write_func_t pd_sck_write;
	dout_read_func_t dout_read;
	delay_us_t delay_us;
	uint8_t gain;
	
} hx710a_t;
/******************************************************************************
        Public function prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

hx710a_ret_t hx710a_init(hx710a_t *hx710a);
uint32_t hx710_read(hx710a_t *hx710a);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __HX710A_DRV_H__

