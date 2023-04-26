#ifndef HAL_LED_H_
#define HAL_LED_H_

#include "../../MCAL/DIO/DIO_INTERFACE.h"

#include "../../MCAL/EXTI/EXTI_INTERFACE.h"
#include "../../MCAL/GIE/GIE_INTERFACE.h"
#include "../../MCAL/Timer1/TI1_Interface.h"
typedef enum led_state{
	ok,notok
}led_state_en;
/****************************************************************
 name           : 	LED_init
 description    : 	intialize led
 parameter      :   ledPort, ledPin
 return         : 	led_state
****************************************************************/
led_state_en LED_init(u8 ledPort, u8 ledPin);
/****************************************************************
 name           : 	LED_on
 description    : 	intialize interrupt
 parameter      :   ledPort, ledPin
 return         : 	led_state
****************************************************************/
led_state_en LED_on(u8 ledPort, u8 ledPin);
/****************************************************************
 name           : 	LED_off
 description    : 	intialize interrupt
 parameter      :   ledPort, ledPin
 return         : 	led_state
****************************************************************/
led_state_en LED_off(u8 ledPort, u8 ledPin);
/****************************************************************
 name           : 	LED_toggle
 description    : 	intialize interrupt
 parameter      :   ledPort, ledPin, *state
 return         : 	led_state
****************************************************************/
led_state_en LED_toggle(u8 ledPort, u8 ledPin, u8 *state);



#endif /* HAL_LED_H_ */
