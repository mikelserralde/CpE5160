/*
 * Timer_Interrupt_Init.c
 *
 * Created: 11/16/2020 8:51:10 AM
 *  Author: youngerr
 */ 

#include <avr/io.h>
#include "board.h"

uint8_t Timer2_Interrupt_Init(uint8_t interval_ms)
{
	uint8_t OCR_value,error_flag;
	
	OCR_value = (uint8_t)((((interval_ms*F_CPU)+(F_DIV*512000UL))/(F_DIV*1024000UL))-1);
	
	if(OCR_value<=255)
	{
		error_flag=0;    // no errors;
		OCR2A=OCR_value;
		TIMSK2=0x02;      // Enables OCRA match interrupt
		TCCR2A=0x02;      // Auto-Reload counter on match with OCRA
		TCCR2B=0x07;      // Starts the counter with a prescale of 1024
	}
	else
	{
		error_flag=0x80;  // interval too big
	}
	
	return error_flag;	
}
