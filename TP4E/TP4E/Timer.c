/*
 * Timer.c
 *
 * Created: 29/7/2024 20:53:12
 *  Author: LENOVO
 */ 
#include "Timer.h"
#define RED_OFF PORTB&=~(1<<PORTB5)
#define  RED_ON PORTB|=(1<<PORTB5)
#define PWM_PERIOD 255
//#define PWM_DELTA 0

volatile uint8_t PWM_value=128;

void Timer0_Init(){
	//Configuracion timer0 en modo ctc para modo pwm por software
	TCCR0A = (1<<COM0A0) | (1<<WGM01);// MODO CTC
	TCCR0B=(1<<CS02)|(1<<CS00);//preescaler 1024
	TIMSK0= (1 << OCIE0A); // Habilita la interrupcion por comparacion del temporizador 0
	sei();
}

void Timer1_Init(){
	//Configuracion del timer1 en modo pwm fast 8bits ( WGM12 y WGM10 en 1 = modo 5 de la tabla)
	//COM1AX y COM1BX en 1 para modo invertido y por ultimo CS12 y CS10 en 1 para preescaler 1024
	TCCR1A=(1<<COM1A0) | (1<<COM1A1) | (1<<COM1B0) | (1<<COM1B1) | (1<<WGM10) ;
	TCCR1B =(1<<WGM12) | (1<<CS12) | (1<<CS10);
}


void PWM_soft_Update(void) { // PWM por software
	static uint16_t PWM_position = 0;
	if (++PWM_position >= PWM_PERIOD) {
		PWM_position = 0;
	}
	if (PWM_position < PWM_value) {
		RED_ON;
		} else {
		RED_OFF;
	}
}

ISR(TIMER0_COMPA_vect) {
	PWM_soft_Update();
}


void PWM_SET_ROJO(uint8_t red_value){
	PWM_value=red_value;
}