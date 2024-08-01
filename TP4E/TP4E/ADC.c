/*
 * ADC.c
 *
 * Created: 27/7/2024 22:42:25
 *  Author: LENOVO
 */ 
#include "ADC.h"
void ADC_Init(void){
	DIDR0 |= (1<<ADC3D); //Se configura el pin del ADC3 como entrada analogica
	ADCSRA|=(1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;//Habilitamos adc y seleccionamos clk/128
	ADMUX |=(1<<ADLAR) | (1<<MUX1) | (1<<MUX0) | (1<<REFS0); // Vref=AVCC,justificado a izquierda
}

uint8_t ADC_LEER(){
	 cli();
	ADCSRA |=(1<<ADSC);//Empezar conversion
	while ((ADCSRA & (1<<ADIF))==0);//Espero a que termine conversion
	ADCSRA |=(1<<ADIF);//Limpiar flag
	sei();
	return ADCH;
}