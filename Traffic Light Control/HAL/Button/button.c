#include "button.h"

button_state_en BUTTON_init(u8 buttonPort, u8 buttonPin)
{
	DIO_SetPinDirection(buttonPort,buttonPin,DIO_INPUT);
	return button_ok;

}

u8 BUTTON_read(u8 buttonPort, u8 buttonPin)
{
	return DIO_GetPinValue(buttonPort,buttonPin);
}
