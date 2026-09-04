#ifndef __LOW_POWER_H
#define	__LOW_POWER_H


#include "bsp_mylib.h"

#define MY_FEEL_DOG             TaskTick_Ms[2]
#define MY_LCD_SHOW             TaskTick_Ms[4] 
#define POWER_DELAY_OFF_DELAY         (10*1000UL)
#define WAKE_UP_DELAY           (POWER_DELAY_OFF_DELAY-100)
#define POWER_DELAY_NULL       (POWER_DELAY_OFF_DELAY-1*20*1000)
#define POWER_DELAY_SHUTDOWN    (POWER_DELAY_OFF_DELAY-4000)

void Sleep_Mode_Fun(void);
void Standby_Mode_Fun(void);
void Stop_Mode_Fun(void);
#endif /* __LOW_POWER_H */

