/**
*******************************************************************************
* @file           : as3020_drv.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : 21/02/2025
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
#include <stdbool.h>
#include <string.h>

#include "include/as3020_drv.h"
/******************************************************************************
    Defines and constants
******************************************************************************/
#define STX				(0x5A)
#define FID_0			(0x00)
#define FID_1			(0x01)
#define FID_2			(0x02)
#define ETX				(0xA5)
/******************************************************************************
    Data types
******************************************************************************/
typedef enum
{
	STX_IDX = 0,
	FID_IDX,
	LEN_HIGH_IDX,
	LEN_LOW_IDX,
	CMD_DATA_IDX,	
} data_format_idx_t;
/******************************************************************************
    Local variables
******************************************************************************/
static uint8_t buffer[BUFFER_RECV_SIZE_MAX] = {0};
static uint16_t buffer_idx = 0; 
static uint16_t cmd_data_len = 0; 
static uint8_t bcc = 0;
static bool analize_start = false;
/******************************************************************************
    Local function prototypes
******************************************************************************/
static as3020_ret_t analize_data(uint8_t data);
/******************************************************************************
    Local function definitions
******************************************************************************/
static as3020_ret_t analize_data(uint8_t data)
{
	if (true == analize_start)
	{
		buffer[buffer_idx] = data;
		
		if(LEN_HIGH_IDX == buffer_idx)
		{
			/* LENH */
			cmd_data_len = (uint16_t)(data << 8);
			bcc ^= data;
		}
		else if (LEN_LOW_IDX == buffer_idx)
		{
			/* LENL */
			cmd_data_len |= data;
			bcc ^= data;
		}
		else if ((buffer_idx - CMD_DATA_IDX) == cmd_data_len)
		{
			/* BCC */
			if (data == bcc)
			{
				bcc = data;
			}
			else
			{
				/* error - sequence reset */
				analize_start = false;			
			}
		}
		else if (ETX == data)
		{
			/* ETX */
			analize_start = false; 
			return AS3020_OK;
		}
		else
		{
			bcc ^= data;
		}
		
		buffer_idx = (buffer_idx < BUFFER_RECV_SIZE_MAX) ? (buffer_idx + 1) : 0;
	}
		
	if (STX == data && false == analize_start)
	{
		/* STX */
		analize_start = true;
		buffer[buffer_idx++] = data;
		buffer_idx = 0;
		bcc = 0;
	}
	
	return AS3020_ERROR;
}
/******************************************************************************
    Public function definitions
******************************************************************************/
as3020_ret_t as3020_init(as3020_t *as3020)
{
	if (NULL == as3020->buzzer || NULL == as3020->led ||
		NULL == as3020->reset || NULL == as3020->trigger || 
		NULL == as3020->uart_rx || NULL == as3020->uart_tx)
		{
			return AS3020_ERROR;
		}
		
	/* Init gpio level by default */
	
	/* Reset */
	
	/* Check is ready */
	
	return AS3020_OK;
}

as3020_ret_t as3020_send_cmd(as3020_data_format_t *cmd)
{
	return AS3020_OK;
}

as3020_ret_t as3020_scanning_code(uint8_t byte, uint8_t *code)
{	
	if (AS3020_OK == analize_data(byte))
	{
		code = malloc(sizeof(uint8_t) * cmd_data_len);
		memcpy(code, &buffer[CMD_DATA_IDX], cmd_data_len);		
		return AS3020_OK;
	}
	
	return AS3020_ERROR;
}

void as3020_buffer_free(uint8_t *code)
{
	free(code);
}
