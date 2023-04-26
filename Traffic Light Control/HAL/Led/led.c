#include "led.h"

led_state_en LED_init(u8 ledPort, u8 ledPin)
{
	DIO_SetPinDirection(ledPort,ledPin,DIO_OUTPUT);
	return ok;
}
led_state_en LED_on(u8 ledPort, u8 ledPin)
{
	DIO_SetPinValue(ledPort,ledPin,DIO_HIGH);
	return ok;
}
led_state_en LED_off(u8 ledPort, u8 ledPin)
{
	DIO_SetPinValue(ledPort,ledPin,DIO_LOW);
	return ok;
}
led_state_en LED_toggle(u8 ledPort, u8 ledPin, u8 *state)
{
	TOG_BIT(*state,0);
	DIO_SetPinValue(ledPort,ledPin,*state);
	return ok;
}
