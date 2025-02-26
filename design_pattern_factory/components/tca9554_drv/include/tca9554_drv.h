/**
*******************************************************************************
* @file           : tca9554_drv.c
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 25/02/2025
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __TCA9554_DRV_H__
#define __TCA9554_DRV_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdint.h>
/******************************************************************************
        Constants
 ******************************************************************************/
#define TCA9554_ADDRESS				(0x27)

#define TCA9554_INPUT_REG 			(0x00)		// Input status register
#define TCA9554_OUTPUT_REG			(0x01)		// Output register to change state of output BIT set to 1, output set HIGH
#define TCA9554_POLARITY_REG 		(0x02)		// Polarity inversion register. BIT '1' inverts input polarity of register 0x00
#define TCA9554_CONFIG_REG			(0x03)		// Configuration register. BIT = '1' sets port to input BIT = '0' sets port to output
/******************************************************************************
        Data types
 ******************************************************************************/
typedef enum
{
	TCA9554_OK = 0,
	TCA9554_ERROR
	
} tca9554_ret_t;

/**
 * @brief this struct represent the bits in Input Register. 
 */
struct tca9554_single_input_reg
{
	uint8_t p0:1;
	uint8_t p1:1;
	uint8_t p2:1;
	uint8_t p3:1;
	uint8_t p4:1;
	uint8_t p5:1;
	uint8_t p6:1;
	uint8_t p7:1;
};

/**
 * @brief this struct represent the all register and bits of Input Register. 
 */
union tca9554_input_reg
{
	uint8_t all;
	struct tca9554_single_input_reg bit;
};

struct tca9554_single_ouput_reg
{
	uint8_t p0:1;
	uint8_t p1:1;
	uint8_t p2:1;
	uint8_t p3:1;
	uint8_t p4:1;
	uint8_t p5:1;
	uint8_t p6:1;
	uint8_t p7:1;
};

union tca9554_output_reg
{
	uint8_t all;
	struct tca9554_single_ouput_reg bit;
};

struct tca9554_single_polarity_reg
{
	uint8_t p0:1;
	uint8_t p1:1;
	uint8_t p2:1;
	uint8_t p3:1;
	uint8_t p4:1;
	uint8_t p5:1;
	uint8_t p6:1;
	uint8_t p7:1;
};

union tca9554_polarity_reg
{
	uint8_t all;
	struct tca9554_single_polarity_reg bit;
};

struct tca9554_single_config_reg
{
	uint8_t p0:1;
	uint8_t p1:1;
	uint8_t p2:1;
	uint8_t p3:1;
	uint8_t p4:1;
	uint8_t p5:1;
	uint8_t p6:1;
	uint8_t p7:1;
};

union tca9554_config_reg
{
	uint8_t all;
	struct tca9554_single_config_reg bit;
};


/**
 * @brief struct of unions the registers. 
 */
typedef struct 
{
	union tca9554_input_reg inputs;
	union tca9554_output_reg outputs;
	union tca9554_polarity_reg polarity;
	union tca9554_config_reg config;
		
} tca9554_regs_t;

typedef struct
{
	tca9554_regs_t reg;
	int (*i2c_write_byte)(uint8_t slave_addr, uint8_t reg_addr, uint8_t reg_value);
	int (*i2c_read_byte)(uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_value);
	
} tca9554_t;
/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

tca9554_ret_t tca9554_init(tca9554_regs_t *reg);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __TCA9554_DRV_H__