/*
 * main.c
 *
 *  Created on: Dec 28, 2022
 *      Author: moham
 */

#include "APP/App.h"


void Led_test(void);
void EXTI_test(void);
void Timer_test(void);
void Led_test_timer(void);
int main(void)
{
	/*To start the code*/
	APP_start();
	/******************************Test Functions******************************/
	//Led_test();
	//EXTI_test();
	//Timer_test();
	while(1)
	{

	}
	return 0;
}


void Led_test(void)
{
	static u8 state = 0;
	LED_init(PORTC,DIO_PIN2);
	LED_toggle(PORTC,DIO_PIN2,&state);
}
void EXTI_test(void)
{
	EXTI_voidInt0Init();
	GIE_voidEnable();

	BUTTON_init(PORTD,DIO_PIN2);
	IN0_CallBackFunction(Led_test);
}

void Timer_test(void)
{
	GIE_voidEnable();
	Timer1_CTC_init(TI1_NoPrescale);
	Timer1_CTC_CallBackFunction(Led_test_timer);
}
void Led_test_timer(void)
{
	static u8 counter = 0;
	counter++;
	if(counter == 20)
	{
		static u8 state = 0;
		LED_init(PORTC,DIO_PIN5);
		LED_toggle(PORTC,DIO_PIN5,&state);
		counter = 0;
	}
}
