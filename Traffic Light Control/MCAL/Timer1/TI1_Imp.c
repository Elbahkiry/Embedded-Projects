#include "../../LIB/STD_Types.h"
#include "../../LIB/Bit_Math.h"

#include "TI1_Interface.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"





static void (*GPTF_CTC) (void) = NULL;

void Timer1_CTC_CallBackFunction(void (*PTF) (void))
{
	if (PTF!=NULL){
		GPTF_CTC = PTF ;
	}
}

void __vector_7()
{

	if(GPTF_CTC != NULL){
		GPTF_CTC();
	}
}


void Timer1_CTC_init(u8 Local_Prescaler)
{

	//Select the Mode -> CTC:
	CLR_BIT(TI1_TCCR1A,TI1_WGM10);
	CLR_BIT(TI1_TCCR1A,TI1_WGM11);
	SET_BIT(TI1_TCCR1B,TI1_WGM12);
	CLR_BIT(TI1_TCCR1B,TI1_WGM13);

	TI1_OCR1A = 50000;

	//Select the Prescaler
	switch (Local_Prescaler)
	{
	case TI1_NoPrescale:
		SET_BIT(TI1_TCCR1B,TI1_CS10);
		CLR_BIT(TI1_TCCR1B,TI1_CS11);
		CLR_BIT(TI1_TCCR1B,TI1_CS12);
		break;
	default:
	case TI1_Prescaler8:
		CLR_BIT(TI1_TCCR1B,TI1_CS10);
		SET_BIT(TI1_TCCR1B,TI1_CS11);
		CLR_BIT(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler64:
		SET_BIT(TI1_TCCR1B,TI1_CS10);
		SET_BIT(TI1_TCCR1B,TI1_CS11);
		CLR_BIT(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler256:
		CLR_BIT(TI1_TCCR1B,TI1_CS10);
		CLR_BIT(TI1_TCCR1B,TI1_CS11);
		SET_BIT(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_Prescaler1024:
		SET_BIT(TI1_TCCR1B,TI1_CS10);
		CLR_BIT(TI1_TCCR1B,TI1_CS11);
		SET_BIT(TI1_TCCR1B,TI1_CS12);
		break;
	case TI1_ExternalClkFalling:
	case TI1_ExternalClkRising:
		break;

	}
	SET_BIT(TI1_TIMSK,TI1_OCIE1A); //Interrupt Enable
}

