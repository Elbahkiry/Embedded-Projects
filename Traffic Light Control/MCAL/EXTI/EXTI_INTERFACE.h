#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "../../LIB/STD_TYPES.h"

/****************************************************************
 name           : 	EXTI_voidInt0Init
 description    : 	intializes interrupt
 parameter      :   none
 return         : 	none
****************************************************************/
void EXTI_voidInt0Init();
/****************************************************************
 name           : 	IN0_CallBackFunction
 description    : 	gets callback function
 parameter      :   callback function PTF
 return         : 	none
****************************************************************/
void IN0_CallBackFunction(void (*PTF) (void));



#endif
