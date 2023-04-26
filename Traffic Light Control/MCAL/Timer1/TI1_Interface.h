#ifndef MCAL_TIMER1_HEADER_TI1_INTERFACE_H_
#define MCAL_TIMER1_HEADER_TI1_INTERFACE_H_

#include "../../LIB/STD_Types.h"
#include "TI1_Config.h"

#include "TI1_Register.h"
#include "TI1_Private.h"

/****************************************************************
 name           : 	Timer1_CTC_CallBackFunction
 description    : 	Sets ISR function for on compare match mode
 parameter      :   PTF
 return         : 	none
****************************************************************/
void Timer1_CTC_CallBackFunction(void (*PTF) (void));
/****************************************************************
 name           : 	Timer1_CTC_init
 description    : 	Sets Timer 1 mode
 parameter      :   None
 options        :   Set from config file
 return         : 	none
****************************************************************/
void Timer1_CTC_init(u8 Local_Prescaler);

void __vector_7() __attribute__((signal));

#endif /* MCAL_TIMER1_HEADER_TI1_INTERFACE_H_ */
