#ifndef APP_APP_H_
#define APP_APP_H_

#include "../HAL/Led/led.h"
#include "../HAL/Button/button.h"

/****************************************************************
 name           : 	APP_start
 description    : 	Start the application
 parameter      :   None
 return         : 	none
****************************************************************/
void APP_start(void);
/****************************************************************
 name           : 	led
 description    : 	callback function to the change the led lights
 parameter      :   None
 return         : 	none
****************************************************************/
void led(void);
/****************************************************************
 name           : 	button
 description    : 	callback function to change the mode to pedestrian mode
 parameter      :   None
 return         : 	none
****************************************************************/
void button(void);

#endif /* APP_APP_H_ */
