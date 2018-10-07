/**
 * @file GPIO.h
 * @author Kirollos Gamal (KirollosGamal22@gmail.com)
 * @brief General Purpose I/O Driver Header File
 * @version 0.1
 * @date 2018-10-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "types.h"

#ifndef GPIO_H_
#define GPIO_H_

/**
 * @brief GPIO Configration Struct.
 * 
 * Detailed Description
 * This struct is considered a Handler for all GPIO-related Operation, 
 * it contains all Port/Pin-related properties and mirrors its state.
 * 
 */
typedef struct GPIO_config {
	u8 port ;/**< Port Selected. 
	Accepted Values: 
	'A','a' ,'B','b','C','c','D','d'*/
	u8 pin_num ; /**< Pin Seleted.
	 Accepted Values:0-7 */
	u8 direction ; /**< Direction of Port or Pin.
	On port-related operations,this variable is treated as a binary pattern.
	 e.g. 0b00010001
	While in pin-related operations, this variable is treated as a boolean variable.
	 e.g. 0(false), any other value (true).*/
	u8 val ;/**< Value of Port or Pin.
	Used as input in write operation and as output in read operations.
	On port-related operations,this variable is treated as a binary pattern.
	 e.g. 0b00010001
	While in pin-related operations, this variable is treated as a boolean variable.
	 e.g. 0(false), any other value (true).*/	
	} GPIO_config;

/**
 * @brief GPIO Error Enum
 * 
 * Detailed Description:
 * It Contains All possible Errors that the GPIO Driver Throws 
 */
typedef enum GPIO_ERR {
	SUCCESS =0 , /**< No Error,Operation Success*/
	PIN_VAL_ERR , /**< Unaccetpable Pin Number (out of range 0-7)*/
	PORT_DIR_ERR , /**< Attempt to use an Input Port as output or vice-versa*/
	PIN_DIR_ERR , /**< Attempt to use an Input pin as output or vice-versa*/
	PORT_NAME_ERR , /**< Unacceptabl Port Name */	
	} GPIO_ERR;
/*****************************************************************************/

/**
 * @brief Initiate a Digital I/O Port Direction as Input or Output.
 * 
 * Detailed:
 * 	Initiate one of the Digital I/O Ports on the ATmega32
 * 	(Port A,Port B, Port C, Port D),
 * 
 * Initialization:
 * @code
 * GPIO_Config gpio_conf;
 * gpio_conf.port = 'A';
 * gpio_conf.pin_num = 0;
 * gpio_conf.direction = 0xFF;
 * gpio_conf.value =0xFF;
 * GPIO_init(&gpio_conf);
 * @endcode
 * 
 * 
 * This code will initaite the whole Port A as output
 * 
 * @note Registers Affected:
 * DDRA,DDRB,DDRC,DDRD
 * @param GPIO_conf_ptr Pointer to A GPIO_config instance as a handle for this port
 * @return GPIO_ERR 
 */
GPIO_ERR GPIO_port_init (GPIO_config* GPIO_conf_ptr);
/**
 * @brief Initiate a Digital I/O Port Direction.
 * 
 * Detailed:
 * 	Initiate one of the Digital I/O Ports on the ATmega32
 * 	(Port A,Port B, Port C, Port D),
 * 
 * Initialization:
 * @code
 * 
 * GPIO_Config gpio_conf;
 * gpio_conf.port = 'A';
 * gpio_conf.pin_num = 1;
 * gpio_conf.direction = 1;
 * gpio_conf.value = 0;
 * GPIO_init(&gpio_conf);
 * 
 * @endcode
 * 
 * 
 * This code will initaite Pin A.1 as output
 * 
 * @note Registers Affected:
 * 	DDRA,DDRB,DDRC,DDRD 
 * @param GPIO_conf_ptr Pointer to A GPIO_config instance as a handle for this pin
 * @return GPIO_ERR 
 */
GPIO_ERR GPIO_pin_init (GPIO_config* GPIO_conf_ptr);

/**
 * @brief Write into a Digital I/O Port output pins. 
 * 
 * Detailed:
 * 	It write on one of the Digital I/O Ports on the ATmega32
 * 	(Port A,Port B, Port C, Port D),
 * 
 * @note Registers Affected:
 * PORTA,PORTB,PORTC,PORTD
 * @param GPIO_conf_ptr Pointer to A GPIO_config instance as a handle for this port
 * @return GPIO_ERR 
 */

GPIO_ERR GPIO_port_write (GPIO_config* GPIO_conf_ptr);



GPIO_ERR GPIO_port_read (GPIO_config* GPIO_conf_ptr);

/**
 * @brief Write into a Digital I/O output pin. 
 * 
 * Detailed:
 * 	It write on one of the Digital I/O pin on the ATmega32
 * 	(Port A,Port B, Port C, Port D),
 * 
 * @note Registers Affected:
 * PORTA,PORTB,PORTC,PORTD
 * @param GPIO_conf_ptr Pointer to A GPIO_config instance as a handle for this pin
 * @return GPIO_ERR 
 */

GPIO_ERR GPIO_pin_write (GPIO_config* GPIO_conf_ptr);

GPIO_ERR GPIO_pin_read (GPIO_config* GPIO_conf_ptr);



#endif /* GPIO_H_ */