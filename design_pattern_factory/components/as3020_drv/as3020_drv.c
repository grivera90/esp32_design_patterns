/**
*******************************************************************************
* @file           : as3020_drv.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : dd/mm/aaaa
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

typedef struct
{
	uint8_t stx;
	uint8_t fid;
	uint16_t len;
	uint8_t *cmd;
	uint8_t *data;
	uint8_t bcc;
	uint8_t etx;
	
} as3020_data_format_t;
/******************************************************************************
    Local variables
******************************************************************************/
static uint8_t buffer[256] = {0};
static uint8_t buffer_idx = 0; 
static uint16_t cmd_data_len = 0; 
static uint8_t bcc = 0;
static bool analize_start = false;
/******************************************************************************
    Local function prototypes
******************************************************************************/
static as3020_ret_t analize_data(uint8_t data);
static uint8_t bcc_calculator(uint8_t *data, uint16_t len);
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
			cmd_data_len = data;
			cmd_data_len <<= 8;
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
		
		buffer_idx++;
	}
		
	if (STX == data && false == analize_start)
	{
		/* STX */
		analize_start = true;
		buffer_idx = 0;
		bcc = 0;
		buffer[buffer_idx++] = data;
	}
	
	return AS3020_ERROR;
}

static uint8_t bcc_calculator(uint8_t *data, uint16_t len)
{
	uint16_t i = 0;
	uint8_t bcc = 0;
	
	for (i = 0; i < len; i++)
	{
		bcc ^= data[i];
	}
	
	return bcc;
}
/******************************************************************************
    Public function definitions
******************************************************************************/
as3020_ret_t as3020_init(as3020_t *as3020)
{
	return AS3020_OK;
}

as3020_ret_t as3020_send_cmd(as3020_cmd_t cmd)
{
	return AS3020_OK;
}

as3020_ret_t as3020_scanning_code(uint8_t byte, uint8_t *code)
{
	as3020_ret_t ret = 0;
	
	// 1. get a byte from uart and call analize function 
	if (AS3020_OK == analize_data(byte))
	{
		// 2. check bcc
		ret = (bcc == bcc_calculator(&buffer[FID_IDX], (cmd_data_len + 3))) ? AS3020_OK : AS3020_ERROR;
		if (AS3020_OK != ret)
		{
			// 3. reserv memory to the code
			code = malloc(sizeof(uint8_t) * cmd_data_len);
			// 4. copy and return OK. For another way return erron and code = NULL.
			memcpy(code, &buffer[CMD_DATA_IDX], cmd_data_len);
		}
		
		return AS3020_ERROR;
	}


	
	return ret;
}

