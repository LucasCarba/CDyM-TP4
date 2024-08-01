/*
 * Timer.h
 *
 * Created: 29/7/2024 20:53:26
 *  Author: LENOVO
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#include <avr/io.h>

void Timer1_Init();
void Timer0_Init();
void PWM_SET_ROJO(uint8_t red_value);
void PWM_soft_Update(void);





#endif /* TIMER_H_ */