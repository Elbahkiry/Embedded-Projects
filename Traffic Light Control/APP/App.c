#include "app.h"

u8 state_A,state_B,mode = 0,button_press = 0;

void APP_start(void)
{
	LED_on(PORTA,DIO_PIN0);

	/*Make PINS 1,2,3 in portA&D output*/
	LED_init(PORTA,DIO_PIN0);
	LED_init(PORTA,DIO_PIN1);
	LED_init(PORTA,DIO_PIN2);
	LED_init(PORTB,DIO_PIN0);
	LED_init(PORTB,DIO_PIN1);
	LED_init(PORTB,DIO_PIN2);

	EXTI_voidInt0Init();
	GIE_voidEnable();
	/*INT0 pulled up*/
	BUTTON_init(PORTD,DIO_PIN2);


	IN0_CallBackFunction(button);

	Timer1_CTC_init(TI1_NoPrescale);

	Timer1_CTC_CallBackFunction(led);
}

void led(void)
{
	static u8 counter = 1;
	static u32 counter2 = 0;
	counter2++;
	if(mode == 0)
	{
		if (counter2 == 100)
		{
			counter++;
			button_press = 0;
			if(counter > 4)
			{
				counter = 1;
			}
			LED_off(PORTA,DIO_PIN0);
			LED_off(PORTA,DIO_PIN1);
			LED_off(PORTA,DIO_PIN2);

			LED_off(PORTB,DIO_PIN0);
			LED_off(PORTB,DIO_PIN1);
			LED_off(PORTB,DIO_PIN2);
			counter2 = 0;
		}
		if(counter == 1)
		{
			LED_on(PORTA,DIO_PIN0);
			LED_on(PORTB,DIO_PIN2);
		}
		else if(counter == 2 || counter == 4)
		{
			if(counter2 % 10 == 0)
			{
				LED_toggle(PORTA,DIO_PIN1,&state_A);
				LED_toggle(PORTB,DIO_PIN1,&state_B);
			}

		}
		else if(counter == 3)
		{
			LED_on(PORTA,DIO_PIN2);
			LED_on(PORTB,DIO_PIN0);
		}
	}
	else if(mode == 1)
	{
		mode = 0;
		counter2 = 0;
		if(counter == 1 || counter == 2 || counter == 4)
		{
			counter = 2;
			LED_off(PORTA,DIO_PIN0);
			LED_off(PORTB,DIO_PIN2);
		}
	}
}

void button(void)
{
	if(button_press == 0)
	{
		mode = 1;
		button_press = 1;
	}
}

