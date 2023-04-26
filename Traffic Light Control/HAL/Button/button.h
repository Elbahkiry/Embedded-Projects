#ifndef HAL_BUTTON_H_
#define HAL_BUTTON_H_

#include "../../MCAL/DIO/DIO_INTERFACE.h"
/****************************************************************
 name           : 	BUTTON_init
 description    : 	intialize button
 parameter      :   buttonPort, buttonPin
 return         : 	none
****************************************************************/
typedef enum button_state{
	button_ok,button_notok
}button_state_en;

button_state_en BUTTON_init(u8 buttonPort, u8 buttonPin);
/****************************************************************
 name           : 	BUTTON_read
 description    : 	read the button signal
 parameter      :   buttonPort, buttonPin
 return         : 	unsingned int
****************************************************************/
u8 BUTTON_read(u8 buttonPort, u8 buttonPin);


#endif /* HAL_BUTTON_H_ */
