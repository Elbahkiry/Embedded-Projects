/**********************************************************************************************************************
 *  HEADER FILES INCLUSION
 *********************************************************************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EXTI_PRIVATE.h"
#include "EXTI_CONFIG.h"
#include "../DIO/DIO_INTERFACE.h"


/**********************************************************************************************************************
 *  Functions Definitions
 *********************************************************************************************************************/
static void (*GPTF_Int0) (void) = NULL;

void EXTI_voidInt0Init(){
	/*Check sense control of Pin INT0*/
#if 	INT0_SENSE == LOW_LEVEL

	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif 	INT0_SENSE == ON_CHANGE

	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif 	INT0_SENSE == FALLING_EDGE

	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif 	INT0_SENSE == RISING_EDGE

	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "WRONG SENSE CONTROL CONFIGURATION FOR INT0"
#endif

	/*Check Peripheral Interrupt Enable for INT0*/
#if 	INT0_INITIAL_STATE == ENABLED

	SET_BIT(GICR,GICR_INT0);

#elif 	INT0_INITIAL_STATE == DISABLED

	CLR_BIT(GICR,GICR_INT0);

#else
#error "WRONG PIE CONFIGURATION FOR INT0"
#endif
	DIO_SetPinDirection(PORTD,DIO_PIN2,DIO_INPUT);
	DIO_SetPinValue(PORTD,DIO_PIN2,DIO_HIGH);
}

void __vector_1() __attribute__((signal));

void IN0_CallBackFunction(void (*PTF) (void))
{
	if (PTF!=NULL)
	{
		GPTF_Int0 = PTF ;
	}
}

void __vector_1()
{

	if(GPTF_Int0 != NULL)
	{
		GPTF_Int0();
	}
}

