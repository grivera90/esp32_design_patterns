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
#include <stdbool.h>
/******************************************************************************
        Constants
 ******************************************************************************/
#define TCA9554_SLAVE_ADDRESS_FIXED			(0x40)
#define TCA9554_WRITE_OPERATION				(0x00)
#define TCA9554_READ_OPERATION				(0x01)
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
	ADDRESS_20H = 0X20,
	ADDRESS_21H,
	ADDRESS_22H,
	ADDRESS_23H,
	ADDRESS_24H,
	ADDRESS_25H,
	ADDRESS_26H,
	ADDRESS_27H
	
} tca9554_address_t;

typedef enum
{
	PORT0 = 0,
	PORT_MAX
	
} tca9554_ports_t;

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
	
} tca9554_reg_address_t;

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
	    
} tca9554_register_t;

/**
 * @brief tca9554 device.  
 */
typedef struct
{
	tca9554_address_t slave_address;
	
	tca9554_register_t input_register;
	tca9554_register_t output_register;
	tca9554_register_t polarity_register;
	tca9554_register_t config_register;
	
	int (*i2c_master_xmit)(uint8_t slave_addr, uint8_t reg_addr, uint8_t reg_value);
	int (*i2c_master_recv)(uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_value);
	
} tca9554_t;
/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function to initializate and configurate tca9554 chip.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param tca9554_address_t chip_address: address slave. 
 * @param bool default_conf: indicate if a default config is set or a particular config. Default = true, Particular = false.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_init(tca9554_t *tca9554, tca9554_address_t chip_address, bool default_conf);

/**
 * @brief Function to write in a register of tca9554.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param tca9554_reg_address_t tca9554_reg_address: register address. 
 * @param uint8_t reg_value: value to will be write in the register.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_write_reg(tca9554_t *tca9554, tca9554_reg_address_t reg_address, uint8_t reg_value);

/**
 * @brief Function to read a register of tca9554.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param tca9554_reg_address_t tca9554_reg_address: register address. 
 * @param uint8_t *reg_value: pointer to storage the value of the register.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_read_reg(tca9554_t *tca9554, tca9554_reg_address_t reg_address, uint8_t *reg_value);

/**
 * @brief Function to write a value in the port of tca9554.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param uint8_t port_value: value to will be write in the port.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_port_write(tca9554_t *tca9554, uint8_t port_value);

/**
 * @brief Function to read the value of tca9554 port.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param uint8_t *port_value: pointer to storage the value of the port.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_port_read(tca9554_t *tca9554, uint8_t *port_value);

/**
 * @brief Function to write a value in the polarity register of tca9554.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param uint8_t pol_value: value to will be write in the polarity register.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_port_write_polarity(tca9554_t *tca9554, uint8_t pol_value);

/**
 * @brief Function to read the value of tca9554 polarity register.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param uint8_t *pol_value: pointer to storage the value of the polarity register.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_port_read_polarity(tca9554_t *tca9554, uint8_t *pol_value);

/**
 * @brief Function to write a pin state of tca9554 output port.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param tca9554_gpio_t gpio: gpio number. 
 * @param bool gpio_value: gpio value.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_pin_write(tca9554_t *tca9554, tca9554_gpio_t gpio, bool gpio_value);

/**
 * @brief Function to read the pin state of tca9554 input port.
 *
 * @param tca9554_t *tca9554: pointer to device struct.
 * @param tca9554_gpio_t gpio: gpio number. 
 * @param bool *gpio_value: pointer to storage the value of the pin.
 * 
 * @return tca9554_ret_t. See \p tca9554_ret_t in Data types section.
 */
tca9554_ret_t tca9554_pin_read(tca9554_t *tca9554, tca9554_gpio_t gpio, bool *gpio_value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __TCA9554_DRV_H__