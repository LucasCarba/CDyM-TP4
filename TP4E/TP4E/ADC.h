/*
 * ADC.h
 *
 * Created: 27/7/2024 22:53:10
 *  Author: LENOVO
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serialPort.h"
void ADC_Init();
uint8_t ADC_LEER();




#endif /* ADC_H_ */