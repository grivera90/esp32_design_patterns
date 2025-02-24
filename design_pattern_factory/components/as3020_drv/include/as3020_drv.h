/**
*******************************************************************************
* @file           : as3020_drv.h
* @brief          : Driver for AS3020 barcode scanner module. Wiki: "https://www.waveshare.com/wiki/Barcode_Scanner_Module".
* @author         : Gonzalo Rivera
* @date           : 21/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __AS3020_DRV_H__
#define __AS3020_DRV_H__
/******************************************************************************
        Includes
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
/******************************************************************************
        Constants
******************************************************************************/

/******************************************************************************
        Data types
******************************************************************************/
typedef enum
{
	AS3020_OK = 0,
	AS3020_ERROR
} as3020_ret_t;

typedef enum
{
	AS3020_BATCH_MODE = 0,
	AS3020_TRIGGER_MODE,
	AS3020_SENSING_MODE,
	AS3020_CONTINUOUS_MODE,
	AS3020_COMMAND_MODE,
	AS3020_MAX_MODES
	
} as3020_reading_mode_t;

/**
 * @brief List of commands implemented.
 *		In the future would be good to implement the 
 *		complete list of command in a typdef enum.
 *		For now just a #define is used.
 */
 
typedef enum
 {
	S_CMD_020F = 23,
	
 } as3020_cmd_t;

typedef uint8_t (*uart_xmit_t)(uint8_t *data, uint16_t data_size);
typedef uint8_t (*uart_recv_t)(uint8_t *data, uint16_t data_size);
typedef void (*gpio_out_t)(uint8_t value);
typedef uint8_t (*gpio_in_t)(void);

typedef struct
{
	uart_xmit_t uart_tx;
	uart_recv_t uart_rx;
	gpio_out_t buzzer;
	gpio_out_t led;
	gpio_in_t trigger;
	gpio_in_t reset;
	
} as3020_t;
/******************************************************************************
        Public function prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

as3020_ret_t as3020_init(as3020_t *as3020);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __AS3020_DRV_H__
