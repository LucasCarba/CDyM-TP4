/*
 * Terminal.h
 *
 * Created: 24/7/2024 16:35:13
 *  Author: LENOVO
 */ 


#ifndef TERMINAL_H_
#define TERMINAL_H_
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "serialPort.h"

void Terminal_Init();
uint8_t Terminal_LeerComando();
uint8_t Terminal_color();
void Terminal_imprimirValor(uint8_t num);


#endif /* TERMINAL_H_ */