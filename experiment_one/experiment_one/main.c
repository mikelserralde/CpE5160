/*
 * experiment_one.c
 * Authors : Mikel Serralde & Hayden B. Long
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "board.h"
#include "UART.h"
// #include 

const int8_t test[15] PROGMEM = "This is test\n\r";

int main(void)
{
	/* From Lecture:
	int8_t *string_p;
	Output_Set(&PC , (1<<PORT_USERLED));
	Output_Init(&PC , (1<<PORT_USERLED));
	UART_Init(&UART1,9600);
	string_p=Export_print_buffer();
	Copy_String_to_Buffer(test,string_p);
	UART_Transmit_String(&UART1,0,string_p);
	*/
    while (1) 
    {
		/* From Lecture: 
		//set_bits_macro(PORTC,(1<<7);
		Output_Clear(&PC, (1<<PORT_USERLED));
		UART_Transmit(&UART1, 'U');
		_delay_ms(500);
		//clear_bits_macro(PORTC, (1<<7));
		Output_Set(&PC, (1<<PORT_USERLED));
		_delay_ms(500);
		*/
    }
}

