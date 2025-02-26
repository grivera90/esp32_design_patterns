/**
*******************************************************************************
* @file           : tca9554_drv.h
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
/******************************************************************************
        Data types
 ******************************************************************************/
typedef enum
{
	TCA9554_OK = 0,
	TCA9554_ERROR
	
} tca9554_ret_t;

typedef enum
{
	GPIO0 = 0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,
	GPIO_MAX
} tca9554_gpio_t;

typedef enum
{
	TCA9554_INPUT_REG = 0,			// Input status register.
	TCA9554_OUTPUT_REG,				// Output register to change state of output BIT set to 1, output set HIGH.
	TCA9554_POLARITY_REG,			// Polarity inversion register. BIT '1' inverts input polarity of register 0x00.
	TCA9554_CONFIG_REG				// Configuration register. BIT = '1' sets port to input BIT = '0' sets port to output.
	
} register_address_t;
/**
 * @brief this typedef represent the bits in a register. 
 */
typedef struct 
{
    uint8_t b0:1;
    uint8_t b1:1;
    uint8_t b2:1;
    uint8_t b3:1;
    uint8_t b4:1;
    uint8_t b5:1;
    uint8_t b6:1;
    uint8_t b7:1;
} bits_t;

/**
 * @brief this typedef represent the register complete and the bits of a register. 
 */
typedef struct 
{
	union 
	{
	    uint8_t all;
	    bits_t bit;
	} set;
	    
} register_t;

/**
 * @brief tca9554 device.  
 */
typedef struct
{
	uint8_t slave_address;
	
	register_t input_register;
	register_t output_register;
	register_t polarity_register;
	register_t config_register;
	
	int (*i2c_write_byte)(uint8_t slave_addr, uint8_t reg_addr, uint8_t reg_value);
	int (*i2c_read_byte)(uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_value);
	
} tca9554_t;
/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

tca9554_ret_t tca9554_init(tca9554_t *tca9554, uint8_t address);
tca9554_ret_t tca9554_write_reg(tca9554_t *tca9554, register_address_t reg_address, uint8_t reg_value);
tca9554_ret_t tca9554_read_reg(tca9554_t *tca9554, register_address_t reg_address, uint8_t *reg_value);
tca9554_ret_t tca9554_write_bit(tca9554_t *tca9554, tca9554_gpio_t gpio, uint8_t gpio_value);
tca9554_ret_t tca9554_read_bit(tca9554_t *tca9554, tca9554_gpio_t gpio, uint8_t *gpio_value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __TCA9554_DRV_H__