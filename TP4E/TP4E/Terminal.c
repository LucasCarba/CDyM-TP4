/*
 * Terminal.c
 *
 * Created: 24/7/2024 16:34:55
 *  Author: LENOVO
 */ 

#include "Terminal.h"

uint8_t color;
uint8_t comando[2];
uint8_t RX_Buffer;
extern uint8_t nuevoComando;

void Terminal_Init(){
	SerialPort_Init(0x67); // Inicializo formato 8N1 y 0X67=103 BAUDRATE=9600BPS
	SerialPort_TX_Enable();    // Activo el transmisor del puerto serie
	SerialPort_RX_Enable();    //Activo el receptor del puerto serie
	SerialPort_RX_Interrupt_Enable();//Activo interrupcion de recepcion
	sei();
}

uint8_t Terminal_LeerComando(){
	if(comando[0]=='R'){
		return 1;
	}
	else if (comando[0]=='G'){
			return 2;
	}
	else if (comando[0]=='B'){
			return 3;
	}
	else if (comando[0]=='S'){
			return 4;
	}
	else return 0;
}

ISR(USART_RX_vect){//interrupcion para recibir datos de la terminal
	SerialPort_TX_Interrupt_Disable();//Deshabilito interrupcion
	RX_Buffer=SerialPort_Recive_Data();//Recibo datos de la terminal
	uint8_t cant =0;
	if (RX_Buffer!='\r') // guardo R,G ,B o S
	{
		comando[cant]=RX_Buffer;
		cant++;
	}
	else{
		comando[cant]='\n';
	}
	color=Terminal_LeerComando();
	if(color!=0){
		nuevoComando=1;
	}
}


uint8_t Terminal_color(){
	return color;
}

void Terminal_imprimirValor(uint8_t num){ 
	static uint8_t c, aux; 
	aux=0; 
	c = num/100; 
	if(c!=0){ 
		aux=1; 
		SerialPort_Wait_For_TX_Buffer_Free(); 
		SerialPort_Send_Data('0'+c); 
		} 
	c = (num%100)/10; 
	if(c!=0){ 
		SerialPort_Wait_For_TX_Buffer_Free(); 
		SerialPort_Send_Data('0'+c); 
		}
	else if(aux==1){ 
		SerialPort_Wait_For_TX_Buffer_Free(); 
		SerialPort_Send_Data('0'+c); 
		aux=0; 
		} 
	c = num%100%10; 
	SerialPort_Wait_For_TX_Buffer_Free(); 
	SerialPort_Send_Data('0'+c); 
	SerialPort_Wait_For_TX_Buffer_Free(); 
	SerialPort_Send_String("\r\n"); 
}